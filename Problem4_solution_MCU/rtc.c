#include "rtc.h"

volatile UINT32 nTick;   // number of RTC ticks since start
volatile UINT32 nUptime; // number of 1/10 seconds since start
volatile UINT16 nSubsec; // number of RTC ticks. Need to calc nUptime

extern UINT32 ToDisplayValue[8];
extern UINT8 cDisplayedSymbols;
extern UINT8 aRfBuf[64];
extern UINT8 cRfBufLength;

extern bool isRfReceived;
extern bool isRfEnabled;

void RTCInit()
{
    nTick = 0;
    nUptime = 0;
    nSubsec = 0;
  
    // TIM4 for RTC
    TIM3_ARRH = 0;
    TIM3_ARRL = RTC_COUNT_FOR_TIMER; // TIM4 auto-reload register. Border for the interrupt appearance.
  
    TIM3_PSCR_PSC = TIM_PRESCALER_128; // Fosc/128

    TIM3_IER_UIE = 1; // enable interrupt

    TIM3_CR1 = 0;
    TIM3_CR1_ARPE = 1; // auto-reload enable
    TIM3_CR1_CEN  = 1; // enable timer
}

UINT32 GetTickCount()
{
    UINT32 res;
    TIM3_IER_UIE = 0; // disable timer interrupt
    res = nTick;
    TIM3_IER_UIE = 1; // enable timer interrupt
    return res;
}

UINT32 GetUptime()
{
    UINT32 res;
    TIM3_IER_UIE = 0; // disable timer interrupt
    res = nUptime;
    TIM3_IER_UIE = 1; // enable timer interrupt
    return res;
}

bool IsTickPassed(UINT32 nTick)
{
    bool bResult = FALSE;
    UINT32 nCurrent = GetTickCount();
    
    if (nTick < nCurrent)
    {
        bResult = TRUE;
    }

    if ( (nTick > (UINT32_MAX - RTC_TIMER_TICK_MAX_DIF)) || (nCurrent > (UINT32_MAX - RTC_TIMER_TICK_MAX_DIF)) ) // move numbers to one region if need
    {
        // if detected out of possible count range, shift counters
        nTick    += RTC_TIMER_TICK_MAX_DIF;
        nCurrent += RTC_TIMER_TICK_MAX_DIF;
    }

    return bResult;
}

#pragma vector = TIM3_OVR_UIF_vector
__interrupt void RTC_Interrupt()
{
    TIM3_IER_UIE = 0; // disable interrupt

    /*if(!Event_RFM && isRfEnabled)          
    {
        isRfReceived = TRUE;
        cRfBufLength = ReceivePacket(aRfBuf);
        isRfEnabled = FALSE;
    }
    
    if (nSubsec >= RTC_SLOW_RATE_HZ)
    {
        nSubsec = 0;
        nUptime++;
    }*/
    
    //if(nTick > 0xFFFFFF00)
    //  while(1);                 //  If nTick close to owerflow - reset
    
    TIM3_SR1_UIF = 0; // Clear interrupt flag
    TIM3_IER_UIE = 1; // enable interrupt

}