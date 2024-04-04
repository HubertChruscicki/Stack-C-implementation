#pragma once

#ifndef MESSAGES__H
#define MESSAGES__H	

enum Messages_List
{
	MESS_MEM_ALOC_ERROR,        
	MESS_EMPTY_STACK,			
	MESS_FATAL_ERROR,			
	MESS_FILE_ERROR,			
	MESS_STACK_CLEARED,
	MESS_EXIT,
	MESS_ELEMENTS_NUMBER
};

void Message(enum Messages_List Mess);
void File_Message(enum Messages_List mess, void* pos, FILE* ptrFile);

#endif