#include "doubly_linked_list.h"
#include "../../bin/_mtLib/base_lib/base_lib.h"
#include "doubly_linked_list_errors.h"

/*----------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h> 

/*----------------------------------------------------------------------------------------------*/

const char* LOG_FILENAME_TEXT              = "log_doubly_link_list_text.txt";
const char* NAME_MODULE_DOUBLY_LINKED_LIST = "DOUBLY_LINKED_LIST";


#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
    const char* LOG_FILENAME_VISUAL        = "dump_doubly_link_list_visual.dot";
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
    int CreateDump(DoublyLinkList* dLinkList); 

 #if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
     int CreateVisualDump(DoublyLinkList* dLinkList);
 #endif 

#elif DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_OFF__

    #define DoublyLinkListOK(dLinkList) ;
    #define CheckBeforeConstract(dLinkList) ;   
    #define _WARNING_DOUBLY_LINK_LIST__(condition, code_warn, warn_text) ;
    #define _ERROR_DOUBLY_LINK_LIST__(condition, code_err, err_text) ;                                                                                                                       

#endif

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

    dLinkList->list = (DoublyLinkListElem*) calloc((size_t) dLinkList->capacity, sizeof(DoublyLinkListElem));
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

    dLinkList->list = (DoublyLinkListElem*) calloc((size_t)dLinkList->capacity, sizeof(DoublyLinkListElem));
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

    dLinkList->list[0] = { 0,0,0 };

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

    return _DoublyLinkListPushAfterIndex__(dLinkList, val, 0 DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPushTail__        (DoublyLinkList* dLinkList, DoublyLinkListElemType val DEBUG_CODE_ADD(, 
                                      LOCATION_VAR_CALL_STRUCT__ info_call)) {
    
    DoublyLinkListOK(dLinkList)
    return _DoublyLinkListPushAfterIndex__(dLinkList, val, dLinkList->capacity DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPushBeforeIndex__ (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_before_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    return _DoublyLinkListPushAfterIndex__(dLinkList, val, index_before_push - 2 DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPushAfterIndex__  (DoublyLinkList* dLinkList, DoublyLinkListElemType val, DoublyLinkListIndexType index_after_push 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)
    _WARNING_DOUBLY_LINK_LIST__(!_IsInizializeElem__(dLinkList, index_after_push) || index_after_push < 0,
                                _WARN_CODE_PUSH_INCORRECT_INDEX__,
                                _WARN_TEXT_PUSH_INCORRECT_INDEX__)

    DoublyLinkListIndexType ind_for_new_elem = getEmptyIndex(dLinkList);
    _ERROR_DOUBLY_LINK_LIST__(ind_for_new_elem <= 0 || ind_for_new_elem > dLinkList->capacity,
                              _ERROR_CODE_CANT_GET_EMPTY_INDEX__,
                              _ERROR_TEXT_CANT_GET_EMPTY_INDEX__)

    if (index_after_push == 0) { // PUSH HEAD 
        dLinkList->list[ind_for_new_elem].prev_elem = 0;
        dLinkList->list[ind_for_new_elem].next_elem = dLinkList->head;
        if (dLinkList->size >= 1) 
            dLinkList->list[dLinkList->head].prev_elem = ind_for_new_elem;
        else 
            dLinkList->tail = ind_for_new_elem;
        dLinkList->head = ind_for_new_elem;    
    }
    else if (index_after_push == dLinkList->capacity) { // PUSH TAIL
        dLinkList->list[ind_for_new_elem].prev_elem = dLinkList->tail;
        dLinkList->list[ind_for_new_elem].next_elem = 0;
        if (dLinkList->size >= 1) 
            dLinkList->list[dLinkList->tail].next_elem = ind_for_new_elem;
        else 
            dLinkList->head = ind_for_new_elem;
        dLinkList->tail = ind_for_new_elem;        
    } else { // another place
        dLinkList->list[ind_for_new_elem].prev_elem = index_after_push;
        dLinkList->list[ind_for_new_elem].next_elem = dLinkList->list[index_after_push].next_elem;
        dLinkList->list[index_after_push].next_elem = ind_for_new_elem;
        dLinkList->list[dLinkList->list[ind_for_new_elem].next_elem].prev_elem = ind_for_new_elem;
    }

    dLinkList->list[ind_for_new_elem].data = val;

    dLinkList->is_sorted = false;

    ++dLinkList->size;

    if (dLinkList->size == dLinkList->capacity - 1) {
        AllocateMoreMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    return ind_for_new_elem;                                     
}

/*----------------------------------------------------------------------------------------------*/

int _DoublyLinkListPopHead__ (DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    return _DoublyLinkListPopAfterIndex__(dLinkList, 0 DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPopTail__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)
    return _DoublyLinkListPopAfterIndex__(dLinkList, dLinkList->capacity DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPopBeforeIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_before_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    return _DoublyLinkListPopAfterIndex__(dLinkList, index_before_pop - 2 DEBUG_CODE_ADD(, info_call));
}

int _DoublyLinkListPopAfterIndex__   (DoublyLinkList* dLinkList, DoublyLinkListIndexType index_after_pop 
                                      DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {

    DoublyLinkListOK(dLinkList)  
    _WARNING_DOUBLY_LINK_LIST__(!_IsInizializeElem__(dLinkList, index_after_pop) || index_after_pop < 0, _WARN_CODE_POP_INCORRECT_INDEX__,
                                _WARN_TEXT_POP_INCORRECT_INDEX__)
    _WARNING_DOUBLY_LINK_LIST__(dLinkList->size == 0, _WARN_CODE_POP_ON_EMPTY_LIST__, _WARN_TEXT_POP_ON_EMPTY_LIST__)  

    DoublyLinkListIndexType deleting_index = 0;
    if (index_after_pop == 0) { // POP HEAD
        deleting_index = dLinkList->head;
        dLinkList->head = dLinkList->list[dLinkList->head].next_elem;
        dLinkList->list[dLinkList->head].prev_elem = 0;
    } else if (index_after_pop == dLinkList->capacity) { // POP TAIL
        deleting_index = dLinkList->tail;
        dLinkList->tail = dLinkList->list[dLinkList->tail].prev_elem;
        dLinkList->list[dLinkList->tail].next_elem = 0;
    } else { // ELSE POP
        deleting_index = index_after_pop + 1;
        dLinkList->list[index_after_pop].next_elem = dLinkList->list[deleting_index].next_elem;
        dLinkList->list[dLinkList->list[deleting_index].next_elem].prev_elem = index_after_pop;
    }

    dLinkList->is_sorted = false;

    --dLinkList->size;

    setEmptyIndex(dLinkList, deleting_index);

    if (dLinkList->capacity - 2 * DEFAULT_DIFFERENCE_CAPACITY >= dLinkList->size) {
        AllocateLeaseMemory(dLinkList DEBUG_CODE_ADD(, info_call));
    }

    DoublyLinkListOK(dLinkList)
    return deleting_index;
}

/*----------------------------------------------------------------------------------------------*/

int AllocateMoreMemory(DoublyLinkList* dLinkList  DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    dLinkList->list = (DoublyLinkListElem*) realloc(dLinkList->list, 
                                                    ((long unsigned int)(dLinkList->capacity + DEFAULT_DIFFERENCE_CAPACITY) * sizeof(DoublyLinkListElem)));
    _ERROR_DOUBLY_LINK_LIST__(dLinkList->list == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    dLinkList->capacity += DEFAULT_DIFFERENCE_CAPACITY;

    for (DoublyLinkListIndexType cur_ind = dLinkList->capacity - 1; cur_ind >= dLinkList->capacity - DEFAULT_DIFFERENCE_CAPACITY; --cur_ind) {
        setEmptyIndex(dLinkList, cur_ind);
    }

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
                                                    (long unsigned int)(dLinkList->capacity - DEFAULT_DIFFERENCE_CAPACITY) * sizeof(DoublyLinkListElem));
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

 #if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__

_ERROR_INFO__ _DoublyLinkListOK__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        err.err_code = _ERROR_CODE_BAD_DOUBLY_LINK_LIST_PTR__;
        err.text_err = _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__;
    } 
    else if (_IsBadReadPtr(dLinkList->list)) {
        err.err_code = _ERROR_CODE_BAD_LIST_PTR__;
        err.text_err = _ERROR_TEXT_BAD_LIST_PTR__;
    }
    else if (dLinkList->size > dLinkList->capacity) {
        err.err_code = _ERROR_CODE_SIZE_MORE_CAPACITY__;
        err.text_err = _ERROR_TEXT_SIZE_MORE_CAPACITY__;
    }
    else if (dLinkList->size < 0) {
        err.err_code = _ERROR_CODE_SIZE_LESS_ZERO__;
        err.text_err = _ERROR_TEXT_SIZE_LESS_ZERO__;
    }
    else if (dLinkList->capacity < 0) {
        err.err_code = _ERROR_CODE_CAPACITY_LESS_ZERO__;
        err.text_err = _ERROR_TEXT_CAPACITY_LESS_ZERO__;
    } else if (dLinkList->list[0].next_elem != 0 || dLinkList->list[0].prev_elem != 0 || dLinkList->list[0].data != 0) {
        err.err_code = _ERROR_CODE_INCORERCT_DATA_IN_ZERO_INDEX__;
        err.text_err = _ERROR_TEXT_INCORERCT_DATA_IN_ZERO_INDEX__;
    }

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__
    // долгие проверки
#endif

    return err;
}

_ERROR_INFO__ _CheckBeforeConstract__(DoublyLinkList* dLinkList) {
    _ERROR_INFO__ err = {0, "No error"};

    if (_IsBadReadPtr(dLinkList)) {
        return { _ERROR_CODE_BAD_DOUBLY_LINK_LIST_PTR__, _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__ };
    } 
    else if (dLinkList->list != nullptr) {
        return { _ERROR_CODE_BAD_DOUBLY_LINK_LIST_PTR__, _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__ };
    }

    if (dLinkList->size     != -1     || 
        dLinkList->capacity != -1     ||
        dLinkList->head     != -1     ||
        dLinkList->tail     != -1     || 
        dLinkList->free_elem_list_head != -1) {

        return { _WARN_CODE_REPEAT_CONSTRUCTOR__, _WARN_TEXT_REPEAT_CONSTRUCTOR__ };
    }

    return err;
}

#endif

bool _IsInizializeElem__(DoublyLinkList* dLinkList, DoublyLinkListIndexType index) {
    if (dLinkList->list[index].data != DEFAULT_START_DATA &&
        dLinkList->list[index].next_elem != -1 &&
        dLinkList->list[index].prev_elem != -1) {

        return true;
    }

    return false;
}

/*----------------------------------------------------------------------------------------------*/

int _If_you_call_this_function_you_will_wake_up_very_angry_ahatina_and_she_will_want_to_kill_anyone_who_she_will_be_near_if_you_want_to_save_you_live_dont_do_stupid_action_if_you_think_she_is_slow_you_are_wrong_she_is_faster_than_meteor_it_is_you_choose__(DoublyLinkList* dLinkList DEBUG_CODE_ADD(, LOCATION_VAR_CALL_STRUCT__ info_call)) {
    DoublyLinkListOK(dLinkList)

    DoublyLinkListElem* newList = (DoublyLinkListElem*) calloc((size_t)dLinkList->capacity, sizeof(DoublyLinkListElem));
    _ERROR_DOUBLY_LINK_LIST__(newList == nullptr, _ERROR_CODE_CANT_CALLOC_MEM__, _ERROR_TEXT_CANT_CALLOC_MEM__)

    newList[0] = dLinkList->list[0];
    DoublyLinkListIndexType cur_ind_old = dLinkList->head;
    for (DoublyLinkListIndexType cur_ind = 1; cur_ind <= dLinkList->size; ++cur_ind) {
       newList[cur_ind].data = dLinkList->list[cur_ind_old].data;
       newList[cur_ind].prev_elem = cur_ind - 1;
       newList[cur_ind].next_elem = cur_ind + 1;
       cur_ind_old = dLinkList->list[cur_ind_old].next_elem;
    }
    dLinkList->head = 1;
    dLinkList->tail = dLinkList->size;
    newList[dLinkList->tail].next_elem = 0;

    free(dLinkList->list);
    dLinkList->list = newList;

    dLinkList->free_elem_list_head = dLinkList->size + 1;
    for (DoublyLinkListIndexType cur_index = dLinkList->capacity - 1; cur_index >= dLinkList->size + 1; --cur_index) {
        setEmptyIndex(dLinkList, cur_index);
        dLinkList->list[cur_index].next_elem = cur_index + 1;
    }
    dLinkList->list[dLinkList->capacity - 1].next_elem = 0;

    dLinkList->is_sorted = true;
    
    return _ERROR_CODE_SUCCESSFULL__;
}

/*----------------------------------------------------------------------------------------------*/

#if DEBUG_MODE_DOUBLY_LINK_LIST == _DEBUG_MODE_DOUBLY_LINK_LIST_ON__

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
    system("dot .\graph_file.dot -T png -o dump_png/photo.png");
#endif
    fprintf(dump_file, "----------------------------------------------------------------------------------------------------------");
    fclose(dump_file);
    return _ERROR_CODE_SUCCESSFULL__;
}

#endif

#if DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST == _DEBUG_MODE_VISUAL_DOUBLY_LINK_LIST_ON__
/*
idea was taken from: https://github.com/mishaglik/LinkedList/blob/main/src/List.cpp
*/
int CreateVisualDump(DoublyLinkList* dLinkList) {
    FILE* graph_file = fopen("graph_file.dot", "w");
    _WARNING_DOUBLY_LINK_LIST__(graph_file == nullptr, _WARN_CODE_CANT_OPEN_DUMP_FILE__, _WARN_TEXT_CANT_OPEN_DUMP_FILE__);

    const char* default_name_node = "node_";
    char color_all[20]   = "beige";
    char color_head[20]  = "green4";
    char color_tail[20]  = "brown1";
    char color_empty[20] = "chartreuse1";

    fprintf(graph_file, "digraph G{\n");
    fprintf(graph_file, "   rankdir=LR;\n");
    fprintf(graph_file, "   splines=ortho;\n");
    fprintf(graph_file, "   nodesep=1;\n");
    fprintf(graph_file, "   info_node[shape=\"circle\", style=\"filled\", fillcolor=\"%s\", label=\"INFO:\\nsize = %d\\ncapacity = %d\\nhead = %d\\ntail = %d\\nfree = %d\\nis_sorted = %d\"];\n",
        "aquamarine3", dLinkList->size, dLinkList->capacity, dLinkList->head, dLinkList->tail, dLinkList->free_elem_list_head, dLinkList->is_sorted);
    fprintf(graph_file, "   free_node[shape=\"circle\", style=\"filled\", fillcolor=\"%s\", label=\"FREE SPACE\"];\n", color_empty);


    for (int cur_node = 0; cur_node < dLinkList->capacity; ++cur_node) {
        char* color = color_all;
        if (cur_node == dLinkList->head) {
            color = color_head;
        }
        else if (cur_node == dLinkList->tail) {
            color = color_tail;
        }
        else if (dLinkList->list[cur_node].prev_elem == -1) {
            color = color_empty;
        }
        fprintf(graph_file, "   %s%d[shape=\"record\", style=\"filled\", fillcolor=\"%s\", label=\" ind = %d | data = %d | { prev = %d | next = %d}\"];\n", default_name_node, cur_node,
            color, cur_node, dLinkList->list[cur_node].data, dLinkList->list[cur_node].prev_elem, dLinkList->list[cur_node].next_elem);
    }

    for (int cur_node = 0; cur_node < dLinkList->capacity - 1; ++cur_node) {
        fprintf(graph_file, "   %s%d->%s%d[color=\"black\", weight=1000, style=\"invis\"];\n", default_name_node, cur_node, default_name_node, cur_node + 1);
    }

    for (int cur_node = 1; cur_node < dLinkList->capacity; ++cur_node) {
        fprintf(graph_file, "   %s%d->%s%d[color=\"%s\", constraint=false];\n", default_name_node, cur_node, default_name_node, 
                dLinkList->list[cur_node].next_elem, ((dLinkList->list[cur_node].prev_elem == -1) ? "forestgreen" : "red"));
        if (dLinkList->list[cur_node].prev_elem != -1) {
            fprintf(graph_file, "   %s%d->%s%d[color=\"%s\", constraint=false];\n", default_name_node, cur_node, default_name_node, 
                    dLinkList->list[cur_node].prev_elem, "red");
        }
    }

    fprintf(graph_file, "   free_node->%s%d[color=\"%s\"]", default_name_node, dLinkList->free_elem_list_head, "forestgreen");


    fprintf(graph_file, "}");

    fclose(graph_file);
    return _ERROR_CODE_SUCCESSFULL__;
}

#endif