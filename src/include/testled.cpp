#include "testled.h"
#include "global.h"
#include <FastLED.h>
#include <arduino-timer.h>
#include <ArduinoSTL.h>

#define TLSE_DEFAULT false // StartEnabled default value
#define TLIN_DEFAULT 0     // IndicatorID default value
#define TLLC_DEFAULT 1     // LEDCount default value

#define LED_CONTROLLER WS2811
#define LED_RGB_ORDER GRB

#define BLINK_INTERVAL_SLOW 1000
#define BLINK_INTERVAL_FAST 250

bool slowBlink = false;
bool fastBlink = false;

// -------------------- PIN DEFINITIONS
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15
#define PIN_16 16

std::vector<TestLED> allLEDs;

uint8_t GetPin(int pin) { return GetPin((byte)pin); }
uint8_t GetPin(byte pin)
{
    switch (pin)
    {
    case 0:
        return PIN_0;
    case 1:
        return PIN_1;
    case 2:
        return PIN_2;
    case 3:
        return PIN_3;
    case 4:
        return PIN_4;
    case 5:
        return PIN_5;
    case 6:
        return PIN_6;
    case 7:
        return PIN_7;
    case 8:
        return PIN_8;
    case 9:
        return PIN_9;
    case 10:
        return PIN_10;
    case 11:
        return PIN_11;
    case 12:
        return PIN_12;
    case 13:
        return PIN_13;
    case 14:
        return PIN_14;
    case 15:
        return PIN_15;
    case 16:
        return PIN_16;
    }
    return PIN_0;
}

#define MAX_LED_SIZE 128

CRGB LEDS_0[MAX_LED_SIZE];
CRGB LEDS_1[MAX_LED_SIZE];
CRGB LEDS_2[MAX_LED_SIZE];
CRGB LEDS_3[MAX_LED_SIZE];
CRGB LEDS_4[MAX_LED_SIZE];
CRGB LEDS_5[MAX_LED_SIZE];
CRGB LEDS_6[MAX_LED_SIZE];
CRGB LEDS_7[MAX_LED_SIZE];
CRGB LEDS_8[MAX_LED_SIZE];
CRGB LEDS_9[MAX_LED_SIZE];
CRGB LEDS_10[MAX_LED_SIZE];
CRGB LEDS_11[MAX_LED_SIZE];
CRGB LEDS_12[MAX_LED_SIZE];
CRGB LEDS_13[MAX_LED_SIZE];
CRGB LEDS_14[MAX_LED_SIZE];
CRGB LEDS_15[MAX_LED_SIZE];
CRGB LEDS_16[MAX_LED_SIZE];

CRGB *GetLEDs(int pin)
{
    switch (pin)
    {
    case 0:
        return LEDS_0;
    case 1:
        return LEDS_1;
    case 2:
        return LEDS_2;
    case 3:
        return LEDS_3;
    case 4:
        return LEDS_4;
    case 5:
        return LEDS_5;
    case 6:
        return LEDS_6;
    case 7:
        return LEDS_7;
    case 8:
        return LEDS_8;
    case 9:
        return LEDS_9;
    case 10:
        return LEDS_10;
    case 11:
        return LEDS_11;
    case 12:
        return LEDS_12;
    case 13:
        return LEDS_13;
    case 14:
        return LEDS_14;
    case 15:
        return LEDS_15;
    case 16:
        return LEDS_16;
    }
    LogError("Invalid pin for LEDs: " + (String)pin);
    return LEDS_0;
}

bool activePins[16] = {false, false, false, false, false, false, false, false,
                       false, false, false, false, false, false, false, false};

