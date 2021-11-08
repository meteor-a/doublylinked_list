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

#define CheckBeforeConstract(dLinkList)                                                                                  \
    {                                                                                                                    \
        LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                      \
        _ERROR_INFO__ err_inf = _CheckBeforeConstract__(dLinkList);                                                      \
        if (err_inf.err_code != EXIT_SUCCESS) {                                                                          \
            CreateWarningLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, place_where_check);    \
        }                                                                                                                \
    }

#define WARNING_DOUBLY_LINK_LIST(condition, warn_text)                                                            \
    {                                                                                                             \
        LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                               \
        if (condition) {                                                                                          \
            CreateWarningLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, warn_text, place_where_check);    \
        }                                                                                                         \
        return 1;                                                                                                 \
    }

/*----------------------------------------------------------------------------------------------*/

const char* _ERROR_BAD_DOUBLY_LINK_LIST_PTR__ = "Failed: Bad pointer to the doubly linked list";
const char* _ERROR_BAD_LIST_PTR__             = "Failed: Bad pointer to the list int doubly linked list";
const char* _ERROR_WHILE_CONSTARACT__         = "Failed: Repeated constructor or incorrect inizialize doubly linked list";

/*----------------------------------------------------------------------------------------------*/

const char* _WARNING_PUSH_INCORRECT_INDEX__ = "Trying to push on incorrect index";
const char* _WARNING_POP_ON_EMPTY_DOUBLY_LINK_LIST__ = "Trying to pop on empty doubly link list";

/*----------------------------------------------------------------------------------------------*/

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList);

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON
    int CreateTextDump(DoublyLinkList* dLinkList);
#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON
    int CreateVisualDump(DoublyLinkList* dLinkList);
#endif

_ERROR_INFO__ _CheckBeforeConstract__(DoublyLinkList* dLinkList);

/*----------------------------------------------------------------------------------------------*/

const int DEFAULT_START_CAPACITY      = 16;
const int DEFAULT_DIFFERENCE_CAPACITY = 16;
const DoublyLinkListElemType DEFAULT_START_DATA = -7854;

/*----------------------------------------------------------------------------------------------*/

int InizializeList      (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

int AllocateMoreMemory  (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

int AllocateLeaseMemory (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

int getEmptyIndex       (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

int setEmptyIndex       (DoublyLinkList* dLinkList, DoublyLinkListIndex index DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    CheckBeforeConstract(dLinkList)

    dLinkList->size      = 0;
    dLinkList->capacity  = DEFAULT_START_CAPACITY;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));

    InizializeList(dLinkList DEBUG_CODE_ADD(, info_call));

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS;
}

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList, int capacity DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    CheckBeforeConstract(dLinkList)

    dLinkList->size      = 0;
    dLinkList->capacity  = capacity;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));

    InizializeList(dLinkList DEBUG_CODE_ADD(, info_call));

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS;
}

int InizializeList(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    dLinkList->head = 1;
    dLinkList->tail = 1;

    for (DoublyLinkListIndex cur_elem = 0; cur_elem < dLinkList->capacity; ++cur_elem) {
        dLinkList->list[cur_elem].data = DEFAULT_START_DATA;
        dLinkList->list[cur_elem].next_elem = -1;
        dLinkList->list[cur_elem].prev_elem = -1;
    }

    dLinkList->free_elem_list = 1;
    for (DoublyLinkListIndex cur_index = 1; cur_index < dLinkList->capacity - 1; ++cur_index) {
         dLinkList->list[cur_index].next_elem = cur_index + 1;
    }
    dLinkList->list[dLinkList->capacity - 1].next_elem = 0;
   
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
    dLinkList->head = -1;
    dLinkList->tail = -1;
    dLinkList->free_elem_list = -1;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPushHead__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndex ind_for_new_elem = getEmptyIndex(dLinkList DEBUG_CODE_ADD(, info_call));

    dLinkList->list[ind_for_new_elem].prev_elem = 0;
    dLinkList->list[ind_for_new_elem].next_elem = dLinkList->head;
    dLinkList->list[dLinkList->head].prev_elem  = ind_for_new_elem;
    dLinkList->head = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        return AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return EXIT_SUCCESS;
}

int _DoublyLinkListPushTail__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndex ind_for_new_elem = getEmptyIndex(dLinkList DEBUG_CODE_ADD(, info_call));

    dLinkList->list[ind_for_new_elem].prev_elem = dLinkList->tail;
    dLinkList->list[ind_for_new_elem].next_elem = 0;
    dLinkList->list[dLinkList->tail].next_elem = ind_for_new_elem;
    dLinkList->tail = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        return AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return EXIT_SUCCESS;
}

