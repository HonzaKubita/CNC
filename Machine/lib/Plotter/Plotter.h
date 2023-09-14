#ifndef __PLOTTER_H__
#define __PLOTTER_H__

#include <Arduino.h>

class Plotter {
  public:
    int x;
    int y;
    String state;

    Plotter(int sizeX, int sizeY, int stepperDirX, int stepperStepX, int stepperDirY1, int stepperStepY1, int stepperDirY2, int stepperStepY2);
    void moveTo(int x, int y);
    void calibrate();
    void stepX(int dir);
    void stepY(int dir);
    void stop();
    void update();

  private:
    int _targetX;
    int _targetY;
    int _dx;
    int _dy;
    int _sx;
    int _sy;
    int _error;
    int _error2;

    int _stepperDirX;
    int _stepperStepX;
    int _stepperDirY1;
    int _stepperStepY1;
    int _stepperDirY2;
    int _stepperStepY2;

    void _updateMoveTo();
    void _updateSteppers(bool doXStep, bool doYStep);
    void _updateCalibrate();

};

#endif // __PLOTTER_H__