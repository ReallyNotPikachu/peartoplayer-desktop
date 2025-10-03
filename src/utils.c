#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int findLastIndexOfChar(const char *str, char target) {
    int idx = -1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == target) {
            idx = i;
        }
    }
    return idx;
}

char *getSongNameWithoutSlashes(char *song) {
    // THIS IS TORTURE
    int len = strlen(song);
    int idx = findLastIndexOfChar(song, '/') + 1;
    int dotIdx = findLastIndexOfChar(song, '.');
    // I CANT BE BOTHERED TO ADD THE NULL TERMINATOR
    char *newStr = calloc(sizeof(char), len + idx + 1);
    // could use memcpy or memmove here
    for (int i = idx; i < len; i++) {
        newStr[i - idx] = song[i];
    }
    return newStr;
}
inline void StringArrayFree(StringArray *arr) { free(arr->strs); }

char *appendStrs(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *newStr = malloc(sizeof(char) * (len1 + len2 + 1));
    for (int i = 0; i < len1; i++) {
        newStr[i] = s1[i];
    }
    for (int i = len1; i < len1 + len2; i++) {
        newStr[i] = s2[i - len1];
    }
    newStr[len1 + len2] = '\0';
    return newStr;
}