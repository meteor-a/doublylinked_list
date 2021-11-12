#ifndef _DOUBLY_LINKED_LIST_ERRORS_H__
#define _DOUBLY_LINKED_LIST_ERRORS_H__

/*----------------------------------------------------------------------------------------------*/

const int _ERROR_CODE_SUCCESSFULL__ = 0;
const int _ERROR_CODE_INCORRECT_CAPACITY__ = 1;
const int _ERROR_CODE_CANT_CALLOC_MEM__ = 2;
const int _ERROR_CODE_BAD_DOUBLY_LINK_LIST_PTR__ = 3;
const int _ERROR_CODE_CANT_GET_EMPTY_INDEX__ = 4;
const int _ERROR_CODE_BAD_LIST_PTR__ = 5;
const int _ERROR_CODE_SIZE_MORE_CAPACITY__ = 7;
const int _ERROR_CODE_SIZE_LESS_ZERO__ = 8;
const int _ERROR_CODE_CAPACITY_LESS_ZERO__ = 9;
const int _ERROR_CODE_INCORERCT_DATA_IN_ZERO_INDEX__ = 10;

/*----------------------------------------------------------------------------------------------*/

const char* _ERROR_TEXT_INCORRECT_CAPACITY__ = "Incorrect capacity of doubly link list";
const char* _ERROR_TEXT_CANT_CALLOC_MEM__    = "Can't calloc memory";
const char* _ERROR_TEXT_BAD_DOUBLY_LINK_LIST_PTR__ = "Bad pointer to the doubly linked list";
const char* _ERROR_TEXT_BAD_LIST_PTR__ = "Bad pointer to list in the doubly linked list";
const char* _ERROR_TEXT_CANT_GET_EMPTY_INDEX__    = "Cant get empty index for new elem";
const char* _ERROR_TEXT_SIZE_MORE_CAPACITY__ = "Size is more than capacity";
const char* _ERROR_TEXT_SIZE_LESS_ZERO__ = "Size is less than zero";
const char* _ERROR_TEXT_CAPACITY_LESS_ZERO__ = "Capacity is less than zero";
const char* _ERROR_TEXT_INCORERCT_DATA_IN_ZERO_INDEX__ = "Incorrect data in zero index of the list";

/*----------------------------------------------------------------------------------------------*/

const int _WARN_CODE_REPEAT_CONSTRUCTOR__      = 101;
const int _WARN_CODE_PUSH_INCORRECT_INDEX__    = 102;
const int _WARN_CODE_POP_ON_EMPTY_LIST__       = 103;
const int _WARN_CODE_POP_INCORRECT_INDEX__     = 104;
const int _WARN_CODE_CANT_OPEN_DUMP_FILE__     = 105;
const int _WARN_CODE_INCORRECT_LOGICAL_INDEX__ = 106;

/*----------------------------------------------------------------------------------------------*/

const char* _WARN_TEXT_REPEAT_CONSTRUCTOR__      = "Repeat constructor";
const char* _WARN_TEXT_PUSH_INCORRECT_INDEX__    = "Incorect index to push";
const char* _WARN_TEXT_POP_ON_EMPTY_LIST__       = "Try to pop on empty doubly linked list";
const char* _WARN_TEXT_POP_INCORRECT_INDEX__     = "Try to pop on incorect index";
const char* _WARN_TEXT_CANT_OPEN_DUMP_FILE__     = "Cant open dump file to write";
const char* _WARN_TEXT_INCORRECT_LOGICAL_INDEX__ = "Incorrect logical index";

/*----------------------------------------------------------------------------------------------*/

#endif