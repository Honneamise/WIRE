#ifndef VECTOR_H
#define VECTOR_H

//vector
typedef struct SVector
{
	float x;
	float y;

} SVector;

/**********/
SVector * VectorInit(float x, float y);

void VectorClose(SVector** v);

void VectorSet(SVector* v, float x, float y);

void VectorAdd(SVector* v, SVector* s);

void VectorSub(SVector* v, SVector* s);

void VectorMul(SVector* v, float n);

void VectorDiv(SVector* v, float n);

SVector _VectorAdd(SVector* v, SVector* s);

SVector _VectorSub(SVector* v, SVector* s);

SVector _VectorMul(SVector* v, float n);

SVector _VectorDiv(SVector* v, float n);

void VectorNormalize(SVector* v);

float VectorMagnitude(SVector* v);

float VectorDot(SVector* v, SVector* s);

float VectorCross(SVector* v, SVector* s);

void VectorRotate(SVector* v, SVector* s, float angle);

#endif