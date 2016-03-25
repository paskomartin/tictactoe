#include <time.h>
#include "timer.h"

/* http://stackoverflow.com/questions/3930363/implement-time-delay-in-c */
void waitFor(double dly)
{
  /* save start clock tick */
  const clock_t start = clock();

  clock_t current;
  do{
      /* get current clock tick */
      current = clock();

      /* break loop when the requested number of seconds have elapsed */
  }while((double)(current-start)/CLOCKS_PER_SEC < dly);
}
