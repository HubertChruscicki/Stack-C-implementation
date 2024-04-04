#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"


void* Initialzation_Data(char* SSurname, int YYear, enum Field_Of_Study MMajor) 
{
	Student* pData = (Student*)malloc(sizeof(Student));			
	
	if (!pData)													
	{
		Message(MESS_MEM_ALOC_ERROR);								
		return NULL;											
	}
	else														
	{
		size_t Len = strlen(SSurname) + 1;
		pData->Length = Len;
		pData->Surname = (char*)malloc(Len * sizeof(char)); 
		if (!pData->Surname)									
		{
			Message(MESS_MEM_ALOC_ERROR);								
			return NULL;											
		}
		strcpy(pData->Surname, SSurname);						
		pData->Year = YYear;									
		pData->Major = MMajor;
	}
	return(void*)(pData);
}

void* Push_Data(char* SSurname, int YYear, enum Field_Of_Study MMajor)
{
	return Initialzation_Data(SSurname, YYear, MMajor);			
}

void Free_Data(void* Ptr)										
{																
	Student* pData = (Student*)Ptr;								
	if (pData)													
	{
		free(pData->Surname);									
		pData->Surname = NULL;									
		free(pData);
		pData = NULL;
	}

}
void Print_Data(void* Ptr)
{
	Student* Temp = (Student*)Ptr;									
	if (Temp)
	{
		printf("%s\n",Temp->Surname);								
		printf("%d\n", Temp->Year);								
		switch (Temp->Major)										
		{
		case COMPUTER_SCIENCE:
			printf("Computer Science\n"); 
			break;
		case MATHS:
			printf("Math\n");
			break;
		case ROBOTICS:
			printf("Robotics\n");
			break;
		case PHYSICS:
			printf("Physics\n");
			break;

		default:
			break;
		}
	}
}

int Surname_Data(void* Current_Data_Ptr, void* Search_Data_Ptr)
{
	Student* pCurrent = (Student*)Current_Data_Ptr;				
	Student* pSearch = (Student*)Search_Data_Ptr;				

	if (strcmp(pCurrent->Surname, pSearch->Surname) == 0)		
		return 1;												
	else
		return 0;												
}

int Year_Data(void* Current_Data_Ptr, void* Search_Data_Ptr)
{
	Student* pCurrent = (Student*)Current_Data_Ptr;				
	Student* pSearch = (Student*)Search_Data_Ptr;				

	if (pCurrent->Year == pSearch->Year)						
		return 1;												
	else
		return 0;												
}


int Field_Of_Study_Data(void* Current_Data_Ptr, void* Search_Data_Ptr)
{
	Student* pCurrent = (Student*)Current_Data_Ptr;				
	Student* pSearch = (Student*)Search_Data_Ptr;				

	if (pCurrent->Major == pSearch->Major)						
		return 1;												
	else
		return 0;												
}

int Save_Data(void* Ptr, FILE* File_Name)
{
	Student* pData = (Student*)Ptr;

	if (fwrite(pData, sizeof(Student), 1, File_Name) != 1)
		return 0;
	if (fwrite(pData->Surname, pData->Length * sizeof(char), 1, File_Name) != 1)										
		return 0;
		

	return 1;
}

void* Load_Data(FILE* File_Name)
{
	Student* pData = (Student*)malloc(sizeof(Student));       
	
	if (!pData)    
	{
		File_Message(MESS_FILE_ERROR, pData,  File_Name);
	}
	else
	{
		memset(pData, 0, sizeof(Student));								

		if (fread(pData, sizeof(Student), 1, File_Name) != 1)
			return 0;

		pData->Surname = (char*)malloc(pData->Length * sizeof(char)); 
		if (!(pData->Surname))
		{
			File_Message(MESS_FILE_ERROR, pData->Surname, File_Name);
		}

		if (fread(pData->Surname, pData->Length * sizeof(char), 1, File_Name) != 1)									
			return 0;
	


		void* tmpData = Push_Data(pData->Surname, pData->Year, pData->Major);
		
		if (pData)
		{
			free(pData);
		}
		
		return tmpData;
	}
}