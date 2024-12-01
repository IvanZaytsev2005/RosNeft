#include "AS5600LikeOdometr.h"
#include "stdio.h"

AS5600_Type AS[6];

extern I2C_HandleTypeDef hi2c1;

//extern TIM_HandleTypeDef htim7;

uint8_t BufOutAS5600[32];
uint8_t DataAS5600[10];

//uint8_t flag;
double RealSpeed[3];
double RealPosition[3];
double TargetSpeed[3];
double TargetAngleVar;

void InitAS5600()
{
	AS[0].TicksPerMetr=21741;
	AS[0].I2C_num=&hi2c1;
	AS[0].FirstOn=0;
	AS[0].NumberOnMultiplexor=1;
	AS[0].MovRaw=0;
	AS[0].minus=0;

	AS[1].TicksPerMetr=21741;
	AS[1].I2C_num=&hi2c1;
	AS[1].FirstOn=0;
	AS[1].NumberOnMultiplexor=1<<1;
	AS[1].MovRaw=0;
	AS[1].minus=1;
	
	AS[2].TicksPerMetr=21741;
	AS[2].I2C_num=&hi2c1;
	AS[2].FirstOn=0;
	AS[2].NumberOnMultiplexor=1<<2;
	AS[2].MovRaw=0;
	AS[2].minus=0;

	AS[3].TicksPerMetr=21741;
	AS[3].I2C_num=&hi2c1;
	AS[3].FirstOn=0;
	AS[3].NumberOnMultiplexor=1<<3;
	AS[3].MovRaw=0;
	AS[3].minus=1;

	AS[4].TicksPerMetr=0;
	AS[4].I2C_num=&hi2c1;
	AS[4].FirstOn=0;
	AS[4].NumberOnMultiplexor=1<<4;
	AS[4].MovRaw=0;
	AS[4].minus=1;

	AS[5].TicksPerMetr=0;
	AS[5].I2C_num=&hi2c1;
	AS[5].FirstOn=0;
	AS[5].NumberOnMultiplexor=1<<5;
	AS[5].MovRaw=0;
	AS[5].minus=1;
}

void CulcMovSpeedAS5600(AS5600_Type *AS5600)
{
	AS5600->VelRaw=AS5600->Raw-AS5600->LastRaw;
	if(AS5600->VelRaw>MaxTicksPerRotation)
	{
		AS5600->VelRaw=(-1)*(4096-AS5600->Raw+AS5600->LastRaw);
	}
	if(AS5600->VelRaw<(-MaxTicksPerRotation))
	{
		AS5600->VelRaw=4096-AS5600->LastRaw + AS5600->Raw;
	}
	
	if(AS5600->minus)
	{
		AS5600->VelRaw=(-1)*AS5600->VelRaw;
	}
	
	AS5600->MovRaw=AS5600->MovRaw + AS5600->VelRaw;
	
	if(AS5600->FirstOn==0)
	{
		AS5600->VelRaw=0;
		AS5600->MovRaw=0;
	}
	
	//AS5600->AccelRaw=AS5600->VelRaw-AS5600->LastVelRaw;
	
	AS5600->FirstOn=1;
	
	// AS5600->MovM=(double)AS5600->MovRaw/AS5600->TicksPerMetr;
	// AS5600->VelMS=(double)AS5600->VelRaw*400/AS5600->TicksPerMetr;//SMA(AS5600->VelMas,(double)AS5600->VelRaw*200/AS5600->TicksPerMetr,&(AS5600->CountPosSMA));
	// AS5600->VelMSFiltred=SMA_Speeds(AS5600,(double)AS5600->VelRaw*400/AS5600->TicksPerMetr);
	// AS5600->LastRaw=AS5600->Raw;
	//AS5600->LastVelRaw=AS5600->VelRaw;
}

uint8_t CheckI2C()
{
	
}

