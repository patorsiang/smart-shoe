#include "utils.h"
#include "global_params.h"

int getTotalForce()
{
  int total = 0;
  for (int i = 0; i < SENSOR_COUNT; i++)
  {
    total += (int)readingsJSONForce[String(i)];
  }
  return total;
}
