//#include "PID.h"
#include <stdint.h>

float Kp[8], Ki[8], Kd[8];
float de = 0;
float du = 0;

double Last_I[8];
double Last_e[8];

float PID(float Target, float Current, uint8_t index)
{
	float e;//cur error e(t)

	double P;
	double D;
	double I;

	float u;
	
	e=Target-Current;	
	// if(abs(e)<de)
	// {
	// 	return(0);
	// }
	P=Kp[index]*e;
	I=Last_I[index]+Ki[index]*e;
	D=Kd[index]*(e-Last_e[index]);
	
	u=(P+I+D);

	Last_e[index]=e;
	Last_I[index]=I;
	
	// if(abs(u)<du)
	// {
	// 	u=0;
	// }
	
	return(u);
}


uint8_t SetKoef(int32_t *par)
{
	Kp[par[0]] = (float)par[1];
	Ki[par[0]] = (float)par[2];
	Kd[par[0]] = (float)par[3];
}