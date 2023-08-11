#include <Arduino.h>
#include <Plotter.h>
#include <PinDefinitions.h>

Plotter plotter(0, 0, stepperDirX, stepperStepX, stepperDirY1, stepperStepY1, stepperDirY2, stepperStepY2);

void setup() {
  plotter.moveTo(500, 100);
  plotter.moveTo(0, 0);
  plotter.moveTo(100, 500);
  plotter.moveTo(0, 0);
}

void loop() {
  plotter.update();
}