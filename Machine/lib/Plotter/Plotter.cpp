#include <Plotter.h>
#include <Arduino.h>

Plotter::Plotter(int sizeX, int sizeY, int stepperDirX, int stepperStepX, int stepperDirY1, int stepperStepY1, int stepperDirY2, int stepperStepY2) {
  state = "";
  _stepperDirX = stepperDirX;
  _stepperStepX = stepperStepX;
  _stepperDirY1 = stepperDirY1;
  _stepperStepY1 = stepperStepY1;
  _stepperDirY2 = stepperDirY2;
  _stepperStepY2 = stepperStepY2;
}

void Plotter::moveTo(int x, int y) {
  state = "moveTo";
  _targetX = x;
  _targetY = y;
  _dx = abs(_targetX - x);
  _dy = abs(_targetY - y);
  _sx = (x < _targetX) ? 1 : -1;
  _sy = (y < _targetY) ? 1 : -1;
  _error = _dx - _dy;
}

void Plotter::calibrate() {
  state = "calibrate";
}

void Plotter::stop() {
  state = "";
}

void Plotter::update() {
  if (state == "moveTo") {
    _updateMoveTo();
  }
  else if (state == "calibrate") {
    _updateCalibrate();
  }
}

void Plotter::stepX(int dir) {
  // Update the position
  x += dir;

  if (dir == 0)
    digitalWrite(_stepperDirX, HIGH);

  digitalWrite(_stepperStepX, HIGH);
  delayMicroseconds(500);
  digitalWrite(_stepperStepX, LOW); 
}

void Plotter::stepY(int dir) {
  // Update the position
  y += dir;

  if (dir == 0) {
    digitalWrite(_stepperDirY1, HIGH);
    digitalWrite(_stepperDirY2, HIGH);
  }

  digitalWrite(_stepperDirY1, HIGH);
  digitalWrite(_stepperDirY2, HIGH);
  delayMicroseconds(500);
  digitalWrite(_stepperDirY1, LOW);
  digitalWrite(_stepperDirY2, LOW);
}

void Plotter::_updateMoveTo() {
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

void Plotter::_updateCalibrate() {

}