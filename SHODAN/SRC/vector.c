
#include "../shodan.h"

/**********/
SVector* VectorInit(float x, float y)
{
	SVector* v = Calloc(1, sizeof(SVector));

	v->x = x;
	v->y = y;

	return v;
}

/**********/
void VectorClose(SVector** v)
{
	Free(*v);
	*v = NULL;
}

/**********/
void VectorSet(SVector* v, float x, float y)
{
	v->x = x;
	v->y = y;
}

/*********/
void VectorAdd(SVector* v, SVector* s)
{
	v->x += s->x;
	v->y += s->y;
}

/**********/
void VectorSub(SVector* v, SVector* s)
{
	v->x -= s->x;
	v->y -= s->y;
}

/**********/
void VectorMul(SVector* v, float n)
{
	v->x *= n;
	v->y *= n;
}

/**********/
void VectorDiv(SVector* v, float n)
{
	v->x /= n;
	v->y /= n;
}

/*********/
SVector _VectorAdd(SVector* v, SVector* s)
{
	return (SVector) { v->x + s->x, v->y + s->y };
}

/**********/
SVector _VectorSub(SVector* v, SVector* s)
{
	return (SVector) { v->x - s->x, v->y - s->y };
}

/**********/
SVector _VectorMul(SVector* v, float n)
{
	return (SVector) { v->x* n, v->y* n };
}

/**********/
SVector _VectorDiv(SVector* v, float n)
{
	return (SVector) { v->x / n, v->y / n };
}

/**********/
void VectorNormalize(SVector* v)
{
	float m = VectorMagnitude(v);

	if (m != 0.0f) { VectorDiv(v, m); };
}

/**********/
float VectorMagnitude(SVector* v)
{
	float val = (v->x * v->x) + (v->y * v->y);
	return (float)sqrt(val);
}

/**********/
float VectorDot(SVector* v, SVector* s)
{
	return (v->x * s->x) + (v->y * s->y);
}

/**********/
float VectorCross(SVector* v, SVector* s)
{
	return (v->x * s->y) - (v->y * s->x);
}

/**********/
void VectorRotate(SVector* v, SVector* s, float angle)
{
	float x = v->x - s->x;
	float y = v->y - s->y;
	float radians = Radians(-angle);

	float _x = s->x + x * cosf(radians) - y * sinf(radians);
	float _y = s->y + x * sinf(radians) + y * cosf(radians);

	v->x = _x;
	v->y = _y;
}
