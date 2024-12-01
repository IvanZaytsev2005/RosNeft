#include "main.h"
#include "math.h"

void App();
void CrossCheck();
void InitStartState();
void InitCmds();
uint8_t NoneOperation(int32_t *par);
uint8_t LED(int32_t *par);
uint8_t I2C_Ping(int32_t *par);
uint8_t I2C_Read(int32_t *par);
uint8_t SetSpeed(int32_t *par);
void PidCulc();
void InitPids();


//defines

#define Uart1ReceivedString 1
#define Uart2ReceivedString 2
#define Tim 4
#define Pid 8


#define TickPerMetr 4096