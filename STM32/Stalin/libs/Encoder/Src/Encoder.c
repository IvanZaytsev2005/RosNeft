#include "Encoder.h"
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
//extern TIM_HandleTypeDef htim2;
extern uint16_t AngleRaw[4];
extern uint16_t LastAngleRaw[4];
extern int32_t CurSpeedRaw[4];
extern float OutPid;
extern int32_t Speed[4];

uint32_t CountR;

void PlotEncOut()
{
    uint8_t N;
    uint8_t data[160];
    N = sprintf(data, "$%d;", CountR);
    HAL_UART_Transmit(&huart2, data, N,100);
}
uint8_t data_in_i2c[2];
// void PlotOutAs5600()
// {
// 	uint8_t data[32];
//     uint8_t N;
// 	I2C1->CR1&=~(1<<15);
// 	HAL_I2C_Mem_Read_IT(&hi2c1, 0x36*2, 0x0C, 1, data_in_i2c, 2);
// 	N = sprintf(data, "$%d %d %d;",CurSpeedRaw[0], Speed[0], (int32_t)OutPid);
// 	HAL_UART_Transmit(&huart2, data, N,100);
// }
    
// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
// {
//     HAL_GPIO_TogglePin(Led_GPIO_Port, Led_Pin);
// 	static uint32_t CCR1_Start;
// 	static uint32_t CCR3_Start;
// 	if(htim->Instance==TIM2)
// 	{
// 		uint32_t currCounter = TIM2->CNT;
// 		if (currCounter>0x80000000)
// 		{
// 			CountR=currCounter-0xFFFFFFFF;
// 		}
// 		else
// 		{
// 			CountR =currCounter;
// 		}
// 	}
	
// }