#ifndef CLYYPID_H
#define CLYYPID_H

extern void PID_init();
extern double PID_realize(double targetT, double currentT);
extern double PID_resistance(double power, double currentT);

#endif // CLYYPID_H
