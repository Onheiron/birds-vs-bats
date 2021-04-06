enum BirdType
{
  Wing_G,
  Speed_E,
  Big_O,
  Steal_T,
  Lead_R
};

enum BirdPower
{
  Chip,
  Sprint,
  Fart,
  Stealth,
  Lead
};

/**
 *    0   0   |  0   0   |   0   0   |   0   0   |
 *    b-spd      b-str       b-wgt       b-attr
 * */
struct BirdModel
{
  enum BirdType type;
  unsigned char stats;
  enum BirdPower power;
};

struct BirdModel winG = {
    .type = Wing_G,
    .stats = 0x55, //   0 1 | 0 1 | 0 1 | 0 1 | ->  1 | 1 | 1 | 1 |
    .power = Chip};

struct BirdModel speedE = {
    .type = Speed_E,
    .stats = 0xA5, //   1 0 | 1 0 | 0 1 | 0 1 | ->  2 | 2 | 1 | 1 |
    .power = Sprint};

struct BirdModel bigO = {
    .type = Big_O,
    .stats = 0x6D, //   0 1 | 1 0 | 1 1 | 0 1 | ->  1 | 2 | 3 | 1 |
    .power = Fart};

struct BirdModel stealT = {
    .type = Steal_T,
    .stats = 0xD6, //   1 1 | 0 1 | 0 1 | 1 0 | ->  3 | 1 | 1 | 2 |
    .power = Stealth};

struct BirdModel leadR = {
    .type = Lead_R,
    .stats = 0x76, //   0 1 | 1 1 | 0 1 | 1 0 | ->  1 | 3 | 1 | 2 |
    .power = Lead};

struct BirdModel* birdDex[] = {
    &winG,
    &speedE,
    &bigO,
    &stealT,
    &leadR};

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
  struct Lane *lane;
  unsigned char posX;
  unsigned char posY;
  unsigned char status;
};
