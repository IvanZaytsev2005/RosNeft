//#include "PID.h"
#include <stdint.h>

float Kp, Ki, Kd;
float de;
float du;

double Last_I[8];
double Last_e[8];

float PID(float Target, float Current, uint8_t index)
{
	return(Target+1);
	// float e;//cur error e(t)

	// double P;
	// double D;
	// double I;

	// float u;
	
	// e=Target-Current;	
	// if(abs(e)<de)
	// {
	// 	return(0);
	// }
	// P=Kp*e;
	// I=Last_I[index]+Ki*e;
	// D=Kd*(e-Last_e[index]);
	
	// u=(P+I+D);

	// Last_e[index]=e;
	// Last_I[index]=I;
	
	// if(abs(u)<du)
	// {
	// 	u=0;
	// }
	
	// return(u);
}
