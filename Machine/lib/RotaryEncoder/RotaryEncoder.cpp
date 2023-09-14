#include <Arduino.h>
#include <RotaryEncoder.h>

RotaryEncoder::RotaryEncoder(int CLK, int DT, int SW) {
  _CLK = CLK;
  _DT = DT;
  _SW = SW;

  _DTLastState = LOW;
  _SWLastState = LOW;
  _isPressed = false;
  _gotClicked = false;

  // Set up pins as inputs
  pinMode(_CLK, INPUT);
  pinMode(_DT, INPUT);
  pinMode(_SW, INPUT);
}

void RotaryEncoder::update() {

  // Process rotation
  int currentStateDT = digitalRead(_DT);  // Read the current state of CLK

  _direction = 0; // Reset direction
  
  if (currentStateDT != _DTLastState && currentStateDT == 1) {
    if (digitalRead(_CLK) != currentStateDT) {
      _direction = 1;
    } else {
      _direction = -1;
    }
  }
  _DTLastState = currentStateDT;
  
  // Process button click and press
  if (digitalRead(_SW) == HIGH) {
    _isPressed = true;
    _SWLastState = HIGH;

    if (_SWLastState == LOW) {
      _gotClicked = true;
    } else {
      _gotClicked = false;
    }
  }
  else {
    _SWLastState = LOW;
    _isPressed = false;
    _gotClicked = false;
  }
}

int RotaryEncoder::getDirection() {
  return _direction;
}

bool RotaryEncoder::isPressed() {
  return _isPressed;
}

bool RotaryEncoder::gotClicked() {
  return _gotClicked;
}
