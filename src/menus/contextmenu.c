#include <raylib.h>
#include <raymath.h>
extern float deltaTime;
extern Rectangle mouseCoordinates;
typedef struct {
    Rectangle box;
    char** functionNames;
    int functionCount;
    void(**func)(void);
    bool active;
} ContextMenuStatus;
ContextMenuStatus currentStatus;

void createContextMenuAtMouse(char** functionNames, int count, void(**funcions)(void)) {
    float width;
    float height; 
    
}

void drawContextMenu() {

}

void updateContextMenu() {
    const Vector2 contextCenter = (Vector2){};
    const Vector2 mouseBox = (Vector2){mouseCoordinates.x, mouseCoordinates.y};
    if(Vector2Distance(mouseBox, contextCenter)) {
        
    }
}