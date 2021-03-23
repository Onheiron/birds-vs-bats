#include <gb/gb.h>
#include "definitions.h"
#include "dex/index.h"
#include "sprites/index.h"
#include "logic/birds/movement.h"

static UBYTE time = 0; /* Global "time" value (counter) */
int currentLanes = 5;
int selLane = 3;
UBYTE sframe = 0;      /* Current frame of the sprite */
fixed wposx, wposy;    /* Window position (fixed point) */
fixed sposx, sposy[6]; /* Sprite position (fixed point) */
fixed aposx, aposy;    /* Sprite position (fixed point) */
fixed sspy[6];         /* Sprite speed (fixed point) */
fixed csspy[6];        /* Sprite speed (fixed point) */
fixed direction[6];
fixed sspybst[6];
fixed arrowup;
unsigned char speedUnit = 0x00FF;

void setupLevel(int level)
{
  for (int l = 0; l < level; l++)
  {
    struct BirdInstance *currentBird = &allBirds[l];
    currentBird->posX = 0x10 + (l * 0x10);
    currentBird->posY = 0x88;
    currentBird->status = 0x80;
  }
}

/* Set sprite tiles */
void tile_sprite(int left)
{
  int from = 0;
  for (int n = 0; n < currentLanes; n++)
  {
    struct BirdInstance *currBird = &allBirds[n];
    from = (n * 2) + left;
    set_sprite_tile(from, win_g_tiles[sframe]);
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
  int from = 0;
  for (int n = 0; n < currentLanes; n++)
  {
    struct BirdInstance *currBird = &allBirds[n];
    from = (n * 2) + left;
    move_sprite(from, currBird->posX + (left * 0x08), currBird->posY);
  }

  move_sprite(12, aposx.b.h + (selLane * 0x10), aposy.b.h);
}

void moveLanes()
{
  for (int n = 0; n < currentLanes; n++)
  {
    movementSequence(&allBirds[n], speedUnit);
  }
}

void main()
{
  UBYTE i, j;

  disable_interrupts();
  DISPLAY_OFF;
  LCDC_REG = 0x67;

  /* Set palettes */
  BGP_REG = OBP0_REG = OBP1_REG = 0xE4U;

  sframe = 0;
  sposx.w = 0x1000;
  /* Initialize the sprites */
  set_sprite_data(0x00, 0x04, win_g_data);
  set_sprite_data(0x04, 0x08, arrow_data);
  setupLevel(currentLanes);
  for (int n = 0; n < currentLanes; n++)
  {
    sposy[n].w = 0x8800;
    sspy[n].w = 0x0200;
    sspybst[n].w = 0x00;
    direction[n].w = 0x01;
  }
  aposx.w = 0x0400;
  aposy.w = 0x9800;
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
    moveLanes();
    place_sprite(0);
    place_sprite(1);
    animate_sprite();
    i = joypad();
    if (i & J_A)
    {
      applyBoost(&allBirds[selLane - 1], -(allBirds[selLane - 1].posY >> 4));
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
