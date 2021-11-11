#include "doubly_linked_list.h"
#include "../../bin/_mtLib/base_lib/base_lib.h"

/*----------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h> 

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__ 
    const char* LOG_FILENAME_TEXT              = "log_doubly_link_list_text.txt";
    const char* NAME_MODULE_DOUBLY_LINKED_LIST = "DOUBLY_LINKED_LIST";
#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
    const char* LOG_FILENAME_VISUAL        = "log_doubly_link_list_visual.txt";
#endif

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__

    #define DoublyLinkListOK(dLinkList) DoublyLinkListOK__(dLinkList, info_call)

    #define DoublyLinkListOK__(dLinkList, info_call)                                                                         \
        {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                      \
            _ERROR_INFO__ err_inf = _DoublyLinkListOK__(dLinkList);                                                                \
            if (err_inf.err_code != _ERROR_CODE_SUCCESSFULL__) {                                                                   \
                CreateErrorLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, info_call, place_where_check); \
                CreateDump(dLinkList);                                                                                             \
                return err_inf.err_code;                                                                                           \
            }                                                                                                                      \
        }

#elif

    #define DoublyLinkListOK(dLinkList) DoublyLinkListOK__(dLinkList)

    #define DoublyLinkListOK__(dLinkList)                                                   \
        {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};     \
            _ERROR_INFO__ err_inf = _DoublyLinkListOK__(dLinkList);                                                                \
            if (err_inf.err_code != _ERROR_CODE_SUCCESSFULL__) {                                                                   \
                CreateErrorLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, place_where_check);            \
                return err_inf.err_code;                                                                                           \
            }                                                                                                                      \
        }                                                                                                                          

#endif

#define CheckBeforeConstract(dLinkList)                                                                                  \
    {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                      \
        _ERROR_INFO__ err_inf = _CheckBeforeConstract__(dLinkList);                                                      \
        if (err_inf.err_code != _ERROR_CODE_SUCCESSFULL__) {                                                             \
            CreateWarningLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_inf.text_err, place_where_check);    \
            return err_inf.err_code;                                                                                     \
        }                                                                                                                \
    }

#define _WARNING_DOUBLY_LINK_LIST__(condition, code_warn, warn_text)                                                        \
    {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                         \
        if (condition) {                                                                                                    \
            CreateWarningLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, warn_text, place_where_check);              \
            return code_warn;                                                                                               \
        }                                                                                                                   \
    }

#define _ERROR_DOUBLY_LINK_LIST__(condition, code_err, err_text)                                                            \
    {   LOCATION_VAR_CALL_STRUCT__ place_where_check = {LOCATION_VAR__(dLinkList)};                                         \
        if (condition) {                                                                                                    \
            CreateErrorLog(LOG_FILENAME_TEXT, NAME_MODULE_DOUBLY_LINKED_LIST, err_text, place_where_check);                 \
            CreateDump(dLinkList);                                                                                          \
            return code_err;                                                                                                \
        }                                                                                                                   \
    }

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList);
_ERROR_INFO__ _CheckBeforeConstract__(DoublyLinkList* dLinkList);

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
    int CreateDump(DoublyLinkList* dLinkList);
#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
    int CreateVisualDump(DoublyLinkList* dLinkList);
#endif

/*----------------------------------------------------------------------------------------------*/

const int _ERROR_CODE_SUCCESSFULL__ = 0;
const int _ERROR_CODE_INCORRECT_CAPACITY__ = 1;
const int _ERROR_CODE_CANT_CALLOC_MEM__ = 2;
const int _ERROR_CODE_BAD_DOUBLY_LINK_LIST_PTR__ = 3;

/*----------------------------------------------------------------------------------------------*/

const char* _ERROR_TEXT_INCORRECT_CAPACITY__ = "Incorrect capacity of doubly link list";
const char* _ERROR_TEXT_CANT_CALLOC_MEM__    = "Can't calloc memory";
const char* _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__ = "Bad pointer to the doubly linked list";

/*----------------------------------------------------------------------------------------------*/

