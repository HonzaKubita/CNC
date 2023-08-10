#include <Arduino.h>
#include <Plotter.h>

Plotter plotter;

void setup() {
  plotter.moveTo(500, 100);
  plotter.moveTo(0, 0);
  plotter.moveTo(100, 500);
  plotter.moveTo(0, 0);
}

void loop() {
  
}