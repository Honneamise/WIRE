#ifndef POLY_H
#define POLY_H

//poly
typedef struct SPoly
{
	int nv;

	SArray* vertices;

	float minx;
	float miny;
	float maxx;
	float maxy;

} SPoly;

/**********/
SPoly* PolyInit();

void PolyClose(SPoly** poly);

void PolyAddVertex(SPoly* poly, float x, float y);

void PolyMove(SPoly* poly, SVector* v);

void PolyRotate(SPoly* poly, float angle);

SVector* PolyCenter(SPoly* poly);

bool PolyCheckPoint(SPoly* poly, float x, float y);

bool PolyConvex(SPoly* poly);

#endif