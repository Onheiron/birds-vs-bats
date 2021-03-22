#include "factory.h"

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
unsigned char baseStrenght(struct BirdInstance *bird)
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

/**
 *  boost_value =   0 0 0 0 | 0 B B B
 *  boost_mask =    0 0 0 0 | 0 1 1 1 = 0x07
 *  shift >> 0
 * 
 *  boost_dir =     0 0 0 0 | D 0 0 0
 *  boost_mask =    0 0 0 0 | 1 0 0 0 = 0x08
 *  shift >> 3
 * 
 *  direction =     D 0 0 0 | 0 0 0 0
 *  dir_mask =      1 0 0 0 | 0 0 0 0 = 0x80
 *  shift >> 7
 * 
 *  boost_dir: 0 -> same as direction, 1 -> opposite to direction
 *  final_direction = boost_dir XOR direction
 *    dir   b_dir   f_dir
 *     0      0       0
 *     1      0       1
 *     0      1       1
 *     1      1       0
 * 
 *  boost_sign = final_direction * 255
 *  unsigned boost -> signed boost = (signed char) boost ^ boost_sign
 * */
char currentSpeedBoost(struct BirdInstance *bird)
{
  return ((signed char)bird->status & 0x07) ^
         (((signed char)((bird->status & 0x80) >> 7) ^
           ((bird->status & 0x08) >> 3)) *
          255);
}

/**
 * base_speed = baseSpeed(bird)
 * speed_sign = direction * 255
 * unsigned speed -> signed_speed = (signed char) speed ^ speed_sign
 * */
fixed* currentBaseSpeed(struct BirdInstance *bird, fixed *speedUnit)
{
  fixed out = {
    .w = speedUnit->w * (baseSpeed(bird) ^ (((signed char)(bird->status & 0x80) >> 7) * 255))
  };
  return &out;
}

/**
 * boost_perc = currentSpeedBoost(bird) / 6 <- percentage over the maximum half/value of 6
 * base_speed = currentBaseSpeed(bird, speedUnit)
 * boost_value = boost_perc * base_speed <- -0.5 * -5 = 2.5 ... boost is correctly opposite to spd direction
 * current_speed = base_speed + boost_value
 * */
fixed* currentSpeed(struct BirdInstance *bird, fixed *speedUnit)
{
  fixed boost_perc = {
    .w = currentSpeedBoost(bird) / 0x06
  };
  fixed *base_speed = currentBaseSpeed(bird, speedUnit);
  fixed current_speed = {
    .w = base_speed->w + (boost_perc.w * base_speed->w)
  };
  return &current_speed;
}