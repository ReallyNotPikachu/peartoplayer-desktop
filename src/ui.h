#ifndef UI_H
#define UI_H

#include <raylib.h>
void drawLogo();
void drawSideMenuBarOutline();
void drawSideMenuIcons();
void drawSongPlaying();
void drawSelectFromFolder();
void drawLoading();
void loadUI();
void drawSongIcons();
void updateUI();
///home/notpika/Documents/peartoplayerdesktop/ui/logo.png
typedef struct {
    //logo.png
    Texture2D logo;
    Texture2D playButton; //could juse use raylibs built in functions tho
    Texture2D settings;
    Texture2D playlist;
    Texture2D playMenu;
    Texture2D selectSongFolder;
} UiTextures;
#endif