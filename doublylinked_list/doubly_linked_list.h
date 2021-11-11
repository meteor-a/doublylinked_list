#ifndef _DOUBLY_LINKED_LIST_H__
#define _DOUBLY_LINKED_LIST_H__

/*----------------------------------------------------------------------------------------------*/

#include "../../bin/_mtLib/logger/logger.h"

/*----------------------------------------------------------------------------------------------*/

#define _DEBUG_MODE_DOUBLY_LINK_LIST_OFF__  0
#define _DEBUG_MODE_DOUBLY_LINK_LIST_ON__   1

#define _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF__  0
#define _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__   1

/*----------------------------------------------------------------------------------------------*/

#define DEBUG_MODE_DOUBLY_LINK_LIST   _DEBUG_MODE_DOUBLY_LINK_LIST_OFF__

#ifndef DEBUG_MODE_DOUBLY_LINK_LIST
    #define DEBUG_MODE_DOUBLY_LINK_LIST  _DEBUG_MODE_DOUBLY_LINK_LIST_OFF__
#endif

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__

    #define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST  _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__

    #ifndef DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST
        #define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST  _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF__
    #endif

#else

    #define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST  _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF__

#endif

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__
    #define DEBUG_CODE_ADD(...) __VA_ARGS__
#endif

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_OFF__
    #define DEBUG_CODE_ADD(...)
#endif

/*----------------------------------------------------------------------------------------------*/

typedef int DoublyLinkListElemType;
typedef int DoublyLinkListIndexType;

typedef int DoublyLinkListSizeType;

/*----------------------------------------------------------------------------------------------*/

struct DoublyLinkListElem {
    DoublyLinkListElemType  data      = 0;
    DoublyLinkListIndexType next_elem = -1;
    DoublyLinkListIndexType prev_elem = -1;
};

struct DoublyLinkList {
    DoublyLinkListSizeType size       = -1;
    DoublyLinkListSizeType capacity   = -1;
    bool is_sorted = true;

    DoublyLinkListElem* list = nullptr;

    DoublyLinkListIndexType head = -1;
    DoublyLinkListIndexType tail = -1;

    DoublyLinkListIndexType free_elem_list_head = -1;
};

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListConstructor(dLinkList)              _DoublyLinkListConstructor__(dLinkList DEBUG_CODE_ADD(,            \
                                                               LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListSizeConstructor(dLinkList, capacity) _DoublyLinkListConstructor__(dLinkList, capacity DEBUG_CODE_ADD(,  \
                                                               LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList, int capacity DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListDestructor(dLinkList) _DoublyLinkListDestructor__(dLinkList DEBUG_CODE_ADD(,                 \
                                                          LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListDestructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListPushHead(dLinkList, val) _DoublyLinkListPushHead__(dLinkList, val DEBUG_CODE_ADD(,               \
                                                          LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPushHead__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPushTail(dLinkList, val) _DoublyLinkListPushTail__(dLinkList, val DEBUG_CODE_ADD(,               \
                                                          LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPushTail__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPushAfterIndex(dLinkList, val, index_after_push) _DoublyLinkListPushAfterIndex__(dLinkList, val, index_after_push     \
                                                                DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPushAfterIndex__  (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPushBeforeIndex(dLinkList, val, index_before_push) _DoublyLinkListPushBeforeIndex__(dLinkList, val, index_before_push  \
                                                                DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListPopHead(dLinkList) _DoublyLinkListPopHead__(dLinkList DEBUG_CODE_ADD(,               \
                                                                  LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopHead__         (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopTail(dLinkList) _DoublyLinkListPopTail__(dLinkList DEBUG_CODE_ADD(,               \
                                                                  LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopTail__         (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopAfterIndex(dLinkList, index_after_pop)   _DoublyLinkListPopAfterIndex__(dLinkList, index_after_pop   \
                                                                   DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopAfterIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_after_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopBeforeIndex(dLinkList, index_before_pop) _DoublyLinkListPopBeforeIndex__(dLinkList, index_before_pop \
                                                                    DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_before_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define If_you_call_this_function_you_will_wake_up_very_angry_ahatina_and_she_will_want_to_kill_anyone_who_she_will_be_near_if_you_want_to_save_you_live_dont_do_stupid_action_if_you_think_she_is_slow_you_are_wrong_she_is_faster_than_meteor_it_is_you_choose(dLinkList) _If_you_call_this_function_you_will_wake_up_very_angry_ahatina_and_she_will_want_to_kill_anyone_who_she_will_be_near_if_you_want_to_save_you_live_dont_do_stupid_action_if_you_think_she_is_slow_you_are_wrong_she_is_faster_than_meteor_it_is_you_choose__(dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _If_you_call_this_function_you_will_wake_up_very_angry_ahatina_and_she_will_want_to_kill_anyone_who_she_will_be_near_if_you_want_to_save_you_live_dont_do_stupid_action_if_you_think_she_is_slow_you_are_wrong_she_is_faster_than_meteor_it_is_you_choose__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#endif
