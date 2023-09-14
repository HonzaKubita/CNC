// 3rd party libraries
#include <Arduino.h> // Library for accessing arduino functionality

// Local libraries
#include <Plotter.h> // Library for controlling the movement of the CNC
#include <UI.h> // Library for communicating with the user (lcd output / rotary encoder input)

// Definitions
#include <PinDefinitions.h> // Global project pin definitions

// Create plotter object
Plotter plotter(0, 0, stepperDirX, stepperStepX, stepperDirY1, stepperStepY1, stepperDirY2, stepperStepY2);

// Create lcd object
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Create rotary encoder object
RotaryEncoder rotaryEncoder(encoderCLK, encoderDT, encoderSW);
// Create ui object
UI ui(&lcd, &rotaryEncoder);

// Create all menus
Menu mainMenu("Main menu");
Menu settingsMenu("Settings");
Menu filesList("Files");

Menu placeholder1("placeholder1");
Menu placeholder2("placeholder2");
Menu placeholder3("placeholder3");

void setup() {
  Serial.begin(9600);

  Serial.println("Setup start");
  ui.init();

  // Organize all screens
  mainMenu.addItem(&settingsMenu);
  mainMenu.addItem(&filesList);
  mainMenu.addItem(&placeholder1);
  mainMenu.addItem(&placeholder2);
  mainMenu.addItem(&placeholder3);

  // Set main menu
  ui.setScreen(&mainMenu);
  Serial.println("Setup done");
}

void loop() {
  // Call updates on plotter and ui
  plotter.update();
  ui.update();
}