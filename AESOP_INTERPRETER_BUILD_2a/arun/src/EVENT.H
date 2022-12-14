//
//  Run-time event handler calls
//

#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#define EV_QSIZE 128             // max # of queued events (circular)
#define NR_LSIZE 768             // max # of event notification requests

#define NSX_IN_REGION  0x100     // notification status flags (high word)
#define NSX_OUT_REGION 0x200
#define NSX_TYPE       0x00FF    // notification event type mask (low word)

typedef struct NREQ
{
   LONG  next;
   LONG  prev;
   LONG  client;
   ULONG message;
   LONG  parameter;
   LONG  status;
}
NREQ;                            // notification request list entry

typedef struct
{
   LONG type;
   LONG owner;
   LONG parameter;
}
EVENT;

extern LONG ENABLED;

extern NREQ NR_list[NR_LSIZE];
extern LONG NR_first[NUM_EVTYPES];

extern LONG current_event_type;

//
// Internal calls
//

void cdecl init_notify_list(void);
void cdecl add_notify_request(LONG client, LONG message, LONG event, LONG
   parameter);
void cdecl delete_notify_request(LONG client, LONG message, LONG event,
   LONG parameter);
void cdecl cancel_entity_requests(LONG client);
void cdecl init_event_queue(void);
EVENT *cdecl find_event(LONG type, LONG parameter);
void cdecl remove_event(LONG type, LONG parameter, LONG owner);
void cdecl add_event(LONG type, LONG parameter, LONG owner);
EVENT *cdecl next_event(void);
EVENT *cdecl fetch_event(void);
void cdecl dump_event_queue(void);

void DISABLE(void);
void ENABLE(void);

//
// AESOP code resource calls
//

void cdecl notify(LONG argcnt, ULONG index, ULONG message, LONG event,
   LONG parameter);
void cdecl cancel(LONG argcnt, ULONG index, ULONG message, LONG event,
   LONG parameter);
void cdecl drain_event_queue(void);
void cdecl post_event(LONG argcnt, ULONG owner, LONG event, LONG parameter);
void cdecl send_event(LONG argcnt, ULONG owner, LONG event, LONG parameter);
ULONG cdecl peek_event(void);
void cdecl dispatch_event(void);
void cdecl flush_event_queue(LONG argcnt, LONG owner, LONG event, LONG parameter);

#ifdef __cplusplus
}
#endif

#endif