TestLED::TestLED(int pin, int ledCount, bool startEnabled, Display displayState, int indicatorId, Pattern patternState)
{
    if (activePins[pin])
    {
        LogError("Cannot re-use pin already occupied by TestLED " + pin);
    }
    if (ledCount > MAX_LED_SIZE)
    {
        LogWarning("Cannot exceed max LED count of " + (String)MAX_LED_SIZE + ", setting to" + (String)MAX_LED_SIZE);
        ledCount = MAX_LED_SIZE;
    }
    TestLED::pin = pin;
    TestLED::enabled = startEnabled;
    TestLED::ledCount = ledCount;
    TestLED::indicatorId = indicatorId;
    display = displayState;
    pattern = patternState;
    activePins[pin] = true;

    // add new FastLED pins

    switch (pin)
    {
    case 0:
        FastLED.addLeds<LED_CONTROLLER, PIN_0, LED_RGB_ORDER>(LEDS_0, ledCount);
        break;
    case 1:
        FastLED.addLeds<LED_CONTROLLER, PIN_1, LED_RGB_ORDER>(LEDS_1, ledCount);
        break;
    case 2:
        FastLED.addLeds<LED_CONTROLLER, PIN_2, LED_RGB_ORDER>(LEDS_2, ledCount);
        break;
    case 3:
        FastLED.addLeds<LED_CONTROLLER, PIN_3, LED_RGB_ORDER>(LEDS_3, ledCount);
        break;
    case 4:
        FastLED.addLeds<LED_CONTROLLER, PIN_4, LED_RGB_ORDER>(LEDS_4, ledCount);
        break;
    case 5:
        FastLED.addLeds<LED_CONTROLLER, PIN_5, LED_RGB_ORDER>(LEDS_5, ledCount);
        break;
    case 6:
        FastLED.addLeds<LED_CONTROLLER, PIN_6, LED_RGB_ORDER>(LEDS_6, ledCount);
        break;
    case 7:
        FastLED.addLeds<LED_CONTROLLER, PIN_7, LED_RGB_ORDER>(LEDS_7, ledCount);
        break;
    case 8:
        FastLED.addLeds<LED_CONTROLLER, PIN_8, LED_RGB_ORDER>(LEDS_8, ledCount);
        break;
    case 9:
        FastLED.addLeds<LED_CONTROLLER, PIN_9, LED_RGB_ORDER>(LEDS_9, ledCount);
        break;
    case 10:
        FastLED.addLeds<LED_CONTROLLER, PIN_10, LED_RGB_ORDER>(LEDS_10, ledCount);
        break;
    }

    // add new TestLED to allLEDs vector
    allLEDs.push_back(*this);
}

#pragma region TestLED Overrides

TestLED::TestLED(int pin, bool startEnabled, Display displayState, int indicatorId, Pattern patternState)
{
    TestLED(pin, TLLC_DEFAULT, startEnabled, displayState, indicatorId, patternState);
}
TestLED::TestLED(int pin, bool startEnabled, Display displayState, Pattern patternState) { TestLED(pin, startEnabled, displayState, TLIN_DEFAULT, patternState); }
TestLED::TestLED(int pin, bool startEnabled, int indicatorId, Pattern patternState) { TestLED(pin, startEnabled, TLD_INDICATOR, indicatorId, patternState); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled, Display displayState, Pattern patternState) { TestLED(pin, ledCount, startEnabled, displayState, indicatorId, patternState); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled, int indicatorId, Pattern patternState) { TestLED(pin, ledCount, startEnabled, TLD_INDICATOR, indicatorId, patternState); }

