///////////////////////////////////////////////////////////////////////////////
//
// DAESOP
// using code from AESOP engine and ReWiki website
// (c) Mirek Luza
// public domain software
//
// version  0.85
//
// History
// 0.1x  initial versions (development)
// 0.20  first release (061014)
// 0.25  internal version
// 0.30  second release including resource extraction (061017)
// 0.31  bugfix release:fixed syntax help
// 0.35  internal: major rewriting, starting to show individuall resource information)
// 0.36  internal: added info about special/import/export/code resources
// 0.40  third release: added more dumps, resolving names in export tables
// 0.452 internal: starting to work on disassembler (nothing really implemented yet)
// 0.453 internal: first disassembler attempt working
// 0.46  internal: reworking disassembly (using code map), partially working
// 0.47  internal: added support for the CASE instruction
// 0.48  internal: support for labels, various improvements
// 0.50  fourth release (various disasm. errors fixed, resource names are case sensitive!)
// 0.51  bugfix release - some minor fixes in the disassembly format:
//       - missing end of line before .OBJECT_NAME
//       - missing hex number in hex dump of CASE
//       - doubling number in the comment ;import_resource_number
//       - changing the way how the numeric parameters are displayed
//       - increasing the disassembly version to 2
// 0.55  internal: reworking the handling of import/export resources, some minor fixes
// 0.551 internal: adding support for procedures (JSR/RTS), some minor fixes
// 0.552 internal: reworking the handling of import/export resources, better displaying of an import dictionary
// 0.56  internal: list of imported variables/runtime functions, better displaying of an export dictionary
// 0.563 internal: list of imported arrays added
// 0.60  fifth release, (061119) added support for static and table variables, increasing disassembly version
// 0.61  internal: adding /ir command
// 0.62  internal: reworking, string detection
// 0.63  sixth release, (061130) showing string values, minor changes/fixes in /ir command
// 0.64  internal: added /test_old_bitmaps (not documented)
// 0.645 internal: stated to work on on /r /rh options (not finished yet)
// 0.65  internal: finishing the options /r /rh
// 0.655 internal: fixes for /r /rh
// 0.660 seventh release
// 0.670 added commands /ioff /create_tbl
// 0.675 internal: working on conversion, /convert_old_bitmaps (not finished yet)
// 0.676 internal: working on conversion (not finished yet)
// 0.68  internal: first buggy bitmap conversion implemented (EOB 3 shows something in AESOP/32)
// 0.70  8th release: fixing bitmap conversion, /cob command, documenting all commands
// 0.71  internal: working on font conversion (not finished yet)
// 0.72  internal: working on font conversion (not finished yet)
// 0.73  internal: some text shown, but not correct yet
// 0.74  internal: font conversion fixed
// 0.75  9th release: font conversion, fixing the resource type detections (maps, palettes)
// 0.80  10th release: added /eob3menupatch (patching menu bug), /eob3conv (/eob3menupatch + /cof + /cob)
// 0.81  internal: working on symbolic names for local variables
// 0.82  internal: first working implementation of symbolic names for local variables
// 0.83  internal: support for symbolic names of LETA/LESA/LEXA (not tested yet)
// 0.84  internal: symbolic names for LEAA, bugfixing (static tables crash, freeing list of loc. variables, LEXA parameter)
// 0.85  11th release: add comments about possible references to AESOP resources into the bytecode, increasing dissasembly version
//
// WARNING: The structure alignment must be set to 1 for this program to work!
//          RES files depend on the structure alignment - EOB 3 uses 1.
//          Remember to set this in compiler options.
//
///////////////////////////////////////////////////////////////////////////////

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <ctype.h>

#include "daesop.h"
#include "tdefs.h"
#include "dblocks.h"
#include "dict.h"
#include "utils.h"
#include "rentry.h"
#include "dasm.h"
#include "convert.h"

char myResName[256];
struct RESGlobalHeader myHeader;
char myHomeDirectory[256];


