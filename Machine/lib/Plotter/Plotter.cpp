#include <Plotter.h>
#include <Arduino.h>
#include <PinDefinitions.h>

class Plotter {
  public:
    int x;
    int y;
    String state;

    Plotter() {
      state = "";
    }

    void moveTo(int x, int y) {
      state = "moveTo";
      _targetX = x;
      _targetY = y;
      _dx = abs(_targetX - x);
      _dy = abs(_targetY - y);
      _sx = (x < _targetX) ? 1 : -1;
      _sy = (y < _targetY) ? 1 : -1;
      _error = _dx - _dy;
    }

    void calibrate() {
      state = "calibrate";
    }

    void stop() {
      state = "";
    }

    void update() {
      if (state == "moveTo") {
        _updateMoveTo();
      }
      else if (state == "calibrate") {
        _updateCalibrate();
      }
    }

  private:

    void stepX(int dir) {
      // Update the position
      x += dir;

      if (dir == 0)
        digitalWrite(stepperDirX, HIGH);

      digitalWrite(stepperStepX, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepperStepX, LOW); 
    }

    void stepY(int dir) {
      // Update the position
      y += dir;

      if (dir == 0) {
        digitalWrite(stepperDirY1, HIGH);
        digitalWrite(stepperDirY2, HIGH);
      }

      digitalWrite(stepperDirY1, HIGH);
      digitalWrite(stepperDirY2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepperDirY1, LOW);
      digitalWrite(stepperDirY2, LOW);
    }

    // Variables for moving
    int _targetX;
    int _targetY;
    int _dx;
    int _dy;
    int _sx;
    int _sy;
    int _error;
    int _error2;

    void _updateMoveTo() {
      if (x == _targetX && y == _targetY) {
        stop();
      }

      _error2 = _error * 2;

      if (_error2 > -_dy) {
        _error -= _dy;
        stepX(_sx);
      }

      if (_error2 < _dx) {
        _error += _dx;
        stepY(_sy);
      }
    }

    void _updateCalibrate() {

    }

};