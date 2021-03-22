#include <gb/gb.h>
#include"dex/birds/factory.h"

const unsigned char earth_data[] = {
    // FRAME 1
    // Top Left
    0x01, 0x01, 0x02, 0x03, 0x03, 0x02, 0x3a, 0x3a,
    0x5d, 0x45, 0xae, 0x9a, 0x98, 0xf8, 0x0d, 0x08,
    // Bottom Left
    0x0a, 0x08, 0x08, 0x08, 0x1c, 0x08, 0x17, 0x35,
    0x03, 0x13, 0x03, 0x03, 0x02, 0x02, 0x00, 0x02,
    // FRAME 2
    // Top Left
    0x01, 0x01, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02,
    0x05, 0x05, 0x3a, 0x3f, 0x58, 0x48, 0xad, 0x98,
    // Bottom Left
    0x9a, 0xf8, 0x08, 0x08, 0x0c, 0x08, 0x0f, 0x05,
    0x0b, 0x1b, 0x03, 0x0b, 0x02, 0x02, 0x00, 0x02};

const unsigned char earth_tiles[] = {
    0x00, 0x02};

const unsigned char arrow_data[] = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x24, 0x18,
    0x5a, 0x3c, 0xbd, 0x7e, 0x7e, 0xff, 0x00, 0x00};

const unsigned char arrow_tiles[] = {
    0x04};
/*
 * Image size: 0x10 x 0x70
 * Number of tiles (total - unique): 0x1C - 0x1C
 */

#define NBSFRAMES 0x02 /* Nb frames for the sprite */
#define WINSZX 0x80    /* Size of the picture in the window */
#define WINSZY 0x50
#define MINWINX (MAXWNDPOSX - WINSZX + 1) /* Bounds of the window origin */
#define MINWINY (MAXWNDPOSY - WINSZY + 1)
#define MAXWINX MAXWNDPOSX
#define MAXWINY MAXWNDPOSY

static UBYTE time = 0; /* Global "time" value (counter) */
const int maxLanes = 6;
UBYTE sframe = 0;      /* Current frame of the sprite */
fixed wposx, wposy;    /* Window position (fixed point) */
fixed sposx, sposy[6]; /* Sprite position (fixed point) */
fixed aposx, aposy;    /* Sprite position (fixed point) */
fixed sspy[6];         /* Sprite speed (fixed point) */
fixed csspy[6];        /* Sprite speed (fixed point) */
fixed direction[6];
fixed sspybst[6];
fixed sellane;
fixed arrowup;

void tile_sprite(int left);
void place_sprite(int left);

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

/* Set sprite tiles */
void tile_sprite(int left)
{
  int from = 0;
  for (int n = 0; n < maxLanes; n++)
  {
    from = (n * 2) + left;
    set_sprite_tile(from, earth_tiles[sframe]);
    set_sprite_prop(from, S_FLIPX * left);
    if (direction[n].w == -1)
    {
      set_sprite_prop(from, S_FLIPY | (S_FLIPX * left));
    }
    else if (direction[n].w == 1)
    {
      set_sprite_prop(from, S_FLIPX * left);
    }
  }

  set_sprite_tile(12, arrow_tiles[0]);
}

/* Place sprite */
void place_sprite(int left)
{
  int from = 0;
  for (int n = 0; n < maxLanes; n++)
  {
    from = (n * 2) + left;
    move_sprite(from, sposx.b.h + (from * 0x08), sposy[n].b.h);
  }

  move_sprite(12, aposx.b.h + (sellane.w * 0x10), aposy.b.h);
}

void move_lane()
{
  for (int n = 0; n < maxLanes; n++)
  {
    if (sspybst[n].w > 1)
    {
      sspybst[n].w /= 2;
    }
    if (sposy[n].w <= 0x1000)
    {
      direction[n].w = -1;
      sspybst[n].w = 0;
    }
    csspy[n].w = (sspy[n].w * direction[n].w) + sspybst[n].w;
    sposy[n].w -= csspy[n].w;
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
  set_sprite_data(0x00, 0x04, earth_data);
  set_sprite_data(0x04, 0x08, arrow_data);
  for (int n = 0; n < maxLanes; n++)
  {
    sposy[n].w = 0x8800;
    sspy[n].w = 0x0200;
    sspybst[n].w = 0x00;
    direction[n].w = 0x01;
  }
  aposx.w = 0x0400;
  aposy.w = 0x9800;
  sellane.w = 0x03;
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
    for(int i = 0; i < 4; i++) 
      wait_vbl_done();
    time++;
    move_lane();
    place_sprite(0);
    place_sprite(1);
    animate_sprite();
    i = joypad();
    if (i & J_A)
    {
      sspybst[sellane.w - 1].w = sposy[sellane.w - 1].w / 0x40;
      if ((sspy[sellane.w - 1].w * direction[sellane.w - 1].w) > 0)
      {
        direction[sellane.w - 1].w = 1;
      }
    }
    if (arrowup.w > 0)
    {
      if (i & J_RIGHT)
      {
        arrowup.w = 0x00;
        sellane.w++;
        if (sellane.w > maxLanes)
        {
          sellane.w = 1;
        }
      }
      else if (i & J_LEFT)
      {
        arrowup.w = 0x00;
        sellane.w--;
        if (sellane.w < 1)
        {
          sellane.w = maxLanes;
        }
      }
    }
    if (!((i & J_RIGHT) || (i & J_LEFT)))
    {
      arrowup.w = 0x01;
    }
  }
}
