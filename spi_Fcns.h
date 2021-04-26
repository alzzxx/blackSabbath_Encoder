
static bool checkIflistened(uint8_t *p_rx0, int BUFFERSIZE)
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

bool SpiWriteArd2STM(uint8_t address, uint16_t body, int slaveSelect)
{
  /* this fcn send to address the body. */
  debug1++;
  uint8_t rx[4] = {0, 0, 0, 0};
  delayMicroseconds(4 * SHORTDELAY);
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelect, LOW); // Starts communication with Slave connected to master. SS lowered
  delayMicroseconds(SHORTDELAY);

  rx[0] = SPI.transfer(0xAA);           //Send 0xAA aka "write"
  delayMicroseconds(SHORTDELAY);        // delay very important: let STM to manage the FIFO hardware stack
  rx[1] = SPI.transfer(address);        //Send address of the target variable
  delayMicroseconds(SHORTDELAY);        // delay very important: let STM to manage the FIFO hardware stack
  rx[2] = SPI.transfer(highByte(body)); //Send first 8 bits of body
  delayMicroseconds(SHORTDELAY);
  rx[3] = SPI.transfer(lowByte(body));
  delayMicroseconds(SHORTDELAY);

  digitalWrite(slaveSelect, HIGH); //  restore SS as "slave not communicating"
  SPI.endTransaction();
  delayMicroseconds(4 * SHORTDELAY);
  if (checkIflistened(&rx[0], 4) == 0)
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

bool SpiReadArd2STM(uint8_t address, uint16_t *body, int slaveSelect)
{
  /*  this fcn read in address.
    1. Write "hey I want to read this variable
    2. Then immediately redo another communication, and read back the values.
  */
  int flag = 0;
  uint8_t rx[4] = {0, 0, 0, 0};
  delayMicroseconds(4 * SHORTDELAY);
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelect, LOW); // Starts communication with Slave connected to master. SS, or NCSS lowered
  delayMicroseconds(SHORTDELAY);

  rx[0] = SPI.transfer(0x0F); //Send 0x0F aka "read"
  delayMicroseconds(SHORTDELAY);
  rx[1] = SPI.transfer(address); //Send address of the target variable
  delayMicroseconds(SHORTDELAY);
  rx[2] = SPI.transfer(0); // send  dummy
  delayMicroseconds(SHORTDELAY);
  rx[3] = SPI.transfer(0); // send  dummy
  delayMicroseconds(SHORTDELAY);
  // delayMicroseconds(100);    // this is because of the loop in the STM takes time
  if (checkIflistened(&rx[0], 4) == 0)
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

  delayMicroseconds(4 * SHORTDELAY);
  rx[0] = SPI.transfer(24); //Send 0x18 aka "I'm listening"
  delayMicroseconds(SHORTDELAY);
  rx[1] = SPI.transfer(25); //Send 0x18 aka "I'm listening"
  delayMicroseconds(SHORTDELAY);
  rx[2] = SPI.transfer(26); //Send 0x18 aka "I'm listening"
  delayMicroseconds(SHORTDELAY);
  rx[3] = SPI.transfer(27); //Send 0x18 aka "I'm listening"
  delayMicroseconds(SHORTDELAY);

  digitalWrite(slaveSelect, HIGH); // Starts communication with Slave connected to master. SS, or NCSS lowered
  SPI.endTransaction();
  delayMicroseconds(4 * SHORTDELAY);

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

int SendParameters()
{ // 100+i : write; 200+i : read; 300+i comparison

  int errorCnt = 0;
  uint16_t readTemp = 0;
  uint8_t i = 0;

  for (int i = 0; i < NUMBER_OF_PARAMETERS; i++)
  {
    /* for every parameter do the following:
        1. write until success
        2. read back until success
        3. compare: if read == write then :) otherwise  start again from 1. But restart from 1 only a limited amount of times
    */

    do
    {

      if (!writeReg(i, encPoint->deviceParameters[i], ST_PIN_NSS))
        break;

      DEBUG_SPITWO(" written parameter i = ");
      DEBUG_SPITWO(i);
      DEBUG_SPITWO(" value: ");
      DEBUG_SPITWOLN(encPoint->deviceParameters[i]);

      if (!readReg(i, &readTemp, ST_PIN_NSS))
      {
        break;
      }

      DEBUG_SPITWO("read  param i = ");
      DEBUG_SPITWO(i);
      DEBUG_SPITWO(" value: ");
      DEBUG_SPITWO(readTemp);

      if (readTemp != encPoint->deviceParameters[i])
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
    } while (errorCnt < ERROR_SPI_LIMIT); // repeat the write-Read-compare operation for a limited amount of times
  }

  return errorCnt; // 0 if everything was OK
}

static void updateDeviceStatus(uint16_t code16)
{
  deviceStatus = (code16 & 0xFF00) >> 8;
  DEBUG_SERVERLN(deviceStatus);
}

int writeReg(uint8_t address, uint16_t body, int slaveSelect)
{
  /* write in register until the writing operation is successful.
   *  but retry the action only for a limited amount of errors.
   */
  int errorCnt = 0;

  while (!SpiWriteArd2STM(address, body, slaveSelect))
  {
    errorCnt++;
    if (errorCnt > ERROR_SPI_LIMIT)
    {
      return (ERROR_SPI_LIMIT + 100 + address);
    }
  }
}

int readReg(uint8_t address, uint16_t *body, int slaveSelect)
{
  /* read in register until the reading operation is successful.
   *  but retry the action only for a limited amount of errors.
   */
  int errorCnt = 0;

  while (!SpiReadArd2STM(address, body, slaveSelect))
  {
    errorCnt++;
    if (errorCnt > ERROR_SPI_LIMIT)
    {

      return (ERROR_SPI_LIMIT + 200 + address);
    }
  }
}
