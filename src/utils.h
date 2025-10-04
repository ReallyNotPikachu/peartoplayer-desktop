#ifndef UTILS_H
#define UTILS_H
typedef struct {
    int capacity;
    int count;
    char **strs;
} StringArray;
#endif
void StringArrayFree(StringArray *arr);
char *getSongNameWithoutSlashes(char *song);
char *appendStrs(const char *s1, const char *s2);
int findLastIndexOfChar(const char *str, char target);
float clampf(float d, float min, float max);
double clamp(double d, double min, double max);