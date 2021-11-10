#include "doublylinked_list/doubly_linked_list.h"

int main() {
    DoublyLinkList list = {};
    DoublyLinkListConstructor(&list);
    DoublyLinkListPushTail(&list, 5);
    DoublyLinkListPushHead(&list, 6);
    DoublyLinkListPushTail(&list, 7);

    DoublyLinkListPushAfterIndex(&list, 8, 2);
    DoublyLinkListPushBeforeIndex(&list, 9, 3);

    DoublyLinkListPopTail(&list);
}