/*************************************************************/
void main(int argc, char *argv[])
{
    char loFunctionOption[256];
    int loFunction = NOTHING;
    int i;
    DIRPOINTER loDirectoryPointers[MAX_DIRECTORIES];
    FILE *loResFile;
    int loResult;
    int loNumberOfRequiredParameters;

    // store the home directory
    strcpy(myHomeDirectory, argv[0]);
    for(i = strlen(myHomeDirectory) - 1; i >= 0; i--)
    {
        if (myHomeDirectory[i] == '/' || myHomeDirectory[i] == '\\')
        {
            myHomeDirectory[i + 1] = '\0';
            break;
        }
    }
    
    // empty table
    for(i = 0; i < MAX_DIRECTORIES; i++)
    {
        loDirectoryPointers[i] = NULL;
    }

    printf("AESOP decompiler version: %1.3f\n", VERSION);
    printf("Public domain software made by Mirek Luza\n");
        
    if (argc < 3)
    {
        syntaxInformation();
        exit(1);
    }

    // decide what to do
    strcpy(loFunctionOption, argv[1]);
    
    if (strcmp(loFunctionOption,"/i") == 0)
    {
        loFunction = GET_INFORMATION;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/ir") == 0)
    {
        loFunction = GET_RESOURCES_INFORMATION;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/ioff") == 0)
    {
        loFunction = GET_OFFSET_INFORMATION;
        loNumberOfRequiredParameters = 2;
    }         
    else if (strcmp(loFunctionOption,"/j") == 0)
    {
        loFunction = GET_RESOURCE_INFORMATION_BY_NAME;
        loNumberOfRequiredParameters = 2;
    } 
    else if (strcmp(loFunctionOption,"/k") == 0)
    {
        loFunction = GET_RESOURCE_INFORMATION_BY_NUMBER;
        loNumberOfRequiredParameters = 2;
    }     
    else if (strcmp(loFunctionOption,"/e") == 0)
    {
        loFunction = GET_RESOURCE_BY_NAME;
        loNumberOfRequiredParameters = 2;
    }
    else if (strcmp(loFunctionOption,"/eh") == 0)
    {
        loFunction = GET_RESOURCE_WITH_HEADER_BY_NAME;
        loNumberOfRequiredParameters = 2;
    }
    else if (strcmp(loFunctionOption,"/x") == 0)
    {
        loFunction = GET_RESOURCE_BY_NUMBER;
        loNumberOfRequiredParameters = 2;
    }
    else if (strcmp(loFunctionOption,"/xh") == 0)
    {
        loFunction = GET_RESOURCE_WITH_HEADER_BY_NUMBER;
        loNumberOfRequiredParameters = 2;
    }
    else if (strcmp(loFunctionOption,"/test_old_bitmaps") == 0)
    {
        loFunction = TEST_OLD_BITMAPS;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/r") == 0)
    {
        loFunction = REPLACE_BY_RESOURCE;
        loNumberOfRequiredParameters = 3;        
    }
    else if (strcmp(loFunctionOption,"/rh") == 0)
    {
        loFunction = REPLACE_BY_RESOURCE_WITH_HEADER;
        loNumberOfRequiredParameters = 3;        
    }
    else if (strcmp(loFunctionOption,"/create_tbl") == 0)
    {
        loFunction = CREATE_TBL_FILE;
        loNumberOfRequiredParameters = 1;        
    }
    else if (strcmp(loFunctionOption,"/cob") == 0)
    {
        loFunction = CONVERT_OLD_BITMAPS;
        loNumberOfRequiredParameters = 1;
    }    
    else if (strcmp(loFunctionOption,"/convert_old_bitmaps") == 0)
    {
        loFunction = CONVERT_OLD_BITMAPS_IGNORE_ERRORS;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/cof") == 0)
    {
        loFunction = CONVERT_OLD_FONTS;
        loNumberOfRequiredParameters = 1;
    }    
    else if (strcmp(loFunctionOption,"/convert_old_fonts") == 0)
    {
        loFunction = CONVERT_OLD_FONTS_IGNORE_ERRORS;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/eob3menupatch") == 0)
    {
        loFunction = PATCH_EOB3_MENU;
        loNumberOfRequiredParameters = 1;
    }
    else if (strcmp(loFunctionOption,"/eob3conv") == 0)
    {
        loFunction = CONVERT_EOB3_TO_AESOP32;
        loNumberOfRequiredParameters = 1;
    }    
    else
    {
        syntaxInformation();
        exit(1);
    }

   if (argc != loNumberOfRequiredParameters + 3)
   {
        syntaxInformation();
        exit(1);        
   }

    // res name
    strcpy(myResName,argv[2]);
    for (i = 0; i <strlen(myResName); i++)
    {
        if (myResName[i] == '.')
        {
            myResName[i] = 0;
            break;
        }
   }
   strcat(myResName,".RES");
    
   printf("Processing AESOP resource file: %s ...\n", myResName);

   loResFile = openAESOPResourceAndSetToFirstDirectoryBlock(myResName, "rb", &myHeader);
   if (loResFile == NULL)
   {
       exit(2);
   }

   loResult = readDirectoryBlocks(loResFile, loDirectoryPointers);
   if (loResult == FALSE)
   {
       printf("The reading of directory blocks failed!\n");
       fclose(loResFile);
       exit(4);
   }

   loResult = FALSE;
   if (loFunction == GET_INFORMATION)
   {
       loResult = getInformation(loResFile, loDirectoryPointers, argv[3]);
   }
   else if (loFunction == GET_RESOURCES_INFORMATION)
   {
       loResult = getResourcesInformation(loResFile, loDirectoryPointers, argv[3]);
   }
   else if (loFunction == GET_OFFSET_INFORMATION)
   {
       loResult = getOffsetInformation(loResFile, loDirectoryPointers, argv[3], argv[4]);
   }   
   else if (loFunction == GET_RESOURCE_INFORMATION_BY_NAME ||
          loFunction == GET_RESOURCE_INFORMATION_BY_NUMBER)
   {
       loResult = getResourceInformation(loResFile, loDirectoryPointers, loFunction, argv[3], argv[4]);
   }
   else if (loFunction == GET_RESOURCE_BY_NAME ||
          loFunction == GET_RESOURCE_WITH_HEADER_BY_NAME ||
          loFunction == GET_RESOURCE_BY_NUMBER ||
          loFunction == GET_RESOURCE_WITH_HEADER_BY_NUMBER)
   {
       loResult = getResource(loResFile, loDirectoryPointers, loFunction, argv[3], argv[4]);
   }
   else if (loFunction == TEST_OLD_BITMAPS)
   {
       loResult = testOldBitmaps(loResFile, loDirectoryPointers, argv[3]);
   }
   else if (loFunction == REPLACE_BY_RESOURCE)
   {
       char *loResNumber = argv[3];
       char *loAddedFile = argv[4];
       char *loNewName = argv[5];
       loResult = replaceResourceByResourceFromFile(loResFile, loDirectoryPointers, loResNumber, loAddedFile,
            loNewName, FALSE);
   }
   else if (loFunction == REPLACE_BY_RESOURCE_WITH_HEADER)
   {
       char *loResNumber = argv[3];
       char *loAddedFile = argv[4];
       char *loNewName = argv[5];
       loResult = replaceResourceByResourceFromFile(loResFile, loDirectoryPointers, loResNumber, loAddedFile,
            loNewName, TRUE);
   }
   else if (loFunction == CREATE_TBL_FILE)
   {
       loResult = createTblFile(loResFile, loDirectoryPointers, argv[3]);
   }
   else if (loFunction == CONVERT_OLD_BITMAPS)
   {
       // convert bitmaps, end on any error
       loResult = convertOldBitmaps(loResFile, loDirectoryPointers, argv[3], FALSE);
   }
   else if (loFunction == CONVERT_OLD_BITMAPS_IGNORE_ERRORS)
   {
       // convert bitmaps, skip bitmaps with errors
       loResult = convertOldBitmaps(loResFile, loDirectoryPointers, argv[3], TRUE);
   }
   else if (loFunction == CONVERT_OLD_FONTS)
   {
       // convert fonts, end on any error
       loResult = convertOldFonts(loResFile, loDirectoryPointers, argv[3], FALSE);
   }
   else if (loFunction == CONVERT_OLD_FONTS_IGNORE_ERRORS)
   {
       // convert fonts, skip fonts with errors
       loResult = convertOldFonts(loResFile, loDirectoryPointers, argv[3], TRUE);
   }
   else if (loFunction == PATCH_EOB3_MENU)
   {
       // patch EOB 3 menu code
       loResult = patchEOB3Menu(loResFile, loDirectoryPointers, argv[3]);
   }
   else if (loFunction == CONVERT_EOB3_TO_AESOP32)
   {
       // convert EOB 3
       loResult = convertEOB3toAESOP32(loResFile, loDirectoryPointers, argv[3]);
   }                    
   fclose(loResFile);
   if (loResult == FALSE)
   {
       printf("Finished with an error!\n");       
   }
   else
   {
       printf("Finished OK.\n");
   }
   exit(0);   
}

/*
Syntax information
*/
void syntaxInformation(void)
{
    printf("        DAESOP COMMAND LINE PARAMETERS\n");
    printf("        Information:\n");    
    printf("        daesop /i <res_file> <output_text_file>\n");    
    printf("        daesop /ir <res_file> <output_text_file>\n");        
    printf("        daesop /j <res_file> <resource_name> <output_text_file>\n");
    printf("        daesop /k <res_file> <resource_number> <output_text_file>\n");
    printf("        daesop /ioff <res_file> <offset> <output_text_file>\n");
    printf("        daesop /test_old_bitmaps <res_file> <output_text_file>\n");        
    printf("        Extraction:\n");
    printf("        daesop /e <res_file> <resource_name> <output_binary_file>\n");
    printf("        daesop /eh <res_file> <resource_name> <output_binary_file>\n");
    printf("        daesop /x <res_file> <resource_number> <output_binary_file>\n");
    printf("        daesop /xh <res_file> <resource_number> <output_binary_file>\n");
    printf("        Conversion:\n");
    printf("        daesop /r <res_file> <resource_number> <new_resource_binary> <output_res_file>\n");
    printf("        daesop /rh <res_file> <resource_number> <new_resource_binary> <output_res_file>\n");
    printf("        daesop /eob3conv <res_file> <output_res_file>\n");
    printf("        daesop /create_tbl <res_file> <output_tbl_file>\n");
    printf("        daesop /cob <res_file> <output_res_file>\n");
    printf("        daesop /convert_old_bitmaps <res_file> <output_res_file>\n");
    printf("        daesop /cof <res_file> <output_res_file>\n");
    printf("        daesop /convert_old_fonts <res_file> <output_res_file>\n");
    printf("        daesop /eob3menupatch <res_file> <output_res_file>\n");                                    
}

/*
Finds out and store the information about the RES file
*/
int getInformation(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aOutputFilename)
{
    DICTENTRYPOINTER *loResourceNameArray;
    int loNumberOfResources;
    int i;
    FILE *loOutputFile;
    char loDateString[256];
    int loNumberOfDirectoryBlocks;
    
    loResourceNameArray = getResourceNameArray(aResFile, aDirectoryPointers);
    if (loResourceNameArray == NULL)
    {
        return FALSE;
    }
    
    loNumberOfResources =  getNumberOfItems(loResourceNameArray);    

    printf("Opening the output file: %s\n", aOutputFilename);
    loOutputFile = fopen(aOutputFilename, "w");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFilename);
        return FALSE;
    }

    fprintf(loOutputFile, "AESOP decompiler version: %1.3f\n", VERSION);
    fprintf(loOutputFile, "Public domain software made by Mirek Luza\n\n");
        
    fprintf(loOutputFile, "Analyzed file:      %s\n", myResName);
    fprintf(loOutputFile, "Signature:          %s\n", myHeader.signature);    
    fprintf(loOutputFile, "File size:          %ld bytes\n", (long)(myHeader.file_size));
    fprintf(loOutputFile, "Lost space:         %ld bytes\n", (long)(myHeader.lost_space));        
    fprintf(loOutputFile, "Creation time:      %s\n", unpackDate(myHeader.create_time, loDateString));
    fprintf(loOutputFile, "Modification time : %s\n\n", unpackDate(myHeader.modify_time, loDateString));

    loNumberOfDirectoryBlocks = getNumberOfDirectoryBlocks(aDirectoryPointers);
    fprintf(loOutputFile, "The number of directory blocks: %d\n", loNumberOfDirectoryBlocks);
    fprintf(loOutputFile, "The list of addresses of directory blocks (every directory block has size %d bytes):\n",
        (int)(sizeof (struct RESDirectoryBlock)));
    fprintf(loOutputFile, "%ld\n", (long)(myHeader.first_directory_block));
    for (i = 0; i < MAX_DIRECTORIES; i++)
    {
        if (aDirectoryPointers[i] != NULL)
        {
            int loNextDirBlockPosition = (aDirectoryPointers[i])->next_directory_block;
            if (loNextDirBlockPosition == 0)
            {
                // end
                break;
            }
            fprintf(loOutputFile, "%ld\n", (long)loNextDirBlockPosition);
        }
    }
    fprintf(loOutputFile, "\n");
         
    fprintf(loOutputFile, "The number of resources in the file: %d\n", loNumberOfResources);
    fprintf(loOutputFile, "The resources 0..4 are special AESOP resources.\n");
    fprintf(loOutputFile, "The resources <name>.IMPT/<name>.EXPT are import/export tables for code resources.\n");
    fprintf(loOutputFile, "The corresponding code resource is <name> (it is an AESOP bytecode binary).\n\n");            
    
    fprintf(loOutputFile, "*** Resource details ***\n");
    fprintf(loOutputFile, " (Every resource starts with %d byte header on address START,\n", (int)(sizeof(struct RESEntryHeader)));    
    fprintf(loOutputFile, " the real resource starts on the address REAL_START,\n", (int)(sizeof(struct RESEntryHeader)));
    fprintf(loOutputFile, " the resource length SIZE does not include the length of the header.\n", (int)(sizeof(struct RESEntryHeader)));
    fprintf(loOutputFile, " ATTRIB is the attribute value from the resource header)\n");        
    fprintf(loOutputFile, "NUMBER     START  (REAL_START)      SIZE                    DATE    ATTRIB  NAME\n");    
    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourceNameArray[i] != NULL; i++)
    {
        char *loResourceNumberString;
        int loResourceNumber;
        char *loResourceName;
        struct RESEntryHeader *loResEntryHeader;
        ULONG loDataSize;
        ULONG loResourceAttributes;
        long loResourceEntryIndex;
        char loStorageTime[256];
            
        //  resource number
        loResourceNumberString = loResourceNameArray[i]->second;
        loResourceNumber = atoi(loResourceNumberString);
        if (loResourceNumber == 0 && strcmp(loResourceNumberString,"0") != 0)
        {
            printf("Failure to convert the resource number: %s!\n", loResourceNumberString);
            fclose(loOutputFile);
            return FALSE;                 
        }
        // resource name
        loResourceName = loResourceNameArray[i]->first;
            
        // start of the resource
        loResourceEntryIndex = getResourceEntryIndex(loResourceNumber, aDirectoryPointers);
            
        // length, date
        loResEntryHeader = getResourceEntryHeader(loResourceNumber, aResFile, aDirectoryPointers);
        loDataSize = loResEntryHeader->data_size;
        unpackDate(loResEntryHeader->storage_time, loStorageTime);
        loResourceAttributes = loResEntryHeader->data_attributes;

        // print it
        fprintf(loOutputFile, "%6d  %8ld  (%10ld)  %8ld   %21s  %8lu  %s\n", loResourceNumber, (long)loResourceEntryIndex,
            (long)loResourceEntryIndex + sizeof(struct RESEntryHeader),
            (long)loDataSize, loStorageTime, loResourceAttributes,
            loResourceName);
        free(loResEntryHeader);            
    }
    fclose(loOutputFile);
    return TRUE;
    
}

/*
Stores the chosen resource to a binary file
*/
int getResource(FILE *aResFile, DIRPOINTER *aDirectoryPointers, int aFunction, char *aResource, char *aOutputFilename)
{
    DICTENTRYPOINTER *loResourceNameArray;
    FILE *loOutputFile;
    int loExtractedResourceNumber;
    struct RESEntryHeader *loResEntryHeader;
    ULONG loDataSize;
    long loResourceEntryIndex;
    char *loBuffer;
    int loReadSize;

    loResourceNameArray = getResourceNameArray(aResFile, aDirectoryPointers);
    if (loResourceNameArray == NULL)
    {
        return FALSE;
    }

    if (aFunction == GET_RESOURCE_BY_NUMBER || aFunction == GET_RESOURCE_WITH_HEADER_BY_NUMBER)
    {
        // aResource is number
        loExtractedResourceNumber = getResourceNumberFromNumberString(aResource);
        if (loExtractedResourceNumber == -1)
        {
            // error
            return FALSE;
        }
    }
    else
    {
        // aResource is name
        loExtractedResourceNumber = getResourceNumberFromNameString(aResource, loResourceNameArray);
        if (loExtractedResourceNumber == -1)
        {
            // error
            printf("The resource %s was not found!\n", aResource);
            return FALSE;
        }
    }

    printf("The resource %s was found.\n", aResource);
    printf("Extracting the resource number: %d...\n", loExtractedResourceNumber);    
    
    // start of the resource
    loResourceEntryIndex = getResourceEntryIndex(loExtractedResourceNumber, aDirectoryPointers);
    // length
    loResEntryHeader = getResourceEntryHeader(loExtractedResourceNumber, aResFile, aDirectoryPointers);
    loDataSize = loResEntryHeader->data_size;

    // now set the position and length according to what should be stored
    if (aFunction == GET_RESOURCE_BY_NUMBER || aFunction == GET_RESOURCE_BY_NAME)
    {
        // the resource will be stored without header
        // set position behind the header
        loResourceEntryIndex += sizeof(struct RESEntryHeader);
    }
    else
    {
        // the resource will be stored with header
        // increase the length by the header size
        loDataSize += sizeof(struct RESEntryHeader);
    }

    printf("Reading %ld bytes from the position %ld...\n", (long)loDataSize, (long)loResourceEntryIndex);    

    // now read the resource from the position loResourceEntryIndex with the length loDataSize
    loBuffer = (char *)malloc(loDataSize);
    if (fseek(aResFile, loResourceEntryIndex, SEEK_SET) != 0)
    {
        printf("Failure to set the file position %ld when reading a resource!\n", loResourceEntryIndex);
        return FALSE;
    }        
    loReadSize = fread(loBuffer, 1, loDataSize, aResFile);
    if (loReadSize != loDataSize)
    {
        printf("The resource could not be read!\n");
        free(loBuffer);
        return FALSE;        
    }    

    // write the binary
    printf("Opening the output file: %s\n", aOutputFilename);
    loOutputFile = fopen(aOutputFilename, "wb");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFilename);
        free(loBuffer);
        return FALSE;
    }
    fwrite(loBuffer, 1, loReadSize, loOutputFile);
    fclose(loOutputFile);
    free(loBuffer);   
    return TRUE;
}

