#include "songlist.h"
#include "io.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern SongList songs;

void addSongToSongs(Music song, char *name) {
  if (songs.count == songs.capacity) {
    songs.capacity *= 2;
    songs.songs = realloc(songs.songs, sizeof(Music) * songs.capacity);
    songs.names = realloc(songs.names, sizeof(char *) * songs.capacity);
    songs.formattedNames =
        realloc(songs.formattedNames, sizeof(char *) * songs.capacity);
  }
  songs.songs[songs.count] = song;
  songs.names[songs.count] = name;
  songs.count++;
}

void initSongList() {
  songs.songs = malloc(sizeof(Music) * 10);
  songs.formattedNames = malloc(sizeof(char *) * 10);
  songs.names = malloc(sizeof(char *) * 10);
  songs.capacity = 10;
  
  songs.count = 0;
  puts("[info] songlist ready!");
}

// calculate formatted names, three lines of 11 chars each for 33 chars maxs
// possible optimization: calculate how much memory we need from malloc
// there's no way this function works (update I worked it out on paper it works)

void calculateFormattedNames(int fromIdx) {
  // i wrote this while hugging a blahaj
  for (int i = fromIdx; i < songs.count; i++) {
    // get the size of the name
    int len = strlen(songs.names[i]);
    char *newPtr;
    // realloc so we can insert newlines
    // cut this one off at 33;
    if (len > 28) {
      newPtr = malloc((sizeof(char) * len) + sizeof(char) + sizeof(char) +
                      sizeof(char));
      strncpy(newPtr, songs.names[i], 31);
      // copy pasted lol
      for (int x = len; x >= 18; x--) {
        newPtr[x] = newPtr[x - 1];
      }
      newPtr[18] = '\n';
      for (int x = len; x >= 9; x--) {
        newPtr[x] = newPtr[x - 1];
      }
      newPtr[9] = '\n';
      songs.formattedNames[i] = newPtr;
    }
    // make this one go up to three lines
    else if (len > 18) {
      newPtr = malloc((sizeof(char) * len) + sizeof(char) + sizeof(char) +
                      sizeof(char));
      strcpy(newPtr, songs.names[i]);
      /*
      I'm not smart enough to figure out how to optimize this lol
      This is some sort of AP CSA Exam FRQ question
      insert newline at char 11 and char 21
      hello_
      hell_o
      hel_lo
      he_llo
      */
      for (int x = len; x >= 18; x--) {
        newPtr[x] = newPtr[x - 1];
      }
      newPtr[18] = '\n';
      for (int x = len; x >= 9; x--) {
        newPtr[x] = newPtr[x - 1];
      }
      newPtr[9] = '\n';
      newPtr[len + 2] = '\0';
      songs.formattedNames[i] = newPtr;
    }
    // make this one two lines
    else if (len > 10) {
      newPtr =
          (char *)malloc((sizeof(char) * len) + sizeof(char) + sizeof(char));
      strcpy(newPtr, songs.names[i]);
      // i think i could use memmove here, instead of doing it the AP CSA way
      for (int x = len; x >= 9; x--) {
        newPtr[i] = newPtr[i - 1];
      }
      newPtr[9] = '\n';
      songs.formattedNames[i] = newPtr;
    }
    // nothing to do here as its under one line, just copy it
    else {
      newPtr = malloc((sizeof(char) * len) + sizeof(char) + sizeof(char));
      memcpy(newPtr, songs.names[i],
             sizeof(char) * len + sizeof(char) + sizeof(char));
      songs.formattedNames[i] = newPtr;
      continue;
    }
  }
}
void clearSongList() {
  for (int i = 0; i < songs.count; i++) {
    UnloadMusicStream(songs.songs[i]);
  }
  free(songs.songs);
  songs.capacity = 0;
  songs.count = 0;
  // TODO FREE NAMES
}