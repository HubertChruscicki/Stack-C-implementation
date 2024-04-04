#pragma once

#pragma warning (disable : 4996)

#ifndef DATA__H
#define DATA__H

enum Field_Of_Study
{
	COMPUTER_SCIENCE,
	MATHS,
	ROBOTICS,
	PHYSICS,
	FIELDS_OF_STUDY_ELEMENTS_NUMBER
};


struct Student
{
	char* Surname;
	int Year;
	enum Field_Of_Study Major;
	size_t Length;
};


void* Initialzation_Data(char* SSurname, int YYear, enum Field_Of_Study MMajor); 
void* Push_Data(char* SSurname, int YYear, enum Field_Of_Study MMajor);
void Free_Data(void* Ptr);
void Print_Data(void* Ptr);
int Surname_Data(void* Current_Data_Ptr, void* Search_Data_Ptr);
int Year_Data(void* Current_Data_Ptr, void* Search_Data_Ptr);
int Field_Of_Study_Data(void* Current_Data_Ptr, void* Search_Data_Ptr);
int Save_Data(void* Ptr, FILE* File_Name);
void* Load_Data(FILE* File_Name);


#endif 
