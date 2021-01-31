//
// FILE				:	ultimateRadio.cpp
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	The functions in this file are used to test the inheritence of 
//						the PioneerWorld class from the PioneerAM class from the 
//						PioneerCarRadio class from the parent class AmFmRadio 
//

#pragma warning (disable :4996)
#pragma warning (disable :4101)

//Include files 
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <exception>
#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include "PioneerAM.h"
#include "PioneerWorld.h"

//Constants 
#define MAX_BUFFER	20			//Max input buffer
#define CAR_RADIO	"-car"		//Input to Pioneer Radio 
#define AM_RADIO	"-am"		//Input to AM Radio 
#define WRLD_RADIO	"-w"		//Input to World Radio

using namespace std;

//Prototypes
PioneerCarRadio * createRadio(char *);


int main(int argc, char* argv[])
{
	char userRadioInput = 0;			//User Radio Input
	char checkInput[MAXCHAR] = "";		//Array to take user input and pass through check
	char *radioType = argv[argc-1];		//Point
	PioneerCarRadio *pRadio = NULL;		//Pointer to PioneerCarRadio
	
	//Check for commandline arguments
	if (argc != 2) 
	{
		printf(">> You need to supply one argument to this program <<");
		return -1;
	}

	while (userRadioInput != 'x')
	{
		//Create new PioneerCarRadio class
		try
		{
			pRadio = createRadio(radioType);
		}
		catch (bad_alloc &e)
		{
			printf("Exception detected: ""bad_alloc""\n");
			return 1;
		}
		do
		{
			userRadioInput = pRadio->ParseInput();
		} while (userRadioInput != 'x');
		//Get user input 
		printf("\n\nWhich radio do you want to create?\n");
		printf("(c = Car, a = AM, w = WRLD, x = Exit)\n");
		userRadioInput = getch();				//Get user input
		//getch();								//**Second getch() to avoid bug**
		//Parse user input 
		checkInput[0] = userRadioInput;
		if (strcmp(checkInput, "c") == 0)
		{
			strcpy(radioType, CAR_RADIO);
		}
		if (strcmp(checkInput, "a") == 0)
		{
			strcpy(radioType, AM_RADIO);
		}
		if (strcmp(checkInput, "w") == 0)
		{
			strcpy(radioType, WRLD_RADIO);
		}
		//Delete radio pointer
		try
		{
			delete pRadio;
		}
		catch (bad_alloc &a)
		{
			printf("Exception detected: ""bad_alloc""\n");
			return 1;
		}
	}
	printf("\nGoodbye!\n");
	return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	createRadio(char *rType)
// DESCRIPTION		:	determines which type of radio to create based on input
// PARAMETERS		:	char* rType			
// RETURNS			:	pRadioRtr	:	pointer to PioneerCarRadio class
//
PioneerCarRadio * createRadio(char *rType)
{
	PioneerCarRadio *pRadioRtr = NULL;	//Pointer to PioneerCarRadio to return to main

	if (strcmp(rType, CAR_RADIO) == 0)
	{
		pRadioRtr = new PioneerCarRadio();
		return pRadioRtr;
	}
	if (strcmp(rType, AM_RADIO) == 0)
	{
		pRadioRtr = (PioneerCarRadio*) new PioneerAM();
		return pRadioRtr;
	}
	if (strcmp(rType, WRLD_RADIO) == 0 || strcmp(rType, "-world") == 0)
	{
		pRadioRtr = (PioneerCarRadio*) new PioneerWorld();
		return pRadioRtr;
	}
	else
	{
		return pRadioRtr;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++