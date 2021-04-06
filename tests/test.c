#include <stdio.h>
#include "../dex/index.h"
#include "../logic/birds/movement.h"

const unsigned short speedUnit = 0x0100;

void printBaseStats(struct BirdInstance *bird)
{
  printf("\n  >>> BESE STATS:\n");
  printf("    Base speed: %d\n", baseSpeed(bird));
  printf("    Base strength: %d\n", baseStrength(bird));
  printf("    Base weight: %d\n", baseWeight(bird));
  printf("    Base attrition: %d\n", baseAttrition(bird));
}

void printStatus(struct BirdInstance *bird)
{
  printf("\n  >>> CURRENT STATUS:\n");
  printf("    Current direction: %d\n", currentDirection(bird));
  printf("    Current base speed: %d\n", currentBaseSpeed(bird));
  printf("    Current state: %d\n", currentState(bird));
  printf("    Current speed boost: %d\n", currentSpeedBoost(bird));
  printf("    Current speed: %d\n", currentSpeed(bird));
}



void printPosition(struct BirdInstance *bird)
{
  printf("\n  >>> CURRENT POSITION:\n");
  printf("    Current x: %d\n", bird->posX);
  printf("    Current y: %d\n", bird->posY);
}

int main()
{
  struct BirdInstance bird = {.model = birdDex[Wing_G],
                              .posX = 0x10,
                              .posY = 0x88,
                              .status = 0x40};
  printf("\n\n---- INIT ----\n\n");
  printBaseStats(&bird);
  printStatus(&bird);

  printf("\n\n---- BOUNCE ----\n\n");
  bounceBack(&bird);
  printStatus(&bird);

  printf("\n\n---- DE-BOUNCE ----\n\n");
  bounceBack(&bird);
  printStatus(&bird);

  printf("\n\n---- BOOST ----\n\n");
  boostSpeed(&bird, 0x07);
  printStatus(&bird);

  printf("\n\n---- DEGRADE BOOST ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- NERF ----\n\n");
  nerfSpeed(&bird, 0x07);
  printStatus(&bird);

  printf("\n\n---- DEGRADE NERF ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- BOOST UP ----\n\n");
  applyBoost(&bird, 0x07);
  printStatus(&bird);

  printf("\n\n---- DEGRADE BOOST UP ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- BOOST DOWN ----\n\n");
  applyBoost(&bird, -0x07);
  printStatus(&bird);

  printf("\n\n---- DEGRADE BOOST DOWN ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- BOOST COMBO POS ----\n\n");
  applyBoost(&bird, 0x07);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  applyBoost(&bird, 0x07);
  printStatus(&bird);

  printf("\n\n---- DEGRADE BOOST COMBO POS ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- BOOST COMBO NEG ----\n\n");
  applyBoost(&bird, 0x87);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  applyBoost(&bird, 0x87);
  printStatus(&bird);

  printf("\n\n---- DEGRADE BOOST COMBO NEG ----\n\n");
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);
  degradeBoost(&bird);
  printStatus(&bird);

  printf("\n\n---- MOVEMENT SEQUENCE ----\n\n");
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);
  boostSpeed(&bird, 0x07);
  movementSequence(&bird, speedUnit);
  printPosition(&bird);

  printf("\n\n---- END ----\n\n");
  return 0;
}