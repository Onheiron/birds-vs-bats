void movementSequence(struct BirdInstance *bird, unsigned char speedUnit, unsigned char obstacles[128][3], char obstNr, int birdLane, char levelProgress)
{
  // update the bird's position
  bird->posY += (currentSpeed(bird) * speedUnit) >> 4;
  unsigned char birdStrength = baseStrength(bird);
  char oX, oY;
  // if the bird went over the screen, bounce back!
  for (int o = 0; o < obstNr; o++)
  {
    unsigned char olife = (obstacles[o][2] & 0x0C) >> 2;
    if (olife == 0)
      continue;
    oY = obstacles[o][0] + levelProgress;
    oX = obstacles[o][1] >> 4;
    if ((birdLane == oX) && (bird->posY <= (oY + 0x10)))
    {
      if(birdStrength <= olife) {
        bounceBack(bird);
        bird->posY = (oY + 0x11);
        olife -= birdStrength;
      } else {
        olife = 0x00;
      }
      boostSpeed(bird, 0x07);
      if (olife <= 0)
      {
        obstacles[o][0] = 0x00;
        obstacles[o][1] = 0x00;
        olife = 0x00;
      }
      obstacles[o][2] = (unsigned)((unsigned)obstacles[o][2] ^ ((unsigned)(obstacles[o][2] & 0x0C) ^ ((olife << 2) & 0x0C)));
    }
  }
  if (bird->posY <= 0x10)
  {
    bounceBack(bird);
    bird->posY = 0x10;
  }
  // degrade boost
  degradeBoost(bird);
}