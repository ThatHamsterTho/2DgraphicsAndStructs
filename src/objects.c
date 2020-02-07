#include "objects.h"

// List functions
// Initialises a list
List *initList(void){
	return NULL;
}

void addToList(List **TheList, void *data){
	ListItem *LI = malloc(sizeof(ListItem));
	LI->data = data;
	LI->free = FreeFromList;

	// linkage
	if(*TheList){		
		LI->tail = (*TheList);
		LI->head = 0;				// list ender
		(*TheList)->head = LI;
		(*TheList) = LI;
		LI->id = (*TheList)->id;
	}
	else{
		// first item in list
		LI->tail = 0;
		LI->head = 0;
		LI->id = 0;
		(*TheList) = LI;
	}
	(*TheList)->id++;
}

// FR should equal to free() or a specific Free routine
// FR specific Free routine should also free the data void pointer
void FreeFromList(void *VP_Item, FreeRoutine FR){
	ListItem *Item = VP_Item;
	List *TheList = Item;
	while(TheList->head){
		TheList = TheList->head;
	}

	if(Item->head && Item->tail){
		Item->head->tail = Item->tail;	// next item's prev-conn is item's prev-conn
		Item->tail->head = Item->head;	// prev item's next-conn is item's next-conn
	}
	// no tail but there is a head
	else if(Item->head){
		Item->head->tail = 0;
	}
	// no head but there is a tail
	else if(Item->tail){
		TheList = Item->tail;	// set list back one element
		Item->tail->head = 0;		// remove head of previous link
	}
	// no head or tail
	else{
		TheList = NULL;
	}
	if(FR){
		FR(Item->data);
	}
	free(Item);
}

// FR should equal to free() or a specific Free routine
// FR specific Free routine should also free the data void pointer
void FreeList(List *TheList, FreeRoutine FR){
	int i = 1;
	while(TheList){
		if(FR){
			// rule: FreeRoutine does NOT free the data void *
			FR(TheList->data);
		}
		ListItem *temp = TheList;
		TheList = TheList->tail;
		free(temp);
		i++;
	}
}

// object functions

// initialises list
void OBJ_initList(){
	for(int i = 0; i < NUMOFOBJTYPES; i++){
		OBJ_List[i] = initList();
		OBJ_ListID[i] = 0;
		OBJ_ListCount[i] = 0;
	}
}

object *initObject(void *data, otype type){
	object *obj = malloc(sizeof(object));	// malloc a new object
	obj->data = data;						// set object pointer
	obj->t = type;							// set object type
	obj->id = OBJ_ListID[type];				// set obj id
	
	obj->free = freeObject;

	OBJ_ListID[type]++;						// set amount of (type) objects up
	OBJ_ListCount[type]++;

	return obj;
}

void freeObject(void *VP_obj){
	object *obj = VP_obj;
	OBJ_ListCount[obj->t]--;
	free(obj);
}

// debug tool
unsigned int count_arr(){
	unsigned int objCount = 0;
	for(int i = 0; i < NUMOFOBJTYPES; i++){
		objCount += OBJ_ListCount[i];
	}
	return objCount;
}