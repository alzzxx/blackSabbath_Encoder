
int listenUDP(void *Buffer, int Size)
{
    /*
    Polls for incoming UDP packets. If one is available, the function saves it in the array 
    of bytes of length "Size", named "Buffer". The function then returns the size in bytes of 
    the incoming packet (0 if none is available)
    */

    int i;
    byte *buf = Buffer;

    for (i = 0; i < Size; i++)
    {
        // Clear the buffer before reading data
        buf[i] = 0;
    }

    int packetSize = Udp.parsePacket();

    if (packetSize)
    {
        IPAddress remote = Udp.remoteIP();
        Udp.read(buf, Size); // read the packet into packetBufffer
#ifdef DEBUG_UDP
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
        if (packetSize > Size)
        {
            DEBUG_UDP(F("Incoming packet exceeds the number of parameters accepted. Ignoring last "));
            DEBUG_UDP(packetSize - bufferSize);
            DEBUG_UDPLN(F(" byte(s)."));
        }
        DEBUG_UDPLN(F("Contents:"));
        for (i = 0; i < Size; i++)
        {
            DEBUG_UDPLNFLO(buf[i], HEX);
        }
#endif
    }
    return packetSize;
}

void writeUDP(void *Buffer, int Size, IPAddress targetIP, unsigned int targetPort)
{
    /*
    Builds a UDP packet containing the elements of the byte array Buffer and sends it to 
    the device identified by targetIP and targetPort input parameters
    */

    byte *buf = Buffer;

    Udp.beginPacket(targetIP, targetPort);
    Udp.write(buf, Size); // Packet must be defined between "Udp.beginPacket()" and "Udp.endPacket()"
    Udp.endPacket();

#ifdef DEBUG_UDP // Print some info on the monitor
    DEBUG_UDP(F("Sent packet of size "));
    DEBUG_UDPLN(Size);
    DEBUG_UDP(F("To "));
    for (int i = 0; i < 4; i++)
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

int bytesToInt(byte byte1, byte byte2)
{
    /*
    Accepts as input 2 bytes and returns a signed integer (16bit)
    The first element of the input array is treated as the MSB
    */

    int result;

    result = int((byte1 << 8) + byte2);
    return result;
}