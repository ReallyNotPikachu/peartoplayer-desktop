#include "songlist.h"
#include <raylib.h>
Camera2D camera;
RenderTexture target;
float windowScale = 0.0f;
Rectangle mouseCoordinates;
FilePathList files;
int filePathCounter = 0;
SongList songs;