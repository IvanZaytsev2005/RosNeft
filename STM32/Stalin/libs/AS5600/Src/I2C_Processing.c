#include "AS5600LikeOdometr.h"

uint8_t I2CBuf[4];
uint8_t NumAs;

extern AS5600_Type AS[6];

extern I2C_HandleTypeDef hi2c1;

void StartMeaserAS5600()
{
	HAL_I2C_Master_Transmit_DMA(&hi2c1, MultiplexAddr, &AS[0].NumberOnMultiplexor,1);
	NumAs = 0;
}

void HAL_I2C_MemRxCpltCallback ( I2C_HandleTypeDef *hi2c)
{
	uint8_t Ad;
	if(hi2c->Instance==I2C1)
	{
		AS[NumAs].Raw=(I2CBuf[0]<<8)+I2CBuf[1];
		CulcMovSpeedAS5600(&AS[NumAs]);
		if(NumAs<5)
		{
			HAL_I2C_Master_Transmit_DMA(&hi2c1, MultiplexAddr, &AS[NumAs+1].NumberOnMultiplexor,1);
			NumAs++;
		}
		else
		{
			NumAs = 0;
		}
	}
}

void HAL_I2C_MasterTxCpltCallback ( I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_Mem_Read_DMA(AS[NumAs].I2C_num,AS5600Addr,0x0C,1,I2CBuf,2);
}