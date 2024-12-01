#include "stdio.h"

typedef struct mot{
    uint16_t PinDir[2];
    GPIO_TypeDef* GpioDir;
    TIM_HandleTypeDef* PWM_TIM_Handle;
    uint16_t PWM_Channel;
    TIM_HandleTypeDef* Encoder_TIM;
    uint8_t TypeOut;//normal or N
    uint32_t* CCR_PWM;
} Motor_TypeDef;