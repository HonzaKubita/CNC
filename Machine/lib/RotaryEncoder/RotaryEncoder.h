#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

class RotaryEncoder {
  public:
    RotaryEncoder(int CLK, int DT, int SW);
    void update(); // Updating function
    int getDirection(); // Get the direction the encoder was rotated to last update
    bool isPressed(); // If the encoder is being pressed
    bool gotClicked(); // Only returns first update in which is isPressed() true
  private:
    int _CLK;
    int _DT;
    int _DTLastState;
    int _SW;
    int _SWLastState;
    bool _isPressed;
    bool _gotClicked;
    int _direction;
};

#endif // __ROTARYENCODER_H__