#include <stdlib.h>
#include "random.h"

int random(int min, int max)
{
  int tmp;
  if(max >= min)
    max -= min;
  else
  {
    tmp = min - max;
    min = max;
    max = tmp;
  }
  return max ? (rand() % max + min) : min;
}
