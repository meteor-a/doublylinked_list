#include "doublylinked_list/doubly_linked_list.h"
#include <stdio.h>

int main() {
    DoublyLinkList list = {};
    DoublyLinkListSizeConstructor(&list, 8);

    DoublyLinkListPushHead(&list, 1);
    DoublyLinkListPushHead(&list, 2);
   // DoublyLinkListPopHead(&list);
    DoublyLinkListPushHead(&list, 4);
    DoublyLinkListPushHead(&list, 6);
    DoublyLinkListPushHead(&list, 89);
   // DoublyLinkListPopTail(&list);

    printf("%d\n", getByLogicalIndex(&list, 2));
    list.size = -1; 
    DoublyLinkListPushHead(&list, 4);
}