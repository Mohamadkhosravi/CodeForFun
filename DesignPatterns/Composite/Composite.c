#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void action1() {
    printf("Run Action1\n");
}
void action2() {
    printf("Run Action2\n");
}
void action3() {
    printf("Run Action3\n");
}

void selectItem(int item) {
    switch (item) {
        case 1:
            action1();
            break;
        case 2:
            action2();
            break;
        case 3:
            action3();
            break;
        default:
            printf("Invalid Item\n");
            break;
    }
}

typedef void(Items)(char *, void (*)()); 

void Item(char *title, void (*action)()) {
    printf("->%s", title);
    action();
}

void createSubMenu(char *title, Items *items) {
    printf("->%s\n", title);
    items();
}

 int main() {
 
    return 0;
}
