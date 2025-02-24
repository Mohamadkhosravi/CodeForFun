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
    char *TITLE;
    void(*ACTION)(void);
    
} MenuComponent;



 MenuComponent *createMenuItem(char *title, void(*action)(void)){

    MenuComponent *Item= (MenuComponent *)malloc(sizeof(MenuComponent));
    Item->TITLE=title;
    Item->ACTION=action;
    return Item;

}



MenuComponent *Menu1Item1;
MenuComponent *Menu1Item2;
MenuComponent *Menu1Item3;
MenuComponent *Menu1Item4;

MenuComponent * createSubMenu(MenuComponent *Item){
    static uint32_t CounterOfChilde =1;

      MenuComponent *subMenu;
      subMenu=(MenuComponent *) realloc(subMenu,sizeof(MenuComponent));
      return subMenu;

}

 int main() {
 
    MenuComponent *subMenu;
    Menu1Item1=createMenuItem("item1",action1);
    Menu1Item2=createMenuItem("item2",action2);
    Menu1Item3=createMenuItem("item1",action3);
    Menu1Item4=createMenuItem("item2",action4);

    subMenu=createSubMenu(Menu1Item4);
    subMenu=createSubMenu(Menu1Item1);
    subMenu=createSubMenu(Menu1Item2);
    subMenu=createSubMenu(Menu1Item3);
  

     subMenu->ACTION();
     subMenu->ACTION();
     subMenu->ACTION();
     subMenu->ACTION();
    // subMenu[2]->ACTION();
    // subMenu[3]->ACTION();
    // subMenu[4]->ACTION();

    return 0;
}
