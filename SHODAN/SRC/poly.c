
#include "../shodan.h"

/**********/
SPoly* PolyInit()
{
	SPoly* poly = Calloc(1, sizeof(SPoly));

	poly->vertices = ArrayInit();

	return poly;
}

/**********/
void PolyClose(SPoly** poly)
{
	for (int i = 0; i < (*poly)->vertices->size; i++)
	{
		SVector* v = ArrayGet((*poly)->vertices, i);
		VectorClose(&v);
	}

	ArrayClose(&(*poly)->vertices);

	Free(*poly);
}

/***********/
void _PolyUpdateSize(SPoly* poly)
{
	if (poly->vertices->size < 1) { return; };

	SVector* v = ArrayGet(poly->vertices, 0);

	poly->minx = v->x;
	poly->miny = v->y;
	poly->maxx = v->x;
	poly->maxy = v->y;

	for (int i = 1; i < poly->vertices->size; i++)
	{
		v = ArrayGet(poly->vertices, i);

		poly->minx = Minf(poly->minx, v->x);
		poly->miny = Minf(poly->miny, v->y);
		poly->maxx = Maxf(poly->maxx, v->x);
		poly->maxy = Maxf(poly->maxy, v->y);
	}
}

/***********/
void PolyAddVertex(SPoly* poly, float x, float y)
{
	if (poly->vertices->size == 0)
	{
		poly->minx = x;
		poly->miny = y;
		poly->maxx = x;
		poly->maxy = y;
	}
	else
	{
		poly->minx = Minf(poly->minx, x);
		poly->miny = Minf(poly->miny, y);
		poly->maxx = Maxf(poly->maxx, x);
		poly->maxy = Maxf(poly->maxy, y);
	}

	ArrayAdd(poly->vertices, VectorInit((float)x, (float)y));
	poly->nv++;
}

/**********/
void PolyMove(SPoly* poly, SVector* v)
{
	for (int i = 0; i < poly->vertices->size; i++)
	{
		SVector* _v = ArrayGet(poly->vertices, i);

		VectorAdd(_v, v);
	}

	_PolyUpdateSize(poly);
}

/**********/
void PolyRotate(SPoly* poly, float angle)
{
	SVector* center = PolyCenter(poly);

	for (int i = 0; i < poly->vertices->size; i++)
	{
		SVector* v = ArrayGet(poly->vertices, i);

		VectorRotate(v, center, angle);
	}

	VectorClose(&center);

	_PolyUpdateSize(poly);
}

/**********/
SVector* PolyCenter(SPoly* poly)
{
	SVector* center = VectorInit(0.0f, 0.0f);

	float signed_area = 0.0f;

	float a = 0.0f; //temp area

	for (int i = 0; i < poly->vertices->size; i++)
	{
		SVector* v0 = ArrayGet(poly->vertices, i);
		SVector* v1 = ArrayGet(poly->vertices, (i + 1) % poly->vertices->size);

		a = v0->x * v1->y - v1->x * v0->y;

		signed_area += a;

		center->x += (v0->x + v1->x) * a;
		center->y += (v0->y + v1->y) * a;
	}

	signed_area *= 0.5f;

	center->x /= (6.0f * signed_area);
	center->y /= (6.0f * signed_area);

	return center;
}

/**********/
/* adapted from : http://alienryderflex.com/polygon/ */
bool PolyCheckPoint(SPoly* poly, float x, float y)
{
	int size = poly->vertices->size;

	if (size < 3) { return false; }

	int j = size - 1;

	bool odd = false;

	SVector** vertices = (SVector**)poly->vertices->items;

	for (int i = 0; i < size; i++)
	{
		if ((vertices[i]->y < y && vertices[j]->y >= y) || (vertices[j]->y < y && vertices[i]->y >= y))
		{
			if (vertices[i]->x + (y - vertices[i]->y) / (vertices[j]->y - vertices[i]->y) * (vertices[j]->x - vertices[i]->x) < x)
			{
				odd = !odd;
			}
		}
		j = i;
	}

	return odd;
}

/**********/
bool PolyConvex(SPoly* poly)
{
	bool sign = false;

	for (int i = 0; i < poly->nv; i++)
	{
		SVector* v0 = ArrayGet(poly->vertices, i);
		SVector* v1 = ArrayGet(poly->vertices, (i + 1) % poly->nv);
		SVector* v2 = ArrayGet(poly->vertices, (i + 2) % poly->nv);

		SVector _v0 = _VectorSub(v1, v0);
		SVector _v1 = _VectorSub(v2, v1);

		float cross = VectorCross(&_v0, &_v1);

		if (i == 0) { sign = cross > 0.0f; }
		else
		{
			if (sign != (cross > 0.0f)) { return false; }
		}
	}

	return true;
}

