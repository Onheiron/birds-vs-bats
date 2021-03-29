#include "types.h"

// STATS PARSERS

/**
 *  speed_stat =    S S 0 0 | 0 0 0 0
 *  mask =          1 1 0 0 | 0 0 0 0 = 0xC0
 *  shift >> 6
 * */
unsigned char baseSpeed(struct BirdInstance *bird)
{
  return ((bird->model->stats & 0xC0) >> 6);
}

/**
 *  strng_stat =    0 0 S S | 0 0 0 0
 *  mask =          0 0 1 1 | 0 0 0 0 = 0x30
 *  shift >> 4
 * */
unsigned char baseStrength(struct BirdInstance *bird)
{
  return ((bird->model->stats & 0x30) >> 4);
}

/**
 *  weight_stat =   0 0 0 0 | W W 0 0
 *  mask =          0 0 0 0 | 1 1 0 0 = 0x0C
 *  shift >> 2
 * */
unsigned char baseWeight(struct BirdInstance *bird)
{
  return ((bird->model->stats & 0x0C) >> 2);
}

/**
 *  attr_stat =     0 0 0 0 | 0 0 A A
 *  mask =          0 0 0 0 | 0 0 1 1 = 0x03
 *  shift >> 0
 * */
unsigned char baseAttrition(struct BirdInstance *bird)
{
  return ((bird->model->stats & 0x03));
}

// STATUS PARSERS
unsigned char currentState(struct BirdInstance *bird)
{
  return ((bird->status & 0x30) >> 4);
}

signed char toSigned(char unsgnd)
{
  return (((signed char)unsgnd) * 254) + 1;
}

signed char currentSpeedBoost(struct BirdInstance *bird)
{
  return ((signed char)bird->status & 0x07) * toSigned(((bird->status & 0x80) >> 7) ^
                                                       ((bird->status & 0x08) >> 3));
}

signed char currentBaseSpeed(struct BirdInstance *bird)
{
  return (signed char)baseSpeed(bird) * toSigned((bird->status & 0x80) >> 7);
}

/**
 * boost_perc = currentSpeedBoost(bird) / 6 <- percentage over the maximum half/value of 6
 * base_speed = currentBaseSpeed(bird)
 * boost_value = boost_perc * base_speed <- -0.5 * -5 = 2.5 ... boost is correctly opposite to spd direction
 * current_speed = base_speed + boost_value
 * */
signed char currentSpeed(struct BirdInstance *bird)
{
  signed char base_speed = currentBaseSpeed(bird);
  signed char current_speed = base_speed + currentSpeedBoost(bird);
  return current_speed;
}

void boostSpeed(struct BirdInstance *bird, char boost)
{
  bird->status = (bird->status & 0xF0) | (boost & 0x07);
}

void nerfSpeed(struct BirdInstance *bird, char boost)
{
  bird->status = (bird->status & 0xF0) | (0x08 | (boost & 0x07));
}

/**
 * status =         1 0 1 1 0 1 1 1
 * direction_bnc =  1 0 0 0 0 0 0 0
 * new_status =     0 0 1 0 0 1 1 1 (status ^ direction_bnc)
 * */
void bounceBack(struct BirdInstance *bird)
{
  bird->status = bird->status ^ 0x80;
}

char currentDirection(struct BirdInstance *bird)
{
  return (bird->status & 0x80) >> 7;
}

/**
 * Apply a signed boost, so positive goes "up" while negative goes "down".
 * If the boost inverts the speed, then toggle direction and change the boost to the difference.
 * If current boost is not 0, then add the two.
 * */
void applyBoost(struct BirdInstance *bird, signed char boost)
{
  signed char cBoost = currentSpeedBoost(bird);
  signed char cSpeed = currentBaseSpeed(bird);
  if ((cBoost ^ boost) >= 0)
  {
    boost = boost >= cBoost ? boost : cBoost;
  }
  else
  {
    boost += cBoost;
  }
  if (((cSpeed + boost) ^ cSpeed) < 0)
  {
    bounceBack(bird);
    boostSpeed(bird, boost + cSpeed);
  }
  else
  {
    if ((boost ^ cSpeed) >= 0)
    {
      boostSpeed(bird, boost);
    }
    else
    {
      nerfSpeed(bird, boost);
    }
  }
}

/**
 * degrades current speed boost by shifting the last 3 bits of the status.
 * 
 * status =         1 0 1 1 0 1 1 1
 * boost =          0 0 0 0 0 1 1 1
 * deg_boost =      0 0 0 0 0 0 1 1
 * boost_delta =    0 0 0 0 0 1 0 0   (boost ^ deg_boost)
 * new_status =     1 0 1 1 0 0 1 1   (status ^ boost_delta)
 * */
void degradeBoost(struct BirdInstance *bird)
{
  if ((bird->status & 0x07) == 0x00)
    return;
  bird->status = (bird->status & 0xF8) | ((bird->status & 0x07) >> 1);
}