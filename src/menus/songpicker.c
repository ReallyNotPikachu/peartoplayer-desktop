#include "../songlist.h"
#include "../ui.h"
#include <raylib.h>
#include <stdlib.h>
extern SongList songs;
typedef struct {
  int id;
  Rectangle rec;
  void (*playSong)(int);
} SongInteractionBox;
typedef struct {
  SongInteractionBox *boxes;
  float yOffset;
  int capacity;
  int count;
} InteractionBoxes;
static InteractionBoxes boxes;
void drawSongIcon(int id) {
  const int iconSize = 50;
  // // TODO optimize strings by adding length to them
  // int nameLength = strlen(name);
  // DrawRectangleRec((Rectangle){x, y, iconSize, iconSize}, BLACK);
  // DrawText(name, x, y + 52, 8, BLACK);
  DrawRectangleRec(boxes.boxes[id].rec, BLACK);
  DrawText(songs.formattedNames[id], boxes.boxes[id].rec.x,
           boxes.boxes[id].rec.y, 8, BLACK);
}

void addSongInteractionBox(int id, Rectangle rec) {
  if (boxes.capacity == boxes.count) {
    boxes.capacity *= 2;
    boxes.boxes = realloc(sizeof(SongInteractionBox) * boxes.capacity);
  }
  boxes.boxes->rec = rec;
  boxes.boxes->id = id;
  boxes.boxes->playSong = startPlayingSong;
  boxes.count++;
}

void clearSongBoxes() {
  free(boxes.boxes);
  boxes.boxes = malloc(sizeof(SongInteractionBox) * boxes.capacity);
}

void initSongSelector() {
  boxes.boxes = malloc(sizeof(SongInteractionBox) * 10);
  boxes.capacity = 10;
  boxes.count = 0;
}

void updateSongIconMenu() {
  const float scrollSpeed = 5.0f;
  float yOffset = GetMouseWheelMove() * scrollSpeed;
  if (yOffset > 0) {
    for (int i = 0; i < boxes.count; i++) {
      boxes.boxes->rec.y -= yOffset;
    }
  }
}

void createSongBoxes() {
  const int iconPadding = 64;
  const int extraYPadding = 16;
  const int iconSize = 50;
  const int startAtY = 52;
  int rowOffset = 0;
  int xOffset = 0;
  for (int i = 0; i < songs.count; i++) {
    if (i % 4 == 0 && i > 0) {
      rowOffset += iconPadding + extraYPadding;
      xOffset = 0;
      addSongInteractionBox(i, (Rectangle){xOffset + 40, rowOffset + startAtY,
                                           iconSize, iconSize});
      puts("e");
    }
  }
}
void drawSongIcons() {
  for (int i, x = 0; i < songs.count; i++) {
    drawSongIcon(i);
  }
}