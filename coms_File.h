// * SPI COMMUNICATION

bool ServerEncoder::checkIflistened(uint8_t *p_rx0, int BUFFERSIZE)
{
    bool flag = 1;

    if (*p_rx0 != 24)
        flag = 0; // check if the other devide was listening. The listening frame is 00011000 (see protocol excel)
    p_rx0++;
    if (*p_rx0 != 25)
        flag = 0; // check if the other devide was listening. The listening frame is  (see protocol excel)
    p_rx0++;
    if (*p_rx0 != 26)
        flag = 0; // check if the other devide was listening. The listening frame is  (see protocol excel)
    p_rx0++;
    if (*p_rx0 != 27)
        flag = 0; // check if the other devide was listening. The listening frame is  (see protocol excel)

    return flag;
}

bool ServerEncoder::spiWriteArd2STM(uint8_t address, uint16_t body, int slaveSelect)
{
    /* 
    - this fcn send to address the body. 
    */

    sP->debug1++;
    uint8_t rx[4] = {0, 0, 0, 0};
    delayMicroseconds(4 * shortDelay);
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(slaveSelect, LOW); // Starts communication with Slave connected to master. SS lowered
    delayMicroseconds(shortDelay);

    rx[0] = SPI.transfer(0xAA);           //Send 0xAA aka "write"
    delayMicroseconds(shortDelay);        // delay very important: let STM to manage the FIFO hardware stack
    rx[1] = SPI.transfer(address);        //Send address of the target variable
    delayMicroseconds(shortDelay);        // delay very important: let STM to manage the FIFO hardware stack
    rx[2] = SPI.transfer(highByte(body)); //Send first 8 bits of body
    delayMicroseconds(shortDelay);
    rx[3] = SPI.transfer(lowByte(body));
    delayMicroseconds(shortDelay);

    digitalWrite(slaveSelect, HIGH); //  restore SS as "slave not communicating"
    SPI.endTransaction();
    delayMicroseconds(4 * shortDelay);
    if (ServerEncoder::checkIflistened(&rx[0], 4) == 0)
        return 0; // first check: if STM sent [24, 24, 24, 24] every frame was received correctly.

    // for debug
    DEBUG_SPIONE(F("Write : Sent: 0xAA, "));
    DEBUG_SPIONE(address);
    DEBUG_SPIONE(F(" , "));
    DEBUG_SPIONE(highByte(body));
    DEBUG_SPIONE(F(" , "));
    DEBUG_SPIONELN(lowByte(body));
    DEBUG_SPIONE(F("      : rec : "));
    DEBUG_SPIONE(rx[0]);
    DEBUG_SPIONE(F(" , "));
    DEBUG_SPIONE(rx[1]);
    DEBUG_SPIONE(F(" , "));
    DEBUG_SPIONE(rx[2]);
    DEBUG_SPIONE(F(" , "));
    DEBUG_SPIONELN(rx[3]);

    return 1;
}

