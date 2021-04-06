#include "types.h"

struct BirdInstance *oneBirdLayout[1] = {
    &allBirds[0]};

struct BirdInstance *threeBirdsLayout[3] = {
    &allBirds[0],
    &allBirds[1],
    &allBirds[2],
};

struct BirdInstance *fiveBirdsLayout[5] = {
    &allBirds[0],
    &allBirds[1],
    &allBirds[4],
    &allBirds[2],
    &allBirds[3],
};

struct BirdInstance *sevenBirdsLayout[7] = {
    &allBirds[0],
    &allBirds[1],
    &allBirds[4],
    &allBirds[6],
    &allBirds[5],
    &allBirds[2],
    &allBirds[3],
};

struct BirdInstance *nineBirdsLayout[9] = {
    &allBirds[0],
    &allBirds[1],
    &allBirds[4],
    &allBirds[6],
    &allBirds[8],
    &allBirds[5],
    &allBirds[7],
    &allBirds[2],
    &allBirds[3],
};

struct BirdInstance *leaderBirdsLayout[9] = {
    &allBirds[0],
    &allBirds[1],
    &allBirds[4],
    &allBirds[6],
    &allBirds[9],
    &allBirds[5],
    &allBirds[7],
    &allBirds[2],
    &allBirds[3],
};

struct Level allLevels[25] = {
    // CHAPTER 1
    {.layout = {0x05, 0x14, 0x00},
     .birds = oneBirdLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = oneBirdLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = oneBirdLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = oneBirdLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = oneBirdLayout},
    // CHAPTER 2
    {.layout = {0x05, 0x14, 0x00},
     .birds = threeBirdsLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = threeBirdsLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = threeBirdsLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = threeBirdsLayout},
    {.layout = {0x05, 0x14, 0x00},
     .birds = threeBirdsLayout},
    // CHAPTER 3
    {.layout = {0x05, 0x0A, 0x00},
     .birds = fiveBirdsLayout,
     .bbirds = {
         { 0x88, 0x08, 0x00, 0x80 },
         { 0x88, 0x08, 0x00, 0x80 },
         { 0x88, 0x88, 0x00, 0x80 },
         { 0x88, 0x08, 0x00, 0x80 },
         { 0x88, 0x08, 0x00, 0x80 }
     },
     .obstacles = {
         {-0x70, 0x00, 0xA8},
         {-0x60, 0x00, 0xA8},
         {-0x60, 0x10, 0xA8},
         {-0x50, 0x10, 0xA8},
         {-0x50, 0x20, 0xA8},
         {-0x40, 0x20, 0xA8},
         {-0x40, 0x30, 0xA8},
         {-0x30, 0x30, 0xA8},
         {-0x30, 0x40, 0xA8},
         {-0x20, 0x40, 0xA8},
         {-0x20, 0x00, 0xA8},
         {-0x10, 0x00, 0xA8},
         {-0x10, 0x10, 0xA8},
         {0x00, 0x10, 0xA8},
         {0x00, 0x20, 0xA8},
         {0x10, 0x20, 0xA8},
         {0x10, 0x30, 0xA8},
         {0x20, 0x30, 0xA8},
         {0x20, 0x40, 0xA8},
         {0x30, 0x40, 0xA8}
     }},
    {.layout = {0x05, 0x14, 0x00}, .birds = fiveBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = fiveBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = fiveBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = fiveBirdsLayout},
    // CHAPTER 4
    {.layout = {0x05, 0x14, 0x00}, .birds = sevenBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = sevenBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = sevenBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = sevenBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = sevenBirdsLayout},
    // CHAPTER 5
    {.layout = {0x05, 0x14, 0x00}, .birds = nineBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = nineBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = nineBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = leaderBirdsLayout},
    {.layout = {0x05, 0x14, 0x00}, .birds = leaderBirdsLayout}};

struct Chapter allChapters[5] = {
    {.layout = 0x10, .levels = {&allLevels[0], &allLevels[1], &allLevels[2], &allLevels[3], &allLevels[4]}},
    {.layout = 0x30, .levels = {&allLevels[5], &allLevels[6], &allLevels[7], &allLevels[8], &allLevels[9]}},
    {.layout = 0x55, .levels = {&allLevels[10], &allLevels[11], &allLevels[12], &allLevels[13], &allLevels[14]}},
    {.layout = 0x76, .levels = {&allLevels[15], &allLevels[16], &allLevels[17], &allLevels[18], &allLevels[19]}},
    {.layout = 0x9C, .levels = {&allLevels[20], &allLevels[21], &allLevels[22], &allLevels[23], &allLevels[24]}}};

void initChapters()
{
    struct Chapter *pre = &allChapters[0];
    while (*pre)
    {
        *(pre + 1)->pre = *pre;
        pre->next = (pre + 1);
        struct Level *preLevel = pre->levels[0];
        while (*preLevel)
        {
            *(preLevel + 1)->pre = *preLevel;
            preLevel->next = (preLevel + 1);
            preLevel->chapter = pre;
            preLevel++;
        }
        pre++;
    }
}