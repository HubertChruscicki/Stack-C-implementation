#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"

static Stack* Top_Element = NULL;
char Name_Of_File[] = "file.bin";
Empty_Data P_Empty_Data;
Print_Element display;
File Save_File;
load Load_File;


void Initialzation_Stack(Empty_Data ptr, Print_Element DDisplay, File SSave, load LLoad)
{
	Top_Element = NULL;
	P_Empty_Data = ptr;
	display = DDisplay;
	Save_File = SSave;
	Load_File = LLoad;
}

void Display_Stack()
{
	Stack* Temp = Top_Element;
	if (Temp != NULL)
	{
		printf("Stack elements\n");
		printf("\n");
		while (Temp != NULL)
		{
			display(Temp->pdata);
			printf("\n");
			Temp = Temp->Next_Element;

		}
		printf("\n");
	}
	else
	{
		printf("\n");
		Message(MESS_EMPTY_STACK);
	}
}

Stack* Push_Stack(void* ptrData)
{
	Stack* Next = (Stack*)malloc(sizeof(Stack));
	if (!Next)
	{
		Message(MESS_MEM_ALOC_ERROR);
		return NULL;
	}
	else
	{ 
	Next->pdata = ptrData;
	Next->Next_Element = Top_Element;
	Top_Element = Next;
	return Next;
	}
}

void* Pop_Stack()
{
	Stack Pop;
	if (!Top_Element)
	{
		Message(MESS_EMPTY_STACK);
		return NULL;
	}
	else
	{
		Stack* Next = Top_Element->Next_Element;
		Pop.pdata = Top_Element->pdata;
		free(Top_Element);
		Top_Element = Next;
		return Pop.pdata;
	}
}

void Free_Stack()
{
	Stack* Ptr = Top_Element;
	Stack* Temp = NULL;
	while (Ptr) 
	{
		(*P_Empty_Data)(Ptr->pdata);
		Temp = Ptr;
		Ptr = Ptr->Next_Element;
		free(Temp);
	}
	Top_Element = NULL;
}

void* Search_Stack(void* Search_Data, find search_ptr, int if_first)
{
	static Stack* Ptr;						
	Stack* Temp = NULL;
	if (Top_Element == NULL)
	{
		Message(MESS_EMPTY_STACK);
		return NULL;
	}
	
	if (if_first)
	{
		Ptr =Top_Element;
	}

		while (Ptr)
		{
			if (!(*search_ptr)(Ptr->pdata, Search_Data))
			{
				Ptr = Ptr->Next_Element;
			}
			else
			{
				Temp = Ptr;
				Ptr = Ptr->Next_Element;
				return Temp->pdata;
			}
		}
	
	return NULL;
}




void Save_Stack()
{
	Stack* Temp = Top_Element;
	if (Temp == NULL)
	{
		Message(MESS_EMPTY_STACK);
		return;
	}
			
		
		size_t elements = 0;    			   
		FILE* file = fopen(Name_Of_File, "wb");
		if (!file)
		{
			File_Message(MESS_FILE_ERROR, NULL, file);
		}
		
		while(Temp != NULL) {
			Temp = Temp->Next_Element;
			elements++;
		}

		fwrite(&elements, sizeof(size_t), 1, file);
		
		int check = fseek(file, elements * sizeof(size_t), SEEK_CUR);
		if(check != 0) 
		{
			return;
		}
		size_t* filePosition = NULL;
		filePosition = (size_t*)malloc(elements * sizeof(size_t));
		if (!filePosition)
		{
			File_Message(MESS_MEM_ALOC_ERROR, filePosition, file);
		}

		Temp = Top_Element;
		int pos = 0;

		while(Temp != NULL) { 
			filePosition[pos] = ftell(file);
			pos++;
			if (Save_Data(Temp->pdata, file) != 1)
			{
				File_Message(MESS_MEM_ALOC_ERROR, filePosition, file);
			}
			Temp = Temp->Next_Element;
		}
		fseek(file, sizeof(size_t), SEEK_SET);

		fwrite(filePosition, sizeof(size_t), elements+1,file); 

		if (file)
		{
			printf("Data saved\n");
			fclose(file);
			file = NULL;
		}
		if (filePosition)
		{
			free(filePosition);
		}
}

void Load_Stack()
{
	Free_Stack();
	size_t elements = 0;

	FILE* file = fopen(Name_Of_File, "rb");
	if (!file)
	{
		File_Message(MESS_FILE_ERROR,NULL, file);
	}

	fread(&elements, sizeof(elements), 1, file);

	size_t* filePosition = (size_t*)malloc(elements * sizeof(size_t));
	if (!filePosition)
	{
		File_Message(MESS_MEM_ALOC_ERROR, filePosition, file);
	}

	
	for (int i = 0; i < elements;i++)
	{ 
		fread(&filePosition[i], sizeof(size_t), 1, file);
	}
	
	for(int i=elements-1;i>=0;i--) 
	{
		fseek(file, filePosition[i], SEEK_SET);
		void* data = Load_File(file);
		if (!Push_Stack(data))
		{
			File_Message(MESS_MEM_ALOC_ERROR, filePosition, file);
		}
	}
	if (file) 
	{
		fclose(file);
		file = NULL;
	}
	if (filePosition)
	{
		free(filePosition);
	}
}
