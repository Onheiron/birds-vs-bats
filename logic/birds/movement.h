void movementSequence(struct BirdInstance *bird, unsigned short speedUnit)
{
  // update the bird's position
  bird->posY += (currentSpeed(bird) * speedUnit) >> 8;
  // if the bird went over the screen, bounce back!
  if (bird->posY <= 0x10) {
    bounceBack(bird);
    bird->posY = 0x10;
  }
  // degrade boost
  degradeBoost(bird);
}