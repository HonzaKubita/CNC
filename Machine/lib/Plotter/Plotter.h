#ifndef __PLOTTER_H__
#define __PLOTTER_H__

#include <Arduino.h>

class Plotter {
  public:
    int x;
    int y;
    String state;

    Plotter();
    void moveTo(int x, int y);
    void calibrate();
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
    void _updateMoveTo();
    void _updateCalibrate();

};

#endif // __PLOTTER_H__