const int _WARN_CODE_REPEAT_CONSTRUCTOR__   = 101;
const int _WARN_CODE_PUSH_INCORRECT_INDEX__ = 102;
const int _WARN_CODE_POP_ON_EMPTY_LIST__    = 103;
const int _WARN_CODE_POP_INCORRECT_INDEX__  = 104;
const int _WARN_CODE_CANT_OPEN_DUMP_FILE__  = 105;

/*----------------------------------------------------------------------------------------------*/

const char* _WARN_TEXT_PUSH_INCORRECT_INDEX__ = "Incorect index to push";
const char* _WARN_TEXT_POP_ON_EMPTY_LIST__    = "Try to pop on empty doubly linked list";
const char* _WARN_TEXT_POP_INCORRECT_INDEX__  = "Try to pop on incorect index";
const char* _WARN_TEXT_CANT_OPEN_DUMP_FILE__  = "Cant open dump file to write";

/*----------------------------------------------------------------------------------------------*/


const int DEFAULT_START_CAPACITY      = 16;
const int DEFAULT_DIFFERENCE_CAPACITY = 16;
const DoublyLinkListElemType DEFAULT_START_DATA = -7854;

/*----------------------------------------------------------------------------------------------*/

int _InizializeList__      (DoublyLinkList* dLinkList);
int _DeInizializeList__    (DoublyLinkList* dLinkList);
int AllocateMoreMemory     (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));
int AllocateLeaseMemory    (DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call));
int getEmptyIndex          (DoublyLinkList* dLinkList);
int setEmptyIndex          (DoublyLinkList* dLinkList, DoublyLinkListIndexType index);
bool _IsInizializeElem__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index);

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    CheckBeforeConstract(dLinkList)

    dLinkList->size      = 0;
    dLinkList->capacity  = DEFAULT_START_CAPACITY;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));
    _ERROR_DOUBLY_LINK_LIST__(dLinkList->list == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    _InizializeList__(dLinkList);

    DoublyLinkListOK(dLinkList)

    return _ERROR_CODE_SUCCESSFULL__;
}

int _DoublyLinkListConstructor__(DoublyLinkList* dLinkList, int capacity DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    CheckBeforeConstract(dLinkList)
    _ERROR_DOUBLY_LINK_LIST__(capacity < 0, _ERROR_CODE_INCORRECT_CAPACITY__, _ERROR_TEXT_INCORRECT_CAPACITY__)

    dLinkList->size      = 0;
    dLinkList->capacity  = capacity;
    dLinkList->is_sorted = true;

    dLinkList->list = (DoublyLinkListElem*) calloc(dLinkList->capacity, sizeof(DoublyLinkListElem));
    _ERROR_DOUBLY_LINK_LIST__(dLinkList->list == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    _InizializeList__(dLinkList);

    DoublyLinkListOK(dLinkList)

    return _ERROR_CODE_SUCCESSFULL__;
}

int _InizializeList__(DoublyLinkList* dLinkList) {
    for (DoublyLinkListIndexType cur_elem = 0; cur_elem < dLinkList->capacity; ++cur_elem) {
        dLinkList->list[cur_elem].data = DEFAULT_START_DATA;
        dLinkList->list[cur_elem].next_elem = -1;
        dLinkList->list[cur_elem].prev_elem = -1;
    }

    dLinkList->free_elem_list_head = 1;
    for (DoublyLinkListIndexType cur_index = 1; cur_index < dLinkList->capacity - 1; ++cur_index) {
         dLinkList->list[cur_index].next_elem = cur_index + 1;
    }
    dLinkList->list[dLinkList->capacity - 1].next_elem = 0;

    dLinkList->head = 0;
    dLinkList->tail = 0;
   
    return _ERROR_CODE_SUCCESSFULL__;
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListDestructor__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    _DeInizializeList__(dLinkList);

    dLinkList->size      = -1;
    dLinkList->capacity  = -1;
    dLinkList->is_sorted = false;

    free(dLinkList->list);

    dLinkList->list = (DoublyLinkListElem*)POISON_POINTERS__::pNullData;
    dLinkList->head = -1;
    dLinkList->tail = -1;
    dLinkList->free_elem_list_head = -1;

    return _ERROR_CODE_SUCCESSFULL__;
}

int _DeInizializeList__    (DoublyLinkList* dLinkList) {
    for (DoublyLinkListIndexType cur_elem = 0; cur_elem < dLinkList->capacity; ++cur_elem) {
        dLinkList->list[cur_elem].data = DEFAULT_START_DATA;
        dLinkList->list[cur_elem].next_elem = -1;
        dLinkList->list[cur_elem].prev_elem = -1;
    }

    return _ERROR_CODE_SUCCESSFULL__;
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPushHead__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndexType ind_for_new_elem = getEmptyIndex(dLinkList);

    dLinkList->list[ind_for_new_elem].prev_elem = 0;
    dLinkList->list[ind_for_new_elem].next_elem = dLinkList->head;
    if (dLinkList->size >= 1) {
        dLinkList->list[dLinkList->head].prev_elem = ind_for_new_elem;
    }
    else {
        dLinkList->tail = ind_for_new_elem;
    }
    dLinkList->head = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return ind_for_new_elem;
}

int _DoublyLinkListPushTail__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndexType ind_for_new_elem = getEmptyIndex(dLinkList);

    dLinkList->list[ind_for_new_elem].prev_elem = dLinkList->tail;
    dLinkList->list[ind_for_new_elem].next_elem = 0;
    if (dLinkList->size >= 1) {
        dLinkList->list[dLinkList->tail].next_elem = ind_for_new_elem;
    }
    else {
        dLinkList->head = ind_for_new_elem;
    }
    dLinkList->tail = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return ind_for_new_elem;
}

