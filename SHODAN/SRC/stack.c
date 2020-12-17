
#include "../shodan.h"

/**********/
SStack* StackInit()
{
	return ArrayInit();
}

/**********/
void StackClose(SStack** stack)
{
	ArrayClose(stack);
}

/**********/
bool StackEmpty(SStack* stack)
{
	return stack->size == 0;
}

/**********/
void StackPush(SStack* stack, void* item)
{
	ArrayAdd(stack, item);
}

/**********/
void* StackPop(SStack* stack)
{
	if (stack->size == 0) { Log(__func__, "Stack is empty"); return NULL; };

	return ArrayRemove(stack, stack->size - 1);
}

/**********/
void* StackTop(SStack* stack)
{
	if (stack->size == 0) { Log(__func__, "Stack is empty"); return NULL; };

	return ArrayGet(stack, stack->size - 1);
}

