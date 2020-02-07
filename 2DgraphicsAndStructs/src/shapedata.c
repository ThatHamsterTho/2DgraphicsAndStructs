#include "shapedata.h"

// do NOT use this function
void *__initundef(float coords[8]){
	coords[0] = 0;
	return NULL;
}

// init a point Ax, Ay
void *initpoint(float coords[8]){
	data_point *p = malloc(sizeof(data_point));
	p->x = coords[0];
	p->y = coords[1];
	p->c.r = 0;
	p->c.g = 0;
	p->c.b = 0;
	p->c.a = 1;
	
	
	p->free = __freeshape;
	p->point_num = 0;
	addToList(&(OBJ_List[typPoint]), initObject(p, typPoint));
	p->item = OBJ_List[typPoint];

	return p;
}

// init a line Ax, Ay, Bx, By
void *initline(float coords[8]){
	/* P1----P2	*/
	data_line *l = malloc(sizeof(data_line));							// get enough space for l
	l->points[0] = (data_point *)initpoint(coords);						// init data_point a
	l->points[1] = (data_point *)initpoint(coords+2);					// init data_point b
	l->width = 1;														// set default width

	l->free = __freeshape;												// set cleanup function
	l->point_num = 2;
	addToList(&(OBJ_List[typLine]), initObject(l, typLine));
	l->item = OBJ_List[typLine];

	return l;
}

// init a triangle Ax, Ay, Bx, By, Cx, Cy
void *inittriangle(float coords[8]){
	/*	   a	-|
		  / \	 | H
		 b - c	-|

		 |___|
		   L 	 */
	data_triangle *t = malloc(sizeof(data_triangle));			// get space for triangle
	t->points[0] = (data_point *)initpoint(coords);				// init data_point A
	t->points[1] = (data_point *)initpoint(coords+2);			// init data_point B
	t->points[2] = (data_point *)initpoint(coords+4);			// init data_point C
	
	t->free   = __freeshape;
	t->point_num = 3;
	addToList(&(OBJ_List[typTri]), initObject(t, typTri));
	t->item = OBJ_List[typTri];

	return t;
}

// init a quad Ax, Ay, Bx, By, Cx, Cy, Dx, Dy
void *initquad(float coords[8]){
	data_quad *q = malloc(sizeof(data_square));
	/* 	A--B
		|  |
		D--C */
	q->points[0] = (data_point *)initpoint(coords);
	q->points[1] = (data_point *)initpoint(coords+2);
	q->points[2] = (data_point *)initpoint(coords+4);
	q->points[3] = (data_point *)initpoint(coords+6);

	q->free	  	 = __freeshape;
	q->point_num = 4;
	addToList(&(OBJ_List[typQuad]), initObject(q, typQuad));
	q->item = OBJ_List[typQuad];

	return q;
}

// init a square Ax, Ay, width, height
void *initsquare(float coords[8]){
	data_square *s = malloc(sizeof(data_square));
	/* 	A--B
		|  |
		D--C */
	s->points[0] = (data_point *)initpoint(coords);
	s->width  = coords[2];
	s->height = coords[3];

	s->free	  = __freeshape;
	s->point_num = 1;
	addToList(&(OBJ_List[typSqr]), initObject(s, typSqr));
	s->item = OBJ_List[typSqr];

	return s;
}

// init a circle Ax, Ay, radius, sectors
void *initcircle(float coords[8]){
	data_circle *c = malloc(sizeof(data_circle));
	c->points[0] = (data_point *)initpoint(coords);
	c->radius = coords[2];
	c->sectors = (int)coords[3];

	c->free = __freeshape;
	c->point_num = 1;
	addToList(&(OBJ_List[typCirc]), initObject(c, typCirc));
	c->item = OBJ_List[typCirc];

	return c;
}



// gen_shape & memory functions

// default free function for every shape
#ifndef FREEDEBUGGER
	void __freeshape(ListItem *item){
		generic_data_shape *shape = ((object *)item->data)->data;
		for(unsigned int i = 0; i < shape->point_num; i++){
			// remove data_point from link and free data_point object
			object *obj = shape->points[i]->item->data;
			shape->points[i]->item->free(shape->points[i]->item, obj->free);
			// free data_point struct
			free(shape->points[i]);		  			
		}
		// remove shape from link and free shape object
		item->free(item, ((object *)item->data)->free);
		// free shape struct
		free(shape);
	}
#else
	void __freeshape(ListItem *item){
		generic_data_shape *shape = ((object *)item->data)->data;
		printf("id: %d, type: %d, shape has %d points\n", ((object *)item->data)->id, ((object *)item->data)->t, shape->point_num);
		for(unsigned int i = 0; i < shape->point_num; i++){
			OBJ_freeItem(shape->points[i]->item);	// free data_point from link
			free(shape->points[i]);		  			// free data_point
			printf("data_point %d freed\n", i);
		}
		OBJ_freeItem(item);	// free obj from list
		printf("object freed from list\n");
		free(shape);		// free shape
		printf("shape freed\n");
	}
#endif

// free's shapes from object list
void freeShapesFromObjList(){
	for(int i = typLine; i < NUMOFSHAPETYPES; i++){
		while(OBJ_List[i]){
			ListItem *o = OBJ_List[i]->tail;
			__freeshape(OBJ_List[i]);
			OBJ_List[i] = o;
		}
	}
	for(int i = typUndef; i < typPoint; i++){
		while(OBJ_List[typPoint]){
			ListItem *o = OBJ_List[i]->tail;
			__freeshape(OBJ_List[i]);
			OBJ_List[i] = o;
		}
	}
}