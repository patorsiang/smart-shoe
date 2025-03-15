#ifndef STEP_DETECTOR_H
#define STEP_DETECTOR_H

#define STEP_THRESHOLD 800     // Minimum force change to detect a step
#define STEP_DEBOUNCE_TIME 300 // 300ms debounce to avoid false steps

void detectStep(int foreForce, int heelForce);

extern bool stepActive;
extern int stepCount;
extern unsigned long lastStepTime;

#endif
