#include "doublylinked_list/doubly_linked_list.h"

int main() {
    DoublyLinkList list = {};
    DoublyLinkListSizeConstructor(&list, 4);
    DoublyLinkListPushHead(&list, 1);
    DoublyLinkListPushHead(&list, 2);
    DoublyLinkListPushHead(&list, 3);
    DoublyLinkListPushTail(&list, 4);
 //   DoublyLinkListPushTail(&list, 5);
    CreateVisualDump(&list);
    
}