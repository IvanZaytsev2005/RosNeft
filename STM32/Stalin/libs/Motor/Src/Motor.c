#include "main.h"
#include "Motor.h"

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;

Motor_TypeDef Motor[4];

void MotorsInitStructs()
{
    Motor[0].PinDir[0] = Dir12_Pin;
    Motor[0].PinDir[1] = Dir11_Pin;

    Motor[0].GpioDir = GPIOB;

    Motor[0].PWM_TIM_Handle = &htim1;
    Motor[0].PWM_Channel = TIM_CHANNEL_1;
    Motor[0].TypeOut = 1;
    Motor[0].CCR_PWM = &(TIM1->CCR1);
}

void MotorStart()
{
    MotorsInitStructs();
    for(uint8_t i = 0; i<1; i++)
    {
        *Motor[i].CCR_PWM = 0;
        if(Motor[i].TypeOut==1)
        {
            HAL_TIMEx_PWMN_Start(Motor[i].PWM_TIM_Handle, Motor[i].PWM_Channel);
        }
        else
        {
            HAL_TIM_PWM_Start(Motor[i].PWM_TIM_Handle, Motor[i].PWM_Channel);
        }
        HAL_GPIO_WritePin(Motor[i].GpioDir, Motor[i].PinDir[0],1);
        HAL_GPIO_WritePin(Motor[i].GpioDir, Motor[i].PinDir[1],1);
    }
}

uint8_t SetMotorPWM(int32_t *par)//number of motor, PWM
{
    uint8_t data[32];
    uint8_t N;
    SetPWM((uint8_t)par[0], par[1]);
    N = sprintf(data, "Motor %d have PWM %d in dir %d", par[0], par[2], par[1]);
    HAL_UART_Transmit(&huart1, data, N,30);
    SendEndOfString();
    //  N = sprintf(data, "TIM1->CCR1 = %d", TIM1->CCR1);
    // HAL_UART_Transmit(&huart1, data, N,30);
    // SendEndOfString();
    return(1);

}

void SetPWM(uint8_t Number, int32_t Data)
{
    if(Data == 0)
    {
        HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[0],1);
        HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[1],1);
    }
    else
    {
        if(Data>0)
        {
            HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[0],1);
            HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[1],0);
            *Motor[Number].CCR_PWM = (uint16_t)(Data);
        }
        else
        {
            HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[0],0);
            HAL_GPIO_WritePin(Motor[Number].GpioDir, Motor[Number].PinDir[1],1);
            *Motor[Number].CCR_PWM = (uint16_t)((-1)*Data);
        }
    }
    
}