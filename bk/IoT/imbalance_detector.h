#ifndef IMBALANCE_DETECTOR_H
#define IMBALANCE_DETECTOR_H

#define BALANCE_PERCENT_THRESHOLD 30 // 30% imbalance triggers an alert
#define MIN_IMBALANCE_TIME 20000     // Keep duration the same

void detectUnevenWeight(int foreForce, int heelForce);
void uploadData();

extern unsigned long lastUploadTime; // Declare as extern so it's accessible in other files
extern const unsigned long uploadInterval;
extern bool imbalanceDetected;

#endif
