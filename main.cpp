#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "messages.h"

#pragma warning (disable : 4996)


int main()
{
	Initialzation_Stack(Free_Data, Print_Data, Save_Data, Load_Data);
	int Option = 0;
	while (1)
	{
		Menu_Print();
		printf("\nChoose your option: ");
		Option = Secure_Option_Input(INTERFACE_STACK_DISPLAY, INTERFACE_ELEMENTS_NUMBER);

		switch (Option)
		{
		case INTERFACE_STACK_DISPLAY: Display(); 
			break;
		case INTERFACE_PUSH: Push();
			break;
		case INTERFACE_POP: Pop();
			break;
		case INTERFACE_CLEAR: Clear(); 
			break;
		case INTERFACE_FIND: Find();
			break;
		case INTERFACE_SAVE: Save();
			break;
		case INTERFACE_LOAD: Load();
			break;
		case INTERFACE_EXIT: Clear_Exit(); 	
			return 0;

		default:
			printf("Input Error\n");
		};
	}

	return 0;
}
