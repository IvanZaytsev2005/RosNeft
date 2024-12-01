#include "App.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

uint8_t data_in;
uint8_t IntFlag;
// extern uint8_t data_in_i2c[2];
// extern uint16_t AngleRaw[4];
// extern uint16_t LastAngleRaw[4];
// extern int32_t CurSpeedRaw[4];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        if(ProcessingInputData(USART1->DR))
        {
            IntFlag |= Uart1ReceivedString; 
        }
        HAL_UART_Receive_IT(&huart1, &data_in,1);
    }
    if(huart->Instance == USART2)
    {
        if(ProcessingInputData(USART2->DR))
        {
            IntFlag |= Uart2ReceivedString; 
        }
        HAL_UART_Receive_IT(&huart2, &data_in,1);
    }
}


// void HAL_I2C_MemRxCpltCallback ( I2C_HandleTypeDef *hi2c)
// {
//     if(hi2c->Instance == I2C1)
//     {
//         LastAngleRaw[0] = AngleRaw[0];
//         AngleRaw[0] = data_in_i2c[1]+data_in_i2c[0]*256;
//         if((AngleRaw[0]>LastAngleRaw[0]))
//         {
//             if((AngleRaw[0]-LastAngleRaw[0])<150)
//             {
//                 CurSpeedRaw[0] = (int32_t)AngleRaw[0] - (int32_t)LastAngleRaw[0];
//             }
//             else
//             {
//                 CurSpeedRaw[0] = (-1)*(-(int32_t)AngleRaw[0] + (int32_t)LastAngleRaw[0]+4096);
//             }
//         }
//         else
//         {
//             if((LastAngleRaw[0]-AngleRaw[0])<150)
//             {
//                 CurSpeedRaw[0] = (-1)*((int32_t)LastAngleRaw[0] - (int32_t)AngleRaw[0]);    
//             }
//             else
//             {
//                 CurSpeedRaw[0] = 4096 -LastAngleRaw[0]+AngleRaw[0];
//             }
//         }
//     }
// }

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    if(hi2c->Instance == I2C1)
    {
        // I2C1->CR1|=(1<<15);
        // HAL_I2C_AbortCpltCallback(hi2c);
        // HAL_I2C_DeInit(&hi2c1);
        //HAL_I2C_Init(&hi2c1);
    }
}