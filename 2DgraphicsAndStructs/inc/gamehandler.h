#ifndef graphicHEADER
#define graphicHEADER
#include "shapehandler.h"

#define WIDTH 800
#define HEIGHT 600

typedef union __updateFLAGS__ {
	struct {
		unsigned int ReInitObjList		: 1; 
		unsigned int MouseDown			: 1;
		unsigned int MouseMoved			: 1;
		unsigned int Point2Placed		: 1;
	};
	unsigned int Flags;
} uFLAGS;

uFLAGS Flags;
int old_mousex;
int old_mousey;

void render();
void update();
void on_key(S2D_Event e);
void on_mouse(S2D_Event e);

S2D_Window *window;



#endif