bool ServerEncoder::spiReadArd2STM(uint8_t address, uint16_t *body, int slaveSelect)
{
    /*  this fcn read in address.
     1. Write "hey I want to read this variable
     2. Then immediately redo another communication, and read back the values.
    */
    int flag = 0;
    uint8_t rx[4] = {0, 0, 0, 0};
    delayMicroseconds(4 * shortDelay);
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    digitalWrite(slaveSelect, LOW); // Starts communication with Slave connected to master. SS, or NCSS lowered
    delayMicroseconds(shortDelay);

    rx[0] = SPI.transfer(0x0F); //Send 0x0F aka "read"
    delayMicroseconds(shortDelay);
    rx[1] = SPI.transfer(address); //Send address of the target variable
    delayMicroseconds(shortDelay);
    rx[2] = SPI.transfer(0); // send  dummy
    delayMicroseconds(shortDelay);
    rx[3] = SPI.transfer(0); // send  dummy
    delayMicroseconds(shortDelay);
    // delayMicroseconds(100);    // this is because of the loop in the STM takes time
    if (ServerEncoder::checkIflistened(&rx[0], 4) == 0)
        flag = 1;

    DEBUG_SPIONE("Read1 : Sent: 0x0F, ");
    DEBUG_SPIONE(address);
    DEBUG_SPIONELN(", 0, 0");
    DEBUG_SPIONE("      : rec :  ");
    DEBUG_SPIONE(rx[0]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONE(rx[1]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONE(rx[2]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONELN(rx[3]);

    delayMicroseconds(4 * shortDelay);
    rx[0] = SPI.transfer(24); //Send 0x18 aka "I'm listening"
    delayMicroseconds(shortDelay);
    rx[1] = SPI.transfer(25); //Send 0x18 aka "I'm listening"
    delayMicroseconds(shortDelay);
    rx[2] = SPI.transfer(26); //Send 0x18 aka "I'm listening"
    delayMicroseconds(shortDelay);
    rx[3] = SPI.transfer(27); //Send 0x18 aka "I'm listening"
    delayMicroseconds(shortDelay);

    digitalWrite(slaveSelect, HIGH); // Starts communication with Slave connected to master. SS, or NCSS lowered
    SPI.endTransaction();
    delayMicroseconds(4 * shortDelay);

    DEBUG_SPIONELN("Read2 : Sent: 24, 25, 26, 27");
    DEBUG_SPIONE("        rec :  ");
    DEBUG_SPIONE(rx[0]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONE(rx[1]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONE(rx[2]);
    DEBUG_SPIONE(" , ");
    DEBUG_SPIONELN(rx[3]);

    if (rx[0] != 0xf0 || rx[1] != address || flag == 1)
    { // check if everything was ok
        *body = 0;
        return 0;
    }

    *body = (rx[2] << 8 | rx[3]); // store received value in buffer

    return 1;
}

int ServerEncoder::sendParameters(void)
{
    /*
    - 100+i : write; 200+i : read; 300+i comparison
    */

    int errorCnt = 0;
    uint16_t readTemp = 0;
    uint8_t i = 0;

    for (int i = 0; i < numberParameters; i++)
    {
        /* for every parameter do the following:
        1. write until success
        2. read back until success
        3. compare: if read == write then :) otherwise  start again from 1. But restart from 1 only a limited amount of times
        */
        do
        {
            if (!ServerEncoder::writeReg(i, eP->deviceParameters[i], ST_PIN_NSS))
                break;

            DEBUG_SPITWO(" written parameter i = ");
            DEBUG_SPITWO(i);
            DEBUG_SPITWO(" value: ");
            DEBUG_SPITWOLN(eP->deviceParameters[i]);

            if (!ServerEncoder::readReg(i, &readTemp, ST_PIN_NSS))
            {
                break;
            }

            DEBUG_SPITWO("read  param i = ");
            DEBUG_SPITWO(i);
            DEBUG_SPITWO(" value: ");
            DEBUG_SPITWO(readTemp);

            if (readTemp != eP->deviceParameters[i])
            {
                errorCnt++;
            }
            else
            {
                errorCnt = 0;

                DEBUG_SPITWO(" compared  param i = ");
                DEBUG_SPITWO(i);
                DEBUG_SPITWOLN(" ___________OK");
                break;
            }
        } while (errorCnt < spiErrorLimit); // repeat the write-Read-compare operation for a limited amount of times
    }
    return errorCnt; // 0 if everything was OK
}

void ServerEncoder::updateDeviceStatus(uint16_t code16)
{
    deviceStatus = (code16 & 0xFF00) >> 8;
    DEBUG_SERVERLN(deviceStatus);
}

int ServerEncoder::writeReg(uint8_t address, uint16_t body, int slaveSelect)
{
    /* 
     - Write in register until the writing operation is successful.
     - but retry the action only for a limited amount of errors.
   */
    int errorCnt = 0;

    while (!ServerEncoder::spiWriteArd2STM(address, body, slaveSelect))
    {
        errorCnt++;
        if (errorCnt > spiErrorLimit)
        {
            return (spiErrorLimit + 100 + address);
        }
    }
}

int ServerEncoder::readReg(uint8_t address, uint16_t *body, int slaveSelect)
{
    /* 
     - Read in register until the reading operation is successful.
     - but retry the action only for a limited amount of errors.
   */
    int errorCnt = 0;

    while (!ServerEncoder::spiReadArd2STM(address, body, slaveSelect))
    {
        errorCnt++;
        if (errorCnt > spiErrorLimit)
        {

            return (spiErrorLimit + 200 + address);
        }
    }
}

// * I2C COMMUNICATION

bool SystemEncoder::writeReadBI2C(uint32_t addr, uint8_t body)
{
    /* 
    Write a byte on EEPROM and the read it back to see if write was correct
    tries a number of times, if suceed returns true, otherwise false
    */

    bool isByteOK = false;
    uint8_t i = 0;
    uint8_t buffer = 0; // buffer to compare the data written
    do
    {
        myEEPROM.put(addr, body);
        delayMicroseconds(delayI2C);
        myEEPROM.get(addr, buffer);
        if (buffer != body)
        {
            // if the data read is different from the parameter try to write again
            // for a fixed number of times
            i++;
            DEBUG_I2CLN(F("Failed to Write"));
            DEBUG_I2C(body);
            DEBUG_I2C(F(" != "));
            DEBUG_I2CLN(buffer);
            delayMicroseconds(delayI2C);
            isByteOK = false;
        }
        else
        {
            // if values are the same exit  the loop
            DEBUG_I2CLN(F("Write/Read OK"));
            DEBUG_I2C(body);
            DEBUG_I2C(" = ");
            DEBUG_I2CLN(buffer);
            isByteOK = true;
            break;
        }
    } while (i < i2cErrorLimit);
    return isByteOK; // return true if process was successful, otherwise false
}

bool SystemEncoder::writeReadWI2C(uint32_t addr, uint16_t body)
{
    /* 
    Write a uint16_t on EEPROM and the read it back to see if write was correct
    tries a number of times, if suceed returns true, otherwise false
    */

    bool isWordOK = false;
    uint8_t i = 0;
    uint16_t buffer = 0;
    do
    {
        DEBUG_I2C(F("Writing address: "));
        DEBUG_I2CLN(addr);
        myEEPROM.put(addr, body);
        delayMicroseconds(delayI2C);
        myEEPROM.get(addr, buffer);
        if (buffer != body)
        {
            // if the data read is different from the parameter try to write again
            // for a fixed number of times
            i++;
            DEBUG_I2CLN(F("Failed to write"));
            DEBUG_I2C(body);
            DEBUG_I2C(F(" != "));
            DEBUG_I2CLN(buffer);
            isWordOK = false;
            delayMicroseconds(delayI2C);
        }
        else
        {
            // if values are the same exit  the loop
            DEBUG_I2CLN(F("Write/Read OK"));
            DEBUG_I2C(body);
            DEBUG_I2C(F(" = "));
            DEBUG_I2CLN(buffer);
            isWordOK = true;
            break;
        }
    } while (i < i2cErrorLimit);
    DEBUG_I2CLN(F("Writing to EEPROM finished"));
    return isWordOK; // return true if process was successful, otherwise false
}

void SystemEncoder::putEncParameters(uint32_t addr)
{
    /*
    Save the entire encSettings structure on the EEPROM
    */

    myEEPROM.put(addr, encSettings);
    delayMicroseconds(delayI2C);
    DEBUG_I2CLN(F("New parameters saved"));
}

void SystemEncoder::writeEncParameter(uint32_t addr, uint8_t byteToSave)
{
    /*
    Save a single byte on the EEPROm
    */

    myEEPROM.write(addr, byteToSave);
    delayMicroseconds(delayI2C);
    DEBUG_I2CLN(F("New parameter saved"));
}

// * UDP COMMUNICATION

uint16_t SystemEncoder::listenUDP(byte *buffer, uint8_t size)
{
    /*
    Polls for incoming UDP packets. If one is available, the function saves it in the array 
    of bytes of length "Size", named "Buffer". The function then returns the size in bytes of 
    the incoming packet (0 if none is available)
    */

    uint8_t i;

    for (i = 0; i < size; i++)
    {
        // Clear the buffer before reading data
        buffer[i] = 0;
    }

    uint16_t packetSize = Udp.parsePacket();

    if (packetSize)
    {
        IPAddress remote = Udp.remoteIP();
        Udp.read(buffer, size); // read the packet into packetBufffer
#ifdef DEBUG
        DEBUG_UDP(F("Received packet of size: "));
        DEBUG_UDPLN(packetSize);
        DEBUG_UDP(F("From "));
        for (i = 0; i < 4; i++)
        {
            DEBUG_UDPFLO(remote[i], DEC);
            if (i < 3)
            {
                DEBUG_UDP(F("."));
            }
        }
        DEBUG_UDP(F(", port "));
        DEBUG_UDPLN(Udp.remotePort());
        if (packetSize > size)
        {
            DEBUG_UDP(F("Incoming packet exceeds the number of parameters accepted. Ignoring last "));
            DEBUG_UDP(packetSize - size);
            DEBUG_UDPLN(F(" byte(s)."));
        }
        DEBUG_UDPLN(F("Contents:"));
        for (i = 0; i < size; i++)
        {
            DEBUG_UDPLNFLO(buffer[i], HEX);
        }
#endif
    }
    return packetSize;
}

void SystemEncoder::writeUDP(uint8_t *buffer, uint16_t size, IPAddress targetIP, uint16_t targetPort)
{
    /*
    Builds a UDP packet containing the elements of the byte array Buffer and sends it to 
    the device identified by targetIP and targetPort input parameters
    */
    DEBUG_UDPLN(F("Preparing UDP packet"));
    Udp.beginPacket(targetIP, targetPort);
    DEBUG_UDPLN(F("Sending packet"));
    Udp.write(buffer, size);
    DEBUG_UDPLN(F("Closing packet"));
    Udp.endPacket();
    DEBUG_UDPLN(F("DONE udp"));

#ifdef DEBUG // Print some info on the monitor
    DEBUG_UDP(F("Sent packet of size: "));
    DEBUG_UDPLN(size);
    DEBUG_UDP(F("To "));
    for (uint8_t i = 0; i < 4; i++)
    {
        DEBUG_UDPFLO(targetIP[i], DEC);
        if (i < 3)
        {
            DEBUG_UDP(F("."));
        }
    }
    DEBUG_UDP(F(", port "));
    DEBUG_UDPLN(targetPort);
#endif
}

int16_t SystemEncoder::bytesToInt(byte byte1, byte byte2)
{
    /*
    Accepts as input 2 bytes and returns a signed integer (16bit)
    The first element of the input array is treated as the MSB
    */

    int16_t result;

    result = int((byte1 << 8) + byte2);
    return result;
}