int _DoublyLinkListPushAfterIndex__  (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndex index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    WARNING_DOUBLY_LINK_LIST(index_after_push >= dLinkList->size || index_after_push < 0, _WARNING_PUSH_INCORRECT_INDEX__)

    if (index_after_push == 0) {
        return _DoublyLinkListPushHead__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    } 
    else if (index_after_push == dLinkList->size - 1) {
        return _DoublyLinkListPushTail__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListIndex ind_for_new_elem = getEmptyIndex(dLinkList DEBUG_CODE_ADD(, info_call));

    dLinkList->list[ind_for_new_elem].prev_elem = index_after_push;
    dLinkList->list[ind_for_new_elem].next_elem = dLinkList->list[index_after_push].next_elem;
    dLinkList->list[index_after_push].next_elem = ind_for_new_elem;
    dLinkList->list[dLinkList->list[ind_for_new_elem].next_elem].prev_elem = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        return AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return EXIT_SUCCESS;                                     
}

int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndex index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    
    DoublyLinkListOK(dLinkList)
    WARNING_DOUBLY_LINK_LIST(index_before_push > dLinkList->size || index_before_push < 1, _WARNING_PUSH_INCORRECT_INDEX__)


    if (index_before_push == 1) {
        return _DoublyLinkListPushHead__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    } 
    else if (index_before_push == dLinkList->size) {
        return _DoublyLinkListPushTail__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListIndex ind_for_new_elem = getEmptyIndex(dLinkList DEBUG_CODE_ADD(, info_call));

    dLinkList->list[ind_for_new_elem].next_elem  = index_before_push;
    dLinkList->list[ind_for_new_elem].prev_elem  = dLinkList->list[index_before_push].prev_elem;
    dLinkList->list[index_before_push].prev_elem = ind_for_new_elem;
    dLinkList->list[dLinkList->list[index_before_push].prev_elem].next_elem = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        return AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return EXIT_SUCCESS;  
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPopHead__ (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)
    WARNING_DOUBLY_LINK_LIST(dLinkList->size == 0, _WARNING_POP_ON_EMPTY_DOUBLY_LINK_LIST__)

    DoublyLinkListIndex new_head = 0;
    if (dLinkList->size > 1) {
        new_head = dLinkList->list[dLinkList->head].next_elem;
        dLinkList->list[new_head].prev_elem = 0;
    }

    setEmptyIndex(dLinkList, dLinkList->head DEBUG_CODE_ADD(, info_call));

    dLinkList->head = new_head;

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        return AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS; 
}

int _DoublyLinkListPopTail__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)
    WARNING_DOUBLY_LINK_LIST(dLinkList->size == 0, _WARNING_POP_ON_EMPTY_DOUBLY_LINK_LIST__)

    DoublyLinkListIndex new_tail = 0;
    if (dLinkList->size > 1) {
        new_tail = dLinkList->list[dLinkList->tail].prev_elem;
        dLinkList->list[new_tail].next_elem = 0;
    }

    setEmptyIndex(dLinkList, dLinkList->tail DEBUG_CODE_ADD(, info_call));

    dLinkList->tail = new_tail;

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        return AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }
}

int _DoublyLinkListPopAfterIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndex index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    WARNING_DOUBLY_LINK_LIST(dLinkList->size == 0, _WARNING_POP_ON_EMPTY_DOUBLY_LINK_LIST__)
}

/*----------------------------------------------------------------------------------------------*/

int getEmptyIndex(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndex ind_for_new_elem = dLinkList->free_elem_list;
    dLinkList->free_elem_list = dLinkList->list[dLinkList->free_elem_list].next_elem; 

    return ind_for_new_elem;
}

int setEmptyIndex(DoublyLinkList* dLinkList, DoublyLinkListIndex index DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    --dLinkList->size;

    return EXIT_SUCCESS;
}

int AllocateMoreMemory(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    dLinkList->list = (DoublyLinkListElem*) realloc(dLinkList->list, 
                                                    (dLinkList->capacity + DEFAULT_DIFFERENCE_CAPACITY) * sizeof(DoublyLinkListElem));

    dLinkList->capacity += DEFAULT_DIFFERENCE_CAPACITY;

    DoublyLinkListOK(dLinkList)

    return EXIT_SUCCESS;
}

int AllocateLeaseMemory(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)



    DoublyLinkListOK(dLinkList)
    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------------------------------*/

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = 1;
        err.text_err = _ERROR_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (_IsBadReadPtr(dLinkList->list)) {
        err.err_code = 2;
        err.text_err = _ERROR_BAD_LIST_PTR__;
    }
    else if (dLinkList->size > dLinkList->capacity) {
        err.err_code = 4;
        err.text_err = _ERROR_BAD_LIST_PTR__;
    }
    else if (dLinkList->size < 0) {
        err.err_code = 5;
        err.text_err = _ERROR_BAD_LIST_PTR__;
    }
    else if (dLinkList->capacity < 0) {
        err.err_code = 6;
        err.text_err = _ERROR_BAD_LIST_PTR__;
    }

#if DEBUG_MODE_DOUBLY_LINK_LIST == DEBUG_MODE_DOUBLY_LINK_LIST_ON
    // долгие проверки
#endif

}

_ERROR_INFO__ _CheckBeforeConstract__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = 1;
        err.text_err = _ERROR_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (dLinkList->list != nullptr) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    }
    else if (dLinkList->size != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    }
    else if (dLinkList->capacity != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    }
    else if (dLinkList->head != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    }
    else if (dLinkList->tail != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    } 
    else if (dLinkList->free_elem_list != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_WHILE_CONSTARACT__;
    }

    return err;
}

int CreateTextDump(DoublyLinkList* dLinkList) {

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON
    CreateVisualDump(dLinkList);
#endif

    return EXIT_SUCCESS;
}