// without interrupt
// void PollAS5600WithMultiplexor(AS5600_Type *AS5600_1,AS5600_Type *AS5600_2,AS5600_Type *AS5600_3,AS5600_Type *AS5600_4)
// {
// 	uint8_t temp;
// 	temp=AS5600_1 ->NumberOnMultiplexor;
// 	HAL_I2C_Master_Transmit(&hi2c1, MultiplexAddr, &temp,1,100);
// 	CulcMovementAS5600I2C1(AS5600_1);
//	
// 	temp=AS5600_2->NumberOnMultiplexor;
// 	HAL_I2C_Master_Transmit(&hi2c1, MultiplexAddr, &temp,1,100);
// 	CulcMovementAS5600I2C1(AS5600_2);
//	
// 	temp=AS5600_3->NumberOnMultiplexor;
// 	HAL_I2C_Master_Transmit(&hi2c1, MultiplexAddr, &temp,1,100);
// 	CulcMovementAS5600I2C1(AS5600_3);
//	
// 	temp=AS5600_4->NumberOnMultiplexor;
// 	HAL_I2C_Master_Transmit(&hi2c1, MultiplexAddr, &temp,1,100);
// 	CulcMovementAS5600I2C1(AS5600_4);
// }


// it's for culculation robots position
// void CulcVel()
// {
// 	//PollAS5600WithMultiplexor(&AS0,&AS1,&AS2,&AS3);
// 	RealSpeed[0]=(AS2.VelMSFiltred+AS1.VelMSFiltred)/2;// at m
// /*	if(abs(AS0.VelMSFiltred)>abs(AS3.VelMSFiltred))
// 	{
// 		RealSpeed[1]=AS0.VelMSFiltred;
// 	}
// 	else
// 	{
// 		RealSpeed[1]=AS3.VelMSFiltred;
// 	}*/
// 	RealSpeed[1]=(AS3.VelMSFiltred+AS0.VelMSFiltred)/2;
// 	TargetAngleVar=TargetAngleVar+(TargetSpeed[2]/400);
// 	RealPosition[0]+=(RealSpeed[0]*cos(RealSpeed[2])-RealSpeed[1]*sin(RealSpeed[2]))*0.0025;
// 	RealPosition[1]+=(RealSpeed[0]*sin(RealSpeed[2])+RealSpeed[1]*cos(RealSpeed[2]))*0.0025;//=AS3.MovM;
// 	//RealSpeed[2]=(AS1.VelMSFiltred-AS2.VelMSFiltred)/DistM;
// 	/*RealSpeed[0]=(AS2.VelMS+AS1.VelMS)/2;// at m
// 	RealSpeed[1]=AS3.VelMS;
// 	RealSpeed[2]=(AS1.VelMS-AS2.VelMS)/DistM;*/
// }

// double SMA_Speeds(AS5600_Type *AS5600, double New)
// {
// //	static uint8_t CountPos;
// 	double Sum=0;
// 	//uint32_t a=data;
// 	AS5600->VelMas[AS5600->CountPosSMA%SmaN]=New;
	
// 	if(AS5600->CountPosSMA==0)
// 	{
// 		AS5600->CountPosSMA=1;
// 		return(New);
// 	}
// 	if(AS5600->CountPosSMA>=SmaN)
// 	{
// 		for(char i=0; i<SmaN; i++)
// 		{
// 			Sum+=AS5600->VelMas[i];
// 		}
// 		Sum=Sum/SmaN;
// 		AS5600->CountPosSMA+=1;
// 		if(AS5600->CountPosSMA>=(2*SmaN))
// 		{
// 			AS5600->CountPosSMA=SmaN;
// 		}
// 		return((double)Sum);///(double)SmaN);
		
// 	}
// 	else
// 	{
// 		for(char i=0;i<AS5600->CountPosSMA;i++)
// 		{
// 			Sum=Sum+AS5600->VelMas[i];
// 		}
// 		AS5600->CountPosSMA=AS5600->CountPosSMA+1;
// 		return((double)Sum/(AS5600->CountPosSMA-1));
// 	}
// }
