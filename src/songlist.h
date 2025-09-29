#ifndef SONGLIST_H
#include <raylib.h>
#define SONGLIST_H
//MAKE SURE TO RESIZE THE CHAR ARRAY TOO
typedef struct {
  int count;
  int capacity;
  Sound *songs;
  char **names;
  //Draw this
  char **formattedNames;
} SongList;
void addSongToSongs(Sound song, char *name);
void clearSongList();
#endif //SONGLIST_H 