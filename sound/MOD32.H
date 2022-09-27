//
// Digital mixer functions
//

#ifndef MOD_H
#define MOD_H

#ifdef __cplusplus
extern "C" {
#endif

// For each channel passed to the mixer.

typedef struct
{
	unsigned char *sound;      // Address of sound mod, Must be on paragraph.
	unsigned char *sndloc;     // Current output location.
	unsigned long sndlen;	   // Sound length.
	unsigned long silence;		// Amount of silence, between samples.
	unsigned long silout; 	 	// Number of silence samples, left over.
	unsigned long oneshot;		// Sample is played as a one shot.
	unsigned long trigger;		// Trigger is high for sample to be played.
	char *buff; 				   // Build buffer. (output is interleaved)
	unsigned long bufflen;		// Length of build buffer.
	unsigned long emshandle;	// EMS handle associated with mod.

} MODSPEC;

extern void cdecl BuildModStream(MODSPEC *mod);

// Build mixer data stream for this mod channel.
// Output buffer has 8 channels of interleaved data to be merged.

extern void cdecl ModSilence(MODSPEC *mod1,char *merge);
extern void cdecl MergeMod1 (MODSPEC *mod1,char *merge);
extern void cdecl MergeMod2 (MODSPEC *mod1,char *merge);
extern void cdecl MergeMod3 (MODSPEC *mod1,char *merge);
extern void cdecl MergeMod4 (MODSPEC *mod1,char *merge);

#ifdef __cplusplus
}
#endif

#endif


