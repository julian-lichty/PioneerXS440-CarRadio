//
// FILE				:	PioneerWorld.h
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains all prototypes, class declarations and method 
//						bodies for the class PioneerWorld
//

#pragma warning(disable: 4996)
#pragma warning(disable: 4244)

//Define the PioneerWorld Radio 
#ifndef _WRLDRADIO_H
#define _WRLDRADIO_H

//Include Files
#include "PioneerAM.h"

//Constants
#define AM_HIGH 1602		//Highest AM frequency
#define AM_LOW	531			//Lowest AM frequency
#define AM_SCAN 9			//AM scan increment

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// NAME		:	PioneerWorld
// PURPOSE	:	The PioneerWorld class behaves like the PioneerAM class except that the 
//				AM band range is 531kHz to 1602 kHz. It also changes in intervals of 
//				9 kHZ instead of 10 kHz. The radio frequencies wrap from its new 
//				respective range of 531kHz to 1602 kHz.
//
class PioneerWorld : public PioneerAM 
{
private:
	Freqs *buttonWorld		=	GetButton();				//Pointer to Button array
public:
	PioneerWorld(char *name = (char*)"Pioneer XS440-WRLD");	//Constructor
	virtual void ScanUp(void);								//Increment Frequency up 9kHz
	virtual void ScanDown(void);							//Increment Frequency up 9kHz
	virtual ~PioneerWorld();								//Destructor
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerWorld::PioneerWorld()
// DESCRIPTION		:	Constructor for the PioneerWorld Class that inherits from the 
//						PioneerAM class 
// PARAMETERS		:	char *rName			:	pointer to the radio type name
// RETURNS			:	void
//
PioneerWorld::PioneerWorld(char *rName)
{
	SetName(rName);						//Set the radio name
	for (int i = 0; i < BUTTONS; ++i)	//Loop setting each button value to 531
	{
		buttonWorld[i].AMFreq = AM_LOW;
	}
	ChangeCurrentStation(AM_LOW);		//Set current station to 531
	SetPrevAMFreq(buttonWorld[0].AMFreq);//Set the previous frequency to first button value
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerWorld::~PioneerWorld()
// DESCRIPTION		:	Destructor for the PioneerWorld Class. Prints its action if 
//						displayOutput is true
// PARAMETERS		:	void
// RETURNS			:	void
//
PioneerWorld::~PioneerWorld()
{
	if (GetDisplayOutput() == true)
	{
		printf("Destroying Pioneer XS440-WRLD Radio\n");
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerWorld::ScanUp()
// DESCRIPTION		:	This function moves the current station up then roles over to the
//						lowest station value once the max station is reached 
// PARAMETERS		:	void
// RETURNS			:	void
//
void PioneerWorld::ScanUp(void)
{
	if (strcmp("AM", GetFrequency()) == 0)
	{
		//if current_station is 1602, the current_station becomes 531
		if (GetCurrentStation() >= AM_HIGH)
		{
			ChangeCurrentStation(AM_LOW);
			SetPrevAMFreq(GetCurrentStation());
		}
		//Else increment the frequency up by 9 kHz
		else
		{
			ChangeCurrentStation(GetCurrentStation() + AM_SCAN);
			SetPrevAMFreq(GetCurrentStation());
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerWorld::ScanDown()
// DESCRIPTION		:	This function moves the current station down then roles over to 
//						the highest station value once the max station is reached
// PARAMETERS		:	void
// RETURNS			:	void
//
void PioneerWorld::ScanDown(void)
{
	if (strcmp("AM", GetFrequency()) == 0)	//If the frequency is AM
	{
		//If current_station is 531, the current_station becomes 1602
		if (GetCurrentStation() <= AM_LOW)
		{
			ChangeCurrentStation(AM_HIGH);
			SetPrevAMFreq(GetCurrentStation());
		}
		//Else increment the frequency down by 9 kHz
		else
		{
			ChangeCurrentStation(GetCurrentStation() - AM_SCAN);
			SetPrevAMFreq(GetCurrentStation());
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif