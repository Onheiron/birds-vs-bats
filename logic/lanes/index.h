/**
 *              0   0   0   0   |   0   0   0   |   0
 * layout       lane-index        lane-height       lane-status
 *  types:
 *    0 -> normal
 *    1 -> frozen
 * */
struct Lane
{
  unsigned char layout;
  struct Lane *left;
  struct Lane *right;
  struct BirdInstance *bird;
};

struct Lane allLanes[9] = {
    {.layout = 0x0E},
    {.layout = 0x1E},
    {.layout = 0x2E},
    {.layout = 0x3E},
    {.layout = 0x4E},
    {.layout = 0x5E},
    {.layout = 0x6E},
    {.layout = 0x7E},
    {.layout = 0x8E}
};

void linkLanes()
{
  struct Lane *curr = &allLanes[0];
  while ((curr->layout & 0xF0) >> 4 < 0x08)
  {
    struct Lane *next = &allLanes[((curr->layout & 0xF0) >> 4) + 1];
    next->left = curr;
    curr->right = next;
  }
}