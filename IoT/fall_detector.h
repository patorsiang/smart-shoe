#ifndef FALL_DETECTOR_H
#define FALL_DETECTOR_H

#define FALL_PERCENT_THRESHOLD 65 // 65% reduction in acceleration is considered a fall
#define TRIP_PERCENT_THRESHOLD 35 // 35% increase in forward acceleration
void detectFall();

#endif
