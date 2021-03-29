#include <gb/gb.h>
#include "definitions.h"
#include "dex/index.h"
#include "sprites/index.h"
#include "logic/index.h"

static UBYTE time = 0; /* Global "time" value (counter) */
int currentLanes = 5;
int selLane = 3;
UBYTE sframe = 0;  /* Current frame of the sprite */
char aposx, aposy; /* Sprite position (fixed point) */
fixed arrowup;
unsigned char speedUnit = 0x17;
struct Level *currentLevel = &allLevels[10];
char levelProgress = 0x00;
char xOffset = 0x30;
char obstNr;
char brdNr;

void setupLevel()
{
  obstNr = currentLevel->layout[1];
  brdNr = currentLevel->layout[0];
  for (int l = 0; l < brdNr; l++)
  {
    struct BirdInstance *currentBird = currentLevel->birds[l];
    currentBird->posX = xOffset + (l * 0x10);
    currentBird->posY = 0x88;
    currentBird->status = 0x80;
  }
}

/* Set sprite tiles */
void tile_sprite(int left)
{
  char from = 0;
  for (int n = 0; n < brdNr; n++)
  {
    struct BirdInstance *currBird = currentLevel->birds[n];
    from = (n * 2) + left;
    set_sprite_tile(from, currBird->model->type == Wing_G ? win_g_tiles[sframe] : speed_e_tiles[sframe]);
    set_sprite_prop(from, S_FLIPX * left);
    if (currentDirection(currBird) == 0)
    {
      set_sprite_prop(from, S_FLIPY | (S_FLIPX * left));
    }
    else if (currentDirection(currBird) == 1)
    {
      set_sprite_prop(from, S_FLIPX * left);
    }
  }
  set_sprite_tile(12, arrow_tiles[0]);

  for (int i = 0; i < obstNr; i++)
  {
    from = i * 2;
    set_sprite_tile(13 + from, leaves_tiles[0]);
    set_sprite_tile(14 + from, leaves_tiles[1]);
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
  unsigned char from;
  char x, y;
  for (int n = 0; n < brdNr; n++)
  {
    struct BirdInstance *currBird = currentLevel->birds[n];
    from = (n * 2) + left;
    move_sprite(from, currBird->posX + (left * 0x07), currBird->posY);
  }

  move_sprite(12, aposx + ((selLane - 1) * 0x10) + 0x04, aposy);
  for (int i = 0; i < obstNr; i++)
  {
    from = (i * 2) + left;
    unsigned char olife = (currentLevel->obstacles[i][2] & 0x0C) >> 2;
    if (olife == 0)
    {
      move_sprite(13 + from, 0x00, 0x00);
    }
    else
    {
      y = currentLevel->obstacles[i][0] + levelProgress;
      x = currentLevel->obstacles[i][1] >> 4;
      move_sprite(13 + from, xOffset + (x * 0x10) + (left * 0x08), y);
    }
  }
}

void moveLanes()
{
  for (int n = 0; n < brdNr; n++)
  {
    movementSequence(currentLevel->birds[n], speedUnit, currentLevel->obstacles, obstNr, n, levelProgress);
  }
}

void main()
{
  UBYTE i;

  disable_interrupts();
  DISPLAY_OFF;
  LCDC_REG = 0x67;

  /* Set palettes */
  BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

  sframe = 0;
  /* Initialize the sprites */
  set_sprite_data(0x00, 0x08, win_g_data);
  set_sprite_data(0x08, 0x08, speed_e_data);
  set_sprite_data(0x10, 0x02, arrow_data);
  set_sprite_data(0x12, 0x04, leaves_data);
  setupLevel();
  aposx = xOffset;
  aposy = 0x98;
  arrowup.w = 0x01;
  tile_sprite(0);
  tile_sprite(1);
  place_sprite(0);
  place_sprite(1);
  DISPLAY_ON;
  enable_interrupts();

  while (1)
  {
    /* Skip four VBLs (slow down animation) */
    for (int i = 0; i < 4; i++)
      wait_vbl_done();
    time++;
    if ((time & 0x01) == 0)
      levelProgress++;
    if (time > 0xFE)
    {
      speedUnit += 0x01;
    }
    moveLanes();
    place_sprite(0);
    place_sprite(1);
    animate_sprite();
    i = joypad();
    if (i & J_A)
    {
      applyBoost(currentLevel->birds[selLane - 1], -(currentLevel->birds[selLane - 1]->posY >> 4));
    }
    if (arrowup.w > 0)
    {
      if (i & J_RIGHT)
      {
        arrowup.w = 0x00;
        selLane++;
        if (selLane > currentLanes)
        {
          selLane = 1;
        }
      }
      else if (i & J_LEFT)
      {
        arrowup.w = 0x00;
        selLane--;
        if (selLane < 1)
        {
          selLane = currentLanes;
        }
      }
    }
    if (!((i & J_RIGHT) || (i & J_LEFT)))
    {
      arrowup.w = 0x01;
    }
  }
}
