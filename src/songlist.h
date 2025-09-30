#ifndef SONGLIST_H
#include <raylib.h>
#define SONGLIST_H
//MAKE SURE TO RESIZE THE CHAR ARRAY TOO
//ALSO MAYBE SWITCH TO STREAMING FROM DISK CUZ OMG THE MEMORY USAGE
typedef struct {
  int count;
  int capacity;
  Music *songs;
  char **names;
  //Draw this
  char **formattedNames;
} SongList;
void addSongToSongs(Music song, char *name);
void clearSongList();
void calculateFormattedNames(int fromIdx);
#endif //SONGLIST_H 