int _DoublyLinkListPushAfterIndex__  (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(!_IsInizializeElem__(dLinkList, index_after_push) || index_after_push < 0, _WARN_CODE_PUSH_INCORRECT_INDEX__,
                                _WARN_TEXT_PUSH_INCORRECT_INDEX__)

    if (index_after_push == dLinkList->tail) {
        return _DoublyLinkListPushTail__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListIndexType ind_for_new_elem = getEmptyIndex(dLinkList);

    dLinkList->list[ind_for_new_elem].prev_elem = index_after_push;
    dLinkList->list[ind_for_new_elem].next_elem = dLinkList->list[index_after_push].next_elem;
    dLinkList->list[index_after_push].next_elem = ind_for_new_elem;
    dLinkList->list[dLinkList->list[ind_for_new_elem].next_elem].prev_elem = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return ind_for_new_elem;                                     
}

int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    
    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(!_IsInizializeElem__(dLinkList, index_before_push) || index_before_push < 1, _WARN_CODE_PUSH_INCORRECT_INDEX__,
                                                    _WARN_TEXT_PUSH_INCORRECT_INDEX__)

    if (index_before_push == dLinkList->head) {
        return _DoublyLinkListPushHead__(dLinkList, val DEBUG_CODE_ADD(, info_call));
    } 

    DoublyLinkListIndexType ind_for_new_elem = getEmptyIndex(dLinkList);

    dLinkList->list[ind_for_new_elem].next_elem  = index_before_push;
    dLinkList->list[ind_for_new_elem].prev_elem  = dLinkList->list[index_before_push].prev_elem;
    dLinkList->list[dLinkList->list[index_before_push].prev_elem].next_elem = ind_for_new_elem;
    dLinkList->list[index_before_push].prev_elem = ind_for_new_elem;

    dLinkList->list[ind_for_new_elem].data = val;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity) {
        AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return ind_for_new_elem;  
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPopHead__ (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(dLinkList->size == 0, _WARN_CODE_POP_ON_EMPTY_LIST__, _WARN_TEXT_POP_ON_EMPTY_LIST__)

    DoublyLinkListIndexType new_head = 0;
    if (dLinkList->size > 1) {
        new_head = dLinkList->list[dLinkList->head].next_elem;
        dLinkList->list[new_head].prev_elem = 0;
        dLinkList->list[dLinkList->list[dLinkList->head].next_elem].prev_elem = new_head;
    }

    --dLinkList->size;

    setEmptyIndex(dLinkList, dLinkList->head);

    dLinkList->head = new_head;

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return new_head; 
}

int _DoublyLinkListPopTail__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(dLinkList->size == 0, _WARN_CODE_POP_ON_EMPTY_LIST__, _WARN_TEXT_POP_ON_EMPTY_LIST__)

    DoublyLinkListIndexType new_tail = 0;
    if (dLinkList->size > 1) {
        new_tail = dLinkList->list[dLinkList->tail].prev_elem;
        dLinkList->list[new_tail].next_elem = 0;
    }

    --dLinkList->size;

    setEmptyIndex(dLinkList, dLinkList->tail);

    dLinkList->tail = new_tail;

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return new_tail; 
}

int _DoublyLinkListPopAfterIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_after_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(_IsInizializeElem__(dLinkList, index_after_pop) || index_after_pop < 0, _WARN_CODE_POP_INCORRECT_INDEX__,
                                _WARN_TEXT_POP_INCORRECT_INDEX__)

    if (index_after_pop == dLinkList->list[dLinkList->tail].prev_elem) {
        return _DoublyLinkListPopTail__(dLinkList DEBUG_CODE_ADD(, info_call));
    } else if (index_after_pop == dLinkList->tail) {
        _WARNING_DOUBLY_LINK_LIST__(true, _WARN_CODE_POP_INCORRECT_INDEX__, _WARN_TEXT_POP_INCORRECT_INDEX__)
    }

    DoublyLinkListIndexType deleting_elem = dLinkList->list[index_after_pop].next_elem;
    dLinkList->list[index_after_pop].next_elem = dLinkList->list[deleting_elem].next_elem;
    dLinkList->list[dLinkList->list[deleting_elem].next_elem].prev_elem = index_after_pop;

    --dLinkList->size;

    setEmptyIndex(dLinkList, dLinkList->tail);

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return deleting_elem; 
}

int _DoublyLinkListPopBeforeIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_before_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(_IsInizializeElem__(dLinkList, index_before_pop) || index_before_pop < 0, _WARN_CODE_POP_INCORRECT_INDEX__,
                                _WARN_TEXT_POP_INCORRECT_INDEX__)

    if (index_before_pop == dLinkList->list[dLinkList->head].next_elem) {
        return _DoublyLinkListPopHead__(dLinkList DEBUG_CODE_ADD(, info_call));
    } else if (index_before_pop == dLinkList->head) {
        _WARNING_DOUBLY_LINK_LIST__(true, _WARN_CODE_POP_INCORRECT_INDEX__, _WARN_TEXT_POP_INCORRECT_INDEX__)
    }

    DoublyLinkListIndexType deleting_elem = dLinkList->list[index_before_pop].prev_elem;
    dLinkList->list[index_before_pop].prev_elem = dLinkList->list[deleting_elem].prev_elem;
    dLinkList->list[dLinkList->list[deleting_elem].prev_elem].next_elem = index_before_pop;

    --dLinkList->size;

    setEmptyIndex(dLinkList, dLinkList->tail);

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)

    return deleting_elem; 
}

/*----------------------------------------------------------------------------------------------*/

