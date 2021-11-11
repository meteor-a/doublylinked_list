#include "doublylinked_list/doubly_linked_list.h"

int main() {
    DoublyLinkList list = {};
    DoublyLinkListSizeConstructor(&list, 4);
    DoublyLinkListPushHead(&list, 4);
    DoublyLinkListPushHead(&list, 5);
    DoublyLinkListPushHead(&list, 6);

    CreateVisualDump(&list);
    
}