#include "Timer_Handmade.h"

static volatile TIM_Handmade_t *TIMx[4] = { TIM2_HANDMADE, TIM3_HANDMADE, TIM4_HANDMADE, TIM5_HANDMADE};


uint32_t ValueAutoReload = 0;

static uint32_t calculateFrequency(uint32_t RCC_Clock, uint32_t Desired_Timer_Freq) {
    if (Desired_Timer_Freq == 0 || Desired_Timer_Freq > RCC_Clock) return 0xFFFF; // Tránh lỗi chia 0 hoặc giá trị sai
    return ((RCC_Clock / Desired_Timer_Freq) - 1);
}
static uint32_t calculateDutyCycle(uint32_t AutoReload, uint8_t DutyCycle){
    return ((AutoReload * DutyCycle)/100);
}
void initTimer(TIM_Config_t *TimerConfig){

    Enable_Clock_RCC_APB1(TIM2_EN_CLK);
    volatile TIM_Handmade_t *TIMER = TIMx[TimerConfig->Timer];
    TIMER->TIM_ARR = TimerConfig->ValueAutoReload;
    ValueAutoReload = TimerConfig->ValueAutoReload;
    TIMER->TIM_CCR1 = calculateDutyCycle(TimerConfig->ValueAutoReload,TimerConfig->DutyCycle);
    // If APB1 prescaler is greater than 1, then the timer clock frequency is twice the APB1 frequency
    TIMER->TIM_PSC = calculateFrequency(((getFrequencyAPB1() < FREQ_36MHZ) && (getFrequencyRCC() != FREQ_36MHZ)) ? getFrequencyAPB1()*2 : getFrequencyAPB1(),TimerConfig->DesiredFrequency);
    // Cấu hình giá trị ban đầu của counter (CNT)
    TIMER->TIM_CNT = TimerConfig->ValueCount;

    // Cấu hình thanh ghi TIM_CR1 (Control Register 1)
    TIMER->TIM_CR1 = 0; // Xóa thanh ghi trước khi cấu hình
    TIMER->TIM_CR1 |= (TimerConfig->clockDivision << 8);      // CKD: Clock division
    TIMER->TIM_CR1 |= (TimerConfig->aligned_mode << 5);       // CMS: Center-aligned mode
    TIMER->TIM_CR1 |= (TimerConfig->Direction_count << 4);    // DIR: Direction
    TIMER->TIM_CR1 |= (TimerConfig->onePulseMode << 3);       // OPM: One-pulse mode
    TIMER->TIM_CR1 |= (TimerConfig->updateSource << 2);       // URS: Update request source
    TIMER->TIM_CR1 |= (TimerConfig->updateDisable << 1);      // UDIS: Update disable
    TIMER->TIM_CR1 |= (TimerConfig->counterEnable << 0);      // CEN: Counter enable (sửa từ bit 4 thành bit 0)
    TIMER->TIM_CR1 |= (TimerConfig->autoReloadPreload << 7);  // ARPE: Auto-reload preload enable

    // Cấu hình thanh ghi TIM_CR2 (Control Register 2)
    TIMER->TIM_CR2 = 0; // Xóa thanh ghi trước khi cấu hình
    TIMER->TIM_CR2 |= (TimerConfig->ti1Selection << 7);       // TI1S: TI1 selection
    TIMER->TIM_CR2 |= (TimerConfig->masterMode << 4);         // MMS: Master mode selection
    TIMER->TIM_CR2 |= (TimerConfig->dmaSelection << 3);       // CCDS: Capture/compare DMA selection

    // Cấu hình thanh ghi TIM_SMCR (Slave Mode Control Register)
    TIMER->TIM_SMCR = 0; // Xóa thanh ghi trước khi cấu hình
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerPolarity << 15);  // ETP: External trigger polarity
    TIMER->TIM_SMCR |= (TimerConfig->extClockEnable << 14);      // ECE: External clock enable
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerPrescaler << 12); // ETPS: External trigger prescaler
    TIMER->TIM_SMCR |= (TimerConfig->extTriggerFilter << 8);     // ETF: External trigger filter
    TIMER->TIM_SMCR |= (TimerConfig->masterSlaveMode << 7);      // MSM: Master/Slave mode
    TIMER->TIM_SMCR |= (TimerConfig->triggerSelection << 4);     // TS: Trigger selection
    TIMER->TIM_SMCR |= (TimerConfig->slaveMode << 0);            // SMS: Slave mode selection
    


}
void StartPWMNormal(Timer_t timer, Channel_timer_t channel) {
    volatile TIM_Handmade_t *TIMER = TIMx[timer];

    switch (channel) {
        case CHANNEL_TIMER_1:
            TIMER->TIM_CCMR1 &= ~(0x7 << 4);   // Xóa chế độ cũ
            TIMER->TIM_CCMR1 |= (TIM_OC_MODE_PWM1 << 4); // Chọn PWM mode 1
            TIMER->TIM_CCER |= (1 << 0); // Kích hoạt kênh 1 PWM
            break;
        case CHANNEL_TIMER_2:
            TIMER->TIM_CCMR1 &= ~(0x7 << 12);
            TIMER->TIM_CCMR1 |= (TIM_OC_MODE_PWM1 << 12); // Chọn PWM mode 1
            TIMER->TIM_CCER |= (1 << 4); // Kích hoạt kênh 2 PWM
            break;
        case CHANNEL_TIMER_3:
            TIMER->TIM_CCMR2 &= ~(0x7 << 4);
            TIMER->TIM_CCMR2 |= (TIM_OC_MODE_PWM1 << 4); // Chọn PWM mode 1
            TIMER->TIM_CCER |= (1 << 8); // Kích hoạt kênh 3 PWM
            break;
        case CHANNEL_TIMER_4:
            TIMER->TIM_CCMR2 &= ~(0x7 << 12);
            TIMER->TIM_CCMR2 |= (TIM_OC_MODE_PWM1 << 12); // Chọn PWM mode 1
            TIMER->TIM_CCER |= (1 << 12); // Kích hoạt kênh 4 PWM
            break;
        default:
            return;
    }

}

void SetDutyCycle(Timer_t timer, Channel_timer_t channel,uint8_t dutycycle){

    volatile TIM_Handmade_t *TIMER = TIMx[timer];

    switch (channel) {
        case CHANNEL_TIMER_1:
        case CHANNEL_TIMER_2:
        case CHANNEL_TIMER_3:
        case CHANNEL_TIMER_4:
            TIMER->TIM_CCR1 = calculateDutyCycle(ValueAutoReload,dutycycle);
            break;
    }

}


