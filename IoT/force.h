#ifndef FORCE_H
#define FORCE_H

#include "utils.h"
#include "config.h"

void setupForceSensors();
void readForceSensors();
int medianFilter(int index);

#endif
