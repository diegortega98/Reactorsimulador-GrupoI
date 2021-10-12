#ifndef _FISSION_GENERAL_H
#define _FISSION_GENERAL_H

bool RadialCollision(float x1, float y1, float rad1, float x2, float y2, float rad2);
float unif(float low, float high);
int rsign(); //will randomly return 1 or -1. Uniform
bool rbool(int p); //p -> % of chance of  being true (0 to 100 range)
void ResetSimulationMetrics();

#endif