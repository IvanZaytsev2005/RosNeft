#include "App.h"
#include "serial_driver.h"
#include "comand_processing.h"
#include "Motor.h"
#include "Encoder.h"
#include "PID.h"
#include "AS5600LikeOdometr.h"
//peripferal
extern TIM_HandleTypeDef htim1;
// extern TIM_HandleTypeDef htim2;
//extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

//flags: interrupts
extern uint8_t IntFlag;


//app var

int32_t Speed[4];// speeds of wheels mm/s
int32_t Alpha[2];// Angles of links radians
int32_t Vel;// linear velocity of robot mm/s
uint32_t R;// radius of circle mm


extern UART_HandleTypeDef huart1;

//commands 
#define Ncmd 7
CmdType coms[Ncmd] = {{"aaa",NoneOperation}, {"Set_PWM", SetMotorPWM}, {"Led", LED}, {"I2C_Ping", I2C_Ping}, {"I2C_Read", I2C_Read}, {"set_speed", SetSpeed}, {"k", SetKoef}};
extern int32_t Params[10];

void InitStartState()
{
    Speed[0] = 0;
    Speed[1] = 0;
    Speed[2] = 0;
    Speed[3] = 0;
    HAL_Delay(100);
    int32_t par[3];
    InitPids();
    SerialInit();
    MotorStart();
    InitAS5600();
    CrossCheck();
}

void App()
{
    uint8_t data;
    uint8_t data_out[32];
    uint8_t N;
    while(1)
    {
        if((IntFlag&Uart1ReceivedString)!=0)
        {
            CMDProcessing();
            data = FindFunc(coms, Ncmd);
            // N = sprintf(data_out, "%d", data);
            // HAL_UART_Transmit(&huart1, data_out, N,10);
            coms[data].func(Params);
            IntFlag&=~Uart1ReceivedString;
        }
        if((IntFlag&Tim)!=0)
        {
            //PlotEncOut();
            //PlotOutAs5600();
            StartMeaserAS5600();
            IntFlag&=~Tim;
        }
        if((IntFlag&Pid)!=0)
        {
            PidCulc();
            IntFlag&=~Pid;
        }
    }
}

void CrossCheck()
{
    // uint8_t data[32];
    // uint8_t N;
    // if(HAL_I2C_Master_Transmit(&hi2c1, 0x36*2, data, 1, 10)==HAL_OK)
    // {
    //     N = sprintf(data, "AS5600 is OK");
    //     SerialWrite(data, N);
    //     SendEndOfString();
    // }
    // else
    // {
    //     N = sprintf(data, "AS5600 have error");
    //     SerialWrite(data, N);
    //     SendEndOfString();
    // }
}

float OutPid;

void InitPids()
{
    par[0] = 0;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);

    par[0] = 1;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);

    par[0] = 2;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);

    par[0] = 3;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);

    par[0] = 4;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);

    par[0] = 5;
    par[1] = 10;
    par[2] = 10;
    par[3] = 10;
    SetKoef(par);
}

void PidCulc()
{
    OutPid = PID((float)Speed[0], (float)CurSpeedRaw[0], 0);
    SetPWM(0, (int32_t)OutPid);
}

void Control()
{

}

uint8_t NoneOperation(int32_t *par)
{}


uint8_t LED(int32_t *par)
{
    uint8_t data[32];
    uint8_t N;
    if(par[0] == 0)
    {
        HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin,1);
        N = sprintf(data, "Led off");
    }
    else
    {
        HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin,0);
        N = sprintf(data, "Led on");
    }
    SerialWrite(data, N);
    SendEndOfString();
}

uint8_t I2C_Ping(int32_t *par)
{
    uint8_t data[32];
    uint8_t N;
    for(uint16_t i=0; i<255; i++)
    {
        if(HAL_I2C_Master_Transmit(&hi2c1, i, data, 1, 10)==HAL_OK)
        {
            N = sprintf(data, "%d", i);
            SerialWrite(data, N);
            SendEndOfString();
        }
    }
    SendEndOfString();
}

uint8_t I2C_Read(int32_t *par)
{
    uint8_t data[32];
    uint8_t N;
    uint8_t data_in[2];
    HAL_I2C_Mem_Read(&hi2c1, par[0], par[1], 1, data_in, par[2], 500);
    N  = sprintf(data, "%d", data_in[1]+data_in[0]*8);
    SerialWrite(data, N);
    SendEndOfString();
}

uint8_t SetSpeed(int32_t *par)
{
    Speed[par[0]] = par[1];
    uint8_t data[32];
    uint8_t N = sprintf(data, "Motor %d have speed %d mm/sec", par[0], par[1]);
    HAL_UART_Transmit(&huart1, data, N,30);
    SendEndOfString();
}
