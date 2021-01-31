//
// FILE				:	AmFmRadio.h
// PROJECT			:	Assign-06 Creating More and More Radios ...
// PROGRAMMER		:	Julian Lichty
// DESCRIPTION		:	This file contains all prototypes and class declarations for 
//						the class AmFmRadio this includes: data members, constructors,
//						destructors, mutators, and accessors
//


#ifndef _CARRADIO_H
#define _CARRADIO_H

//Constants
#define BUTTONS 5			//Number of radio buttons

//Structs
struct Freqs
{
	int AMFreq;
	double FMFreq;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//NAME		:	AmFmRadio
//PURPOSE	:	The AmFmRadio class has been created to model the behaviour of a AM/FM 
//				radio. The AmFmRadio class has members that track 5 preset stations, the 
//				current volume (and the previously set volume), the current station (and
//				previously chosen station), the current frequency, whether the AmFmRadio 
//				is on/off, and whether the class methods should display anything.
//
class AmFmRadio
{
private:
	Freqs	button[BUTTONS];	//Five buttons to which any radio station can be saved to
	Freqs	prevFreq;			//The previous frequency that was the radio was on
	double	current_station;	//The current station that the radio is on
	char	freq[3];			//The band of the radio (AM or FM)
	char	last_frequency[3];	//The previous band the radio was on (AM or FM)
	int		volume;				//Current volume for the radio
	int		last_volume;		//The previous radio volume level
	bool	on;					//True or false if the radio is on
	bool	displayOutput;		//True or false to display outputs

public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false

	AmFmRadio(bool power = false);			//Constructor
	AmFmRadio(bool power, Freqs button[5]);	//Constructor with button presets

	//Methods
	void PowerToggle(void);				//sets on to true
	bool IsRadioOn(void);				//returns a true if the radio is currently powered
										//on, and false if the radio is in the off position
	virtual void ToggleFrequency(void);	//toggles frequency between AM and FM and sets 
										//current station
	int SetButton(int button_num);		//sets button with current station by being passed 
										//a button number
	int SetButtonStation(int button_num);//sets current station by being passed a button 
										//number
	int SetVolume(void);				//sets volume 1
	int SetVolume(int volume);			//sets volume 2
	void ShowCurrentSettings(void);		//shows volume, button settings, current station,
										//AM or FM
	virtual void ScanUp(void);			//changes frequency up in increments of .2 for 
											//FM, 10 for AM
	virtual void ScanDown(void);		//changes frequency down in increments of .2 for
										//FM, 10 for AM
	void ChangeCurrentStation(double);	//changes the current station 
	void ToggleDisplayOutput(void);		//toggles if ouput is displayed or not
	void SetPrevAMFreq(int);			//sets the previous frequency

	//Accessors
	Freqs* GetButton(void);				//Returns a pointer to the button presets
	Freqs GetPrevFreq(void);			//Returns a pointer to the previous frequencies
	double GetCurrentStation(void);		//Returns the current radio frequency 
	char* GetFrequency(void);			//Returns the current radio band set (AM or FM)
	char* GetLastFrequency(void);		//Returns the last frequency band 
	int GetVolume(void);				//Returns the current volume value
	int GetLastVolume(void);			//Returns the last volume value
	bool GetOn(void);					//Returns the power state of the radio
	bool GetDisplayOutput(void);		//Returns the true or false to display the output

	virtual ~AmFmRadio(void);			//Destructor
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif