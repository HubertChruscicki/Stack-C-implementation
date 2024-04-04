#pragma once

#ifndef INTERFACE__H
#define INTERFACE__H


enum INTERFACE
{
	INTERFACE_STACK_DISPLAY,
	INTERFACE_PUSH,
	INTERFACE_POP,
	INTERFACE_CLEAR,
	INTERFACE_FIND,
	INTERFACE_SAVE,
	INTERFACE_LOAD,
	INTERFACE_EXIT,
	INTERFACE_ELEMENTS_NUMBER
};


enum SEARCH_DATA
{
	SURNAME_SEARCH,
	YEAR_SEARCH,
	FIELD_OF_STUDY_SEARCH,
	SEARCH_ELEMENTS_NUMBER
};

int Secure_Option_Input(int First_Option, int Last_Option);
int Secure_Year_Input(int Min_Year, int Max_Year);
int Secure_Major_Input(int First_Major, int Last_Major);
void Menu_Print();
void Fields_Print();
void Search_Menu_Print();
void Display();
void Push();
void Pop();
void Clear();
void Clear_Exit();
void Find();
void Save();
void Load();



#endif