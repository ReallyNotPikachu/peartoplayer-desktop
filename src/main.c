#include "menus/songplayer.h"
#include "songlist.h"
#include "ui.h"
#include <dirent.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
// sorry windows!
#include "config.h"
#include "io.h"
#include <dirent.h>
#include <unistd.h>

const int TARGETWIDTH = 320;
const int TARGETHEIGHT = 180;
/*
apparently music streams from disk and song is from ram

You aren't loading a 1TB wav file are you? this should be fine..
(lol just increase your swapping capacity and 1TB should work)
*/
extern Camera2D camera;
extern PlaybackConfig playbackConfig;
extern RenderTexture target;
extern float windowScale;
extern Rectangle mouseCoordinates;
extern FilePathList files;
extern int filePathCounter;
extern SongList songs;

// forward declarations
void addSongToSongs(Music song, char *name, char *filePath);
// mutable statics, take that rust

// dont know if i need this tbh
void draw() { drawUI(); }

void lateUpdate() {}

void onWindowResize() { windowScale = GetScreenWidth() / (float)TARGETWIDTH; }
// get mouse coords
void updateMouse() {
    Vector2 vec = GetMousePosition();
    vec.x = vec.x / windowScale;
    vec.y = vec.y / windowScale;
    mouseCoordinates = (Rectangle){vec.x, vec.y, 3, 3};
}

// it works? i think??
// My ap csa teacher would be proud

// i love c it was a great idea doing this in C i dont need help

// it works!

//I refactored and moved the function the above comments were referring to a long time ago so
//idk lol.. probably that stupid formattedstrings one
void update() {
    static bool WindowHidden = false;
    if (IsWindowHidden() && !WindowHidden) {
        SetTargetFPS(40);
        WindowHidden = true;
    } else if (!IsWindowHidden() && WindowHidden) {
        WindowHidden = false;
        SetTargetFPS(40);
    }
    if (IsFileDropped()) {
        loadDroppedSongs();
    }
    // debug logic
    if (IsKeyPressed(KEY_F3)) {
        printf("%d\n", songs.count);
        fflush(NULL);
    }
    if (IsWindowResized())
        onWindowResize();
    updateMouse();
    // update everything else after the mouse cuz yes
    updateUI();
}

void loop() {
    while (!WindowShouldClose()) {
        // TODO it won't continue playing when hidden.. not sure why
        updateSongPlayer();
        update();
        BeginDrawing();
        BeginTextureMode(target);
        ClearBackground(WHITE);
        BeginMode2D(camera);
        {
            draw();
        }
        EndMode2D();
        EndTextureMode();
        DrawTexturePro(target.texture,
                       (Rectangle){0.0f, 0.0f, (float)target.texture.width,
                                   -(float)target.texture.height},
                       (Rectangle){-windowScale, -windowScale,
                                   GetScreenWidth() + (windowScale * 2),
                                   GetScreenHeight() + (windowScale * 2)},
                       (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
        // draw non render textures stuff i guess
        EndDrawing();
    }
    CloseWindow();
    // we dont need to unload ANYTHING!!
    // let the OPERATING SYSTEM handle it!
    // theres probably a reason to but idrc im lazy
}

void init() {
    // SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetTargetFPS(30);
    InitWindow(1280, 720, "Pearto Player :P");
    SetTargetFPS(30);
    InitAudioDevice();
    initSongList();
    target = LoadRenderTexture(TARGETWIDTH, TARGETHEIGHT);
    windowScale = GetScreenWidth() / (float)TARGETWIDTH;
    camera = (Camera2D){{0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 1.0f};
    loadUI();
    puts("\nHappy music listening");
    SetWindowMinSize(TARGETWIDTH, TARGETHEIGHT);
    playbackConfig = (PlaybackConfig){.isLooping = true};
}

// ahh yes so elegant and refined, init and then loop
// we are not parsing args just yet but I guess I can take them..
int main(int argc, char **argv) {
    init();
    loop();
    return 0;
}
