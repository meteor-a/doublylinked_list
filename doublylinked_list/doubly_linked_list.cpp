#include "doubly_linked_list.h"
#include "../bin/_mtLib/base_lib/base_lib.h"

/*----------------------------------------------------------------------------------------------*/

#include <stdlib.h>

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON 
    const char* LOG_FILENAME_TEXT              = "log_doubly_link_list_text.txt";
    const char* NAME_MODULE_DOUBLY_LINKED_LIST = "DOUBLY_LINKED_LIST";
#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON
    const char* LOG_FILENAME_VISUAL        = "log_doubly_link_list_visual.txt";
#endif

/*----------------------------------------------------------------------------------------------*/

#define DoublyLinkListOK(dLinkList) DoublyLinkListOK__(dLinkList, info_call)

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON

    #define DoublyLinkListOK__(dLinkList, info_call)                                                                         \
        {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                      \
            _ERROR_INFO__ err_inf = _DoublyLinkListOK__(dLinkList);                                                                \
            if (err_inf.err_code == EXIT_FAILURE) {                                                                                \
                CreateErrorLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, info_call, place_where_check); \
                CreateTextDump(dLinkList);                                                                                         \
                return EXIT_FAILURE;                                                                                               \
            }                                                                                                                      \
        }

#elif

    #define DoublyLinkListOK(dLinkList) DoublyLinkListOK__(dLinkList)

    #define DoublyLinkListOK__(dLinkList)                                                   \
        {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};     \
            _ERROR_INFO__ err_inf = _DoublyLinkListOK__(dLinkList);                                                                \
            if (err_inf.err_code == EXIT_FAILURE) {                                                                                \
                CreateErrorLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, place_where_check);            \
                return EXIT_FAILURE;                                                                                               \
            }                                                                                                                      \
        }                                                                                                                          

#endif

/*----------------------------------------------------------------------------------------------*/

const char* _ERROR_BAD_LIST_PTR__ = "";

/*----------------------------------------------------------------------------------------------*/

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList);

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON
    int CreateTextDump(DoublyLinkList* dLinkList);
#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON
    int CreateVisualDump(DOUBLY_LINK_LIST* dLinkList);
#endif

/*----------------------------------------------------------------------------------------------*/

const int DEFAULT_START_CAPACITY      = 16;
const int DEFAULT_DIFFERENCE_CAPACITY = 16;
const DoublyLinkListElemType DEFAULT_START_DATA = -7854;

/*----------------------------------------------------------------------------------------------*/

int InizializeList(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    dLinkList->size      = 0;
    dLinkList->capacity  = DEFAULT_START_CAPACITY;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));
    dLinkList->head = dLinkList->list;
    dLinkList->tail = dLinkList->list;

    InizializeList(dLinkList DEBUG_CODE_ADD(, info_call));

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS;
}

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList, int capacity DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    dLinkList->size      = 0;
    dLinkList->capacity  = capacity;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));
    dLinkList->head = dLinkList->list;
    dLinkList->tail = dLinkList->list;

    InizializeList(dLinkList DEBUG_CODE_ADD(, info_call));

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS;
}

int InizializeList(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
   for (int cur_elem = 0; cur_elem < dLinkList->capacity; ++cur_elem) {
       dLinkList->list[cur_elem].data = DEFAULT_START_DATA;
       dLinkList->list[cur_elem].next_elem = nullptr;
       dLinkList->list[cur_elem].prev_elem = nullptr;
   }

   dLinkList->free_elems = dLinkList->head;
   for (int cur_elem = 0; cur_elem < dLinkList->capacity - 1; ++cur_elem) {
       dLinkList->head->next_elem = dLinkList->list + cur_elem;
   }
   
    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListDestructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    dLinkList->size      = -1;
    dLinkList->capacity  = -1;
    dLinkList->is_sorted = false;

    free(dLinkList->list);

    dLinkList->list = (DoublyLinkListElem*)POISON_POINTERS__::pNullData;
    dLinkList->head = (DoublyLinkListElem*)POISON_POINTERS__::pNullData;
    dLinkList->tail = (DoublyLinkListElem*)POISON_POINTERS__::pNullData;
    dLinkList->free_elems = (DoublyLinkListElem*)POISON_POINTERS__::pNullData;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPushHead__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)

    

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------------------------*/

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = 1;
        err.text_err = 
    }
    if (_IsBadReadPtr(dLinkList->list)) {

    }
    if (_IsBadReadPtr(dLinkList->tail)) {

    }
    if (_IsBadReadPtr(dLinkList->head)) {

    }

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON
    // долгие проверки
#endif

}

int CreateTextDump(DoublyLinkList* dLinkList) {

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON
    CreateVisualDump(dLinkList);
#endif

    return EXIT_SUCCESS;
}
