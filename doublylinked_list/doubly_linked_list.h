#ifndef DOUBLY_LINKED_LIST_H__
#define DOUBLY_LINKED_LIST_H__

/*----------------------------------------------------------------------------------------------*/

#include "../../bin/_mtLib/logger/logger.h"

/*----------------------------------------------------------------------------------------------*/

#define DEBUG_MODE_DOUBLY_LINK_LIST_OFF  0
#define DEBUG_MODE_DOUBLY_LINK_LIST_ON   1

#define DEBUG_MODE_DOUBLY_LINK_LIST   DEBUG_MODE_DOUBLY_LINK_LIST_ON

#ifndef DEBUG_MODE_DOUBLY_LINK_LIST
    #define DEBUG_MODE_DOUBLY_LINK_LIST  DEBUG_MODE_DOUBLY_LINK_LIST_OFF
#endif

/*----------------------------------------------------------------------------------------------*/

#define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF  0
#define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON   1

#define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST  DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF

#ifndef DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST
    #define DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST  DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_OFF
#endif

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON
    #define DEBUG_CODE_ADD(...) __VA_ARGS__
#endif

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_OFF
    #define DEBUG_CODE_ADD(...)
#endif

/*----------------------------------------------------------------------------------------------*/

typedef int DoublyLinkListElemType;
typedef int DoublyLinkListIndex;

/*----------------------------------------------------------------------------------------------*/

struct DoublyLinkListElem {
    DoublyLinkListElemType data   = 0;
    DoublyLinkListIndex next_elem = -1;
    DoublyLinkListIndex prev_elem = -1;
};

struct DoublyLinkList {
    DoublyLinkListIndex size       = -1;
    DoublyLinkListIndex capacity   = -1;
    bool is_sorted = true;

    DoublyLinkListElem* list = nullptr;

    DoublyLinkListIndex head = -1;
    DoublyLinkListIndex tail = -1;

    DoublyLinkListIndex free_elem_list = -1;
};

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListConstructor(dLinkList) _DoublyLinkListConstructor__(dLinkList DEBUG_CODE_ADD(,               \
                                                          LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListSizeConstructor(dLinkList, capacity) _DoublyLinkListConstructor__(dLinkList, capacity DEBUG_CODE_ADD(,  \
                                                          LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList, int capacity DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListDestructor(dLinkList) _DoublyLinkListDestructor__(dLinkList DEBUG_CODE_ADD(,               \
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
int _DoublyLinkListPushAfterIndex__  (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndex index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPushBeforeIndex(dLinkList, val, index_before_push) _DoublyLinkListPushBeforeIndex__(dLinkList, val, index_before_push  \
                                                                DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndex index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListPopHead(dLinkList) _DoublyLinkListPopHead__(dLinkList DEBUG_CODE_ADD(,               \
                                                                  LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopHead__         (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopTail(dLinkList) _DoublyLinkListPopTail__(dLinkList DEBUG_CODE_ADD(,               \
                                                                  LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopTail__         (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopAfterIndex(dLinkList, index_after_push)   _DoublyLinkListPopAfterIndex__(dLinkList, index_after_push   \
                                                                   DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)}))
int _DoublyLinkListPopAfterIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndex index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

#define DoublyLinkListPopBeforeIndex(dLinkList, index_before_push) _DoublyLinkListPushBeforeIndex__(dLinkList, index_before_push \
                                                                    DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__{LOCATION_VAR__(dLinkList)})
int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListIndex index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

#endif
