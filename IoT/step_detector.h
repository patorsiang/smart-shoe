#ifndef STEP_DETECTOR_H
#define STEP_DETECTOR_H

#define STEP_THRESHOLD 800     // Reduce to detect lighter steps
#define STEP_DEBOUNCE_TIME 150 // Reduce to capture fast steps
#define MPU_ACC_THRESHOLD 1.02 // Slightly reduce threshold

void detectStep(int foreForce, int heelForce);

extern bool stepActive;
extern int stepCount;
extern unsigned long lastStepTime;

#endif
