
uint16_t BestEncoder::listenUDP(byte *buffer, uint8_t size)
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
        DEBUG_PRINT(F("Received packet of size: "));
        DEBUG_PRINTLN(packetSize);
        DEBUG_PRINT(F("From "));
        for (i = 0; i < 4; i++)
        {
            DEBUG_PRINTFLO(remote[i], DEC);
            if (i < 3)
            {
                DEBUG_PRINT(F("."));
            }
        }
        DEBUG_PRINT(F(", port "));
        DEBUG_PRINTLN(Udp.remotePort());
        if (packetSize > size)
        {
            DEBUG_PRINT(F("Incoming packet exceeds the number of parameters accepted. Ignoring last "));
            DEBUG_PRINT(packetSize - size);
            DEBUG_PRINTLN(F(" byte(s)."));
        }
        DEBUG_PRINTLN(F("Contents:"));
        for (i = 0; i < size; i++)
        {
            DEBUG_PRINTLNFLO(buffer[i], HEX);
        }
#endif
    }
    return packetSize;
}
void BestEncoder::writeUDP(uint8_t *buffer, uint16_t size, IPAddress targetIP, uint16_t targetPort)
{
    /*
    Builds a UDP packet containing the elements of the byte array Buffer and sends it to 
    the device identified by targetIP and targetPort input parameters
    */

    Udp.beginPacket(targetIP, targetPort);
    Udp.write(buffer, size); // Packet must be defined between "Udp.beginPacket()" and "Udp.endPacket()"
    Udp.endPacket();

#ifdef DEBUG // Print some info on the monitor
    DEBUG_PRINT(F("Sent packet of size "));
    DEBUG_PRINTLN(size);
    DEBUG_PRINT(F("To "));
    for (uint8_t i = 0; i < 4; i++)
    {
        DEBUG_PRINTFLO(targetIP[i], DEC);
        if (i < 3)
        {
            DEBUG_PRINT(F("."));
        }
    }
    DEBUG_PRINT(F(", port "));
    DEBUG_PRINTLN(targetPort);
#endif
}

int16_t BestEncoder::bytesToInt(byte byte1, byte byte2)
{
    /*
    Accepts as input 2 bytes and returns a signed integer (16bit)
    The first element of the input array is treated as the MSB
    */

    int16_t result;

    result = int((byte1 << 8) + byte2);
    return result;
}
