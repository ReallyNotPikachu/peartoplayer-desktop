#ifndef IO_H
#define IO_H
#include "utils.h"
#include <raylib.h>
int isDirectory(const char *path);
StringArray getAllFilePathsFromDir(const char *dir);
void tryToLoadSong(char *name, Sound sound);
void loadSongFolder();
void loadDroppedSongs();
#endif //IO_H   