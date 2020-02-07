#include "gamehandler.h"


void render(){
	for(int i = typUndef+1; i < NUMOFSHAPETYPES; i++){
		List *Items2Draw = Graphics[i];
		while(Items2Draw){
			graphic *g = (graphic *)Items2Draw->data;
			g->draw(g);
			Items2Draw = Items2Draw->tail;
		}
	}
}

void update(){
	if(Flags.ReInitObjList){
		freeGraphicsList();
		OBJ_initList();
		Flags.Flags = 0;
	}
	if(Flags.MouseDown && Flags.MouseMoved){
		if(Flags.Point2Placed){
			initGraphic(typLine, true, 
				window->mouse.x, window->mouse.y, 
				(int)(((data_point *)((graphic *)Graphics[typPoint]->data)->shape)->x),
				(int)(((data_point *)((graphic *)Graphics[typPoint]->data)->shape)->y));
			//Flags.Point2Placed = 0;
		}
		else{
			Flags.Point2Placed = 1;
		}
		initGraphic(typPoint, true, window->mouse.x, window->mouse.y);
		Flags.MouseMoved = 0;
	}
	else if(Flags.MouseDown){
		initGraphic(typPoint, true, window->mouse.x, window->mouse.y);
	}
}


// events

void on_key(S2D_Event e){
	if(e.type != S2D_KEY_DOWN) return;
	if(strcmp(e.key, "Delete") == 0){
		Flags.ReInitObjList = 1;
	}
	if(strcmp(e.key, "Escape") == 0){
		S2D_Close(window);
	}
}

void on_mouse(S2D_Event e){
	if(e.type == S2D_MOUSE_MOVE){
		Flags.MouseMoved = 1;
	}
	if(e.type == S2D_MOUSE_UP){
		if(e.button == S2D_MOUSE_LEFT){
			Flags.MouseDown = 0;
			return;
		}
	}
	// mouse down
	if(e.type == S2D_MOUSE_DOWN){
		if(e.button == S2D_MOUSE_LEFT){
			Flags.MouseDown = 1;
		}
		if(e.button == S2D_MOUSE_RIGHT){
			#ifdef blabla
			for(int i = 1; i < NUMOFOBJTYPES; i++){
				printf("amount object type %d: %d\n", i, OBJ_ListCount[i]);
			}
			printf("total amount of objects: %d\n", count_arr());
			#endif
		}
	}
}