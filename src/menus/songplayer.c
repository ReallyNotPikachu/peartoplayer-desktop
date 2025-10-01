#include "songplayer.h"
#include "../songlist.h"
#include "../ui.h"
#include <raylib.h>
extern SongList songs;
extern UiTextures textures;
typedef struct {
  int currentIdx;
  int textSize;
  float songProgressPercent;
} SongPlayerStatus;
static SongPlayerStatus status;
extern const int TARGETWIDTH;
extern const int TARGETHEIGHT;

void initSongPlayer() { status.currentIdx = 0; }

void updateSongPlayer() {
  if (songs.count > 0) {
    status.songProgressPercent = GetMusicTimeLength(songs.songs[status.currentIdx]) / GetMusicTimePlayed(songs.songs[status.currentIdx]);
  }
}

void drawSongPlayer() {
  if (songs.count > 0) {
    drawSongPlaying();
  }
}

void drawSongPlaying() {
  const int fontSize = 17;
  status.textSize = MeasureText(songs.names[status.currentIdx], fontSize);
  //draw 
  DrawText(songs.formattedNames[status.currentIdx], (33),
           (28 + TARGETHEIGHT) / 4, fontSize, BLACK);
            //draw the temporary album cover (I'll add them eventually trust!)
  DrawRectangle(TARGETWIDTH / 2, 35, 140, 140, BLACK);
  //draw the progress bar
  DrawRectangle(33, TARGETHEIGHT*3/4, (TARGETWIDTH/2.0f)-40, 10, GRAY );
  DrawRectangle(33, TARGETHEIGHT*3/4,((TARGETWIDTH/2.0f)-40) * status.songProgressPercent , 10, GREEN);
  //draw play button
  DrawTexture(textures.playButton, (TARGETWIDTH / 2) / 2,
              ((TARGETHEIGHT - 28) / 2) + 70, WHITE);
}