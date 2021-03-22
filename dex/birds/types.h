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
    .stats = 0x39, //   0 0 | 1 1 | 1 0 | 0 1 | ->  0 | 3 | 2 | 1 |
    .power = Fart};

struct BirdModel stealT = {
    .type = Steal_T,
    .stats = 0xA2, //   1 0 | 1 0 | 0 0 | 1 0 | ->  2 | 2 | 0 | 2 |
    .power = Stealth};

struct BirdModel leadR = {
    .type = Lead_R,
    .stats = 0xA2, //   1 0 | 1 0 | 0 1 | 1 1 | ->  2 | 2 | 1 | 3 |
    .power = Lead};

struct BirdModel* birdDex[] = {
    &winG,
    &speedE,
    &bigO,
    &stealT,
    &leadR};
