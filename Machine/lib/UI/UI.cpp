#include <UI.h> // Library header file
#include <Arduino.h>
#include <LiquidCrystal_I2C.h> // Library for LCD

// Screen class

Screen::Screen(String screenTitle) {
  title = screenTitle;
  from = nullptr;
}

void Screen::navigate(String navigation) {
  _navigation = navigation;
}

void Screen::render(LiquidCrystal_I2C* lcd) {}
void Screen::update(UI* ui) {}


// Menu class - Type of screen

Menu::Menu(String menuTitle) : Screen(menuTitle) {
  title = menuTitle;
  _itemCount = 0;
  selectedItem = 0;
  scroll = 0;

  // Fill the items array
  for (int i = 0; i < 20; i++) {
    _items[i] = nullptr;
  }
}

void Menu::addItem(Screen* item) {
  if (_itemCount >= 20) 
    return; // Exit if menu is already full (for safety)

  // Add the item to the item array
  _items[_itemCount] = item;
  // Increase the item count
  _itemCount++;
}

int Menu::getItemCount() {
  int itemCount = _itemCount;
  if (from != nullptr) {
    itemCount++;
  }
  return itemCount;
}

Screen* Menu::getItem(int index) {
  if (from != nullptr) {
    if (index == 0) {
      return from;
    }
    else {
      return _items[index - 1];
    }
  }
  else {
    return _items[index];
  }
}

void Menu::render(LiquidCrystal_I2C* lcd) {
  // Render
  // Clear the lcd
  lcd->clear();

  // Render all the items
  for (int i = 0; i < getItemCount() + 1; i++) {
    // If item is on screen
    if (i >= scroll && i < scroll + 4) {
      if (i == 0) {
        // Item is the menu title
        lcd->setCursor(0, 0);
        lcd->print(title);
      }
      else {
        // Item is regular item
        Screen* currItem = getItem(i - 1);

        // If item is selected
        if (selectedItem == i - 1) {
          lcd->setCursor(0, i);

          // If item is back to shortcut render different symbol
          if (currItem == from) {
            lcd->print("<");
          } else {
            lcd->print(">");
          }
        }

        lcd->setCursor(1, i);
        lcd->print(currItem->title);
      }
    }
  }
}

void Menu::update(UI* ui) {
  // Process navigation and request render if navigation
  if (_navigation == "select") {
    // Item got selected
    // Change the ui currentScreen to the selected item

    // Select the screen in ui
    ui->setScreen(getItem(selectedItem));
    ui->requestRender();
  }

  if (_navigation == "down") {
    // Increase selectedItem if possible, scroll if needed.

    if (selectedItem + 1 <= getItemCount()) {
      selectedItem++;

      // If needed scroll
      if (scroll + 4 < selectedItem) {
        scroll++;
      }
    }
    ui->requestRender();
  }

  if (_navigation == "up") {
    // Decrease selectedItem if possible, scroll if needed.

    if (selectedItem - 1 >= 0) {
      selectedItem--;

      // If needed scroll
      if (scroll > selectedItem) {
        scroll--;
      }
    }
    ui->requestRender();
  }
}


// UI class

UI::UI(LiquidCrystal_I2C* lcd) {
  // Initialize variable values
  currentAction = "";

  _currentScreen = nullptr;
  _lcd = lcd;
  _renderRequest = true;
}

void UI::setScreen(Screen* newScreen) {
  newScreen->from = _currentScreen; // Tell the new screen which screen linked to it
  _currentScreen = newScreen; // Change the screen
}

void UI::init() {
  // Initialize the lcd
  _lcd->init();
  _lcd->backlight();
  _lcd->setCursor(0,0);
}

void UI::update() {
  // Call render on the current screen
  if (_currentScreen) {
    _currentScreen->update(this);

    if (_renderRequest) {
      _currentScreen->render(_lcd);
      _renderRequest = false;
    }
  }
}

void UI::requestRender() {
  _renderRequest = true;
}