int AllocateMoreMemory(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    dLinkList->list = (DoublyLinkListElem*) realloc(dLinkList->list, 
                                                    (dLinkList->capacity + DEFAULT_DIFFERENCE_CAPACITY) * sizeof(DoublyLinkListElem));
    _ERROR_DOUBLY_LINK_LIST__(dLinkList->list == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    dLinkList->capacity += DEFAULT_DIFFERENCE_CAPACITY;

    DoublyLinkListOK(dLinkList)

    return _ERROR_CODE_SUCCESSFULL__;
}

int AllocateLeaseMemory(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    DoublyLinkListIndexType new_index = 1;
    for (DoublyLinkListIndexType cur_ind = dLinkList->head; cur_ind < dLinkList->size;) {
        if (cur_ind > dLinkList->capacity - DEFAULT_DIFFERENCE_CAPACITY) {
            while (_IsInizializeElem__(dLinkList, new_index)) ++new_index;
            if (cur_ind == dLinkList->head) {
                dLinkList->list[new_index] = dLinkList->list[dLinkList->head];
                dLinkList->list[dLinkList->list[dLinkList->head].next_elem].prev_elem = new_index;
                dLinkList->head = new_index;
            } else if (cur_ind == dLinkList->tail) {
                dLinkList->list[new_index] = dLinkList->list[dLinkList->tail];
                dLinkList->list[dLinkList->list[dLinkList->head].prev_elem].next_elem = new_index;
                dLinkList->tail = new_index;
            } else {
                dLinkList->list[new_index] = dLinkList->list[cur_ind];
                dLinkList->list[dLinkList->list[cur_ind].prev_elem].next_elem = new_index;
                dLinkList->list[dLinkList->list[cur_ind].next_elem].prev_elem = new_index;
            }
            setEmptyIndex(dLinkList, cur_ind);
        }
        cur_ind = dLinkList->list[cur_ind].next_elem;
    }

    dLinkList->list = (DoublyLinkListElem*) realloc(dLinkList->list, 
                                                    (dLinkList->capacity - DEFAULT_DIFFERENCE_CAPACITY) * sizeof(DoublyLinkListElem));
    _ERROR_DOUBLY_LINK_LIST__(dLinkList->list == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    dLinkList->capacity -= DEFAULT_DIFFERENCE_CAPACITY;

    dLinkList->free_elem_list_head = dLinkList->size;
    for (DoublyLinkListIndexType cur_index = dLinkList->size; cur_index < dLinkList->capacity - 1; ++cur_index) {
         dLinkList->list[cur_index].next_elem = cur_index + 1;
    }
    dLinkList->list[dLinkList->capacity - 1].next_elem = 0;

    DoublyLinkListOK(dLinkList)
    return _ERROR_CODE_SUCCESSFULL__;
}

/*----------------------------------------------------------------------------------------------*/

int getEmptyIndex(DoublyLinkList* dLinkList) {
    DoublyLinkListIndexType ind_for_new_elem = dLinkList->free_elem_list_head;
    dLinkList->free_elem_list_head = dLinkList->list[dLinkList->free_elem_list_head].next_elem; 

    return ind_for_new_elem;
}

int setEmptyIndex(DoublyLinkList* dLinkList, DoublyLinkListIndexType index ) {
    dLinkList->list[index].data      = DEFAULT_START_DATA;
    dLinkList->list[index].next_elem = -1;
    dLinkList->list[index].prev_elem = -1;

    dLinkList->list[index].next_elem = dLinkList->free_elem_list_head;
    dLinkList->free_elem_list_head   = index;

    return _ERROR_CODE_SUCCESSFULL__;
}

/*----------------------------------------------------------------------------------------------*/

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (_IsBadReadPtr(dLinkList->list)) {
        err.err_code = 2;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->size > dLinkList->capacity) {
        err.err_code = 4;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->size < 0) {
        err.err_code = 5;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->capacity < 0) {
        err.err_code = 6;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__
    // долгие проверки
#endif

    return err;
}

_ERROR_INFO__ _CheckBeforeConstract__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (dLinkList->list != nullptr) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->size != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->capacity != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->head != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }
    else if (dLinkList->tail != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (dLinkList->free_elem_list_head != -1) {
        err.err_code = 1;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    }

    return err;
}

bool _IsInizializeElem__(DoublyLinkList* dLinkList, DoublyLinkListIndexType index) {
    if (dLinkList->list[index].data != DEFAULT_START_DATA &&
        dLinkList->list[index].next_elem != -1 &&
        dLinkList->list[index].prev_elem != -1) {

        return true;
    }

    return false;
}

int CreateDump(DoublyLinkList* dLinkList) {
    FILE* dump_file = fopen("dump_file.html", "a+");
    _WARNING_DOUBLY_LINK_LIST__(dump_file == nullptr, _WARN_CODE_CANT_OPEN_DUMP_FILE__, _WARN_TEXT_CANT_OPEN_DUMP_FILE__);

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(dump_file, "<pre>\n");
    fprintf(dump_file, "%s\n\n", asctime(timeinfo));
    fprintf(dump_file, "size = %d\ncapacity = %d\nhead = %d\ntail = %d\nfree_elems = %d\nis_sorted = %d\n\n",
            dLinkList->size, dLinkList->capacity, dLinkList->head, dLinkList->tail, dLinkList->free_elem_list_head, dLinkList->is_sorted);
    
    fprintf(dump_file, "index ");
    for (DoublyLinkListIndexType cur_ind = 0; cur_ind < dLinkList->size; ++cur_ind) fprintf(dump_file, " %d ", cur_ind);

    fprintf(dump_file, "\ndata  ");
    for (DoublyLinkListIndexType cur_ind = 0; cur_ind < dLinkList->size; ++cur_ind) fprintf(dump_file, " %d ", dLinkList->list[cur_ind].data);

    fprintf(dump_file, "\nnext  ");
    for (DoublyLinkListIndexType cur_ind = 0; cur_ind < dLinkList->size; ++cur_ind) fprintf(dump_file, " %d ", dLinkList->list[cur_ind].next_elem);

    fprintf(dump_file, "\nprev  ");
    for (DoublyLinkListIndexType cur_ind = 0; cur_ind < dLinkList->size; ++cur_ind) fprintf(dump_file, " %d ", dLinkList->list[cur_ind].prev_elem);

    fprintf(dump_file, "\n<pre>\n");
#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
    CreateVisualDump(dLinkList);
#endif
    fprintf(dump_file, "----------------------------------------------------------------------------------------------------------");
    fclose(dump_file);
    return _ERROR_CODE_SUCCESSFULL__;
}

int CreateVisualDump(DoublyLinkList* dLinkList) {
    FILE* graph_file = fopen("graph_file.dot", "w");
    _WARNING_DOUBLY_LINK_LIST__(graph_file == nullptr, _WARN_CODE_CANT_OPEN_DUMP_FILE__, _WARN_TEXT_CANT_OPEN_DUMP_FILE__);

    fprintf(graph_file, "digraph G");
    fprintf(graph_file, " {\n");
    fprintf(graph_file, "\tnode[fontsize=9];\n");
    fprintf(graph_file, "\t{\n");
    fprintf(graph_file, "\t\trankdir=LR;\n");
    fprintf(graph_file, "\t\tnode[shape=plaintext];\n");
    fprintf(graph_file, "\t\tedge[color=white];\n");
    fprintf(graph_file, "\t\tinfo_node [shape=record, label=\"size = %d \\n capacity = %d \\n head = %d \\n tail = %d \\n free_elems_head = %d \\n is_sorted = %d\"];\n", 
            dLinkList->size, dLinkList->capacity, dLinkList->head, dLinkList->tail, dLinkList->free_elem_list_head, dLinkList->is_sorted);
    fprintf(graph_file, "\t}\n");

    fprintf(graph_file, "\t{\n");

    fprintf(graph_file, "\t\trank = same;\n");
    fprintf(graph_file, "\t\tfree_node [label=\"prev = %d \\n data = %d \\n next = %d\"];\n", dLinkList->list[dLinkList->free_elem_list_head].prev_elem,
        dLinkList->list[dLinkList->free_elem_list_head].data, dLinkList->list[dLinkList->free_elem_list_head].next_elem);


    fprintf(graph_file, "\t}\n");

    fprintf(graph_file, "\t{\n");

    const char* standart_node_name = "node_";

    fprintf(graph_file, "\t\trank = same;\n");
    for (int cur_node = 0; cur_node < dLinkList->capacity; ++cur_node) {
        fprintf(graph_file, "\t\t%s%d [label=\"prev = %d \\n data = %d \\n next = %d\"];\n", standart_node_name, cur_node, dLinkList->list[cur_node].prev_elem,
                dLinkList->list[cur_node].data, dLinkList->list[cur_node].next_elem);
    }

    fprintf(graph_file, "\t}\n");

    for (int cur_node = 1; cur_node < dLinkList->capacity; ++cur_node) {
        if (dLinkList->list[cur_node].next_elem >= 0) {
            fprintf(graph_file, "\t%s%d -> %s%d\n", standart_node_name, cur_node, standart_node_name, dLinkList->list[cur_node].next_elem);
        }
        if (dLinkList->list[cur_node].prev_elem >= 0) {
            fprintf(graph_file, "\t%s%d -> %s%d\n", standart_node_name, dLinkList->list[cur_node].prev_elem, standart_node_name, cur_node);
        }
        if (cur_node == dLinkList->free_elem_list_head) {
            fprintf(graph_file, "\tfree_node -> %s%d\n", standart_node_name, cur_node);
        }
    }

    fprintf(graph_file, "}");

    fclose(graph_file);
    return _ERROR_CODE_SUCCESSFULL__;
}

