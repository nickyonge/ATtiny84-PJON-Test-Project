// commented out, removing FastLED because filesize =_=

// #ifndef TESTLED_H
// #define TESTLED_H

// #include <ArduinoSTL.h>
// #include <FastLED.h>
// #include <arduino-timer.h>

// enum Display
// {
//     TLD_NONE = 0,

//     TLD_DEFAULT = 1,
//     TLD_ON = 1,
//     TLD_OFF = 0,

//     TLD_WHITE = 1,
//     TLD_RED = 2,
//     TLD_YELLOW = 3,
//     TLD_GREEN = 4,
//     TLD_CYAN = 5,
//     TLD_BLUE = 6,
//     TLD_MAGENTA = 7,

//     TLD_GOOD = 4,
//     TLD_BAD = 2,
//     TLD_WARNING = 3,
//     TLD_READY = 6,

//     TLD_INTERNALERROR = -1,

//     TLD_INDICATOR = UINT8_MAX,
// };

// enum Pattern
// {
//     TLP_DEFAULT = 0,
//     TLP_SOLID = 0,
//     TLP_BLINK_SLOW = 1,
//     TLP_BLINK_FAST = 2,
//     TLP_FLASH_SLOW = 3,
//     TLP_FLASH_FAST = 4,
// };

// struct TestLEDRGB
// {
// private:
//     const int _rgbTable[8][3] =
//         {{0, 0, 0},       // black
//          {255, 255, 255}, // white
//          {255, 0, 0},     // red
//          {255, 255, 0},   // yellow
//          {255, 255, 0},   // green
//          {0, 255, 255},   // cyan
//          {0, 0, 255},     // blue
//          {255, 0, 255}};  // magenta

//     byte r;
//     byte g;
//     byte b;

// public:
//     TestLEDRGB(bool enabled);
//     TestLEDRGB(byte rgb);
//     TestLEDRGB(int rgb);
//     TestLEDRGB(byte r, byte g, byte b);
//     TestLEDRGB(int r, int g, int b);
//     TestLEDRGB(Display displayState);
//     TestLEDRGB(Display displayState, int indicatorId);
//     TestLEDRGB(Display displayState, bool enabled);
//     TestLEDRGB(Display displayState, int indicatorId, bool enabled);
// };

// class TestLED
// {
// private:
//     std::vector<int> usedPins;
//     int pin;
//     int ledCount;
//     bool enabled;
//     int indicatorId;
//     Display display;
//     Pattern pattern;
//     TestLED *self;

//     TestLED(int pin, bool startEnabled, Display displayState, int indicatorId, Pattern patternState);
//     TestLED(int pin, int ledCount, bool startEnabled, Display displayState, int indicatorId, Pattern patternState);

//     void UpdateLED();
//     bool IsBlinking();
//     bool IsSlowBlinking();
//     bool IsFastBlinking();

// public:
//     TestLED(int pin);
//     TestLED(int pin, bool startEnabled);
//     TestLED(int pin, Display displayState);
//     TestLED(int pin, Display displayState, int indicatorId);
//     TestLED(int pin, Pattern patternState);
//     TestLED(int pin, bool startEnabled, Display displayState);
//     TestLED(int pin, bool startEnabled, int indicatorId);
//     TestLED(int pin, bool startEnabled, Pattern patternState);
//     TestLED(int pin, Display displayState, Pattern patternState);
//     TestLED(int pin, Pattern patternState, int indicatorId);
//     TestLED(int pin, bool startEnabled, Display displayState, Pattern patternState);
//     TestLED(int pin, bool startEnabled, int indicatorId, Pattern patternState);

//     TestLED(int pin, int ledCount);
//     TestLED(int pin, int ledCount, bool startEnabled);
//     TestLED(int pin, int ledCount, Display displayState);
//     TestLED(int pin, int ledCount, int indicatorId);
//     TestLED(int pin, int ledCount, Pattern patternState);
//     TestLED(int pin, int ledCount, bool startEnabled, Display displayState);
//     TestLED(int pin, int ledCount, bool startEnabled, int indicatorId);
//     TestLED(int pin, int ledCount, bool startEnabled, Pattern patternState);
//     TestLED(int pin, int ledCount, Display displayState, Pattern patternState);
//     TestLED(int pin, int ledCount, int indicatorId, Pattern patternState);
//     TestLED(int pin, int ledCount, bool startEnabled, Display displayState, Pattern patternState);
//     TestLED(int pin, int ledCount, bool startEnabled, int indicatorId, Pattern patternState);

//     TestLED TestLED_Good(int pin);
//     TestLED TestLED_Good(int pin, bool startEnabled);
//     TestLED TestLED_Bad(int pin);
//     TestLED TestLED_Bad(int pin, bool startEnabled);
//     TestLED TestLED_Indicator(int pin, int indicatorId);
//     TestLED TestLED_Indicator(int pin, int indicatorId, bool startEnabled);

//     TestLED TestLED_Good(int pin, int ledCount);
//     TestLED TestLED_Good(int pin, int ledCount, bool startEnabled);
//     TestLED TestLED_Bad(int pin, int ledCount);
//     TestLED TestLED_Bad(int pin, int ledCount, bool startEnabled);
//     TestLED TestLED_Indicator(int pin, int ledCount, int indicatorId);
//     TestLED TestLED_Indicator(int pin, int ledCount, int indicatorId, bool startEnabled);

//     void ToggleEnabled();

//     void SetEnabled(bool enabled);
//     void SetDisplay(Display displayState);
//     void SetPattern(Pattern patternState);
//     void SetIndicatorID(int indicatorId);

//     bool GetEnabled();
//     Display  GetDisplay();
//     Pattern GetPattern();
//     int GetIndicatorID();
// };

// void UpdatePin(int pin);
// void UpdateBlink(bool fast);
// void InitializeTimers();
// void UpdateTimers();

// #endif