/*
Displays information about code related resources (code/import/export)
*/
void displayCodeResourceInformation(FILE *aResFile, DIRPOINTER *aDirectoryPointers, FILE *aOutputFile, int aResourceType,char *aResourceName, DICTENTRYPOINTER* aResourceNameArray)
{
    char loImportResourceName[256];
    char loExportResourceName[256];
    char loCodeResourceName[256];
    int loImportResourceNumber;
    int loExportResourceNumber;
    int loCodeResourceNumber;
    int loImportResourceSize = -1;
    int loExportResourceSize = -1;
    char loTmp[256];
    DICTENTRYPOINTER *loRawImportResourceDictionary = NULL;
    IMPORTENTRYPOINTER *loFullImportResourceDictionary = NULL;    
    DICTENTRYPOINTER *loRawExportResourceDictionary = NULL;
    EXPORTENTRYPOINTER *loFullExportResourceDictionary = NULL;    

    printf("Processing code related resource (code or import or export): %s ...\n", aResourceName);

    fprintf(aOutputFile, "\nThe type of code/import/export resources is determined by the extensions\n"
        ".IMPT/.EXPT of names of import/export resources!\n\n");
    
    if (aResourceType == RESOURCE_TYPE_IMPORT)
    {
        fprintf(aOutputFile, "This is an AESOP code import resource (IMPT).\n");
        strcpy(loImportResourceName, aResourceName);
        strcpy(loTmp, aResourceName);
        (*strstr(loTmp,IMPORT_EXTENSION)) = '\0';
        strcpy(loCodeResourceName, loTmp);
        strcat(loTmp, EXPORT_EXTENSION);
        strcpy(loExportResourceName, loTmp);
    }
    else if (aResourceType == RESOURCE_TYPE_EXPORT)
    {
        fprintf(aOutputFile, "This is an AESOP code export resource (EXPT).\n");
        strcpy(loExportResourceName, aResourceName);
        strcpy(loTmp, aResourceName);
        (*strstr(loTmp,EXPORT_EXTENSION)) = '\0';
        strcpy(loCodeResourceName, loTmp);
        strcat(loTmp, IMPORT_EXTENSION);
        strcpy(loImportResourceName, loTmp);                
    }
    else if (aResourceType == RESOURCE_TYPE_CODE)
    {
        fprintf(aOutputFile, "This is an AESOP code resource.\n");        
        strcpy(loCodeResourceName, aResourceName);
        strcpy(loTmp, aResourceName);
        strcat(loTmp, IMPORT_EXTENSION);
        strcpy(loImportResourceName, loTmp);
        strcpy(loTmp, aResourceName);
        strcat(loTmp, EXPORT_EXTENSION);
        strcpy(loExportResourceName, loTmp);                
    }
    else
    {
        // it is not a code resource, error
        fprintf(aOutputFile, "The resource %s is not code related resource!", aResourceName);
        return;
    }

    loImportResourceNumber = getResourceNumberFromNameString(loImportResourceName, aResourceNameArray);
    loExportResourceNumber = getResourceNumberFromNameString(loExportResourceName, aResourceNameArray);    
    loCodeResourceNumber = getResourceNumberFromNameString(loCodeResourceName, aResourceNameArray);    

    fprintf(aOutputFile, "\n");
    fprintf(aOutputFile, "DETAILS ABOUT THE CODE RESOURCE GROUP\n");
    // code
    if (loCodeResourceNumber == -1)
    {
        fprintf(aOutputFile, "There is no code resource for the resource %s!\n", aResourceName);
    }
    else
    {
        fprintf(aOutputFile, "The code resource name  : %s\n", loCodeResourceName);
        fprintf(aOutputFile, "The code resource number: %d\n", loCodeResourceNumber);        
    }

    // import
    if (loImportResourceNumber == -1)
    {
        fprintf(aOutputFile, "There is no import resource for the resource %s!\n", aResourceName);
    }
    else
    {
        fprintf(aOutputFile, "The import resource name  : %s\n", loImportResourceName);
        fprintf(aOutputFile, "The import resource number: %d\n", loImportResourceNumber);                
    }
    
    // export
    if (loExportResourceNumber == -1)
    {
        fprintf(aOutputFile, "There is no export resource for the resource %s!\n", aResourceName);
    }
    else
    {
        fprintf(aOutputFile, "The export resource name  : %s\n", loExportResourceName);
        fprintf(aOutputFile, "The export resource number: %d\n", loExportResourceNumber);                        
    }        

    if (loImportResourceNumber != -1)
    {
        loRawImportResourceDictionary = getRawImportArray(loImportResourceNumber, aResFile, aDirectoryPointers, &loImportResourceSize);
        if (loRawImportResourceDictionary == NULL)
        {
            fprintf(aOutputFile, "The reading of the import resource %d failed!", loImportResourceNumber);
        }
        else
        {
            loFullImportResourceDictionary = getFullImportArray(loRawImportResourceDictionary, aResFile, aDirectoryPointers);
            if (loFullImportResourceDictionary == NULL)
            {
                fprintf(aOutputFile, "The conversion of the raw import dictionary for the resource %d failed!", loImportResourceNumber);
            }
            else
            {
                // show the import dictionary
                fprintf(aOutputFile, "\n");                
                displayImportDictionary(loImportResourceName, loImportResourceNumber, aOutputFile,
                    loFullImportResourceDictionary, FALSE);                
            }            

        }        
    }

    if (loExportResourceNumber != -1)
    {
        loRawExportResourceDictionary = getRawExportArray(loExportResourceNumber, aResFile, aDirectoryPointers, &loExportResourceSize);
        if (loRawExportResourceDictionary == NULL)
        {
            fprintf(aOutputFile, "The reading of the export resource %d failed!", loExportResourceNumber);            
        }
        else
        {
            loFullExportResourceDictionary = getFullExportArray(loRawExportResourceDictionary, aResFile, aDirectoryPointers);
            if (loFullExportResourceDictionary == NULL)
            {
                fprintf(aOutputFile, "The conversion of the raw export dictionary for the resource %d failed!", loExportResourceNumber);
            }
            else
            {
                // show the export dictionary
                fprintf(aOutputFile, "\n");
                displayExportDictionary(loExportResourceName, loExportResourceNumber, aOutputFile,
                    loFullExportResourceDictionary, FALSE);                
            }
        }                    
    }

    if (loCodeResourceNumber != -1)
    {
        displayCodeResource(loCodeResourceNumber, loCodeResourceName, loFullImportResourceDictionary, loImportResourceSize, 
            loFullExportResourceDictionary, loExportResourceSize, aResFile, aDirectoryPointers, aOutputFile);
    }
}

