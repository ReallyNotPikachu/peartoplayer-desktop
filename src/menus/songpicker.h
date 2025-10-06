#include <raylib.h>
#ifndef SONGPICKER_H
typedef struct {
    Rectangle *boxes;
    int count;
    int capacity;
    int *ids;
} InteractionBoxArray;


typedef struct {
    InteractionBoxArray songBoxes;
    int bottomLimit;
} SongPickerMenu;
void initSongSelector();
void updateSongIconMenu();
void clearSongBoxes();
void updateSongSelectorMenu();
void freeInteractionBoxes();
void createSongBoxes();
void drawSongIcons();
void addSongInteractionBox(int id, Rectangle rec);
#define SONGPICKER_H
#endif