#include"birds/index.h"

/**
 *              0   0   |   0   0   |   0   0   |   0   0
 * layout       chpt-n      lvl-n      bts-knd     pwps
 * chpt-n: index of the chapter
 * lvl-n: level index within the chapter
 * bts-knd: what kind of bats can spawn in this level
 * pwps: what kind of power-ups can spawn in this level
 * */
struct Level {
  struct Level *pre;
  unsigned char layout;
  struct BirdInstance *birds[];
};