/*
Displays information about a special AESOP resource (0...4)
*/
void displaySpecialAESOPResource(FILE *aResFile, DIRPOINTER *aDirectoryPointers, FILE *aOutputFile, int aResourceNumber)
{
    DICTENTRYPOINTER *loSpecialDictionary;
    char loText[256];
    char loFormat[256];
    char loHeader[256];
    fprintf(aOutputFile, "This is a special AESOP engine resource.\n");
    fprintf(aOutputFile, "Below are the two sorted tables:\n");
    fprintf(aOutputFile, " - the first is sorted according to the FIRST ENTRY\n");
    fprintf(aOutputFile, " - the second is sorted according to the SECOND ENTRY (numerically if possible)\n");
    fprintf(aOutputFile, "When the value of the second entry is a number, its hexadecimal value is in ().\n");    
    loSpecialDictionary = getSpecialArray(aResourceNumber, aResFile, aDirectoryPointers);
    if (loSpecialDictionary == NULL)
    {
        fprintf(aOutputFile, "The reading of the special resource %d failed!", aResourceNumber);        
    }
    else
    {
        int loSecondIsDecimalNumber;
        if (aResourceNumber == 0 || aResourceNumber == 3 || aResourceNumber == 4)
        {
            loSecondIsDecimalNumber = TRUE;
        }
        else
        {
            loSecondIsDecimalNumber = FALSE;
        }
        
        // sorting according to the first entry
        if (sortDictionaryAccordingToFirstString(loSpecialDictionary) == FALSE)
        {
            fprintf(aOutputFile, "The sorting of the special resource %d according to the FIRST ENTRY failed!", aResourceNumber);
        }
        strcpy(loText, "\n  *** SPECIAL TABLE (sorted by the FIRST ENTRY) ***");
        strcpy(loFormat, "%30s     %20s");
        sprintf(&loHeader, loFormat, "FIRST ENTRY", "SECOND ENTRY");
        displayDictionary(loText, loHeader, loFormat, aOutputFile, loSpecialDictionary, loSecondIsDecimalNumber);
        fprintf(aOutputFile, "\n");

        // sorting accoding to the second entry
        if (loSecondIsDecimalNumber == TRUE)
        {
            // these special AESOP resources have the second entry numeric so sort it like that
            if (sortDictionaryAccordingToSecondNumber(loSpecialDictionary) == FALSE)
            {
                fprintf(aOutputFile, "The sorting of the special resource %d according to the SECOND ENTRY (numeric) failed!", aResourceNumber);
            }
            strcpy(loText, "\n  *** SPECIAL TABLE (sorted by the SECOND ENTRY taken as a number) ***");
            strcpy(loFormat, "%30s     %20s");
            sprintf(&loHeader, loFormat, "FIRST ENTRY", "SECOND ENTRY");
        }
        else
        {
            // otherwise sort according to the second entry (as string)
            if (sortDictionaryAccordingToSecondString(loSpecialDictionary) == FALSE)
            {
                fprintf(aOutputFile, "The sorting of the special resource %d according to the SECOND ENTRY %d failed!", aResourceNumber);
            }            
            strcpy(loText, "\n  *** SPECIAL TABLE (sorted by the SECOND ENTRY) ***");
            strcpy(loFormat, "%30s     %20s");
            sprintf(&loHeader, loFormat, "FIRST ENTRY", "SECOND ENTRY");             
        }
        displayDictionary(loText, loHeader, loFormat, aOutputFile, loSpecialDictionary, loSecondIsDecimalNumber);
        fprintf(aOutputFile, "\n*** SPECIAL AESOP RESOURCE DUMP (resource number: %d) ***\n", aResourceNumber);
        displayHexadecimalDump(aResourceNumber, aResFile, aDirectoryPointers, aOutputFile);        
    }
}

