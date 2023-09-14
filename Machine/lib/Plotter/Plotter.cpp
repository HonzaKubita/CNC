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

  _targetX = 0;
  _targetY = 0;
  _dx = 0;
  _dy = 0;
  _sx = 0;
  _sy = 0;
  _error = 0;
  _error2 = 0;

  pinMode(_stepperDirX, OUTPUT);
  pinMode(_stepperStepX, OUTPUT);
  pinMode(_stepperDirY1, OUTPUT);
  pinMode(_stepperStepY1, OUTPUT);
  pinMode(_stepperDirY2, OUTPUT);
  pinMode(_stepperStepY2, OUTPUT);
}

void Plotter::moveTo(int targetX, int targetY) {
  // Set the state to indicate that the plotter is in the process of moving to a target position
  state = "moveTo";

  // Set the target coordinates
  _targetX = targetX;
  _targetY = targetY;

  // Calculate the absolute differences in x and y
  _dx = abs(_targetX - x);
  _dy = abs(_targetY - y);

  // Determine the direction of movement along the x and y axes
  _sx = (x < _targetX) ? 1 : -1;
  _sy = (y < _targetY) ? 1 : -1;

  // Initialize the error term for the line drawing algorithm
  _error = _dx - _dy;

  // Print a message to indicate the target position
  // Serial.print("Moving to: X: ");
  // Serial.print(targetX);
  // Serial.print(" Y: ");
  // Serial.print(targetY);
  // Serial.println("");
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

  if (dir == 1)
    digitalWrite(_stepperDirX, HIGH);
  else
    digitalWrite(_stepperDirX, LOW);

  digitalWrite(_stepperStepX, HIGH);
  delayMicroseconds(500);
  digitalWrite(_stepperStepX, LOW); 
  delayMicroseconds(500);
}

void Plotter::stepY(int dir) {
  // Update the position
  y += dir;

  if (dir == 1) {
    digitalWrite(_stepperDirY1, HIGH);
    digitalWrite(_stepperDirY2, HIGH);
  } else {
    digitalWrite(_stepperDirY1, LOW);
    digitalWrite(_stepperDirY2, LOW);
  }

  digitalWrite(_stepperStepY1, HIGH);
  digitalWrite(_stepperStepY2, HIGH);
  delayMicroseconds(500);
  digitalWrite(_stepperStepY1, LOW);
  digitalWrite(_stepperStepY2, LOW);
  delayMicroseconds(500);
}

void Plotter::_updateSteppers(bool doXStep, bool doYStep) {
  // Stepper directions
  if (_sx == 1)
    digitalWrite(_stepperDirX, HIGH);
  else
    digitalWrite(_stepperDirX, LOW);

  if (_sy == 1) {
    digitalWrite(_stepperDirY1, HIGH);
    digitalWrite(_stepperDirY2, HIGH);
  } else {
    digitalWrite(_stepperDirY1, LOW);
    digitalWrite(_stepperDirY2, LOW);
  }

  if (doXStep) {
    x += _sx;
    digitalWrite(_stepperStepX, HIGH);
  }

  if (doYStep) {
    y += _sy;
    digitalWrite(_stepperStepY1, HIGH);
    digitalWrite(_stepperStepY2, HIGH);
  }

  delayMicroseconds(500);

  digitalWrite(_stepperStepX, LOW);
  digitalWrite(_stepperStepY1, LOW);
  digitalWrite(_stepperStepY2, LOW);

  delayMicroseconds(500);
}

void Plotter::_updateMoveTo() {
  // Check if the plotter has already reached the final destination
  if (x == _targetX && y == _targetY) {
    stop();
    return;
  }

  // Calculate the differences in x and y
  int dx = _targetX - x;
  int dy = _targetY - y;

  // Calculate error terms scaled by 2
  int error2 = _error * 2;

  bool doXStep = false;
  bool doYStep = false;

  // Adjust the plotter's position based on error values
  if (error2 > -dy) {
    _error -= dy;
    doXStep = true;
  }

  if (error2 < dx) {
    _error += dx;
    doYStep = true;
  }

  // Do the requested steps with the steppers
  _updateSteppers(doXStep, doYStep);
}

void Plotter::_updateCalibrate() {

}