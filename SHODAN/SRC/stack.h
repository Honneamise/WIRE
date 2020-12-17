#ifndef STACK_H
#define STACK_H

//stack
typedef SArray SStack;

/**********/
SStack* StackInit();

void StackClose(SStack** stack);

bool StackEmpty(SStack* stack);

void StackPush(SStack* stack, void* item);

void* StackPop(SStack* stack);

void* StackTop(SStack* stack);

#endif