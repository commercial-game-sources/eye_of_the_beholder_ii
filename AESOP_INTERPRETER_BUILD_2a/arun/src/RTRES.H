//
//  Runtime heap/resource class
//

#ifndef RTRES_H
#define RTRES_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_OBJ_TYPES  2450      // # of possible resource names
#define DIR_BLK        256       // # of cache directory entries/block
#define OD_SIZE        128       // # of entries/ordinal file directory block

#define DA_FIXED       0x00000001U   // Entry attribute equates
#define DA_MOVEABLE    0x00000000U   // (only low word preserved in cache)
#define DA_PRECIOUS    0x00000020U
#define DA_DISCARDABLE 0x00000010U
#define DA_TEMPORARY   0x00000000U

#define DA_EVANESCENT  0x00000040U   // Special runtime attribute equates
#define DA_DISCARDED   0x00000100U
#define DA_FREE        0x00000200U
#define DA_DEFAULT     0xFFFFFFFFU

#define DA_PLACEHOLDER 0x10000000L

#define SA_UNUSED      0x00000001    // Storage attribute flag equates
#define SA_DELETED     0x00000002
                        
#define ROED 0                   // Resource Ordinal Entry Directory
#define RDES 1                   // Resource Description Directory
#define RDEP 2                   // Resource Dependency Directory
#define CRFD 3                   // Code Resource Function Directory

#define RTR_FREEBASE   0x0001U   // TRUE for destructor to free heap memory

#define SIZE_DB (DIR_BLK * sizeof(HD_entry))

#define DOS_BUFFSIZE 32768U

typedef struct
{
   void *seg;                    // pointer to resource data

   ULONG size;                   // size of resource in bytes
   ULONG flags;                  // DA_ flags
   ULONG history;                // LRU counter value
   ULONG locks;                  // locking depth
   ULONG user;                   // .RES file offset or instance object name
}
HD_entry;                        // cached resource entry descriptor

typedef struct
{
   BYTE  signature[16];
   ULONG file_size;
   ULONG lost_space;
   ULONG FOB;
   ULONG create_time;
   ULONG modify_time;
}
RF_file_hdr;                     // resource file header

typedef struct
{
   ULONG timestamp;
   ULONG data_attrib;
   ULONG data_size;
}
RF_entry_hdr;                    // resource file entry header

typedef struct OD_block
{
   ULONG next;
   UBYTE flags[OD_SIZE];
   ULONG index[OD_SIZE];
}
OD_block;

typedef struct                   // name directory entry
{                                
   ULONG OE;                     // public
   HRES thunk;                   // public
   HRES handle;                  // public
}
ND_entry;

typedef struct
{
   HD_entry *dir;             // public
   UWORD nentries;            // public

   WORD file;                    
   RF_file_hdr RFH;              
   RF_entry_hdr REH;             
   OD_block OD;                  
   ULONG cur_blk;              

   UWORD LRU_cnt;                    
   void *base;
   void *next_M;                 
   ULONG free;                   
   void *last_F;

   HRES name_dir;
   WORD nd_entries;
}
RTR_class;

//
// RTR_addr macro returns current address of resource cache entry
// (See comments in RTRES.C)
//

#define RTR_addr(x) ((void *) (* (ULONG *) (x)))

//
// RTR_member macro allows access to HD_entry structure members
//

#define RTR_member(x,y)   ( (HD_entry *)(x)->y )

//
// Extern *RTR allows public access to application's main RTR class
//

extern RTR_class *LNK;
extern RTR_class *RTR;

RTR_class *cdecl RTR_construct(void *base, ULONG size, ULONG nnames, BYTE *filename);
void cdecl RTR_destroy(RTR_class *RTR, ULONG flags);

ULONG cdecl RTR_force_discard(RTR_class *RTR, ULONG goal);

HRES cdecl RTR_alloc(RTR_class *RTR, ULONG bytes, ULONG attrib);
void cdecl RTR_free(RTR_class *RTR, HRES entry);

void cdecl RTR_lock(RTR_class *RTR, HRES entry);
void cdecl RTR_unlock(HRES entry);

ULONG cdecl RTR_size(HRES entry);

HRES cdecl RTR_get_resource_handle(RTR_class *RTR, ULONG resource, ULONG attrib);
void cdecl RTR_free_resource(RTR_class *RTR, ULONG resource);

HRES cdecl RTR_load_resource(RTR_class *RTR, ULONG resource, ULONG attrib);
void cdecl RTR_read_resource(RTR_class *RTR, void *dest, ULONG len);
ULONG cdecl RTR_seek(RTR_class *RTR, ULONG rnum);

#ifndef RTR_addr
void *cdecl RTR_addr(HRES entry);
#endif
void cdecl RTR_fixup(void **ptr, HRES entry);

ND_entry *cdecl RTR_search_name_dir(RTR_class *RTR, ULONG resource);

BYTE *cdecl ASCII_name(ULONG name);
void cdecl RTR_dump(RTR_class *RTR);

void cdecl RTR_HRES_chksum(BYTE *situation);
ULONG cdecl RTR_chksum(HRES entry);

#ifdef __cplusplus
}
#endif

#endif

