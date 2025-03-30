#include "utils.h"
#include "global_params.h"

int getTotalForce()
{
  int total = 0;
  for (int i = 0; i < SENSOR_COUNT; i++)
  {
    total += getForce(i);
  }
  return total;
}

int getForce(int i)
{
  return (int)readingsJSONForce[String(i)];
}
