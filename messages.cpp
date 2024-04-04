#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"


static const char* My_Message[] = 
{
	"E Memory allocation error	",	    
	"W Stack is empty			",		
	"E Fatal Error				",      
	"E File Error				",		
	"W Stack Cleared			",
	"W Program Exited			"
};

void Message(enum Messages_List mess)

{
	puts(My_Message[mess] + 1); 


	if (My_Message[mess][0] == 'E')
	{
		Free_Stack();  
	}
}


void File_Message(enum Messages_List mess, void* pos, FILE* ptrFile)
{
	
	if (ptrFile)
	{
		fclose(ptrFile);
	}
	
	puts(My_Message[mess] + 1);


	if (My_Message[mess][0] == 'E')
	{
		Free_Stack();
	}

	if (pos)
	{
		free(pos);
	}

	Message(MESS_FILE_ERROR);
	exit(1);
}