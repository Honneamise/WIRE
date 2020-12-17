
#include "../shodan.h"

/**********/
int Min(int a, int b)
{
	return a <= b ? a : b;
}

/**********/
float Minf(float a, float b)
{
	return a <= b ? a : b;
}

/**********/
int Max(int a, int b)
{
	return a >= b ? a : b;
}

/**********/
float Maxf(float a, float b)
{
	return a >= b ? a : b;
}

/**********/
int Rand(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**********/
float Randf(float min, float max)
{
	float f = rand() / ((float)(RAND_MAX)+1);

	if (min > max)
		return f * (min - max) + max;
	else
		return f * (max - min) + min;
}

/**********/
int Map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
float Mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********/
int Clamp(int x, int min, int max)
{
	int t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float Clampf(float x, float min, float max)
{
	float t = x < min ? min : x;
	return t > max ? max : t;
}

/**********/
float Radians(float degrees)
{
	return (float)(degrees * (float)M_PI / 180.0f);
}

/**********/
float Degrees(float radians)
{
	return (float)(radians * 180.0f / (float)M_PI);
}

