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
    .stats = 0xAA, //   1 0 | 1 0 | 1 0 | 1 0 | ->  1 | 1 | 1 | 1 |
    .power = Chip};

struct BirdModel speedE = {
    .type = Speed_E,
    .stats = 0xFA, //   1 1 | 1 1 | 1 0 | 1 0 | ->  2 | 2 | 1 | 1 |
    .power = Sprint};

struct BirdModel bigO = {
    .type = Big_O,
    .stats = 0x7F, //   0 1 | 1 1 | 1 1 | 1 1 | ->  0 | 3 | 2 | 1 |
    .power = Fart};

struct BirdModel stealT = {
    .type = Steal_T,
    .stats = 0xE5, //   1 1 | 1 0 | 0 1 | 0 1 | ->  2 | 2 | 0 | 2 |
    .power = Stealth};

struct BirdModel leadR = {
    .type = Lead_R,
    .stats = 0xBB, //   1 0 | 1 1 | 1 0 | 1 1 | ->  2 | 2 | 1 | 3 |
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
  unsigned char posX;
  unsigned char posY;
  unsigned char status;
};
