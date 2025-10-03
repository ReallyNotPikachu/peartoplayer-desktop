#include "io.h"
#include "menus/songpicker.h"
#include "songlist.h"
#include "ui.h"
#include "utils.h"
#include <dirent.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
extern SongList songs;

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
// if it fails it unloads the sound
//TODO add filepaths
void tryToLoadSong(char *name, Music sound) {
    if (IsMusicValid(sound)) {
        addSongToSongs(sound, name);
    } else {
        UnloadMusicStream(sound);
    }
}
bool isDuplicateFile(char *filePath) {
    for (int i = 0; i < songs.count; i++) {
        if (strcmp(filePath, songs.filePaths[i]) == 0) {
            return true;
        }
    }
    return false;
}

// gets a string array of all filepaths from absolutel filepath
StringArray getAllFilePathsFromDir(const char *dir) {
    struct dirent *de;
    int i = 0;
    DIR *dr = opendir(dir);
    StringArray arr = {
        .capacity = 10, .count = 0, .strs = malloc(sizeof(char *) * 10)};
    if (dr != NULL) {
        while ((de = readdir(dr)) != NULL) {
            if (strcmp(de->d_name, ".") == 0) {
                continue;
            } else if (strcmp(de->d_name, "..") == 0) {
                continue;
            }
            if (arr.count == arr.capacity) {
                arr.capacity *= 2;
                arr.strs = realloc(arr.strs, sizeof(char *) * arr.capacity);
            }
            arr.strs[i] = malloc(sizeof(char) * 256 /*Sizeof de->d_name*/);
            arr.count++;
            strcpy(arr.strs[i], de->d_name);
            i++;
        }
    }
    return arr;
}
void loadADirectory(const char *path) {
    StringArray files = getAllFilePathsFromDir(path);
    char *fullPath;
    for (int i = 0; i < files.count; i++) {
        {
            char *nameWithSlash = appendStrs(path, "/");
            fullPath = appendStrs(nameWithSlash, files.strs[i]);
            free(nameWithSlash);
        }
        tryToLoadSong(files.strs[i], LoadMusicStream(fullPath));
        printf("Loaded song at: %s\n", fullPath);
        free(fullPath);
    }
    StringArrayFree(&files);
}

void loadDroppedSongs() {
    int previousCount = songs.count;
    printf("Previous song count: %d\n", previousCount);
    FilePathList list = LoadDroppedFiles();
    for (int i = 0; i < list.count; i++) {
        if (isDirectory(list.paths[i])) {
            loadADirectory(list.paths[i]);
        } else {
            char *temp =
                malloc((sizeof(char) * strlen(list.paths[i])) + sizeof(char));
            strcpy(temp, list.paths[i]);
            char *name = getSongNameWithoutSlashes(temp);
            printf("%s\n", temp);
            tryToLoadSong(name, LoadMusicStream(temp));
            free(temp);
        }
    }
    calculateFormattedNames(previousCount);
    freeInteractionBoxes();
    createSongBoxes();
    UnloadDroppedFiles(list);
}
// given a filepath from FilePathList
//  void loadSongFolder() {
//    FilePathList list = LoadDroppedFiles();
//    // if the stuff we dropped is a folder
//    if (isDirectory(list.paths[0])) {
//      StringArray paths = getAllFilePathsFromDir(list.paths[0]);
//      for (int i = 0; i < paths.count; i++) {
//        // turn them into full filepaths
//        char *temp = appendStrs(list.paths[0], "/");
//        char *fullPathOfSound = appendStrs(temp, paths.strs[i]);
//        // free the temporary string
//        free(temp);
//        // now we try to load the song
//        tryToLoadSong(paths.strs[i], LoadSound(fullPathOfSound));
//        // free the path of the sound
//        free(fullPathOfSound);
//      }
//    }
//    // if it is just a bunch of songs
//    else {
//      for(int i = 0; i < list.count; i++) {
//        tryToLoadSong(getSongNameWithoutSlashes(list.paths[i]),
//        LoadSound(list.paths[i]));
//      }
//    }
//  end:
//    // when we are done with all of that
//    UnloadDroppedFiles(list);
//    fflush(stdout);
//  }