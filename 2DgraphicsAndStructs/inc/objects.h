#ifndef objectHEADER
#define objectHEADER

#include <stdlib.h>
#include <stdio.h>

//#define FREEDEBUGGER

typedef enum __shapetype__ {
	typUndef,
	typPoint,
	typLine,
	typTri,
	typQuad,
	typSqr,
	typCirc,
	// do not use
	typShapeCounter
} stype;

typedef enum __objtype__ {
	typGraphic = typShapeCounter,
	// do not use
	typObjCounter
} otype;

enum NUMOFOBJTYPES {
	NUMOFSHAPETYPES = typShapeCounter, 
	NUMOFOBJTYPES = typObjCounter
};

// Functionpointer of type: void FreeRoutine(void *data);
// the data pointer is passed from the ItemList
typedef void (*FreeRoutine)(void *data);

typedef struct __ListItem__ {
	void *data;
	void (*free)(void *Item, FreeRoutine FR);
	struct __ListItem__ *head;
	struct __ListItem__ *tail;
	unsigned int id;
} ListItem;

typedef ListItem List;

typedef struct __object__ {
	otype t;					// stores type of object
	void *data;					// stores the object address
	unsigned int id;			// stores the id of the object
	void (*free)(void *VP_obj);	// free function for objects
} object;

List 		*OBJ_List[NUMOFOBJTYPES];
unsigned int OBJ_ListID[NUMOFOBJTYPES];
unsigned int OBJ_ListCount[NUMOFOBJTYPES];

void OBJ_initList();

object *initObject(void *data, otype type);
void 	freeObject(void *VP_obj);
unsigned int count_arr();

List *initList(void);
void addToList(List **TheList, void *data);
void FreeFromList(void *VP_Item, FreeRoutine FR);
void FreeList(List *TheList, FreeRoutine FR);

#endif