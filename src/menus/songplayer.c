#include "songplayer.h"
#include "../songlist.h"
#include "../ui.h"
#include "../utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <xmmintrin.h>
extern SongList songs;
extern UiTextures textures;

typedef struct {
    int currentIdx;
    int textSize;
    float songProgressPercent;
    bool isSongPlaying;
    bool songStateChanged;
} SongPlayerStatus;
static SongPlayerStatus status;
extern Sound click;
extern const int TARGETWIDTH;
extern const int TARGETHEIGHT;
extern Rectangle mouseCoordinates;
const Rectangle playButton = {79, 78 + 69, 30, 28};

void setCurrentSong(int idx) {
    StopMusicStream(songs.songs[status.currentIdx]);
    status.currentIdx = idx;
    status.songProgressPercent = 0.0f;
    status.isSongPlaying = true;
    status.songStateChanged = true;
}

void initSongPlayer() {
    status.currentIdx = 0;
    status.songStateChanged = false;
    status.songProgressPercent = 0.0f;
}

void playSong() {
    if (status.songStateChanged) {
        if (status.isSongPlaying) {
            PlayMusicStream(songs.songs[status.currentIdx]);
        } else if (!status.isSongPlaying) {
            PauseMusicStream(songs.songs[status.currentIdx]);
        }
        status.songStateChanged = false;
    }
}

void togglePlaying() {
    status.isSongPlaying = !status.isSongPlaying;
    status.songStateChanged = true;
}

void updateSongPlayer() {
    if (songs.count > 0) {
        if (status.isSongPlaying) {
            fflush(stdout);
            UpdateMusicStream(songs.songs[status.currentIdx]);
        }
        status.songProgressPercent =
            GetMusicTimePlayed(songs.songs[status.currentIdx]) /
            GetMusicTimeLength(songs.songs[status.currentIdx]);
        // SIMD i found off of stack overflow, basically now I can't compile
        // this for arm, TODO write a normal Clampf function for arm and 32 bit
        // targets
        // _mm_store_ss(
        //     &status.songProgressPercent,
        //     _mm_min_ss(_mm_max_ss(_mm_set_ss(status.songProgressPercent),
        //                           _mm_set_ss(0.0f)),
        //                _mm_set_ss(1.0f)));
        // note to self Satellite L775D supports SSE3
        status.songProgressPercent =
            clampf(status.songProgressPercent, 0.0f, 1.0f);
        playSong();
    }
}

void drawSongPlayer() {
    if (songs.count > 0) {
        drawSongPlaying();
    } else {
        drawDragDialogue();
    }
}

/*
We need to add looping and playlist shuffling/selection i guess.
*/

void drawSongPlaying() {
    const Rectangle playbackBar = (Rectangle){
        33,
        (3 * TARGETHEIGHT) / 4.0f,
        (TARGETWIDTH / 2.0f) - 40,
        10,
    };
    const int fontSize = 17;
    status.textSize = MeasureText(songs.names[status.currentIdx], fontSize);
    // draw
    DrawText(songs.formattedNames[status.currentIdx], (33),
             (28 + TARGETHEIGHT) / 4, fontSize, BLACK);
    // draw the temporary album cover (I'll add them eventually trust!)
    DrawRectangle(TARGETWIDTH / 2, 35, 140, 140, BLACK);
    // draw the progress bar
    DrawRectangle(33, TARGETHEIGHT * 3 / 4, (TARGETWIDTH / 2.0f) - 40, 10,
                  GRAY);
    DrawRectangle(33, TARGETHEIGHT * 3 / 4,
                  ((TARGETWIDTH / 2.0f) - 40) * status.songProgressPercent, 10,
                  GREEN);
    // draw play button
    if (CheckCollisionRecs(mouseCoordinates, playButton)) {
        DrawRectangleRec(playButton, LIGHTGRAY);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!IsSoundPlaying(click)) {
                PlaySound(click);
                togglePlaying();
            }
        }
    }
    // process seeking
    if (CheckCollisionRecs(playbackBar, mouseCoordinates)) {
        DrawLineEx(
            (Vector2){mouseCoordinates.x, playbackBar.y},
            (Vector2){mouseCoordinates.x, playbackBar.y + playbackBar.height},
            2, RED);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            float timeToGoTo =
                (GetMusicTimeLength(songs.songs[status.currentIdx])) *
                (mouseCoordinates.x - playbackBar.x) / playbackBar.width;
            SeekMusicStream(songs.songs[status.currentIdx], timeToGoTo);
        }
    }
    // forgot that the pause icon shows when its playing and vice versa, just
    // change it to not lol
    if (!status.isSongPlaying) {
        DrawTexture(textures.playButton, (TARGETWIDTH / 2) / 2,
                    ((TARGETHEIGHT - 28) / 2) + 70, WHITE);
    } else {
        DrawTexture(textures.pause, playButton.x - 1, playButton.y - 1, WHITE);
    }
    // draw the play selector
}

