enum ObstacleType
{
  Leaves,
  Log,
  Bricks,
  Seel,
  Cloud
};

/**
 *    0   0   |  0   0   |   0   0   |   0   0   |
 *    hp         bounce      type        fall-spd
 * 
 * types:
 *   0 -> boost bounce
 *   1 -> slow
 *   2 -> speed
 *   3 -> nerf boost
 * */
struct ObstacleModel
{
  enum ObstacleType type;
  unsigned char stats;
};

struct ObstacleModel leaves = {
    .type = Leaves,
    .stats = 0x51};

struct ObstacleModel log = {
    .type = Log,
    .stats = 0x91};

struct ObstacleModel *obstaclesDex[] = {
    &leaves,
    &log};

/**
 *    0   0   |  0   0   |   0   0   |   0   0   |
 *    cur-hp     hit         xxx         xxx
 * */
struct ObstacleInstance
{
  struct ObstacleModel *model;
  unsigned char status;
};