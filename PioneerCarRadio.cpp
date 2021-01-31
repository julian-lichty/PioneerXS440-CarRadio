
//
// FILE				:	PioneerCarRadio.cpp
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains the methods for the PioneerCarRadio Class. This 
//						includes the constructor, destructor, Parsing user input into 
//						inherited functions, and the data display
//

#pragma warning(disable: 4996)

//Include Files 
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "PioneerCarRadio.h"

//Constants
#define MAX_BUFFER	20	//Max input buffer
#define POWER		'o'	//Power toggle reference char
#define VOLUME_UP	'+'	//Volume up reference char
#define VOLUME_DOWN '_'	//Volume down reference char
#define SCAN_UP		'='	//Scan up reference char
#define SCAN_DOWN	'-'	//Scan down reference char
#define TOGGLE_BAND	'b'	//Toggle frequency reference char
#define BUTTON_1	'1'	//Change station to button 1 preset reference char
#define BUTTON_2	'2'	//Change station to button 2 preset reference char
#define BUTTON_3	'3'	//Change station to button 3 preset reference char
#define BUTTON_4	'4'	//Change station to button 4 preset reference char
#define BUTTON_5	'5'	//Change station to button 5 preset reference char
#define SET_BUTTON1	'!'	//Set button 1 to current station reference char
#define SET_BUTTON2	'@'	//Set button 2 to current station reference char
#define SET_BUTTON3	'#'	//Set button 3 to current station reference char
#define SET_BUTTON4	'$'	//Set button 4 to current station reference char
#define SET_BUTTON5	'%'	//Set button 5 to current station reference char
#define EXIT		'x'	//Exit the menu reference char


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::PioneerCarRadio() : AmFmRadio()
// DESCRIPTION		:	Constructor for the PioneerCarRadio Class that inherits from the 
//				 		AmFmRadio class and sets the Radio name 
// PARAMETERS		:	char* rName		:	pointer to the radio type name
// RETURNS			:	void
//
PioneerCarRadio::PioneerCarRadio(char* rName) : AmFmRadio()
{
	strcpy(name, rName);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::ParseInput()
// DESCRIPTION		:	This function gets the users single char input and parses the 
//						the input into the respective action
// PARAMETERS		:	void
// RETURNS			:	char choice		:	user input character
//
char PioneerCarRadio::ParseInput(void)
{
	char		choice = 0;			//User input 

	PioneerCarRadio::DisplayCurrentSettings();	//Display current settings 
	choice = getch();				//Get use input 
	//getch();						//**Second getch to avoid bug**
	if (choice == 'o')				//Turn radio on
	{
		PowerToggle();				//Toggle Radio power
	}
	if (true == IsRadioOn())
	{
		switch (choice)
		{
		case VOLUME_UP:				//Volume Up
			SetVolume(GetVolume() + 1);
			break;
		case VOLUME_DOWN:			//Volume Down
			SetVolume(GetVolume() - 1);
			break;
		case SCAN_UP:				//Scan frequency up
			ScanUp();
			break;
		case SCAN_DOWN:				//Scan frequecny down 
			ScanDown();
			break;
		case TOGGLE_BAND:			//Toggle AM and FM
			ToggleFrequency();
			break;
	//CHOOSE BUTTON
		case BUTTON_1:				//Change to the frequency from button 1
			SetButtonStation(0);
			break;
		case BUTTON_2:				//Change to the frequency from button 2
			SetButtonStation(1);
			break;
		case BUTTON_3:				//Change to the frequency from button 3
			SetButtonStation(2);
			break;
		case BUTTON_4:				//Change to the frequency from button 4
			SetButtonStation(3);
			break;
		case BUTTON_5:				//Change to the frequency from button 5
			SetButtonStation(4);
			break;
	//SET BUTTON
		case SET_BUTTON1:			//Save the current frequency to button 1
			SetButton(0);
			break;
		case SET_BUTTON2:			//Save the current frequency to button 2
			SetButton(1);
			break;
		case SET_BUTTON3:			//Save the current frequency to button 3
			SetButton(2);
			break;
		case SET_BUTTON4:			//Save the current frequency to button 4
			SetButton(3);
			break;
		case SET_BUTTON5:			//Save the current frequency to button 5
			SetButton(4);
			break;
		case EXIT:					//Exit the radio 
			break;
		default:
			break;
		}
	}
	return choice;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::DisplayCurrentSettings(void)
// DESCRIPTION		:	This function displays all the current settings including the 
//						Radio name, volume, current station, saved stations for AM and
//						FM or if the radio is turned off.
// PARAMETERS		:	void
// RETURNS			:	void
//
void PioneerCarRadio::DisplayCurrentSettings(void)
{
	system("CLS");
	bool on = GetOn();							//Power state of the radio
	Freqs *buttons = GetButton();				//Saved frequencies

	printf("\n\n%s\n", GetName());				//Display the Radio name
	if (on == true)								//If the radio is on 
	{
		printf("Radio is on. \n");
		printf("Volume: %d\n", GetVolume());	//Display the current volume
		if (strcmp(GetFrequency(), "AM") == 0)	//If the band is in AM display frequency
		{
			printf("Current Station: %.0f %s\n", GetCurrentStation(), GetFrequency());
		}
		//Only display FM station if it is the PioneerCarRadio class in FM band
		if (strcmp(GetFrequency(), "FM") == 0 && strcmp(GetName(), "Pioneer XS440") == 0)
		{	
			printf("Current Station: %.1f %s\n", GetCurrentStation(), GetFrequency());
		}
		//Display the saved AM button frquencies 
		printf("AM Buttons:\n");
		for (int i = 0; i < BUTTONS; ++i)
		{
			printf("%d: %6d", i + 1, buttons[i].AMFreq);
			if (i < 4)
			{
				printf(", ");
			}
		}
		//Only display FM buttons if it is the PioneerCarRadio class
		if (strcmp(GetName(), "Pioneer XS440") == 0)
		{
			printf("\nFM Buttons:\n");
			for (int j = 0; j < BUTTONS; ++j)
			{
				printf("%d: %6.1f", j + 1, buttons[j].FMFreq);
				if (j < 4)
				{
					printf(", ");
				}
			}
		}
	}
	else
	{
		printf("Radio is off\n");
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::getName()
// DESCRIPTION		:	Accessor for name variable
// PARAMETERS		:	void
// RETURNS			:	char* name	:	pointer to the radio type name	
//
char* PioneerCarRadio::GetName(void)
{
	return name;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::SetName()
// DESCRIPTION		:	Mutator for name variable
// PARAMETERS		:	char* newName	:	pointer to the new radio type name
// RETURNS			:	void
//
void PioneerCarRadio::SetName(char* newName)
{
	strcpy(name, newName);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerCarRadio::~PioneerCarRadio()
// DESCRIPTION		:	Destructor for the PioneerCarRadio Class. Prints its action if 
//						displayOutput is true
// PARAMETERS		:	void
// RETURNS			:	void
//
PioneerCarRadio::~PioneerCarRadio()
{
	if (GetDisplayOutput() == true)
	{
		printf("Destroying Pioneer XS440 Radio\n");
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++