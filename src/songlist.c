#include "songlist.h"
#include "io.h"
#include <stdlib.h>
extern SongList songs;

void addSongToSongs(Sound song, char *name) {
  if (songs.count == songs.capacity) {
    songs.capacity *= 2;
    songs.songs = realloc(songs.songs, sizeof(Sound) * songs.capacity);
    songs.names = realloc(songs.names, sizeof(char *) * songs.capacity);
    songs.formattedNames = realloc(songs.formattedNames, sizeof(char*) * songs.capacity);
  }
  songs.songs[songs.count] = song;
  songs.names[songs.count] = name;
  songs.count++;
}

//calculate formatted names, three lines of 11 chars each for 33 chars max
void calculateFormattedNames(int fromIdx) {
  for(int i = fromIdx; i < songs.count; i++) {
    
  }
}

void clearSongList() {
  for (int i = 0; i < songs.count; i++) {
    UnloadSound(songs.songs[i]);
  }
  free(songs.songs);
  songs.capacity = 0;
  songs.count = 0;
  // TODO FREE NAMES
}