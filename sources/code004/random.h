#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>

/* return random number between [min, max)
 * In other words return from min to max - 1
 */
inline int random(int min, int max)
{
  return ( rand() % (max - min) ) + min;
}

#endif // RANDOM_H
