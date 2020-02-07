// $ export DISPLAY=localhost:0

#include "init.h"

int main() {
	init(&Flags.Flags);
	printf("initialisation finished\nshowing window\n");
	S2D_Show(window);

	S2D_FreeWindow(window);
	freeGraphicsList();

	return 0;
}


