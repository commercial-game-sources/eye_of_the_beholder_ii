//
//  Run-time linker
//

#ifndef RTLINK_H
#define RTLINK_H

#ifdef __cplusplus
extern "C" {
#endif

HRES cdecl create_instance(RTR_class *RTR, ULONG object);
void cdecl destroy_instance(RTR_class *RTR, HRES instance);

#ifdef __cplusplus
}
#endif

#endif

