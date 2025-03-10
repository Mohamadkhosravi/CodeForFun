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
void action4() {
    printf("Run Action4\n");
} 

void Item(char *title, void (*action)()) {
    printf("->%s", title);
    action();
}

typedef struct  {
    char *TITLE;*
    void(*ACTION)(void);
    
} MenuComponent;


typedef struct {
    MenuComponent **items;  
    size_t itemCount;
} Menu;


 MenuComponent *addMenuItem(char *title, void(*action)(void)){

    MenuComponent *Item= (MenuComponent *)malloc(sizeof(MenuComponent));
    Item->TITLE=title;
    Item->ACTION=action;
    return Item;

}
Menu addMenu(MenuComponent **items, size_t itemCount) {
    Menu *menu = (Menu *)malloc(sizeof(Menu));
    menu->items = items;
    menu->itemCount = itemCount;
    return menu;
}


 int main() {




    menu *Submenu =addMenu (addMenuItem("Action1", action1),0);
    MenuComponent *Submenu = addMenuItem("Action2", action2);
    MenuComponent *Submenu = addMenuItem("Action3", action3);
    MenuComponent *Submenu = addMenuItem("Action4", action4);
    
  


 


    // menu1->ACTION();
    // menu2->ACTION();
    // menu3->ACTION();
    // menu4->ACTION();
    return 0;
}