TestLED::TestLED(int pin) { TestLED(pin, TLSE_DEFAULT, TLD_DEFAULT, TLP_DEFAULT); }
TestLED::TestLED(int pin, bool startEnabled) { TestLED(pin, startEnabled, TLD_INDICATOR, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, Display displayState) { TestLED(pin, TLSE_DEFAULT, displayState, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, Display displayState, int indicatorId) { TestLED(pin, TLSE_DEFAULT, displayState, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, Pattern patternState) { TestLED(pin, TLSE_DEFAULT, TLD_INDICATOR, indicatorId, patternState); }
TestLED::TestLED(int pin, bool startEnabled, Display displayState) { TestLED(pin, startEnabled, displayState, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, bool startEnabled, int indicatorId) { TestLED(pin, startEnabled, TLD_INDICATOR, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, bool startEnabled, Pattern patternState) { TestLED(pin, startEnabled, TLD_INDICATOR, indicatorId, patternState); }
TestLED::TestLED(int pin, Display displayState, Pattern patternState) { TestLED(pin, TLSE_DEFAULT, displayState, indicatorId, patternState); }
TestLED::TestLED(int pin, Pattern patternState, int indicatorId) { TestLED(pin, TLSE_DEFAULT, TLD_INDICATOR, indicatorId, patternState); }

TestLED::TestLED(int pin, int ledCount) { TestLED(pin, ledCount, TLSE_DEFAULT, TLD_DEFAULT, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled) { TestLED(pin, ledCount, startEnabled, TLD_INDICATOR, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, Display displayState) { TestLED(pin, ledCount, TLSE_DEFAULT, displayState, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, int indicatorId) { TestLED(pin, ledCount, TLSE_DEFAULT, TLD_INDICATOR, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, Pattern patternState) { TestLED(pin, ledCount, TLSE_DEFAULT, TLD_INDICATOR, indicatorId, patternState); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled, Display displayState) { TestLED(pin, ledCount, startEnabled, displayState, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled, int indicatorId) { TestLED(pin, ledCount, startEnabled, TLD_INDICATOR, indicatorId, TLP_DEFAULT); }
TestLED::TestLED(int pin, int ledCount, bool startEnabled, Pattern patternState) { TestLED(pin, ledCount, startEnabled, TLD_INDICATOR, indicatorId, patternState); }
TestLED::TestLED(int pin, int ledCount, Display displayState, Pattern patternState) { TestLED(pin, ledCount, TLSE_DEFAULT, displayState, indicatorId, patternState); }
TestLED::TestLED(int pin, int ledCount, int indicatorId, Pattern patternState) { TestLED(pin, ledCount, TLSE_DEFAULT, TLD_INDICATOR, indicatorId, patternState); }

TestLED TestLED::TestLED_Good(int pin) { return TestLED(pin, TLSE_DEFAULT, TLD_GOOD); }
TestLED TestLED::TestLED_Good(int pin, bool startEnabled) { return TestLED(pin, startEnabled, TLD_GOOD); }
TestLED TestLED::TestLED_Bad(int pin) { return TestLED(pin, TLSE_DEFAULT, TLD_BAD); }
TestLED TestLED::TestLED_Bad(int pin, bool startEnabled) { return TestLED(pin, startEnabled, TLD_BAD); }
TestLED TestLED::TestLED_Indicator(int pin, int indicatorId) { return TestLED(pin, TLSE_DEFAULT, indicatorId); }
TestLED TestLED::TestLED_Indicator(int pin, int indicatorId, bool startEnabled) { return TestLED(pin, startEnabled, indicatorId); }

TestLED TestLED::TestLED_Good(int pin, int ledCount) { return TestLED(pin, ledCount, TLSE_DEFAULT, TLD_GOOD); }
TestLED TestLED::TestLED_Good(int pin, int ledCount, bool startEnabled) { return TestLED(pin, ledCount, startEnabled, TLD_GOOD); }
TestLED TestLED::TestLED_Bad(int pin, int ledCount) { return TestLED(pin, ledCount, TLSE_DEFAULT, TLD_BAD); }
TestLED TestLED::TestLED_Bad(int pin, int ledCount, bool startEnabled) { return TestLED(pin, ledCount, startEnabled, TLD_BAD); }
TestLED TestLED::TestLED_Indicator(int pin, int ledCount, int indicatorId) { return TestLED(pin, ledCount, TLSE_DEFAULT, indicatorId); }
TestLED TestLED::TestLED_Indicator(int pin, int ledCount, int indicatorId, bool startEnabled) { return TestLED(pin, ledCount, startEnabled, indicatorId); }

TestLEDRGB::TestLEDRGB(bool enabled)
{
    if (enabled)
        TestLEDRGB(255);
    else
        TestLEDRGB(0);
}
TestLEDRGB::TestLEDRGB(int rgb) : r(rgb), g(rgb), b(rgb) {}
TestLEDRGB::TestLEDRGB(byte rgb) : r(rgb), g(rgb), b(rgb) {}
TestLEDRGB::TestLEDRGB(int r, int g, int b) : r(r), g(g), b(b) {}
TestLEDRGB::TestLEDRGB(byte r, byte g, byte b) : r(r), g(g), b(b) {}
TestLEDRGB::TestLEDRGB(Display displayState) { TestLEDRGB(displayState, TLIN_DEFAULT); }
TestLEDRGB::TestLEDRGB(Display displayState, bool enabled) { TestLEDRGB(enabled ? displayState : TLD_OFF, TLIN_DEFAULT); }
TestLEDRGB::TestLEDRGB(Display displayState, int indicatorId, bool enabled) { TestLEDRGB(enabled ? displayState : TLD_OFF, indicatorId); }

#pragma endregion

TestLEDRGB::TestLEDRGB(Display displayState, int indicatorId)
{
    int x = (int)displayState;
    if (x == UINT8_MAX)
    {
        // Indicator, modulo to (max value - 1) + 1
        x = (indicatorId % 6) + 1;
    }
    else if (x < -1 || x > 7)
    {
        // invalid value
        LogWarning("Invalid TestLED Display ID " + (String)x + ", assigning -1 (error)");
    }
    if (x == -1)
    {
        // error
        TestLEDRGB(127, 31, 7);
    }
    else
    {
        // normal execution
        TestLEDRGB(_rgbTable[x][0], _rgbTable[x][1], _rgbTable[x][2]);
    }
}

void TestLED::ToggleEnabled()
{
    SetEnabled(!GetEnabled());
}

void TestLED::SetEnabled(bool enabled)
{
    if (TestLED::enabled == enabled)
        return;
    TestLED::enabled = enabled;
    UpdateLED();
}
void TestLED::SetDisplay(Display displayState)
{
    if (display == displayState)
        return;
    display = displayState;
    UpdateLED();
}
void TestLED::SetPattern(Pattern patternState)
{
    if (pattern == patternState)
        return;
    pattern = patternState;
    UpdateLED();
}
void TestLED::SetIndicatorID(int indicatorId)
{
    if (TestLED::indicatorId == indicatorId)
        return;
    TestLED::indicatorId = indicatorId;
    UpdateLED();
}

bool TestLED::IsBlinking() { return IsSlowBlinking() || IsFastBlinking(); }
bool TestLED::IsSlowBlinking() { return pattern == TLP_BLINK_SLOW || pattern == TLP_FLASH_SLOW; }
bool TestLED::IsFastBlinking() { return pattern == TLP_BLINK_FAST || pattern == TLP_FLASH_FAST; }

void TestLED::UpdateLED()
{

    TestLEDRGB rgb = TestLEDRGB(display, indicatorId);
}

void UpdatePin(int pin)
{
}
void UpdateBlink(bool fast) {
    
}

bool TestLED::GetEnabled() { return TestLED::enabled; }
Display TestLED::GetDisplay() { return TestLED::display; }
Pattern TestLED::GetPattern() { return TestLED::pattern; }
int TestLED::GetIndicatorID() { return TestLED::indicatorId; }

// auto testLEDTimer = timer_create_default();
// TestLEDTimer2.every(1000, Test);

bool Test(void *) { return true; }

Timer<2> TestLEDTimer;
void InitializeTimers()
{
    TestLEDTimer.every(BLINK_INTERVAL_SLOW, [](void *) -> bool
                       { slowBlink = !slowBlink; UpdateBlink(false); return true; });
    TestLEDTimer.every(BLINK_INTERVAL_FAST, [](void *) -> bool
                       { fastBlink = !fastBlink; UpdateBlink(true); return true; });
}
void UpdateTimers()
{
    TestLEDTimer.tick();
}

#undef TLSE_DEFAULT
#undef TLIN_DEFAULT
#undef TLLC_DEFAULT
