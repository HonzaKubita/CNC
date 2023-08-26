#ifndef __UI_H__
#define __UI_H__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h> // Library for LCD

class UI;

// The main class for creating screens
class Screen {
  public:
    String title; // title of the screen
    Screen* from; // Link to the screen that redirected to this screen
    Screen(String screenTitle);
    void navigate(String direction); // Send user input to the screen
    virtual void render(LiquidCrystal_I2C* lcd); // Render
    virtual void update(UI* ui); // Rendering and updating

  protected:
    String _navigation; // Input from user in current update
};

class Menu : public Screen {
  public:
    int selectedItem; // Currently selected item
    int scroll; // How much is the menu scrolled down

    Menu(String menuTitle);
    void addItem(Screen* item); // Adding items to the menu

    int getItemCount(); // itemCount getter
    Screen* getItem(int index); // item getter

    void render(LiquidCrystal_I2C* lcd); // Rendering the menu
    void update(UI* ui); // Updating the menu according to user input
  protected:
    Screen* _items[20]; // Items of the menu
    int _itemCount; // Number of items
};

class UI {
  public:
    String currentAction; // Currently selected action by the user

    UI(LiquidCrystal_I2C* lcd);
    void setScreen(Screen* newScreen); // Setting the current screen
    void init(); // Initialization function
    void update();
    
    void requestRender(); // Function for requesting the screen to be redrawn

  protected:
    Screen* _currentScreen; // Currently displayed screen
    LiquidCrystal_I2C* _lcd; // The lcd UI is getting rendered to
    bool _renderRequest;
};

#endif // __UI_H__