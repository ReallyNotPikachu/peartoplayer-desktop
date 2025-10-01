#include "songpicker.h"
#include "../songlist.h"
#include "../ui.h"
#include <raylib.h>
#include <stdlib.h>
static SongPickerMenu menu;
extern SongList songs;
// load the menu's stuff

void addSongToMenu(Rectangle rec, int id) {
  if (menu.songBoxes.capacity == menu.songBoxes.count) {
    menu.songBoxes.capacity *= 2;
    menu.songBoxes.boxes = realloc(menu.songBoxes.boxes,
                                   sizeof(Rectangle) * menu.songBoxes.capacity);
    menu.songBoxes.ids =
        realloc(menu.songBoxes.ids, sizeof(int) * menu.songBoxes.capacity);
  }
  menu.songBoxes.boxes[menu.songBoxes.count] = rec;
  menu.songBoxes.ids[menu.songBoxes.count] = id;
  menu.songBoxes.count++;
}
void initSongSelector() {
  menu.songBoxes.boxes = malloc(sizeof(Rectangle) * 10);
  menu.songBoxes.capacity = 10;
  menu.songBoxes.ids = malloc(sizeof(int) * menu.songBoxes.capacity);
}

void createSongBoxes() {
  const int padding = 64;
  const int extraYPadding = 16;
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
  }
}

void drawSongIcons() {
  for (int i = 0; i < menu.songBoxes.count; i++) {
    DrawRectangleRec(menu.songBoxes.boxes[i], BLACK);
    DrawText(songs.formattedNames[i], menu.songBoxes.boxes[i].x,
             menu.songBoxes.boxes[i].y+51, 8, BLACK);
  }
}

void updateSongSelectorMenu() {
  // if the mouse didn't move don't do this (battery life :D)
  int move = GetMouseWheelMove();
  if (move == 0)
    return;
  for(int i = 0; i < menu.songBoxes.count; i++) {
    menu.songBoxes.boxes[i].y -= move;
  }
}
