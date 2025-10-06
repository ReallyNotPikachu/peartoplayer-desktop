#include "songpicker.h"
#include "../songlist.h"
#include "../ui.h"
#include "songplayer.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
static SongPickerMenu menu;
extern SongList songs;
extern Rectangle mouseCoordinates;
extern Sound teto;
extern Sound click;
extern CurrentMenu currentMenu;
// load the menu's stuff

void freeInteractionBoxes() {
    for (int i = 0; i < menu.songBoxes.count; i++) {
        free(menu.songBoxes.boxes);
        free(menu.songBoxes.ids);
        menu.songBoxes.count = 0;
        menu.songBoxes.capacity = 0;
    }
    menu.songBoxes.capacity = 10;
    menu.songBoxes.boxes =
        (Rectangle *)malloc(sizeof(Rectangle) * menu.songBoxes.capacity);
    menu.songBoxes.ids = (int *)malloc(sizeof(int) * menu.songBoxes.capacity);
}

void addSongToMenu(Rectangle rec, int id) {
    if (menu.songBoxes.capacity == menu.songBoxes.count) {
        menu.songBoxes.capacity *= 2;
        menu.songBoxes.boxes = realloc(
            menu.songBoxes.boxes, sizeof(Rectangle) * menu.songBoxes.capacity);
        menu.songBoxes.ids =
            realloc(menu.songBoxes.ids, sizeof(int) * menu.songBoxes.capacity);
    }
    menu.songBoxes.boxes[menu.songBoxes.count] = rec;
    menu.songBoxes.ids[menu.songBoxes.count] = id;
    menu.songBoxes.count++;
}
// please call this somewhere!
void initSongSelector() {
    menu.songBoxes.boxes = malloc(sizeof(Rectangle) * 10);
    menu.songBoxes.capacity = 10;
    menu.songBoxes.ids = malloc(sizeof(int) * menu.songBoxes.capacity);
}



void createSongBoxes() {
    const int padding = 64;
    const int extraYPadding = 24;
    const int size = 50;
    int x, y = 0;
    for (int i = 0; i < songs.count; i++) {
        if (i % 4 == 0 && i > 0) {
            y += padding + extraYPadding;
            x = 0;
        }
        Rectangle rec = {x + 40, y + extraYPadding + 25, size, size};
        addSongToMenu(rec, i);
        x += padding;
        menu.bottomLimit = y + extraYPadding * -1;
    }
}

// Draws the song icons inside of the song picker menu.
void drawSongIcons() {
    const int extraYPadding = 24;
    for (int i = 0; i < menu.songBoxes.count; i++) {
        // if the mouse is inside of it
        if (CheckCollisionRecs(menu.songBoxes.boxes[i], mouseCoordinates)) {
            SongPickerMenu menuu = menu;
            DrawRectangle(
                menu.songBoxes.boxes[i].x - 1, menu.songBoxes.boxes[i].y + 1,
                menu.songBoxes.boxes[i].width + 2,
                menu.songBoxes.boxes[i].height + extraYPadding + 12, LIGHTGRAY);
            // if the mouse is pressed on the thingy
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                setCurrentSong(i);
                if (!IsSoundPlaying(click)) {
                    PlaySound(click);
                }
            }
        }
        DrawRectangleRec(menu.songBoxes.boxes[i], BLACK);
        DrawText(songs.formattedNames[i], menu.songBoxes.boxes[i].x,
                 menu.songBoxes.boxes[i].y + 51, 8, BLACK);
    }
}
void processScrolling() {
    static int totalOffset = 0;
    // my desktop's bios calls it this
    const float mouseMovementDelta = 15.0f;
    // TODO add limits to scrolling
    int move = GetMouseWheelMove() * mouseMovementDelta;

    if (totalOffset > 10 && move < 0 /*this shouldn't work*/) {
        move = 0;
    }
    if (totalOffset < menu.bottomLimit * -1 && move > 0) {
        move = 0;
    }
    totalOffset -= move;
    if (move != 0) {
        for (int i = 0; i < menu.songBoxes.count; i++) {
            menu.songBoxes.boxes[i].y -= move;
        }
    }
}
void updateSongSelectorMenu() {
    if(currentMenu == SONGPLAYING){
        processScrolling();
    }
}
