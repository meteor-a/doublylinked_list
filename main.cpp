#include "doublylinked_list/doubly_linked_list.h"

int main() {
    DoublyLinkList list = {};
    DoublyLinkListSizeConstructor(&list, 10);
    DoublyLinkListPushTail(&list, 5);
    DoublyLinkListPushHead(&list, 6);
    DoublyLinkListPushTail(&list, 7);

    list.size = -1;

    DoublyLinkListPushAfterIndex(&list, 8, 2);
    DoublyLinkListPushBeforeIndex(&list, 9, 3);

    DoublyLinkListSizeConstructor(&list, 10);

    DoublyLinkListPopTail(&list);
}