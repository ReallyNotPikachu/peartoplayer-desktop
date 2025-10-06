#ifndef CONTEXTMENU_H

#define CONTEXTMENU_H
#include <raylib.h>
typedef struct {
    Rectangle box;
    int functionCount;
    void (*func)(void);
} ContextMenu;

void updateContextMenu();
void drawContextMenu();
void createContextMenuAtMouse();

#endif // CONTEXTMENU_H