#include "doublylinked_list/doubly_linked_list.h"

int main() {
    DoublyLinkList list = {};
    DoublyLinkListSizeConstructor(&list, 4);
    DoublyLinkListPushHead(&list, 4);
    DoublyLinkListPushHead(&list, 5);
    DoublyLinkListPushHead(&list, 6);
    DoublyLinkListPushHead(&list, 7);
    DoublyLinkListPopTail(&list);
    DoublyLinkListPushHead(&list, 8);

    If_you_call_this_function_you_will_wake_up_very_angry_ahatina_and_she_will_want_to_kill_anyone_who_she_will_be_near_if_you_want_to_save_you_live_dont_do_stupid_action_if_you_think_she_is_slow_you_are_wrong_she_is_faster_than_meteor_it_is_you_choose(&list);
    
}