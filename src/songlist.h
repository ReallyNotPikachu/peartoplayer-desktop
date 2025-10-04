#ifndef SONGLIST_H
#include <raylib.h>
#define SONGLIST_H
// MAKE SURE TO RESIZE THE CHAR ARRAY TOO
// ALSO MAYBE SWITCH TO STREAMING FROM DISK CUZ OMG THE MEMORY USAGE
typedef struct {
    int count;
    int capacity;
    Music *songs;
    char **names;
    // Draw this
    char **formattedNames;
    char **filePaths;
} SongList;
void addSongToSongs(Music song, char *name, char* filePath);
void clearSongList();
void calculateFormattedNames(int fromIdx);
void initSongList();
#endif // SONGLIST_H