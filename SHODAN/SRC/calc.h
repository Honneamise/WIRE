#ifndef CALC_H
#define CALC_H

//math
int Min(int a, int b);

float Minf(float a, float b);

int Max(int a, int b);

float Maxf(float a, float b);

int Rand(int min, int max);

float Randf(float min, float max);

int Map(int x, int in_min, int in_max, int out_min, int out_max);

float Mapf(float x, float in_min, float in_max, float out_min, float out_max);

int Clamp(int x, int min, int max);

float Clampf(float x, float min, float max);

float Radians(float degrees);

float Degrees(float radians);

#endif