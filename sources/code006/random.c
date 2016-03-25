#include <stdlib.h>
#include "random.h"

int random(int min, int max)
{
  return ( rand() % (max - min) ) + min;
}
