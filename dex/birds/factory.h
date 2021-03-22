#include <gb/gb.h>
#include "types.h"

/**
 *      0   |   0   |   0   0   |   0   |   0   0   0   |
 *     dir     size     state    bst-dir   spd-bst-val        
 * 
 *     dir: 0 -> up , 1 -> down
 *     size: 0 -> small, 1 -> big
 *     state:
 *        - 0 -> ready
 *        - 1 -> launched
 *        - 2 -> frozen
 *        - 3 -> dead
 *     bst-dir: 0 -> same as dir, 1 -> opposite of dir
 * */
struct BirdInstance
{
  struct BirdModel *model;
  fixed posX, posY;
  fixed bSpd, cSpd;
  unsigned char status;
};

struct BirdInstance* makeSmallBird(enum BirdType type)
{
  struct BirdInstance rtrn = {
      .model = birdDex[type],
      .status = 0x00};
  return &rtrn;
}

struct BirdInstance* makeBigBird(enum BirdType type)
{
  struct BirdInstance rtrn = {
      .model = birdDex[type],
      .status = 0x40};
  return &rtrn;
}