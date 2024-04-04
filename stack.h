#pragma once

#ifndef STACK__H
#define STACK__H

#pragma warning (disable : 4996)


struct Stack 
{
	void* pdata;					
	struct Stack* Next_Element;		
};

typedef void(*Empty_Data)(void* pdat);
typedef void(*Print_Element)(void* pdat);
typedef int(*File)(void* pdat, FILE* file);
typedef void* (*load)(FILE* file);								
typedef int(find)(void* Current_Data, void* Search_Data);		

void Initialzation_Stack(Empty_Data ptr, Print_Element display, File save, load load);
void Display_Stack();
Stack* Push_Stack(void* ptrData);
void* Pop_Stack();
void Free_Stack();
void* Search_Stack(void* Search_Data, find search_ptr, int if_first);
void Save_Stack();
void Load_Stack();

#endif