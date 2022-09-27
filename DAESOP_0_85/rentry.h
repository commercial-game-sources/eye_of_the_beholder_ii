///////////////////////////////////////////////////////////////////////////////
//
// DAESOP
// using code from AESOP engine and ReWiki website
// (c) Mirek Luza
// public domain software
//
///////////////////////////////////////////////////////////////////////////////

#ifndef RENTRY_H
#define RENTRY_H

#include <stdio.h>

#include "tdefs.h"
#include "resstr.h"

long getResourceEntryIndex(int i, DIRPOINTER * loDirectoryPointers);
struct RESEntryHeader *getResourceEntryHeader(int aNumber, FILE *aResFile, DIRPOINTER * aDirectoryPointers);
int getMaxNumberOfResourceEntries(DIRPOINTER *aDirectoryPointers);
char *readResourceBinary(int aResourceNumber, FILE *aResFile, DIRPOINTER *aDirectoryPointers, int *aResourceLength);            

#endif

