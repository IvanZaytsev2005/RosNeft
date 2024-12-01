#include "main.h"
#include "types.h"

void MotorsInitStructs();
void MotorStart();
uint8_t SetMotorPWM(int32_t *par);//number of motor, dir, PWM
void SetPWM(uint8_t Number, int32_t Data);