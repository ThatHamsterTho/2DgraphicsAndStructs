#ifndef shapehandlerHEADER
#define shapehandlerHEADER

#include <stdarg.h>
#include <simple2d.h>
#include "shapedata.h"
#include "calcfunc.h"

void initGraphicList(void);

// graphic object
typedef struct __graphic__ {
	generic_data_shape *shape;	// pointer to shape data
	void (*draw)(void *self);	// pointer to draw function
	void (*free)(void *self);	// free self
	bool drawable;				// boolian drawable or not
	stype type;					// type of shape
} graphic;

// type of shape, drawable, followed by a max of 8 coords
graphic *initGraphic(stype type, bool drawable, ...);
void __freegraphic(void *VP_self);
void freeGraphicsList(void);

List *Graphics[NUMOFSHAPETYPES];

generic_data_shape *initshape(stype type, float coords[8]);
typedef void (*fp_drawshape)(void *self);
fp_drawshape drawshape(stype type);

void __drawpoint(void *self);
void __drawline(void *self);
void __drawtriangle(void *self);
void __drawquad(void *self);
void __drawsquare(void *self);
void __drawcircle(void *self);

void set_color(S2D_Color *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif