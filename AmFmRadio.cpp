//
// FILE				:	AmFmRadio.cpp
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains the definitions for the class method functions. 
//						The functionality includes turning the radio on or off, setting the 
//						volume up or down, toggling the fequency to AM or FM, changing the 
//						frequency up or down, or saving a radio preset to one of five buttons.
//

#pragma warning(disable: 4996)
#pragma warning(disable: 4244)

//Include Files 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"

//Constants
#define AM_HIGH		1700	//Highest AM frequency
#define AM_LOW		530		//Lowest AM frequency
#define AM_SCAN		10		//AM scan increment
#define FM_HIGH		107.9	//Highest FM frequency
#define FM_LOW		87.9	//Lowest FM frequency
#define FM_SCAN		0.2		//FM scan increment
#define BUTTONS		5		//Number of radio buttons
#define MAX_BUFFER	20		//Max input buffer
#define VOLUME_HIGH 100		//Highest volume setting
#define VOLUME_LOW	0		//Lowest volume setting



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::AmFmRadio
// DESCRIPTION		:	This function takes a single bool parameter that indicates whether
//						the radio should be on or not when instantiated.
// PARAMETERS		:	bool power : power state of the radio 
// RETURNS			:	void
//
AmFmRadio::AmFmRadio(bool power) : on(power)
{
	for (int i = 0; i < BUTTONS; ++i)
	{
		button[i].AMFreq = AM_LOW;
	}
	for (int j = 0; j < BUTTONS; ++j)
	{
		button[j].FMFreq = FM_LOW;
	}
	//initialize all variables / elements
	//station
	current_station = AM_LOW;
	prevFreq.AMFreq = button[0].AMFreq;
	prevFreq.FMFreq = button[0].FMFreq;
	//frequency
	strcpy(freq, "AM");
	strcpy(last_frequency, freq);
	//volume
	volume = VOLUME_LOW;
	last_volume = VOLUME_LOW;
	// display output
	displayOutput = false;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::AmFmRadio
// DESCRIPTION		:	This function takes a single bool parameter that indicates whether
//						the radio should be on or not when instantiated.
// PARAMETERS		:	bool power			: power state of the radio 
//						Freqs buttons[5]	: the five presets for the radio stations 
// RETURNS			:	none
//
AmFmRadio::AmFmRadio(bool power, Freqs buttons[5]) : on(power)
{
	if (on == true)
	{
		for (int i = 0; i < BUTTONS; ++i)
		{
			button[i].AMFreq = AM_LOW;
		}
		for (int j = 0; j < BUTTONS; ++j)
		{
			button[j].FMFreq = FM_LOW;
		}
		//initialize all variables / elements
		//station
		current_station = AM_LOW;
		prevFreq.AMFreq = button[0].AMFreq;
		prevFreq.FMFreq = button[0].FMFreq;
		//frequency
		strcpy(freq, "AM");
		strcpy(last_frequency, freq);
		//volume
		volume = VOLUME_LOW;
		last_volume = VOLUME_LOW;
		// display output
		displayOutput = false;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::PowerToggle
// DESCRIPTION		:	This function toggles the radio power and saves the current
//						station
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::PowerToggle(void)
{

	if (on == false)
	{
		on = true;

		//set volume to previous level ( if on for the first time defaults to 0)
		volume = last_volume;
		//set band and frequency 
		if (strcmp(freq, "AM") == 0)
		{
			current_station = prevFreq.AMFreq;
		}
		else
		{
			current_station = prevFreq.FMFreq;
		}
	}
	else
	{
		on = false;

		//save volume level & set volume to 0
		last_volume = volume;
		volume = VOLUME_LOW;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::IsRadioOn
// DESCRIPTION		:	This function returns the current power status of the radio
// PARAMETERS		:	void
// RETURNS			:	bool on : power state of the radio
//
bool AmFmRadio::IsRadioOn(void)
{
	return on;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::SetVolume
// DESCRIPTION		:	This function sets the volume for te radio
// PARAMETERS		:	void
// RETURNS			:	int 0	:	if the volume entered is less than zero
//						int 1	:	if the volume was set 
//						int 2	:	if the volume entered is greater than zero
//
int AmFmRadio::SetVolume(void)
{
	char buf[MAX_BUFFER] = "";
	int newVolume = 0;

	printf("\nEnter the volume level (0 - 100). ");
	fgets(buf, sizeof buf, stdin);
	newVolume = atoi(buf);
	SetVolume(newVolume);
	return 1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::SetVolume
// DESCRIPTION		:	This function sets the volume for te radio
// PARAMETERS		:	int volume	:	can pass volume to the method 
// RETURNS			:	int 0		:	if the volume entered is less than zero
//						int 1		:	if the volume was set 
//						int 2		:	if the volume entered is greater than zero
//
int AmFmRadio::SetVolume(int newVolume)
{
	volume = newVolume;
	if (volume < VOLUME_LOW) //if user enters volume less than 0, volume = 0
	{
		volume = VOLUME_LOW;
		return 0;
	}
	if (volume > VOLUME_HIGH) //if user enters volume greater than 100, volume = 100
	{
		volume = VOLUME_HIGH;
		return 2;
	}
	return 1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ToggleFrequency
// DESCRIPTION		:	This function toggles the frequency between AM and FM and saves 
//						the frequency 
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::ToggleFrequency(void)
{
	if (strcmp(freq, "AM") == 0)
	{
		strcpy(freq, "FM");
		current_station = prevFreq.FMFreq;
	}
	else
	{
		strcpy(freq, "AM");
		current_station = prevFreq.AMFreq;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::SetButton
// DESCRIPTION		:	This function takes a single bool parameter that indicates whether
//						the radio should be on or not when instantiated.
// PARAMETERS		:	int button_num	:	the radio preset number 
// RETURNS			:	int 1			:	if the button was set
//					:	int 0			:	if the button was not set 
//
int AmFmRadio::SetButton(int button_num)
{
	if ((button_num >= 0) && (button_num <= 4))
	{
		if (strcmp("AM", freq) == 0)
		{
			button[button_num].AMFreq = current_station;
		}
		else
		{
			button[button_num].FMFreq = current_station;
		}
		return 1;

	}
	return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::SetButtonStation
// DESCRIPTION		:	This function changes the current station to the selected preset
// PARAMETERS		:	int button_num		:	radio preset numbers 
// RETURNS			:	int 0				:	button was not selected 
//						int 1				:	button was selected
//
int AmFmRadio::SetButtonStation(int button_num)
{
	if ((button_num >= 0) && (button_num <= 4))
	{
		if (strcmp("AM", freq) == 0)
		{
			current_station = button[button_num].AMFreq;
			prevFreq.AMFreq = current_station;
		}
		else
		{
			current_station = button[button_num].FMFreq;
			prevFreq.FMFreq = current_station;
		}
		return 1;
	}
	return 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ShowCurrentSettings
// DESCRIPTION		:	This function displays all the current settings 
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::ShowCurrentSettings(void)
{
	if (on == true)
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", freq);
	printf("Volume: %d\n", volume);
	if (strcmp(freq, "AM") == 0)	//If the frequency is AM display no decimals
	{
		printf("Current Station: %.0f %s\n", current_station, freq);
	}
	else
	{
		printf("Current Station: %.1f %s\n", current_station, freq);
	}
		
	printf("AM Button Settings: ");
	for (int i = 0; i < BUTTONS; ++i)
	{
		printf("%d) %6d ", i + 1, button[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	for (int j = 0; j < BUTTONS; ++j)
	{
		printf("%d) %6.1f ", j + 1, button[j].FMFreq);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ScanUp
// DESCRIPTION		:	This function moves the current station up then roles over to the
//						lowest station value once the max station is reached 
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", freq) == 0)
	{
		//if current_station is 1700, the current_station becomes 530
		if (current_station >= AM_HIGH)
		{
			current_station = AM_LOW;
			prevFreq.AMFreq = current_station;
		}
		else
		{
			current_station = current_station + AM_SCAN;
			prevFreq.AMFreq = current_station;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station >= FM_HIGH)
		{
			current_station = FM_LOW;
			prevFreq.FMFreq = current_station;
		}
		else
		{
			current_station = current_station + FM_SCAN;
			prevFreq.FMFreq = current_station;
		}
	}
	if (displayOutput == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, freq);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ScanDown
// DESCRIPTION		:	This function moves the current station down then roles over to the
//						highest station value once the max station is reached
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", freq) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station <= AM_LOW)
		{
			current_station = AM_HIGH;
			prevFreq.AMFreq = current_station;
		}
		else
		{
			current_station = current_station - AM_SCAN;
			prevFreq.AMFreq = current_station;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= FM_LOW)
		{
			current_station = FM_HIGH;
			prevFreq.FMFreq = current_station;
		}
		else
		{
			current_station = current_station - FM_SCAN;
			prevFreq.FMFreq = current_station;
		}
	}
	if (displayOutput == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, freq);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ChangeCurrentStation
// DESCRIPTION		:	This function changes the current station 
// PARAMETERS		:	double new_station	:	the new station being set  
// RETURNS			:	void
//
void AmFmRadio::ChangeCurrentStation(double new_station)
{
	if ((new_station >= AM_LOW && new_station <= AM_HIGH) && strcmp(freq, "AM") == 0)
	{
		strcpy(freq, "AM");
		current_station = new_station;
	}
	if ((new_station >= FM_LOW && new_station <= FM_HIGH) && strcmp(freq, "FM") == 0)
	{
		strcpy(freq, "FM");
		current_station = new_station;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::ToggleDisplayOutput
// DESCRIPTION		:	This function toggles whether or not the information is displayed
// PARAMETERS		:	void
// RETURNS			:	void
//
void AmFmRadio::ToggleDisplayOutput(void)
{
	if (displayOutput == true)
	{
		displayOutput = false;
	}
	else
	{
		displayOutput = true;
	}
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::SetPrevFreq()
// DESCRIPTION		:	This function changes the prevFreq variable
// PARAMETERS		:	Freqs prevF	:	previous frequency
// RETURNS			:	void
//
void AmFmRadio::SetPrevAMFreq(int prevF)
{
	if (strcmp(freq, "AM") == 0)
	{
		prevFreq.AMFreq = prevF;
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetButton()
// DESCRIPTION		:	Accessor for the button array struck variable
// PARAMETERS		:	void
// RETURNS			:	Freqs* button		:	point to the Freqs struct variable
//
Freqs* AmFmRadio::GetButton(void)
{
	return button;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetPrevFreq()
// DESCRIPTION		:	Accessor for the freqeuncy struct variable
// PARAMETERS		:	void
// RETURNS			:	Freqs* Freqs()		:	point to the Freqs struct variable
//
Freqs AmFmRadio::GetPrevFreq(void)
{
	return Freqs();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetCurrentStation()
// DESCRIPTION		:	Accessor for the current station variable
// PARAMETERS		:	void
// RETURNS			:	double current_station		:	current station value
//
double AmFmRadio::GetCurrentStation(void)
{
	return current_station;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetFrequency()
// DESCRIPTION		:	Accessor for the current frequency band variable
// PARAMETERS		:	void
// RETURNS			:	char* freq		:	pointer to the current band (AM or FM)
//
char* AmFmRadio::GetFrequency(void)
{
	return freq;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetLastFrequency()
// DESCRIPTION		:	Accessor for the previous frequency band variable
// PARAMETERS		:	void
// RETURNS			:	char* last_frequency :	pointer to the previous band (AM or FM)
//
char* AmFmRadio::GetLastFrequency(void)
{
	return last_frequency;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetVolume()
// DESCRIPTION		:	Accessor for the current volume variable
// PARAMETERS		:	void
// RETURNS			:	int	volume		:	current volume value
//
int AmFmRadio::GetVolume(void)
{
	return volume;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetLastVolume()
// DESCRIPTION		:	Accessor for the previous volume variable
// PARAMETERS		:	void
// RETURNS			:	int	last_volume		:	previous volume value
//
int AmFmRadio::GetLastVolume(void)
{
	return last_volume;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetOn()
// DESCRIPTION		:	Accessor for the current radio power state
// PARAMETERS		:	void
// RETURNS			:	bool on		:	true or false if the radio is currently on
//
bool AmFmRadio::GetOn(void)
{
	return on;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::GetDisplayOutput()
// DESCRIPTION		:	Accessor for the current display output state
// PARAMETERS		:	void
// RETURNS			:	bool displayOutput	:	true or false if the radio is displaying 
//												data
//
bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	AmFmRadio::AmFmRadio
// DESCRIPTION		:	This function destroys the class
// PARAMETERS		:	void
// RETURNS			:	none
//
AmFmRadio::~AmFmRadio(void)
{
	if (displayOutput == true)
	{
		printf("Destroying AmFmRadio");
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++