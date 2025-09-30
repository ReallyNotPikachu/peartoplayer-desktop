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
void drawUI();
void updateUI();
void createSongBoxes();
void startPlayingSong(int id);

typedef enum {
    SONGSELECT,
    SETTINGS,
    PLAYLIST,
    SONGPLAYING
} CurrentMenu;
///home/notpika/Documents/peartoplayerdesktop/ui/logo.png
typedef struct {
    //logo.png
    Texture2D logo;
    Texture2D playButton; 
    Texture2D settings;
    Texture2D playlist;
    Texture2D playMenu;
    Texture2D selectSongFolder;
} UiTextures;
#endif