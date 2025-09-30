#include "ui.h"
#include "songlist.h"
#include <linux/limits.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
UiTextures textures;
extern const int TARGETWIDTH;
extern const int TARGETHEIGHT;
extern Rectangle mouseCoordinates;

typedef struct {
  Rectangle location;

}SongSelectionBox;
// constants
const Rectangle playRec = (Rectangle){0, 28, 27, 28};
const Rectangle playlistRec = (Rectangle){0, 28 + 32, 27, 29};
extern SongList songs;
static int songIconYOffset = 40;
const Rectangle folderRec = (Rectangle){0, 28 + (32 * 2) + 1, 27, 29};
const Rectangle settingsRec = (Rectangle){0, 28 + (32 * 3) + 1, 27, 28};
const Rectangle logoBox = {29, 0, 78, 28};
Sound teto;
Sound click;
// load the uiTextures
void loadUI() {
  textures.logo = LoadTexture("ui/logo.png");
  textures.settings = LoadTexture("ui/5_cog.png");
  textures.playlist = LoadTexture("ui/4_cd.png");
  textures.selectSongFolder = LoadTexture("ui/3_folder.png");
  textures.playButton = LoadTexture("ui/play.png");
  teto = LoadSound("sfx/error.mp3");
  click = LoadSound("sfx/click.wav");
}
void drawSideMenuBarOutline() {
  // going off the logo,i want 1px margin between that and the top
  DrawRectangleLines(28, 28, TARGETWIDTH, TARGETHEIGHT, BLACK);
}
// 320x180

//performance critical technically 
void drawSongIcon(float x, float y, char *name) {
  const int iconSize = 50;
  // TODO optimize strings by adding length to them
  int nameLength = strlen(name);
  DrawRectangleRec((Rectangle){x, y, iconSize, iconSize}, BLACK);
    DrawText(name, x, y + 52, 8, BLACK);
}

// TODO make this actually work
void drawSongIcons() {
  const float scrollSpeed = 5.0f;
  const int iconPadding = 64;
  const int extraYPadding = 16;
  const int iconSize = 50;
  songIconYOffset-= GetMouseWheelMove() * scrollSpeed;
  int yOffset = 0;
  for (int i, x = 0; i < songs.count; i++) {
    // move the y down every couple songs
    if (i % 4 == 0 && i > 0) {
      yOffset += iconPadding + extraYPadding;
      x = 0;
    }
    drawSongIcon(x + 40, yOffset + songIconYOffset , songs.formattedNames[i]);
    x += iconPadding;
  }
}

void updateSongIcons() {

}

// draw select song, play button, the other two  too
void drawSideMenuIcons() {
  // draw where the mouse is hovering
  if (CheckCollisionRecs(mouseCoordinates, playRec)) {
    DrawRectangleRec(playRec, LIGHTGRAY);
  } else if (CheckCollisionRecs(mouseCoordinates, playlistRec)) {
    DrawRectangleRec(playlistRec, LIGHTGRAY);
  } else if (CheckCollisionRecs(mouseCoordinates, folderRec)) {
    DrawRectangleRec(folderRec, LIGHTGRAY);
  } else if (CheckCollisionRecs(mouseCoordinates, settingsRec)) {
    DrawRectangleRec(settingsRec, LIGHTGRAY);
  }
  // draw the buttons and stuff
  DrawTexture(textures.playButton, 0, 28, WHITE);
  DrawTexture(textures.playlist, -2, 28 + (29), WHITE);
  DrawTexture(textures.selectSongFolder, -2, 28 + (32 * 2) + 2, WHITE);
  DrawTexture(textures.settings, -2, 28 + (32 * 3), WHITE);
}
void drawLogo() {

  if (CheckCollisionRecs(logoBox, mouseCoordinates)) {
    DrawRectangleRec(logoBox, LIGHTGRAY);
  }
  DrawTexture(textures.logo, 28, 1, WHITE);
}
void drawLoading() {}

void updateUI() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    // Check where the flippity flip the user clicked
    if (CheckCollisionRecs(mouseCoordinates, playRec)) {
      if (!IsSoundPlaying(click))
        PlaySound(click);
    } else if (CheckCollisionRecs(mouseCoordinates, playlistRec)) {
      if (!IsSoundPlaying(click))
        PlaySound(click);
    } else if (CheckCollisionRecs(mouseCoordinates, folderRec)) {
      if (!IsSoundPlaying(click))
        PlaySound(click);
      // this is scuffed asf
      // settings
    } else if (CheckCollisionRecs(mouseCoordinates, settingsRec)) {
      if (!IsSoundPlaying(click))
        PlaySound(click);
    }
    if (CheckCollisionRecs(logoBox, mouseCoordinates)) {
      if (!IsSoundPlaying(click))
        PlaySound(teto);
    }
  }
}
void drawSongPlaying() {}