/*
Display a hexadecimal dump of the resource
*/
void displayHexadecimalDump(int aResourceNumber, FILE *aResFile, DIRPOINTER *aDirectoryPointers, FILE *aOutputFile)
{
    char *loBuffer;
    int loResourceLength;

    loBuffer = readResourceBinary(aResourceNumber, aResFile, aDirectoryPointers, &loResourceLength);
    if (loBuffer == NULL)
    {
        fprintf(aOutputFile, "The reading of the resource %d failed!\n", aResourceNumber);
        return;
    }
    displayHexadecimalDumpOfMemoryBuffer(loBuffer, loResourceLength, aOutputFile); 
    free(loBuffer);
}    
        
/*
Display a hexadecimal dump of array
*/
void displayHexadecimalDumpOfMemoryBuffer(char *aBuffer, int aLength, FILE *aOutputFile)
{
    int i;
    int j;
    // dump the code
    for(i = 0; i < aLength; i++)
    {
        if (i % DUMP_LINE_SIZE == 0)
        {
            if (i != 0)
            {
                // write characters
                fprintf(aOutputFile, "  ");
                j = i - DUMP_LINE_SIZE;
                for(; j < i; j++)
                {
                    fprintf(aOutputFile, "%c", getCharacterForDump((char)aBuffer[j]));
                }
            }
            // address
            fprintf(aOutputFile, "\n%6d (%06x): ", i, i);
        }
        fprintf(aOutputFile, " %02x", (int)aBuffer[i]);
    }

    // write remaining characters
    j = aLength % DUMP_LINE_SIZE;
    if (j == 0 && aLength != 0)
    {
        // there is whole line
        j = DUMP_LINE_SIZE;
    }
    for( i = DUMP_LINE_SIZE - j; i > 0; i--)
    {
        fprintf(aOutputFile, "   ");
    }
    fprintf(aOutputFile, "  ");        
    for(; j > 0; j--)
    {
        fprintf(aOutputFile, "%c", getCharacterForDump((char)aBuffer[aLength - j]));
    }        
    
    fprintf(aOutputFile, "\n");    
}

/*
Gets the information about the specified resource
*/
int getResourceInformation(FILE *aResFile, DIRPOINTER *aDirectoryPointers, int aFunction, char *aResource, char *aOutputFilename)
{
    DICTENTRYPOINTER *loResourceNameArray;
    FILE *loOutputFile;
    int loExtractedResourceNumber;
    struct RESEntryHeader *loResEntryHeader;
    ULONG loDataSize;
    long loResourceEntryIndex;
    //char *loBuffer;
    //int loReadSize;
    ULONG loResourceAttributes;
    char loStorageTime[256];
    char loResourceName[256];
    char loTmp[256];
    int loResourceType = RESOURCE_TYPE_UNKNOWN;

    loResourceNameArray = getResourceNameArray(aResFile, aDirectoryPointers);
    if (loResourceNameArray == NULL)
    {
        return FALSE;
    }

    if (aFunction == GET_RESOURCE_INFORMATION_BY_NUMBER)
    {
        // aResource is number
        loExtractedResourceNumber = getResourceNumberFromNumberString(aResource);
        if (loExtractedResourceNumber == -1)
        {
            // error
            return FALSE;
        }
    }
    else
    {
        // aResource is name
        loExtractedResourceNumber = getResourceNumberFromNameString(aResource, loResourceNameArray);
        if (loExtractedResourceNumber == -1)
        {
            // error
            printf("The resource %s was not found!\n", aResource);
            return FALSE;
        }
    }

    if (getResourceName(loResourceName, loExtractedResourceNumber) == NULL)
    {
        // error
        return FALSE;
    }
    
    printf("The resource %s was found.\n", aResource);
    printf("Looking for the information about the resource number: %d...\n", loExtractedResourceNumber);

    // resource details
    loResourceEntryIndex = getResourceEntryIndex(loExtractedResourceNumber, aDirectoryPointers);
    loResEntryHeader = getResourceEntryHeader(loExtractedResourceNumber, aResFile, aDirectoryPointers);
    loDataSize = loResEntryHeader->data_size;
    unpackDate(loResEntryHeader->storage_time, loStorageTime);
    loResourceAttributes = loResEntryHeader->data_attributes;
    
    printf("Opening the output file: %s\n", aOutputFilename);
    loOutputFile = fopen(aOutputFilename, "w");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFilename);
        return FALSE;
    }
    fprintf(loOutputFile,"AESOP decompiler version: %1.3f\n", VERSION);
    fprintf(loOutputFile,"Public domain software made by Mirek Luza\n\n");    
    fprintf(loOutputFile,"Analyzing the resource %s in the file: %s\n\n", aResource, myResName);
    fprintf(loOutputFile,"Resource name:   %s\n", loResourceName);
    fprintf(loOutputFile,"Resource number: %d\n", loExtractedResourceNumber);
    fprintf(loOutputFile,"Starts at:       %ld\n", (long)loResourceEntryIndex + sizeof(struct RESEntryHeader));
    fprintf(loOutputFile,"Length:          %lu\n", loDataSize);
    fprintf(loOutputFile,"Attributes:      %lu\n", loResourceAttributes);
    fprintf(loOutputFile,"Time:            %s\n", loStorageTime);

    strcpy(loTmp, loResourceName);
    //toUpperCase(loTmp); // resouce names ARE CASE SENSITIVE, so do not convert to uppercase!
    if (stringEndsWith(loTmp, IMPORT_EXTENSION) == TRUE)
    {
        loResourceType = RESOURCE_TYPE_IMPORT;
        displayCodeResourceInformation(aResFile, aDirectoryPointers, loOutputFile, loResourceType, loResourceName, loResourceNameArray);
    }
    else if (stringEndsWith(loTmp, EXPORT_EXTENSION) == TRUE)
    {
        loResourceType = RESOURCE_TYPE_EXPORT;
        displayCodeResourceInformation(aResFile, aDirectoryPointers, loOutputFile, loResourceType, loResourceName, loResourceNameArray);
    }
    strcpy(loTmp, loResourceName);
    strcat(loTmp, EXPORT_EXTENSION);
    if (getResourceNumberFromNameString(loTmp, loResourceNameArray) != -1)
    {
        loResourceType = RESOURCE_TYPE_CODE;
        displayCodeResourceInformation(aResFile, aDirectoryPointers, loOutputFile, loResourceType, loResourceName, loResourceNameArray);
    }
    if (loExtractedResourceNumber < NUMBER_OF_SPECIAL_TABLES)
    {
        loResourceType = RESOURCE_TYPE_SPECIAL;
        displaySpecialAESOPResource(aResFile, aDirectoryPointers, loOutputFile, loExtractedResourceNumber);
    }

    if (loResourceType == RESOURCE_TYPE_UNKNOWN)
    {
        // write hexadecimal dump for any other resource type
        fprintf(loOutputFile, "\n*** GENERAL RESOURCE DUMP (resource name %s, resource number: %d) ***\n", loResourceName, loExtractedResourceNumber);
        displayHexadecimalDump(loExtractedResourceNumber, aResFile, aDirectoryPointers, loOutputFile);            
    }
        
    fclose(loOutputFile);                 
    free(loResEntryHeader);            
        
    return TRUE;
}

/*
Display information about the code resource
*/
void displayCodeResource(int aCodeResourceNumber, char *aCodeResourceName, IMPORTENTRYPOINTER *aFullImportResourceDictionary,
            int aImportResourceSize, EXPORTENTRYPOINTER *aFullExportResourceDictionary, int aExportResourceSize,
            FILE *aResFile, DIRPOINTER *aDirectoryPointers, FILE *aOutputFile)
{
    char *loResourceBinary;
    int loResourceLength;
    printf("Starting to read the code resource %d\n ...", aCodeResourceNumber);

    loResourceBinary = readResourceBinary(aCodeResourceNumber, aResFile, aDirectoryPointers, &loResourceLength);
    if (loResourceBinary != NULL)
    {
        // disassembly
        fprintf(aOutputFile, "\n*** CODE RESOURCE DISASSEMBLER (resource name %s, resource number: %d) ***\n", aCodeResourceName, aCodeResourceNumber) ;
        disassembleCodeResource(aCodeResourceNumber, loResourceBinary, loResourceLength, aFullImportResourceDictionary,
            aImportResourceSize, aFullExportResourceDictionary, aExportResourceSize, aOutputFile, aResFile,
            aDirectoryPointers);
        // hexadecimal dump   
        fprintf(aOutputFile, "\n*** CODE RESOURCE DUMP (resource name %s, resource number: %d) ***\n", aCodeResourceName, aCodeResourceNumber) ;    
        displayHexadecimalDumpOfMemoryBuffer(loResourceBinary, loResourceLength, aOutputFile);
    }
    printf("Finished reading of the code resource.\n");    
}

