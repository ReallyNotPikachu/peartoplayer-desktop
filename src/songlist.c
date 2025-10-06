#include "songlist.h"
#include "io.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern SongList songs;

void addSongToSongs(Music song, char *name, char *filepath) {
    if (songs.count == songs.capacity) {
        songs.capacity *= 2;
        songs.songs = realloc(songs.songs, sizeof(Music) * songs.capacity);
        songs.names = realloc(songs.names, sizeof(char *) * songs.capacity);
        songs.formattedNames =
            realloc(songs.formattedNames, sizeof(char *) * songs.capacity);
        songs.filePaths =
            realloc(songs.filePaths, sizeof(char *) * songs.capacity);
    }
    songs.songs[songs.count] = song;
    songs.names[songs.count] = name;
    songs.filePaths[songs.count] = filepath;
    songs.count++;
}

// maybe they weren't kidding when they said don't trust someone who doesn't put
// swears in their codebase...
void initSongList() {
    songs.songs = malloc(sizeof(Music) * 10);
    songs.formattedNames = malloc(sizeof(char *) * 10);
    songs.names = malloc(sizeof(char *) * 10);
    songs.filePaths = malloc(sizeof(char *) * 10);
    songs.capacity = 10;
    songs.count = 0;
    puts("[info] songlist ready!");
}

//TODO rework this function I think its still broken
void calculateFormattedNames(int fromIdx) {
    // i wrote this while hugging a blahaj
    for (int i = fromIdx; i < songs.count; i++) {
        // get the size of the name
        int len = strlen(songs.names[i]);
        char *newPtr;
        // realloc so we can insert newlines
        // cut this one off at 33;
        if (len > 28) {
            newPtr = malloc((sizeof(char) * 31));
            // this entire function is one massive CVE lmao
            // Hopefully I can convince my friend who knows what's shes doing to
            // look at it >:3
            memcpy(newPtr, songs.names[i], 31 * sizeof(char));
            // copy pasted lol
            for (int x = len; x >= 18; x--) {
                newPtr[x] = newPtr[x - 1];
            }
            newPtr[18] = '\n';
            //"optimized" for AMD A6 3400M
            for (int x = len; x >= 9; x--) {
                newPtr[x] = newPtr[x - 1];
            }
            // this would all be so much easier in C++
            newPtr[9] = '\n';
            newPtr[30] = '\0';
            songs.formattedNames[i] = newPtr;
        }
        // make this one go up to three lines
        else if (len > 18) {
            // this should be good?
            newPtr = malloc((sizeof(char) * len) + (sizeof(char) * 3)); // 24
            strcpy(newPtr, songs.names[i]);
            /*
            I'm not smart enough to figure out how to optimize this
            lol.. This is some sort of AP CSA Exam FRQ question..
            */
            for (int x = len; x >= 18; x--) {
                newPtr[x] = newPtr[x - 1];
            }
            newPtr[18] = '\n';
            for (int x = len + 1; x >= 9; x--) {
                newPtr[x] = newPtr[x - 1];
            }
            newPtr[9] = '\n';
            newPtr[len + 2] = '\0';
            songs.formattedNames[i] = newPtr;
        }
        // make this one two lines
        // THIS ONE IS BROKEN, REWRITE NEXT CLASS PERIOD
        else if (len > 10) {
            newPtr = (char *)malloc((sizeof(char) * len) + sizeof(char) +
                                    sizeof(char));
            memcpy(newPtr, songs.names[i], (len * sizeof(char)) + sizeof(char));
            // i think i could use memmove here, instead of doing it
            // the AP CSA way

            for (int x = len; x >= 9; x--) {
                // I HAD THIS AS I INSTEAD OF X 😭💀💀
                newPtr[x] = newPtr[x - 1];
            }
            newPtr[9] = '\n';
            // almost forgot this! whoops!
            newPtr[len + 1] = '\0';
            songs.formattedNames[i] = newPtr;
        }
        // nothing to do here as its under one line, just copy it
        else {
            // i think im wasting a single byte of memory here lol
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
    songs.capacity = 10;
    songs.songs = (Music *)malloc(sizeof(Music) * 10);
    songs.count = 0;
    // TODO FREE NAMES
}
