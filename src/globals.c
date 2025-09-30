#include "songlist.h"
#include "ui.h"
#include <raylib.h>
/*
Rust programmers hate this one simple trick!
global static mutables!
*/
CurrentMenu currentMenu;
int currentSongPlaying;
Camera2D camera;
RenderTexture target;
float windowScale = 0.0f;
Rectangle mouseCoordinates;
FilePathList files;
int filePathCounter = 0;
SongList songs;