#include "main.h"

typedef struct AS5600{
	uint16_t Raw;
	uint32_t TicksPerMetr;
	uint16_t LastRaw;
	int32_t LastVelRaw;
	int32_t MovRaw;
	int32_t VelRaw;
	double MovM;
	double VelMS;
	double VelMSFiltred;
	I2C_HandleTypeDef *I2C_num;
	uint8_t FirstOn;
	uint8_t NumberOnMultiplexor;
	uint8_t minus;
	// double VelMas[SmaN];
	// uint16_t CountPosSMA;
	// int32_t AccelRaw;
} AS5600_Type;

#define MaxTicksPerRotation 150
#define MultiplexAddr 0xE0
#define AS5600Addr 0x36*2

void InitAS5600();
void CulcMovSpeedAS5600(AS5600_Type *AS5600);
void PollAS5600WithMultiplexor(AS5600_Type *AS5600_1,AS5600_Type *AS5600_2,AS5600_Type *AS5600_3,AS5600_Type *AS5600_4);
void StartMeaserAS5600();
void CulcVel();
double SMA_Speeds(AS5600_Type *AS5600, double New);

