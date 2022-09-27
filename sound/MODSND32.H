//
// Digital mixer API functions
//

#ifndef MODSND_H
#define MODSND_H

#include "ail32.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFSIZE 1024           // Size of build buffer in bytes

#define CHANNELS 4              // # of logical channels

#define PHYSICAL 4	           // # of physical channels

//
// Return number of bytes needed by mixer for
// the specified number of channels.
//

int ModSizeNeeded(void);        

//
// Report address of pending flag.
//

char * ReportPending(void); 

//
// Bootstrap the mod player object.  MOD player requires a fixed address
// buffer for workspace.	Return code of zero if no sound driver is available.
//

int StartMod(HDRIVER driver, char *soundbase, char *emsloc);

//
// Stop mixer.
//

void StopMod(void);             

//
// Give the mod player a timeslice
//

void PollMod(void);

//
// If channel passed is -1 then it means to establish on the first available
// channel found.  A return code of -1 means there was no channel free.
//

int  SetChannel(int emshandle,			  // address of sound file.
					 unsigned int emsoffset,  // Offset into this page.
					 unsigned int length,	  // length of sound effect.
					 int channel,				  // channel to establish.
					 int mode);					  // mode 0=continuous loop, 1=one-shot

//
// Set physical channel active to this logical channel.
//

void SetActive(int channel,int mod);

//
// Make this physical channel inactive.
//

void InActive(int channel); 

//
// Trigger a channel to play.
//

void ChannelOn(int channel); 

//
// Turn channel off.
//

void ChannelOff(int channel); 

void ChannelSilence(int channel,int silence);

//
// Report channel status on/off.
//

int ChannelState(int channel); 

//
// Report if physical channel is free.
//

int PhysicalState(int channel); 

#ifdef __cplusplus
}
#endif

#endif



