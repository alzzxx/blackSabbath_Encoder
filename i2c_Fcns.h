
/*
Functions used to speak with I2C devices other than oled Screen, e.g. extEEPROM
*/

bool BestEncoder::writeReadBI2C(uint32_t addr, uint8_t body)
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
        delayMicroseconds(SHORTDELAY_I2C);
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
            delayMicroseconds(SHORTDELAY_I2C);
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
    } while (i < ERROR_I2C_LIMIT);
    return isByteOK; // return true if process was successful, otherwise false
}

bool BestEncoder::writeReadWI2C(uint32_t addr, uint16_t body)
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
        myEEPROM.put(addr, body);
        delayMicroseconds(SHORTDELAY_I2C);
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
            delayMicroseconds(SHORTDELAY_I2C);
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
    } while (i < ERROR_I2C_LIMIT);
    return isWordOK; // return true if process was successful, otherwise false
}

void BestEncoder::putEncParameters(uint32_t addr)
{
    /*
    Save the entire encSettings structure on the EEPROM
    */
    myEEPROM.put(addr, encSettings);
    delayMicroseconds(SHORTDELAY_I2C);
    DEBUG_I2CLN(F("New parameters saved"));
}

void BestEncoder::writeEncParameter(uint32_t addr, uint8_t byteToSave)
{
    /*
    Save a single byte on the EEPROm
    */
    myEEPROM.write(addr, byteToSave);
    delayMicroseconds(SHORTDELAY_I2C);
    DEBUG_I2CLN(F("New parameter saved"));
}
