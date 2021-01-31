//
// FILE				:	PioneerAM.h
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains all prototypes, class declarations and method 
//						bodies for the class PioneerAM
//


//Define the PioneerWorld Radio 
#ifndef _AMRADIO_H
#define _AMRADIO_H

//Include Files
#include "PioneerCarRadio.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// NAME		:	PioneerAM
// PURPOSE	:	The PioneerAM class behaves like PioneerCarRadio except that it only 
//				operates in the AM band. It has no ability to change to the FM band or 
//				display FM band. It inherites its methods from the PioneerCarRadio class.
//
class PioneerAM : public PioneerCarRadio
{
private:
public:
	PioneerAM(char *name = (char*)"Pioneer XS440-AM");	//Constructor
	virtual void ToggleFrequency(void);					//Toggle band between AM and FM
	virtual ~PioneerAM();								//Destructor
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerAM::PioneerAM()
// DESCRIPTION		:	Constructor for the PioneerAM Class that inherits from the 
//						PioneerCarRadio class 
// PARAMETERS		:	char *rName			:	pointer to the radio type name
// RETURNS			:	void
//
PioneerAM::PioneerAM(char *rName)
{
	SetName(rName);			//Set the radio name 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerAM::~PioneerAM()
// DESCRIPTION		:	Destructor for the PioneerAM Class. Prints its action if 
//						displayOutput is true
// PARAMETERS		:	void
// RETURNS			:	void
//
PioneerAM::~PioneerAM()
{
	if (GetDisplayOutput() == true)
	{
		printf("Destroying Pioneer XS440-AM Radio\n");
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// FUNCTION			:	PioneerAM::ToggleFrequency()
// DESCRIPTION		:	Override the ToggleFrequency to only allow the AM frequency band
// PARAMETERS		:	void
// RETURNS			:	void
//
void PioneerAM::ToggleFrequency(void)
{
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif