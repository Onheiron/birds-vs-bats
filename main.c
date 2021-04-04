#include <gb/gb.h>
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
UBYTE i, j, x, y, z, w; // variables
unsigned char obstacles[14][3];

void setupLevel()
{
  obstNr = currentLevel->layout[1];
  brdNr = currentLevel->layout[0];
  for (i = 0; i < brdNr; i++)
  {
    struct BirdInstance *currentBird = currentLevel->birds[i];
    currentBird->posX = xOffset + (i * 0x10);
    currentBird->posY = 0x88;
    currentBird->status = 0x80;
  }
}

/* Set sprite tiles */
void tile_sprite(int left)
{
  set_sprite_tile(12, arrow_tiles[0]);

  for (i = 0; i < obstNr; i++)
  {
    j = i * 2;
    set_sprite_tile(13 + j, leaves_tiles[0]);
    set_sprite_tile(14 + j, leaves_tiles[1]);
  }

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

/* Place sprite */
void place_sprite(int left)
{
  move_sprite(12, aposx + ((selLane - 1) * 0x10) + 0x04, aposy);
  for (i = 0; i < obstNr; i++)
  {
    j = (i * 2) + left;
    w = (currentLevel->obstacles[i][2] & 0x0C) >> 2;
    if (w == 0)
    {
      move_sprite(13 + j, 0x00, 0x00);
    }
    else
    {
      y = currentLevel->obstacles[i][0] + levelProgress;
      x = currentLevel->obstacles[i][1] >> 4;
      move_sprite(13 + j, xOffset + (x * 0x10) + (left * 0x08), y);
    }
  }

  for (i = 0; i < brdNr; i++)
  {
    struct BirdInstance *currBird = currentLevel->birds[i];
    j = (i * 2) + left;
    move_sprite(j, currBird->posX + (left * 0x07), currBird->posY);
  }
}

void moveLanes()
{
  for (i = 0; i < brdNr; i++)
  {
    movementSequence(currentLevel->birds[i], speedUnit, currentLevel->obstacles, obstNr, i, levelProgress);
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
  tile_sprite(0);
  tile_sprite(1);
  place_sprite(0);
  place_sprite(1);

  DISPLAY_ON;
  enable_interrupts();

  while (1)
  {
    /* Skip four VBLs (slow down animation) */
    for (i = 0; i < 4; i++)
      wait_vbl_done();
    time++;
    if ((time & 0x01) == 0)
    {
      levelProgress++;
      scroll_bkg(0, -1);
    }
    if (time > 0xFE)
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
    place_sprite(0);
    place_sprite(1);
  }
}