/*
Finds out and store the information about resources
*/
int getResourcesInformation(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aOutputFilename)
{
    RESINFOPOINTER   *loResInfo;
    FILE *loOutputFile;
    char loDateString[256];
    
    loResInfo = getResourcesInformationTable(aResFile, aDirectoryPointers, TRUE);
    if (loResInfo == NULL)
    {
        // unable to get the resource information table
        return FALSE;
    }
  
    printf("Opening the output file: %s\n", aOutputFilename);
    loOutputFile = fopen(aOutputFilename, "w");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFilename);
        return FALSE;
    }

    fprintf(loOutputFile, "AESOP decompiler version: %1.3f\n", VERSION);
    fprintf(loOutputFile, "Public domain software made by Mirek Luza\n\n");
        
    fprintf(loOutputFile, "Analyzed file:      %s\n", myResName);
    fprintf(loOutputFile, "Signature:          %s\n", myHeader.signature);    
    fprintf(loOutputFile, "File size:          %ld bytes\n", (long)(myHeader.file_size));
    fprintf(loOutputFile, "Lost space:         %ld bytes\n", (long)(myHeader.lost_space));        
    fprintf(loOutputFile, "Creation time:      %s\n", unpackDate(myHeader.create_time, loDateString));
    fprintf(loOutputFile, "Modification time : %s\n\n", unpackDate(myHeader.modify_time, loDateString));

    // display the table
    displayResourcesInfoEntries(loOutputFile, loResInfo);
    
    fclose(loOutputFile);
    return TRUE;
    
}

/*
Test old bitmaps
*/
int testOldBitmaps(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aOutputFilename)
{
    RESINFOPOINTER   *loResourcesInfoTable;
    FILE *loOutputFile;
    int loResult = FALSE;
    int i;
    
    loResourcesInfoTable = getResourcesInformationTable(aResFile, aDirectoryPointers, FALSE);
    if (loResourcesInfoTable == NULL)
    {
        // unable to get the resource information table
        return loResult;
    }
  
    printf("Opening the output file: %s\n", aOutputFilename);
    loOutputFile = fopen(aOutputFilename, "w");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFilename);
        return loResult;
    }

    loResult = TRUE;
    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourcesInfoTable[i] != NULL; i++)
    {
        int loResourceType;
        loResourceType = loResourcesInfoTable[i]->resourceType;
        if (loResourceType == RESOURCE_TYPE_BITMAP)
        {
            char *loName;
            int loNumber;
            char *loFileName;        
            loName = loResourcesInfoTable[i]->name;
            loNumber = loResourcesInfoTable[i]->number;
            loFileName = loResourcesInfoTable[i]->infoFromResource2;
            if (testOneOldBitmap(aResFile, aDirectoryPointers, loName, loNumber, loOutputFile) == FALSE)
            {
                fprintf(loOutputFile, "%-6s %5d \"%s\" \"%s\"\n\n", "FAILED", loNumber, loName, loFileName);
                loResult = FALSE;
            }
            else
            {
                fprintf(loOutputFile, "%-6s %5d \"%s\" \"%s\"\n\n", "OK", loNumber, loName, loFileName);
            }
        }           
    }

    fclose(loOutputFile);
    return TRUE;        
}


/*
Replaces a resource by a new resource read from a file (with or without a header)
*/
int replaceResourceByResourceFromFile(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aResourceNumberString,
    char *aAddedResourceFileName, char *aNewFileName, int aNewResourceHasHeader)
{
    DICTENTRYPOINTER* loResourceNameArray;
    int loResourceNumber;
    char loResourceName[256];
    long loAddedResourceSize;
    char *loBuffer;
    FILE *loAddedResourceFile;
    int loReadSize;
    int loResult;
    
    loResourceNameArray = getResourceNameArray(aResFile, aDirectoryPointers);
    if (loResourceNameArray == NULL)
    {
        return FALSE;
    }

    loResourceNumber = atoi(aResourceNumberString);
    if (loResourceNumber == 0 && strcmp(aResourceNumberString,"0") != 0)
    {
        printf("Failure to convert the resource number: %s!\n", aResourceNumberString);
        return FALSE;                 
    }    

    if (getResourceName(loResourceName, loResourceNumber) == NULL)
    {
        printf("Unable to find the original resource number: %d\n", loResourceNumber);
        return FALSE; 
    }
                
    // added resource
    loAddedResourceFile = fopen(aAddedResourceFileName, "rb");
    if (loAddedResourceFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aAddedResourceFileName);
        return FALSE;
    }
    fseek(loAddedResourceFile, 0, SEEK_END); // at the end
    loAddedResourceSize = ftell(loAddedResourceFile);
    printf("The length of the added resource file is %ld\n", loAddedResourceSize);

    loBuffer = (char *)malloc(loAddedResourceSize);
    if (loBuffer == NULL)
    {
        printf("The allocation of the array for the added resource with the size %d failed!\n", loAddedResourceSize);
        fclose(loAddedResourceFile);
        return FALSE;
    }    

    fseek(loAddedResourceFile, 0, SEEK_SET);  // at the beginning
    loReadSize = fread( loBuffer, 1, loAddedResourceSize, loAddedResourceFile);
    if (loReadSize != loAddedResourceSize)
    {
        printf("Failure to read the added resource into memory!\n");
        free(loBuffer);
        fclose(loAddedResourceFile);
        return FALSE;           
    }
    fclose(loAddedResourceFile);

    loResult = replaceResourceByResourceFromMemory(aResFile, loResourceName, loResourceNumber,
                loBuffer, loAddedResourceSize, aNewFileName, aNewResourceHasHeader);
    free(loBuffer);
    return loResult;    
}

