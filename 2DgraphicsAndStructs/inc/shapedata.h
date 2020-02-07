#ifndef initHeader
#define initHeader

#include "objects.h"

// this data needs to be in this order in every struct
#define STATICPOS_SHAPEDATASTRUCT \
		unsigned int point_num;\
		ListItem *item;\
\
		void (*free)(ListItem *item);

typedef struct __RGBA__ {
	float r;
	float g;
	float b;
	float a;
} RGBA;

// do not use
void *__initundef(float coords[8]);

typedef struct __data_point__ {
	STATICPOS_SHAPEDATASTRUCT

	// x, y coordinates
	float x, y;
	// data_point color
	RGBA c;
} data_point;

// creates a data_point P at (x, y)
void *initpoint(float coords[8]);


typedef struct __data_circle__ {
	STATICPOS_SHAPEDATASTRUCT

	// center data_point M
	data_point *points[1];
	// circle radius
	float radius;
	int sectors;
} data_circle;

/* 	creates circle around center data_point M(x, y) with radius R
	coords: x, y, radius, sectors; */
void *initcircle(float coords[8]);


typedef struct __data_line__ {
	STATICPOS_SHAPEDATASTRUCT

	// A -- B
	data_point *points[2];
	// drawing width for S2D_drawline
	float width;
} data_line;

// creates a line from data_point A to B
void *initline(float coords[8]);


typedef struct __data_triangle__ {
	STATICPOS_SHAPEDATASTRUCT

	data_point *points[3];
} data_triangle;

// creates a triangle with A at top, B at bottom left and C at bottom right
void *inittriangle(float coords[8]);
	

typedef struct __data_quad__ {
	STATICPOS_SHAPEDATASTRUCT

	data_point *points[4];
} data_quad;

// creates a square with A at top left, B at top right, C at bottom right and D at bottom left
void *initquad(float coords[8]);
	

typedef struct __data_square__ {
	STATICPOS_SHAPEDATASTRUCT

	data_point *points[1];
	float width;
	float height;
} data_square;

// coords: x, y, width, height
void *initsquare(float coords[8]);
	
typedef data_quad generic_data_shape;
typedef union __dynamic_data_shape__ {
	data_quad 	 *shape;
	data_triangle *t;
	data_quad	 *q;
	data_square	 *s;
	data_line	 *l;
	data_circle	 *c;
	data_point	 *p;
}dynamic_data_shape;	// generic shape


// memory clean up

void __freeshape(ListItem *obj);

void freeShapesFromObjList();
#endif