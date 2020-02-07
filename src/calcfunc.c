#include "calcfunc.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// maps input to a scale of 0 - max
float MapToScale(int x, int max){
	return ((float)x / (float)max);
}

float dist2p(float Ax, float Ay, float Bx, float By){
	return fsqrt(powint(Bx - Ax, 2) + powint(By - Ay, 2));
}

float powint(float base, int exp){
	for(int i = 1; i < exp; i++){
		base = base*base;
	}
	return base;
}

float fsqrt(float n) {
    n = 1.0f / n;
    long i;
    float x, y;

    x = n * 0.5f;
    y = n;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (x * y * y));

    return y;
}