#include "songlist.h"
#include "ui.h"
#include <raylib.h>
#include "config.h"
/*
Rust programmers hate this one simple trick!
global static mutables!
*/
PlaybackConfig playbackConfig;
CurrentMenu currentMenu;
int currentSongPlaying;
Camera2D camera;
RenderTexture target;
float windowScale = 0.0f;
Rectangle mouseCoordinates;
FilePathList files;
UiTextures textures;
int filePathCounter = 0;
SongList songs;
Sound teto;
Sound click;