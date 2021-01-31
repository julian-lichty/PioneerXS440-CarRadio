//
// FILE				:	PioneerCarRadio.h
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains all prototypes and class declarations for 
//						the class PioneerCarRadio This includes: data members, 
//						constructors, destructors, mutators, and accessors
//


//Define the PioneerWorld Radio 
#ifndef _PIONEERRADIO_H
#define _PIONEERRADIO_H

//Include Files
#include "AmFmRadio.h"

//Constants
#define MAXCHAR 25

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// NAME		:	PioneerCarRadio
// PURPOSE	:	The PioneerCarRadio class has been created to accurately model the 
//				attributes of a standard car radio. The PioneerCarRadio class inherits 
//				data members and methods from the AmFmRadio Class
//
class PioneerCarRadio : public AmFmRadio
{
private:
	char name[MAXCHAR];										//Radio name
public:
	PioneerCarRadio(char *name = (char*)"Pioneer XS440");	//Constructor
	char ParseInput(void); 									//Parse Input
	void DisplayCurrentSettings(void);						//Displays all current values
	char* GetName(void);									//Accessor for name variable
	void SetName(char*);									//Mutator for name variable 
	virtual ~PioneerCarRadio();								//Destructor
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif