#include <gb/gb.h>
#include"sprites.h"

/* Set sprite tiles */
void tile_sprite(int left, UBYTE sframe, UBYTE currentLanes)
{
  int from = 0;
  for (int n = 0; n < currentLanes; n++)
  {
    from = (n * 2) + left;
    set_sprite_tile(from, win_g_tiles[sframe]);
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

/* Animate sprite */
void animate_sprite(UBYTE time, UBYTE sframe)
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
  for (int n = 0; n < maxLanes; n++)
  {
    from = (n * 2) + left;
    move_sprite(from, sposx.b.h + (from * 0x08), sposy[n].b.h);
  }

  move_sprite(12, aposx.b.h + (sellane.w * 0x10), aposy.b.h);
}