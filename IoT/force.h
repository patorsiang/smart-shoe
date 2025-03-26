#ifndef FORCE_H
#define FORCE_H

#include "utils.h"
#include "config.h"

#define FORCE_WAKEUP_THRESHOLD 100

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);
bool shouldSleep();

#endif