/*
Gets the information to which part of the file the offset points
*/
int getOffsetInformation(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aOffsetString,
    char *aOutputFileName)
{
    int loOffset;
    DICTENTRYPOINTER *loResourceNameArray;
    int loFileHeaderSize;
    int loDirBlockSize;
    int loResEntryHeaderSize;
    char loTmp[256];
    FILE *loOutputFile;
    int i;

    loFileHeaderSize = sizeof(struct RESGlobalHeader);
    loDirBlockSize = sizeof(struct RESDirectoryBlock);
    loResEntryHeaderSize = sizeof(struct RESEntryHeader);
    
    if (aOffsetString == NULL || strlen(aOffsetString) == 0)
    {
        printf("File offset is NULL or an empty string!\n");
        return FALSE;
    }
    if (strlen(aOffsetString) > 1 && aOffsetString[0] == '#')
    {
        // hex number starting by #
        char loHexadecimalNumber[256];
        strcpy(loHexadecimalNumber, "0x");
        strcat(loHexadecimalNumber, aOffsetString + 1);
        if (sscanf(loHexadecimalNumber, "%x", &loOffset) != 1)
        {
            printf("Failed to convert the hexadecimal number: %s\n", aOffsetString);
            return FALSE;
        }
    }
    else if (strlen(aOffsetString) > 2 && aOffsetString[0] == '0' &&
        (aOffsetString[1] == 'x' || aOffsetString[1] == 'X'))
    {
        // hex number starting by 0x
        if (sscanf(aOffsetString, "%x", &loOffset) != 1)
        {
            printf("Failed to convert the hexadecimal number: %s\n", aOffsetString);
            return FALSE;
        }        
    }
    else
    {
        // decadic number
        if (sscanf(aOffsetString, "%d", &loOffset) != 1)
        {
            printf("Failed to convert the number: %s\n", aOffsetString);
            return FALSE;
        }        
    }

    if (loOffset < 0 || loOffset >= myHeader.file_size)
    {
        printf("The offset %d points does not point into the file %s!\n", loOffset, myResName);
        return FALSE;
    }
    
    loResourceNameArray = getResourceNameArray(aResFile, aDirectoryPointers);
    if (loResourceNameArray == NULL)
    {
        return FALSE;
    }

    printf("Opening the output file: %s\n", aOutputFileName);
    loOutputFile = fopen(aOutputFileName, "w");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aOutputFileName);
        return FALSE;
    }

    fprintf(loOutputFile, "AESOP decompiler version: %1.3f\n", VERSION);
    fprintf(loOutputFile, "Public domain software made by Mirek Luza\n\n");
        
    fprintf(loOutputFile, "Analyzed file:      %s\n\n", myResName);

    sprintf(loTmp, "The offset value: %d (#%06x)", loOffset, loOffset);
    fprintf(loOutputFile, "%s\n", loTmp);
    printf("%s\n", loTmp);

    if (loOffset < loFileHeaderSize)
    {
        sprintf(loTmp, "The offset %d points to the RES file header.", loOffset);
        fprintf(loOutputFile, "%s\n", loTmp);
        printf("%s\n", loTmp);
        fclose(loOutputFile);
        return TRUE;        
    }
    if (loOffset >= myHeader.first_directory_block  &&
        loOffset < myHeader.first_directory_block + loDirBlockSize)
    {
        sprintf(loTmp, "The offset %d points to the directory block %d.", loOffset, 1);
        fprintf(loOutputFile, "%s\n", loTmp);
        printf("%s\n", loTmp);
        fclose(loOutputFile);
        return TRUE;        
    }
    for (i = 0; i < MAX_DIRECTORIES; i++)
    {
        if (aDirectoryPointers[i] != NULL && aDirectoryPointers[i]->next_directory_block != 0)
        {
            if (loOffset >= aDirectoryPointers[i]->next_directory_block  &&
                loOffset < aDirectoryPointers[i]->next_directory_block + loDirBlockSize)
            {
                sprintf(loTmp, "The offset %d points to the directory block %d.", loOffset, i + 1);
                fprintf(loOutputFile, "%s\n", loTmp);
                printf("%s\n", loTmp);
                fclose(loOutputFile);
                return TRUE;        
            }
        }
    }
    // now check the resources
    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourceNameArray[i] != NULL; i++)
    {
        char *loResourceNumberString;
        int loResourceNumber;
        char *loResourceName;
        struct RESEntryHeader *loResEntryHeader;
        ULONG loDataSize;
        long loResourceEntryIndex;
            
        //  resource number
        loResourceNumberString = loResourceNameArray[i]->second;
        loResourceNumber = atoi(loResourceNumberString);
        if (loResourceNumber == 0 && strcmp(loResourceNumberString,"0") != 0)
        {
            printf("Failure to convert the resource number: %s!\n", loResourceNumberString);
            fclose(loOutputFile);
            return FALSE;                 
        }
        // resource name
        loResourceName = loResourceNameArray[i]->first;
            
        // start of the resource
        loResourceEntryIndex = getResourceEntryIndex(loResourceNumber, aDirectoryPointers);
            
        // length, date
        loResEntryHeader = getResourceEntryHeader(loResourceNumber, aResFile, aDirectoryPointers);
        loDataSize = loResEntryHeader->data_size;

        if (loOffset >= loResourceEntryIndex && loOffset < loResourceEntryIndex + loResEntryHeaderSize)
        {
            sprintf(loTmp, "The offset %d points to the header of the resource number: %d, name \"%s\".",
                loOffset, loResourceNumber, loResourceName);
            fprintf(loOutputFile, "%s\n", loTmp);
            printf("%s\n", loTmp);
            free(loResEntryHeader);
            fclose(loOutputFile);
            return TRUE;            
        }

        if (loOffset >= loResourceEntryIndex + loResEntryHeaderSize &&
            loOffset < loResourceEntryIndex + loResEntryHeaderSize + loDataSize)
        {
            sprintf(loTmp, "The offset %d points to the content of the resource number: %d, name \"%s\".",
                loOffset, loResourceNumber, loResourceName);
            fprintf(loOutputFile, "%s\n", loTmp);
            printf("%s\n", loTmp);
            free(loResEntryHeader);
            fclose(loOutputFile);
            return TRUE;            
        }        

        free(loResEntryHeader);            
    }
    sprintf(loTmp, "The offset %d points to an unknown part of the file!", loOffset);    
    fprintf(loOutputFile, "%s\n", loTmp);
    printf("%s\n", loTmp);
    fclose(loOutputFile);
    return TRUE;            
}

/*
Create a corresponding TBL file for the used RES file
(the Dungeon Hack engine uses needs to have for every RES file its corresponding TBL file)
*/
int createTblFile(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aTblFileName)
{
    int i;
    FILE *loOutputFile;
    
    // open the binary file
    printf("Creating the output TBL file: %s\n", aTblFileName);
    loOutputFile = fopen(aTblFileName, "wb");
    if (loOutputFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aTblFileName);
        return FALSE;
    }

    // write the indexes
    for (i = 0; i < MAX_DIRECTORIES && aDirectoryPointers[i] != NULL; i++)
    {
        int j;
        for(j = 0; j < DIRECTORY_BLOCK_ITEMS; j++)
        {
            ULONG loIndex;
            loIndex = aDirectoryPointers[i]->entry_header_index[j];
            if (fwrite(&loIndex, 1, sizeof(ULONG), loOutputFile) != sizeof(ULONG))
            {
                printf("Error while writing a TBL file!\n");
                fclose(loOutputFile);
                return FALSE;
            }                
        }
    }

    // write end markers
    for(i = 0; i < TBL_END_MARKER_LENGTH; i++)
    {
        UBYTE loZero = 0;
        if (fwrite(&loZero, 1, sizeof(UBYTE), loOutputFile) != sizeof(UBYTE))
        {
            printf("Error while writing a TBL file!\n");
            fclose(loOutputFile);
            return FALSE;
        }        
    }

    // close the file
    fclose(loOutputFile);    
    return TRUE;
}

