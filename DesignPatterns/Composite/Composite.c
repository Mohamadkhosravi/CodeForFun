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
 

void Item(char *title, void (*action)()) {
    printf("->%s", title);
    action();
}

typedef struct  {
    char *TITLE;
    void(*ACTION)(void);
    
} MenuComponent;

 MenuComponent *createMenuItem(char *title, void(*action)(void)){

    MenuComponent *Menu= (MenuComponent *)malloc(sizeof(MenuComponent));
    Menu->TITLE=title;
    Menu->ACTION=action;
    return Menu;

}
MenuComponent *Menu1Item1;
MenuComponent *Menu1Item2;
MenuComponent *Menu1Item3;
MenuComponent *Menu1Item4;

 int main() {
 
    
    Menu1Item1=createMenuItem("item1",action1);
    Menu1Item2=createMenuItem("item2",action2);
    Menu1Item3=createMenuItem("item1",action1);
    Menu1Item4=createMenuItem("item2",action2);
    Menu1Item1->ACTION();
    Menu1Item2->ACTION();
    Menu1Item3->ACTION();
    return 0;
}
