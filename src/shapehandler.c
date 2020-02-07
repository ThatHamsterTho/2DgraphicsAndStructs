#include "shapehandler.h"

void initGraphicList(void){
	for(int i = 0; i < NUMOFSHAPETYPES; i++){
		Graphics[i] = initList();
	}
}

generic_data_shape *initshape(stype type, float coords[8]){
	void *(*initshape[NUMOFSHAPETYPES])(float coords[8]) = {
		__initundef,
		initpoint,
		initline,
		inittriangle,
		initquad,
		initsquare,
		initcircle
	};
	return (generic_data_shape *)((*initshape[type]))(coords);
}

fp_drawshape drawshape(stype type){
	void (*drawshape[NUMOFSHAPETYPES])(void *self) = {
		NULL,
		__drawpoint,
		__drawline,
		__drawtriangle,
		__drawquad,
		__drawsquare,
		__drawcircle
	};
	return drawshape[type];
}

graphic *initGraphic(stype type, bool drawable, ...){
	graphic *g = malloc(sizeof(graphic));
	g->type = type;
	g->drawable = drawable;

	float coords[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	// typundef, typpoint, typline, typtri, typquad, typsqr, typcircle
	int coordnum[] = {0, 2, 4, 6, 8, 4, 4};
	va_list list;
	va_start(list, drawable);
	for(int i = 0; i < coordnum[type]; i++){
		coords[i] = (float)va_arg(list, int);
	}
	va_end(list);
	
	g->shape = initshape(type, coords);
	g->free = __freegraphic;
	g->draw = drawshape(type);

	//printf("graphic made, obj id: %d, type: %d @ x: %f, y: %f\n", ((object *)((generic_data_shape *)g->shape)->item->data)->id, ((object *)((generic_data_shape *)g->shape)->item->data)->t, coords[0], coords[1]);
	addToList(&(Graphics[g->type]), g);
	//printf("graphic added to list\n");
	return g;
}

void __freegraphic(void *VP_self){
	graphic *self = VP_self;
	generic_data_shape *shape = (self->shape);
	shape->free(shape->item);	// free shape
	free(self);
}

void freeGraphicsList(void){
	// free shapes from object list
	printf("cleaning up %d objects\n", count_arr());
	for(int i = 0; i < NUMOFSHAPETYPES; i++){
		FreeList(Graphics[i], __freegraphic);
		Graphics[i] = NULL;
	}
}

void __drawpoint(void *self){
	data_point *p = (data_point *)((graphic *)self)->shape;
	S2D_DrawCircle(p->x, p->y, 5, 3, p->c.r, p->c.g, p->c.b, p->c.a);
}

void __drawline(void *self){
	data_line *l = (data_line *)((graphic *)self)->shape;
	S2D_DrawLine(l->points[0]->x, l->points[0]->y, l->points[1]->x, l->points[1]->y, 
		l->width, 
		l->points[0]->c.r, l->points[0]->c.g, l->points[0]->c.b, l->points[0]->c.a,
		l->points[0]->c.r, l->points[0]->c.g, l->points[0]->c.b, l->points[0]->c.a,
		l->points[1]->c.r, l->points[1]->c.g, l->points[1]->c.b, l->points[1]->c.a,
		l->points[1]->c.r, l->points[1]->c.g, l->points[1]->c.b, l->points[1]->c.a);
}

void __drawtriangle(void *self){
	data_triangle *t = (data_triangle *)((graphic *)self)->shape;
	S2D_DrawTriangle(
		t->points[0]->x, t->points[0]->y, t->points[0]->c.r, t->points[0]->c.g, t->points[0]->c.b, t->points[0]->c.a,
		t->points[1]->x, t->points[1]->y, t->points[1]->c.r, t->points[1]->c.b, t->points[1]->c.g, t->points[1]->c.a,
		t->points[2]->x, t->points[2]->y, t->points[2]->c.r, t->points[2]->c.b, t->points[2]->c.g, t->points[2]->c.a);
}

void __drawquad(void *self){
	data_quad *s = (data_quad *)((graphic *)self)->shape;
	S2D_DrawQuad(
		s->points[0]->x, s->points[0]->y, s->points[0]->c.r, s->points[0]->c.g, s->points[0]->c.b, s->points[0]->c.a,
		s->points[1]->x, s->points[1]->y, s->points[1]->c.r, s->points[1]->c.g, s->points[1]->c.b, s->points[1]->c.a,
		s->points[2]->x, s->points[2]->y, s->points[2]->c.r, s->points[2]->c.g, s->points[2]->c.b, s->points[2]->c.a,
		s->points[3]->x, s->points[3]->y, s->points[3]->c.r, s->points[3]->c.g, s->points[3]->c.b, s->points[3]->c.a
	);
}

void __drawsquare(void *self){
	data_square *s = (data_square *)((graphic *)self)->shape;
	S2D_DrawQuad(
		s->points[0]->x			  , s->points[0]->y				, s->points[0]->c.r, s->points[0]->c.g, s->points[0]->c.b, s->points[0]->c.a,
		s->points[0]->x + s->width, s->points[0]->y				, s->points[0]->c.r, s->points[0]->c.g, s->points[0]->c.b, s->points[0]->c.a,
		s->points[0]->x	+ s->width, s->points[0]->y + s->height	, s->points[0]->c.r, s->points[0]->c.g, s->points[0]->c.b, s->points[0]->c.a,
		s->points[0]->x			  , s->points[0]->y + s->height	, s->points[0]->c.r, s->points[0]->c.g, s->points[0]->c.b, s->points[0]->c.a
	);
}

void __drawcircle(void *self){
	data_circle *c = (data_circle *)((graphic *)self)->shape;
	S2D_DrawCircle(c->points[0]->x, c->points[0]->y, c->radius, c->sectors, c->points[0]->c.r, c->points[0]->c.g, c->points[0]->c.b, c->points[0]->c.a);
}

void set_color(S2D_Color *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	c->r = MapToScale(r, 255);
	c->g = MapToScale(g, 255);
	c->b = MapToScale(b, 255);
	c->a = MapToScale(a, 255);
}