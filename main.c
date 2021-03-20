/*
 * C version of the 'space' assembly demo.
 *
 * Little demo illustrating how to use the graphical possibilities
 *  of the GB (background, window and animated sprite)
 * I have used fixed-point values for both the position and
 *  speed of objects to get smooth movements
 * 
 * OBJ data             : 0x8000 -> 0x8FFF (unsigned)
 * Window data          : 0x8800 -> 0x97FF (unsigned)
 * Background data      : 0x8800 -> 0x97FF (signed)
 * 
 * Tiled 0xFC -> 0xFF are standard tiles (all black -> all white)
 * 
 * Keys:
 * Arrow keys           : Change the speed (and direction) of the sprite
 * Arrow keys + A       : Change the speed (and direction) of the window
 * Arrow keys + B       : Change the speed (and direction) of the background
 * START                : Open/close the door
 * SELECT               : Basic fading effect
 * 
 * Note that the window is kept in the lower right part of the screen
 * since it can't be made transparent
 */

#include <gb/gb.h>

const unsigned char earth_data[] = {

    // FRAME 1

    // Top Left
    0x01, 0x01, 0x02, 0x03, 0x03, 0x02, 0x3a, 0x3a,
    0x5d, 0x45, 0xae, 0x9a, 0x98, 0xf8, 0x0d, 0x08,
    // Bottom Left
    0x0a, 0x08, 0x08, 0x08, 0x1c, 0x08, 0x17, 0x35,
    0x03, 0x13, 0x03, 0x03, 0x02, 0x02, 0x00, 0x02,
    // Top Right
    0x80, 0x80, 0x40, 0xc0, 0xc0, 0x40, 0x5c, 0x5c,
    0xba, 0xa2, 0x75, 0x59, 0x19, 0x1f, 0x50, 0x10,
    // Bottom Right
    0xb0, 0x10, 0x10, 0x10, 0x38, 0x10, 0xe8, 0xac,
    0xc0, 0xc8, 0xc0, 0xc0, 0x40, 0x40, 0x00, 0x40,

    // FRAME 2

    // Top Left
    0x01, 0x01, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02,
    0x05, 0x05, 0x3a, 0x3f, 0x58, 0x48, 0xad, 0x98,
    // Bottom Left
    0x9a, 0xf8, 0x08, 0x08, 0x0c, 0x08, 0x0f, 0x05,
    0x0b, 0x1b, 0x03, 0x0b, 0x02, 0x02, 0x00, 0x02,
    // Top Right
    0x80, 0x80, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0x40,
    0xa0, 0xa0, 0x5c, 0xfc, 0x1a, 0x12, 0x55, 0x19,
    // Bottom Right
    0x59, 0x1f, 0x10, 0x10, 0x30, 0x10, 0xf0, 0xa0,
    0xd0, 0xd8, 0xc0, 0xd0, 0x40, 0x40, 0x00, 0x40};

const unsigned char earth_tiles[] = {
    0x00, 0x02,
    0x04, 0x06};

const unsigned char arrow_data[] = {
    0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x24, 0x18,
    0x5a, 0x3c, 0xbd, 0x7e, 0x7e, 0xff, 0x00, 0x00};

const unsigned char arrow_tiles[] = {
    0x30};
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

void tile_sprite();
void place_sprite();

/* Animate sprite */
void animate_sprite()
{
  if ((time & 0x03) == 0)
  {
    sframe++;
    if (sframe == NBSFRAMES)
      sframe = 0;
    tile_sprite();
  }
}

/* Set sprite tiles */
void tile_sprite()
{
  UBYTE s;

  s = sframe << 1;

  int from = 0;
  for (int n = 0; n < maxLanes; n++)
  {
    from = n * 2;
    set_sprite_tile(from, earth_tiles[s]);
    set_sprite_tile(from + 1, earth_tiles[s + 1]);
    if (direction[n].w == -1)
    {
      set_sprite_prop(from, S_FLIPY);
      set_sprite_prop(from + 1, S_FLIPY);
    }
    else if (direction[n].w == 1)
    {
      set_sprite_prop(from, 0x00);
      set_sprite_prop(from + 1, 0x00);
    }
  }

  set_sprite_tile(12, arrow_tiles[0]);
}

/* Place sprite */
void place_sprite()
{
  int from = 0;
  for (int n = 0; n < maxLanes; n++)
  {
    from = n * 2;
    move_sprite(from, sposx.b.h + (from * 0x08), sposy[n].b.h);
    from++;
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
  set_sprite_data(0x30, 0x08, arrow_data);
  for (int n = 0; n < maxLanes; n++)
  {
    set_sprite_data(0x08 * n, 0x08, earth_data);
    sposy[n].w = 0x8800;
    sspy[n].w = 0x0200;
    sspybst[n].w = 0x00;
    direction[n].w = 0x01;
  }
  aposx.w = 0x0400;
  aposy.w = 0x9800;
  sellane.w = 0x03;
  arrowup.w = 0x01;
  tile_sprite();
  place_sprite();

  DISPLAY_ON;
  enable_interrupts();

  while (1)
  {
    /* Skip four VBLs (slow down animation) */
    for (i = 0; i < 4; i++)
      wait_vbl_done();
    time++;
    move_lane();
    place_sprite();
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
