#include "ui.h"
#include "menus/songpicker.h"
#include "menus/songplayer.h"
#include "songlist.h"
#include <linux/limits.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
extern UiTextures textures;
extern const int TARGETWIDTH;
extern const int TARGETHEIGHT;
extern Rectangle mouseCoordinates;
extern CurrentMenu currentMenu;
extern int currentSongPlaying;
// make sure the window is not hidden before calling cuz optimization
void drawTime() {
    time_t currentTime = time(NULL);
    struct tm *timeStruct = localtime(&currentTime);
    char timeString[15];
    if (timeStruct->tm_min < 10) {
        sprintf(timeString, "%d:0%d", timeStruct->tm_hour, timeStruct->tm_min);
    } else {
        sprintf(timeString, "%d:%d", timeStruct->tm_hour, timeStruct->tm_min);
    }
    DrawText(timeString, 200, 1, 28, BLACK);
}

// constants
const Rectangle playRec = (Rectangle){0, 28, 27, 28};
const Rectangle playlistRec = (Rectangle){0, 28 + 32, 27, 29};
extern SongList songs;
static int songIconYOffset = 40;
const Rectangle folderRec = (Rectangle){0, 28 + (32 * 2) + 1, 27, 29};
const Rectangle settingsRec = (Rectangle){0, 28 + (32 * 3) + 1, 27, 28};
const Rectangle logoBox = {29, 0, 78, 28};
extern Sound teto;
extern Sound click;
// load the uiTextures

void startPlayingSong(int id) {
    currentMenu = SONGPLAYING;
    currentSongPlaying = id;
    PlayMusicStream(songs.songs[id]);
}
// adds the song's box to the boxes array
// also inits the song interaction boxes!
void loadUI() {
    textures.logo = LoadTexture("ui/logo.png");
    textures.settings = LoadTexture("ui/5_cog.png");
    textures.playlist = LoadTexture("ui/4_cd.png");
    currentSongPlaying = -1;
    textures.selectSongFolder = LoadTexture("ui/3_folder.png");
    currentMenu = SONGSELECT;
    textures.playButton = LoadTexture("ui/play.png");
    teto = LoadSound("sfx/error.mp3");
    click = LoadSound("sfx/click.wav");
    SetSoundVolume(click, 0.25f);
    SetSoundVolume(teto, 0.25f);
    initSongSelector();
    initSongPlayer();
}
// literally just free the memory then realloc it

void drawSideMenuBarOutline() {
    // going off the logo,i want 1px margin between that and the top
    DrawRectangle(0, 0, TARGETWIDTH, 28, WHITE);
    DrawRectangleLines(28, 28, TARGETWIDTH, TARGETHEIGHT, BLACK);
}
// 320x180

void drawDragDialogue() {
    DrawText("Drag a file or folder!", 30, 30, 20, BLACK);
}
void drawUI() {
    if (!IsWindowHidden()) {
        switch (currentMenu) {
        case SONGSELECT: {
            if (songs.count == 0)
                drawDragDialogue();
            else {
                drawSongIcons();
            }
        } break;
        case SONGPLAYING:
            drawSongPlayer();
            break;
        case SETTINGS:
        case PLAYLIST:
            break;
        }
        drawSideMenuBarOutline();
        drawLogo();
        drawSideMenuIcons();
        drawTime();
    }
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
    // check the other stuff
    switch (currentMenu) {

    case SONGSELECT:
        updateSongSelectorMenu();
        break;
    case SETTINGS:
    case PLAYLIST:
    case SONGPLAYING:
        break;
    }
    // checking the menus
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Check where the flippity flip the user clicked
        if (CheckCollisionRecs(mouseCoordinates, playRec)) {
            if (!IsSoundPlaying(click))
                PlaySound(click);
            currentMenu = SONGPLAYING;
        } else if (CheckCollisionRecs(mouseCoordinates, playlistRec)) {
            if (!IsSoundPlaying(click))
                PlaySound(click);
        } else if (CheckCollisionRecs(mouseCoordinates, folderRec)) {
            if (!IsSoundPlaying(click))
                PlaySound(click);
            currentMenu = SONGSELECT;
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