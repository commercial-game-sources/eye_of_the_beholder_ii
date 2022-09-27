//
// Sound effects/music equates (shared by C and AESOP)
//

#ifndef SOUND_H
#define SOUND_H

//
// Predefined sound block handles
//

#define BLK_COMMON   0                 // COMMON sounds at EMS blocks 0-8
#define END_COMMON   8

#define BLK_LEVEL    9                 // LEVEL sounds at EMS blocks 9-14
#define END_LEVEL    14

#define FIRST_COMMON 0                 // COMMON sound array indices = 0-49
#define FIRST_LEVEL  50                // LEVEL sound array indices = 50-63

//
// COMMON sound array indices
//

#define S_LAPC_HIT  0
#define S_SWING1    1
#define S_THUMP2    2
#define S_WEASEL    3
#define S_TRNSPTR1  4
#define S_STRAVHIT  5
#define S_MISS7     6
#define S_MISS9     7
#define S_13SLING   8
#define S_PRESSURE  9
#define S_BOWTWANG  10
#define S_TWIGSNAP  11
#define S_CLINK1    12

#define S_FIREMIX1  13
#define S_WHAMMY1   14
#define S_SWARM2    15
#define S_INVISIBL  16
#define S_SPELL1    17
#define S_SPELL10   18
#define S_SPELL100  19
#define S_SPELL101  20
#define S_SPELL11   21
#define S_SPELL12   22
#define S_SPELL15   23
#define S_SPELL2    24
#define S_WATER2A   25
#define S_SPELL22   26
#define S_SPELL24   27
#define S_SPELL25   28
#define S_SPELL26   29
#define S_SPELL28   30
#define S_METALDWN  31
#define S_LGOLOM    32
#define S_CRACKLE2  33
#define S_SPELL38   34
#define S_SPELL44   35
#define S_SPELL46   36
#define S_SPELL52   37
#define S_SPELL66   38
#define S_SPELL54   39
#define S_SPELL64   40
#define S_SPELL81   41
#define S_SPELL87   42
#define S_SPELL95   43
#define S_SPELL98   44

#ifndef __AESOP__
void cdecl shutdown_sound(void);
#endif

#endif

