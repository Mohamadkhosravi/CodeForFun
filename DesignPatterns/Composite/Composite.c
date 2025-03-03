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

Menu *createSubMenu() {
    Menu *subMenu = (Menu *)malloc(sizeof(Menu));
    if (!subMenu) {
        // perror("Memory allocation failed");
        // exit(EXIT_FAILURE);
    }
    subMenu->items = NULL;
    subMenu->itemCount = 0;
    return subMenu;
}


//       

// Menu *createSubMenu() {
//     Menu *subMenu = (Menu *)malloc(sizeof(Menu));
//     if (!subMenu) {
//         // perror("Memory allocation failed");
//         // exit(EXIT_FAILURE);
//     }
//     subMenu->items = NULL;
//     subMenu->itemCount = 0;
//     return subMenu;
// }
// void addMenuItem(Menu *menu, MenuComponent *item) {
//     menu->items = (MenuComponent **)realloc(menu->items, (menu->itemCount + 1) * sizeof(MenuComponent *));
//     if (!menu->items) {
//         // perror("Memory reallocation failed");
//         // exit(EXIT_FAILURE);
//     }
//     menu->items[menu->itemCount] = item;
//     menu->itemCount++;
// }
 int main() {
  //  Menu *subMenu = createSubMenu();

    // MenuComponent *subMenu=NULL;

    // addMenuItem(subMenu, createMenuItem("Item 1", action1));
    // addMenuItem(subMenu, createMenuItem("Item 2", action2));
    // addMenuItem(subMenu, createMenuItem("Item 3", action3));
    // addMenuItem(subMenu, createMenuItem("Item 4", action4));
    // subMenu=createSubMenu(Menu1Item4);
    // subMenu=createSubMenu(Menu1Item1);
    // subMenu=createSubMenu(Menu1Item2);
    // subMenu=createSubMenu(Menu1Item3);
  

    //  subMenu->ACTION();
    //  subMenu->ACTION();
    //  subMenu->ACTION();
    //  subMenu->ACTION();
    // subMenu[2]->ACTION();
    // subMenu[3]->ACTION();
    // subMenu[4]->ACTION();
    
    return 0;
}