/*
Converts old bitmaps (EOB3 -> AESOP/32)
*/
int convertOldBitmaps(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aNewFileName, int aIgnoreErrors)
{
    RESINFOPOINTER   *loResourcesInfoTable;
    int loResult = FALSE;
    int i;
    int loOkConversions = 0;
    int loFailedConversions = 0;
    DIRPOINTER loNewFileDirectoryPointers[MAX_DIRECTORIES];
    struct RESGlobalHeader loNewFileHeader;
    FILE *loNewFile;    
    
    loResourcesInfoTable = getResourcesInformationTable(aResFile, aDirectoryPointers, FALSE);
    if (loResourcesInfoTable == NULL)
    {
        // unable to get the resource information table
        return loResult;
    }

    // copy the original file
    // (only the copy will be modified)
    if (copyFile(aResFile, aNewFileName) == FALSE)
    {
        printf("Copying of the original file failed!\n");
        return FALSE;   
    }
  
    // open the copied file and read the header
    loNewFile = openAESOPResourceAndSetToFirstDirectoryBlock(aNewFileName, "r+b", &loNewFileHeader);
    if (loNewFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aNewFileName);
        return FALSE;
    }     
    
    // read the directory
    if (readDirectoryBlocks(loNewFile, loNewFileDirectoryPointers) == FALSE)
    {
       printf("The reading of directory blocks in the new file failed!\n");
       fclose(loNewFile);
       return FALSE;
    }

    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourcesInfoTable[i] != NULL; i++)
    {
        int loResourceType;
        loResourceType = loResourcesInfoTable[i]->resourceType;
        if (loResourceType == RESOURCE_TYPE_BITMAP)
        {
            char *loName;
            int loNumber;
            loName = loResourcesInfoTable[i]->name;
            loNumber = loResourcesInfoTable[i]->number;
            if (convertOneOldBitmap(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader, loNumber, loName) == FALSE)
            {
                loFailedConversions++;
                printf("The conversion of the bitmap resource number %d, name \"%s\" FAILED!\n", loNumber, loName);
                if (aIgnoreErrors == FALSE)
                {
                    printf("Ending the conversion prematurely!\n");
                    // mark the file as invalid (by overwriting the beginning)
                    fseek(loNewFile, 0, SEEK_SET);
                    fprintf(loNewFile, "BAD FILE: THE BITMAP CONVERSION FAILED !!!\n");
                    break;
                }
            }
            else
            {
                loOkConversions++;
            }
            
        }           
    }
    fclose(loNewFile);
    printf("The number of correctly converted bitmaps: %d\n", loOkConversions);
    printf("The number of failed bitmap conversions: %d\n", loFailedConversions);    
    if (loFailedConversions > 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*
Converts old fonts (EOB3 -> AESOP/32)
*/
int convertOldFonts(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aNewFileName, int aIgnoreErrors)
{
    RESINFOPOINTER   *loResourcesInfoTable;
    int loResult = FALSE;
    int i;
    int loOkConversions = 0;
    int loFailedConversions = 0;
    DIRPOINTER loNewFileDirectoryPointers[MAX_DIRECTORIES];
    struct RESGlobalHeader loNewFileHeader;
    FILE *loNewFile;    
    
    loResourcesInfoTable = getResourcesInformationTable(aResFile, aDirectoryPointers, FALSE);
    if (loResourcesInfoTable == NULL)
    {
        // unable to get the resource information table
        return loResult;
    }

    // copy the original file
    // (only the copy will be modified)
    if (copyFile(aResFile, aNewFileName) == FALSE)
    {
        printf("Copying of the original file failed!\n");
        return FALSE;   
    }
  
    // open the copied file and read the header
    loNewFile = openAESOPResourceAndSetToFirstDirectoryBlock(aNewFileName, "r+b", &loNewFileHeader);
    if (loNewFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aNewFileName);
        return FALSE;
    }     
    
    // read the directory
    if (readDirectoryBlocks(loNewFile, loNewFileDirectoryPointers) == FALSE)
    {
       printf("The reading of directory blocks in the new file failed!\n");
       fclose(loNewFile);
       return FALSE;
    }

    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourcesInfoTable[i] != NULL; i++)
    {
        int loResourceType;
        loResourceType = loResourcesInfoTable[i]->resourceType;
        if (loResourceType == RESOURCE_TYPE_FONT)
        {
            char *loName;
            int loNumber;
            loName = loResourcesInfoTable[i]->name;
            loNumber = loResourcesInfoTable[i]->number;
            if (convertOneOldFont(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader, loNumber, loName) == FALSE)
            {
                loFailedConversions++;
                printf("The conversion of the font resource number %d, name \"%s\" FAILED!\n", loNumber, loName);
                if (aIgnoreErrors == FALSE)
                {
                    printf("Ending the conversion prematurely!\n");
                    // mark the file as invalid (by overwriting the beginning)
                    fseek(loNewFile, 0, SEEK_SET);
                    fprintf(loNewFile, "BAD FILE: THE FONT CONVERSION FAILED !!!\n");
                    break;
                }
            }
            else
            {
                loOkConversions++;
            }
            
        }           
    }
    fclose(loNewFile);
    printf("The number of correctly converted fonts: %d\n", loOkConversions);
    printf("The number of failed font conversions: %d\n", loFailedConversions);    
    if (loFailedConversions > 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*
Patch EOB 3 menu code to run in AESOP/32
*/
int patchEOB3Menu(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aNewFileName)
{    
    int loResult = FALSE;
    DIRPOINTER loNewFileDirectoryPointers[MAX_DIRECTORIES];
    struct RESGlobalHeader loNewFileHeader;
    FILE *loNewFile;    

    // read the resource name array (it is used later)
    if (getResourceNameArray(aResFile, aDirectoryPointers) == NULL)
    {
        return FALSE;
    }
    
    // copy the original file
    // (only the copy will be modified)
    if (copyFile(aResFile, aNewFileName) == FALSE)
    {
        printf("Copying of the original file failed!\n");
        return loResult;   
    }
  
    // open the copied file and read the header
    loNewFile = openAESOPResourceAndSetToFirstDirectoryBlock(aNewFileName, "r+b", &loNewFileHeader);
    if (loNewFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aNewFileName);
        return loResult;
    }     
    
    // read the directory
    if (readDirectoryBlocks(loNewFile, loNewFileDirectoryPointers) == FALSE)
    {
       printf("The reading of directory blocks in the new file failed!\n");
       fclose(loNewFile);
       return loResult;
    }

    if (patchEOB3MenuInOpenedFile(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader) == FALSE)
    {
        printf("Patching of the menu resource failed!\n");
        // mark the file as invalid (by overwriting the beginning)
        fseek(loNewFile, 0, SEEK_SET);
        fprintf(loNewFile, "BAD FILE: THE MENU RESOURCE PATCHING FAILED !!!\n");
        loResult = FALSE;        
    }
    else
    {
        loResult = TRUE;
    }

    fclose(loNewFile);  
    return loResult;
}

/*
Converts EOB 3 to AESOP/32
*/
int convertEOB3toAESOP32(FILE *aResFile, DIRPOINTER *aDirectoryPointers, char *aNewFileName)
{
    RESINFOPOINTER   *loResourcesInfoTable;
    int loResult = FALSE;
    int i;
    int loOkFontConversions = 0;
    int loOkBitmapConversions = 0;
    DIRPOINTER loNewFileDirectoryPointers[MAX_DIRECTORIES];
    struct RESGlobalHeader loNewFileHeader;
    FILE *loNewFile;

    printf("Starting the full EOB3 to AESOP/32 conversion (menu patching, bitmap/font conversion)...\n");    
    
    loResourcesInfoTable = getResourcesInformationTable(aResFile, aDirectoryPointers, FALSE);
    if (loResourcesInfoTable == NULL)
    {
        // unable to get the resource information table
        return loResult;
    }

    // copy the original file
    // (only the copy will be modified)
    if (copyFile(aResFile, aNewFileName) == FALSE)
    {
        printf("Copying of the original file failed!\n");
        return FALSE;   
    }
  
    // open the copied file and read the header
    loNewFile = openAESOPResourceAndSetToFirstDirectoryBlock(aNewFileName, "r+b", &loNewFileHeader);
    if (loNewFile == NULL)
    {
        printf("The file could not be opened: %s!\n", aNewFileName);
        return FALSE;
    }     
    
    // read the directory
    if (readDirectoryBlocks(loNewFile, loNewFileDirectoryPointers) == FALSE)
    {
       printf("The reading of directory blocks in the new file failed!\n");
       fclose(loNewFile);
       return FALSE;
    }

    // patch the menu resource
    if (patchEOB3MenuInOpenedFile(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader) == FALSE)
    {
        printf("Patching of the menu resource failed!\n");
        // mark the file as invalid (by overwriting the beginning)
        fseek(loNewFile, 0, SEEK_SET);
        fprintf(loNewFile, "BAD FILE: THE MENU RESOURCE PATCHING FAILED !!!\n");
        fclose(loNewFile);
        return FALSE;       
    }    

    // convert fonts and bitmaps
    for(i = 0; i < MAX_NUMBER_OF_DICTIONARY_ITEMS && loResourcesInfoTable[i] != NULL; i++)
    {
        int loResourceType;
        char *loName;
        int loNumber;
        
        loResourceType = loResourcesInfoTable[i]->resourceType;            
        loName = loResourcesInfoTable[i]->name;
        loNumber = loResourcesInfoTable[i]->number;
                
        if (loResourceType == RESOURCE_TYPE_BITMAP)
        {        
            if (convertOneOldBitmap(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader, loNumber, loName) == FALSE)
            {
                printf("The conversion of the bitmap resource number %d, name \"%s\" FAILED!\n", loNumber, loName);
                printf("Ending the conversion prematurely!\n");
                // mark the file as invalid (by overwriting the beginning)
                fseek(loNewFile, 0, SEEK_SET);
                fprintf(loNewFile, "BAD FILE: THE BITMAP CONVERSION FAILED !!!\n");
                fclose(loNewFile);
                return FALSE;
            }
            else
            {
                loOkBitmapConversions++;
            }
        }
        else if (loResourceType == RESOURCE_TYPE_FONT)
        {
            if (convertOneOldFont(loNewFile, loNewFileDirectoryPointers, &loNewFileHeader, loNumber, loName) == FALSE)
            {
                printf("The conversion of the font resource number %d, name \"%s\" FAILED!\n", loNumber, loName);
                printf("Ending the conversion prematurely!\n");
                // mark the file as invalid (by overwriting the beginning)
                fseek(loNewFile, 0, SEEK_SET);
                fprintf(loNewFile, "BAD FILE: THE FONT CONVERSION FAILED !!!\n");
                fclose(loNewFile);
                return FALSE;
            }
            else
            {
                loOkFontConversions++;
            }            
        }                           
    }
    fclose(loNewFile);
    printf("The number of correctly converted bitmaps: %d\n", loOkBitmapConversions);
    printf("The number of correctly converted fonts: %d\n", loOkFontConversions);    
    if (loOkBitmapConversions == 0)
    {
        printf("Warning: no bitmap conversions were done!\n");
    }
    if (loOkFontConversions == 0)
    {
        printf("Warning: no font conversions were done!\n");
    }        
    return TRUE;
}

