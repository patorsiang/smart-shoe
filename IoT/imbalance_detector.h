#ifndef IMBALANCE_DETECTOR_H
#define IMBALANCE_DETECTOR_H

void detectUnevenWeight(int foreForce, int heelForce);
void uploadData();

extern unsigned long lastUploadTime; // Declare as extern so it's accessible in other files
extern const unsigned long uploadInterval;
extern bool imbalanceDetected;

#endif
