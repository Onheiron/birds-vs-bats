/**
 *              0   0   0   0   |   0   0   |   0   0
 * layout       lanes number        chpt-n      style
 *  style:
 *    0 -> same starting birds for all levels
 *    1 -> starting birds are those left from previous levels
 *    2 -> each level has its birds layout
 *    3 -> player can pick the starting birds for each level
 * */
struct Chapter {
  struct Chapter *pre;
  struct Chapter *next;
  unsigned char layout;
  struct Level *levels[];
};

struct Position {
  unsigned char lane;
  unsigned char posY;
};

/**
 *              0   0   |  0   0   0   |   0   0   0
 * layout       bds-nr     obst-nr         bats-nr
 * 
 * bbirds -> position Y   |   stats   |   status   | xtras
 * */
struct Level {
  struct Chapter *chapter;
  struct Level *pre;
  struct Level *next;
  unsigned char layout[3];
  struct BirdInstance **birds;
  unsigned int bbirds[9];
  char obstacles[128][3];
};
