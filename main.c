#include <gb/gb.h>
#include <rand.h>
#include "definitions.h"
#include "dex/index.h"
#include "sprites/index.h"
#include "logic/index.h"

static UBYTE time = 0; /* Global "time" value (counter) */
UBYTE currentLanes = 5;
UBYTE selLane = 3;
UBYTE sframe = 0;   /* Current frame of the sprite */
UBYTE aposx, aposy; /* Sprite position (fixed point) */
UBYTE preJoypad = 0x00;
UBYTE speedUnit = 0x17;
struct Level *currentLevel = &allLevels[10];
UBYTE levelProgress = 0x00;
UBYTE xOffset = 0x30;
UBYTE obstNr;
UBYTE brdNr;
unsigned char lasRndLane;
UBYTE i, j, x, y, z, w; // variables
unsigned char obstacles[9][3] = {
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00}};

void setupLevel()
{
  obstNr = 9; // currentLevel->layout[1];
  brdNr = 5;  //currentLevel->layout[0];
  for (i = 0; i < brdNr; i++)
  {
    struct BirdInstance *currentBird = currentLevel->birds[i];
    currentBird->posX = xOffset + (i * 0x10);
    currentBird->posY = 0x88;
    currentBird->status = 0x80;
  }
}

void shuffle(unsigned char *array, size_t n)
{
  if (n > 1)
  {
    size_t i;
    for (i = 0; i < n - 1; i++)
    {
      size_t j = i + rand() / (0xFF / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void makeObstacle()
{
  unsigned char straightRow[5] = {0x00U, 0x01U, 0x02U, 0x03U, 0x04U};
  shuffle(straightRow, 5);
  UBYTE laneNeedle = 0x00;
  for (i = 0; i < obstNr; i++)
  {
    if(laneNeedle >= 0x05) break;
    if (((obstacles[i][2] & 0x0C) >> 2) == 0)
    {
      obstacles[i][0] = -(levelProgress + 0x08);
      obstacles[i][1] = ((((unsigned char) straightRow[laneNeedle]) % 5) << 4);
      obstacles[i][2] = 0xA8;
      laneNeedle++;
    }
  }
}

void onTimeSprites()
{
  set_sprite_tile(10, arrow_tiles[0]);

  for (i = 0; i < obstNr; i++)
  {
    j = (i * 2);
    set_sprite_tile(11 + j, leaves_tiles[1]);
    set_sprite_tile(12 + j, leaves_tiles[0]);
  }
}

/* Set sprite tiles */
void tile_sprite(int left)
{
  for (i = 0; i < brdNr; i++)
  {
    struct BirdInstance *currBird = currentLevel->birds[i];
    j = (i * 2) + left;
    set_sprite_tile(j, currBird->model->type == Wing_G ? win_g_tiles[sframe] : speed_e_tiles[sframe]);
    set_sprite_prop(j, S_FLIPX * left);
    if (currentDirection(currBird) == 0)
    {
      set_sprite_prop(j, S_FLIPY | (S_FLIPX * left));
    }
    else if (currentDirection(currBird) == 1)
    {
      set_sprite_prop(j, S_FLIPX * left);
    }
  }
}

/* Animate sprite */
void animate_sprite()
{
  if ((time & 0x03) == 0)
  {
    sframe++;
    if (sframe == NBSFRAMES)
      sframe = 0;
    tile_sprite(0);
    tile_sprite(1);
  }
}

void oneSidePlace()
{
}

/* Place sprite */
void place_sprite()
{
  move_sprite(10, aposx + ((selLane - 1) * 0x10) + 0x04, aposy);
  for (i = 0; i < obstNr; i++)
  {
    j = (i * 2);
    w = (obstacles[i][2] & 0x0C) >> 2;
    if (w == 0)
    {
      move_sprite(11 + j, 0x00, 0x00);
      move_sprite(12 + j, 0x00, 0x00);
    }
    else
    {
      y = obstacles[i][0] + levelProgress;
      x = (obstacles[i][1] >> 4);
      move_sprite(11 + j, xOffset + (x * 0x10) + 0x08, y);
      move_sprite(12 + j, xOffset + (x * 0x10), y);
    }
  }

  for (i = 0; i < brdNr; i++)
  {
    struct BirdInstance *currBird = currentLevel->birds[i];
    j = (i * 2);
    move_sprite(j, currBird->posX, currBird->posY);
    move_sprite(j + 1, currBird->posX + 0x07, currBird->posY);
  }
}

void moveLanes()
{
  for (i = 0; i < brdNr; i++)
  {
    movementSequence(currentLevel->birds[i], speedUnit, obstacles, obstNr, i, levelProgress);
    if ((time & 0x01) == 0)
    {
      degradeBoost(currentLevel->birds[i]);
    }
  }
}

void main()
{
  disable_interrupts();
  DISPLAY_OFF;

  LCDC_REG = 0x06U;

  /* Set palettes */
  // 1 1 1 0 0 1 0 0
  BGP_REG = OBP1_REG = 0xE4U;
  OBP0_REG = 0xD2U;

  set_bkg_data(0x00, background_tile_data_size, background_tile_data);
  set_bkg_tiles(0, 0, background_tile_map_width, background_tile_map_height * 2, background_map_data);
  SHOW_BKG;

  /* Initialize the sprites */
  set_sprite_data(0x00, 0x08, win_g_data);
  set_sprite_data(0x08, 0x08, speed_e_data);
  set_sprite_data(0x10, 0x02, arrow_data);
  set_sprite_data(0x12, 0x04, leaves_data);
  setupLevel();
  aposx = xOffset;
  aposy = 0x98;
  onTimeSprites();
  tile_sprite(0);
  tile_sprite(1);
  place_sprite();

  DISPLAY_ON;
  enable_interrupts();

  while (1)
  {
    /* Skip four VBLs (slow down animation) */
    for (i = 0; i < 4; i++)
      wait_vbl_done();
    time++;
    if ((levelProgress & 0x0F) == 0)
    {
      makeObstacle();
    }
    if ((time & 0x01) == 0)
    {
      levelProgress++;
      scroll_bkg(0, -1);
    }
    if ((time & 0x3F) == 0)
    {
      speedUnit += 0x01;
    }
    moveLanes();
    j = joypad();
    i = (preJoypad ^ j) & j;
    preJoypad = j;
    if (i & J_A)
    {
      applyBoost(currentLevel->birds[selLane - 1], -(currentLevel->birds[selLane - 1]->posY >> 4));
    }
    if (i & J_RIGHT)
    {
      selLane++;
      if (selLane > currentLanes)
      {
        selLane = 1;
      }
    }
    else if (i & J_LEFT)
    {
      selLane--;
      if (selLane < 1)
      {
        selLane = currentLanes;
      }
    }
    animate_sprite();
    place_sprite();
  }
}
