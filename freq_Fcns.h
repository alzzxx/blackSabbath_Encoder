
void BestEncoder::readEncoder(void)
{
    const uint8_t readInterval = 20;
    uint8_t i = 0;
    static uint32_t lastPulses, justBefore, rightNow, actualPulses;
    static uint32_t deltaPulses[MEAN_PUL_SAMPLES];

    do
    {
        rightNow = millis();
        if (rightNow - justBefore >= readInterval)
        {
            justBefore = millis();
            actualPulses = myPulse.getPulses();
            deltaPulses[i] = actualPulses - lastPulses;
            mediaPuls.push(deltaPulses[i]);
            lastPulses = actualPulses;
            DEBUG_FREQ(F("deltaPuls["));
            DEBUG_FREQ(i);
            DEBUG_FREQ(F("] are: "));
            DEBUG_FREQLN(deltaPulses[i]);
            i++;
        }
    } while (i < MEAN_PUL_SAMPLES);
    DEBUG_FREQ(F("Exit the loop, now mean calculation"));
    secPoint->mPul = mediaPuls.mean();
    DEBUG_FREQ(F("Mean pulse is: "));
    DEBUG_FREQLN(secPoint->mPul);
    secPoint->encFreq = secPoint->mPul / readInterval / ENCODING_TYPE;
    DEBUG_FREQ(F("Frequency is: "));
    DEBUG_FREQLN(secPoint->encFreq);
}