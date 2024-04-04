#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"

#pragma warning (disable : 4996)

const static char* Menu[] =
{
	"						",
	"0 - Display the stack	",
	"1 - Push				",
	"2 - Pop				",
	"3 - Clear				",
	"4 - Find in stack		",
	"5 - Save to file		",
	"6 - Load from file		",
	"7 - Exit				"
};

const static char* Fields_List[]
{
	"0 - Computer Science",
	"1 - Maths",
	"2 - Robotics",
	"3 - Physics"
};

const static char* Search_List[]
{
	"0 - Surname",
	"1 - Year",
	"2 - Field of study"
};

int Secure_Option_Input(int First_Option, int Last_Option)
{
	int Option, input = 1;

	while (input) {
		if (scanf("%d", &Option) == 1 && Option >= First_Option && Option < Last_Option)
			input = 0;
		else
		{
			printf("Wrong option input, try again: ");
		}

		while (getchar() != '\n'); 
	}

	return Option;
}

int Secure_Year_Input(int Min_Year, int Max_Year)
{
	int Year, input = 1;

	while (input) {
		if (scanf("%d", &Year) == 1 && Year >= Min_Year && Year <= Max_Year)
			input = 0;
		else
		{
			printf("Wrong Year input, try again: ");
		}

		while (getchar() != '\n'); 
	}

	return Year;
}

int Secure_Major_Input(int First_Major, int Last_Major)
{
	int Major, input = 1;

	while (input) {
		if (scanf("%d", &Major) == 1 && Major >= First_Major && Major < Last_Major)
			input = 0;
		else
		{
			printf("Wrong field of study input, try again: ");
		}

		while (getchar() != '\n'); 
	}

	return Major;
}

void Menu_Print()
{
	size_t i;
	for (i = 0; i < INTERFACE_ELEMENTS_NUMBER+1; i++)
	{
		printf("%s\n", Menu[i]);
	}
}

void Fields_Print()
{
	size_t i;
	for (i = 0; i < FIELDS_OF_STUDY_ELEMENTS_NUMBER; i++)
	{
		printf("%s\n", Fields_List[i]);
	}

}

void Search_Menu_Print()
{
	size_t i;
	for (i = 0; i < SEARCH_ELEMENTS_NUMBER; i++)
	{
		printf("%s\n", Search_List[i]);
	}

}

void Display()
{
	system("cls");
	Display_Stack();
	system("PAUSE");
	system("cls");
}

void Push()
{
	char Surname_Buff[256];
	int Year, Major;
	system("cls");
	printf("\nSurname: ");
	scanf_s("%s", Surname_Buff, sizeof(Surname_Buff));
	printf("Year: ");
	Year = Secure_Year_Input(0,3000); //mozemy tu zmienic zakres
	Fields_Print();
	printf("Field of study: ");
	Major = Secure_Major_Input(COMPUTER_SCIENCE,FIELDS_OF_STUDY_ELEMENTS_NUMBER);
	printf("\n");
	
	void* pData = Push_Data(Surname_Buff, Year, (Field_Of_Study)Major);
	Push_Stack(pData);
	system("cls");

}

void Pop()
{
	system("cls");
	void* Temp = Pop_Stack();
	if (Temp != NULL)
	{

		printf("\nPopped:\n");
		Print_Data(Temp);
		printf("\n");
	}
	Free_Data(Temp);
	system("PAUSE");
	system("cls");
}

void Clear()
{
	Free_Stack();
	system("cls");
	Message(MESS_STACK_CLEARED);
	system("PAUSE");
	system("cls");
}

void Clear_Exit()
{
	Free_Stack();
	system("cls");
	Message(MESS_EXIT);
}

void Find() 
{
	int Option = 0;
	system("cls");
	printf("Find by:\n");
	Search_Menu_Print();
	printf("\nChoose your option: ");
	Option = Secure_Option_Input(SURNAME_SEARCH, SEARCH_ELEMENTS_NUMBER);
	system("cls");

	Student* Temp = (Student*)malloc(sizeof(Student));
	if (!Temp)
	{
		Message(MESS_MEM_ALOC_ERROR);
		return;
	}
	else
	{
		memset(Temp, 0, sizeof(Student));
		size_t Length;
		void* Ptr;
		switch (Option)
		{
		case SURNAME_SEARCH:
			char Surname_Buff[256];
			printf("Surname: ");
			scanf_s("%s", Surname_Buff, sizeof(Surname_Buff));
			Length = strlen(Surname_Buff) + 1;
			Temp->Surname = (char*)malloc(Length * sizeof(char));
			if (!Temp->Surname)
			{
				Message(MESS_MEM_ALOC_ERROR);
				return;
			}
			else
			{
				system("cls");
				strcpy(Temp->Surname, Surname_Buff);
				Ptr = Search_Stack(Temp, Surname_Data, 1);
				if (Ptr)
				{
					printf("Found:\n\n");
					Print_Data(Ptr);
					printf("\n");
				}
				else
				{

					printf("Nothing Found\n");
				}
				while (Ptr)
				{
					Ptr = Search_Stack(Temp, Surname_Data, 0);
					if (Ptr)
					{
						Print_Data(Ptr);
						printf("\n");
					}
				}

				printf("\n");
				Free_Data(Temp);

			}
			break;
		
		/////////////////////////////////////////////////////////////////
		
		case YEAR_SEARCH:
			int Year_Buff;
			printf("Year: ");
			Year_Buff = Secure_Year_Input(0, 3000);

			Temp->Year = Year_Buff;
			Ptr = Search_Stack(Temp, Year_Data, 1);
			system("cls");
			if (Ptr)
			{
				printf("Found:\n\n");
				Print_Data(Ptr);
				printf("\n");
			}
			else
			{

				printf("Nothing Found\n");
			}
			while (Ptr)
			{
				Ptr = Search_Stack(Ptr, Year_Data, 0);
				if (Ptr)
				{
					Print_Data(Ptr);
					printf("\n");
				}
			}

			printf("\n");
			Free_Data(Temp);
			break;

		//////////////////////////////////////////////////////////////////
		
		case FIELD_OF_STUDY_SEARCH:
			int Major_Buff;
			Fields_Print();
			printf("Field of study: ");
			Major_Buff = Secure_Major_Input(COMPUTER_SCIENCE, FIELDS_OF_STUDY_ELEMENTS_NUMBER);

			Temp->Major = (Field_Of_Study)Major_Buff;
			Ptr = Search_Stack(Temp, Field_Of_Study_Data, 1);
			system("cls");
			if (Ptr)
			{
				printf("Found:\n\n");
				Print_Data(Ptr);
				printf("\n");
			}
			else
			{

				printf("Found:\n\n");
			}
			while (Ptr)
			{
				Ptr = Search_Stack(Temp, Field_Of_Study_Data, 0);
				if (Ptr)
				{
					Print_Data(Ptr);
					printf("\n");
				}
			}
			printf("\n");
			Free_Data(Temp);
			break;

		default:
			printf("Input Error\n");
		};
		system("PAUSE");
		system("cls");
	}

}


void Save()
{
	system("cls");
	Save_Stack();
	system("PAUSE");
	system("cls");
}


void Load()
{
	system("cls");
	Load_Stack();
	printf("Data loaded\n");
	system("PAUSE");
	system("cls");
}

