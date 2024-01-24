#include "./includes/keys.h"
#include <stdio.h>
int main() {
#ifdef LINUX_KEYS
    // Linux-specific code using Linux key codes
    printf("Using Linux key codes\n");
    printf("ESC key code: %d\n", KEY_ESC);
#else
    // Non-Linux code using alternative key codes
    printf("Using alternative key codes\n");
    printf("ESC key code: %d\n", KEY_ESC);
#endif

    // Rest of your code...

    return 0;
}