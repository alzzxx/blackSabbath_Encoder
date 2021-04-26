
void BestEncoder::readEncoder(void)
{
    const uint8_t readInterval = 20;
    uint8_t j = 0;
    static uint32_t lastPulses, justBefore, rightNow, actualPulses;
    static uint32_t deltaPulses[MEAN_PUL_SAMPLES];

    do
    {
        rightNow = millis();
        if (rightNow - justBefore >= readInterval)
        {
            justBefore = millis();
            actualPulses = myPulse.getPulses();
            deltaPulses[j] = actualPulses - lastPulses;
            mediaPuls.push(deltaPulses[j]);
            lastPulses = actualPulses;
            DEBUG_FREQ(F("deltaPuls["));
            DEBUG_FREQ(j);
            DEBUG_FREQ(F("] are: "));
            DEBUG_FREQLN(deltaPulses[j]);
            j++;
        }
    } while (j < MEAN_PUL_SAMPLES);
    DEBUG_FREQ(F("Exit the loop, now mean calculation"));
    secPoint->mPul = mediaPuls.mean();
    DEBUG_FREQ(F("Mean pulse is: "));
    DEBUG_FREQLN(secPoint->mPul);
    secPoint->encFreq = secPoint->mPul / readInterval / ENCODING_TYPE;
    DEBUG_FREQ(F("Frequency is: "));
    DEBUG_FREQLN(secPoint->encFreq);
}