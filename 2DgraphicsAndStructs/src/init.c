#include "init.h"

void init(){
	Flags.Flags = 0;
	
	printf("initialising ItemList...\n");
	OBJ_initList();

	printf("initialising GraphicList...\n");
	initGraphicList();

	printf("initialising window...\n");
	windowinit();
	graphic *g = initGraphic(typTri, true, 150, 0, 0, 300, 300, 300);
	for(int i = 0; i < 3; i++){
		((data_triangle *)g->shape)->points[0]->c.r = 255;
	} 
	
}

void windowinit(){
	window = S2D_CreateWindow(
		"test",  // title of the window
		WIDTH, HEIGHT,        // width and height
		update, render,  // callback function pointers (these can be NULL)
		S2D_HIGHDPI      // flags
	);
	window->viewport.mode = S2D_FIXED;
	window->on_key = on_key;
	window->on_mouse = on_mouse;
	set_color(&window->background, 255, 255, 255, 255);
	window->fps_cap = 30;
}