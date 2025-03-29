#ifndef FORCE_H
#define FORCE_H

#include "global_heads.h"

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);
bool shouldSleep();

#endif
