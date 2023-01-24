#include <Arduino.h>
#include <arduino-timer.h>

Timer<2> timer;

bool triggerLed(void *)
{
    digitalWrite(5, LOW);
    timer.in(250, [](void *) -> bool
             { 
            digitalWrite(5, HIGH);
            return false; });
    return false;
}

void setup()
{
    // print(BUILD_TYPE);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    timer.every(1000, triggerLed);
}
void loop()
{
    // digitalWrite(5, HIGH);
    timer.tick();
    // delay(1000);
    // digitalWrite(5, LOW);
    // delay(1000);
    // digitalWrite(5, HIGH);
}

/*

#include <WS2812.h>
#include <arduino-timer.h>

#include "global.h"
#include "testled.h"

#include <PJONSoftwareBitBang.h>

#define IS_CONSUMER false

// #define BLOCKTYPE PowerSupply

// Bus id definition
uint8_t bus_id[] = {0, 0, 0, 1};

// PJON object
PJONSoftwareBitBang bus(bus_id, IS_CONSUMER ? 44 : 45);

#define LED_PIN 5 // source
// #define LED_PIN 3
// #define LED_PIN 7

// #define SOURCE_COMMUNICATION_PIN 10
// #define CONSUMER_COMMUNICATION_PIN 9
#define SOURCE_COMMUNICATION_PIN 0
#define CONSUMER_COMMUNICATION_PIN 1

Timer<4> timer;

// CRGB leds[2];
WS2812 LED(3);
cRGB rgb;

void CommsReceived(uint8_t *payload, uint16_t length,
                   const PJON_Packet_Info &packet_info)
{
  // packet received
  if (packet_info.rx.id != 45)
  {
    // leds[1] = CRGB::Yellow;
    rgb.r = 255;
    rgb.g = 255;
    rgb.b = 0;
  }
  else
  {
    if ((String)payload[1] != "B")
    {
      // leds[1] = CRGB::Red;
      rgb.r = 255;
      rgb.g = 0;
      rgb.b = 0;
    }
    else
    {
      // leds[1] = CRGB::Green;
      rgb.r = 0;
      rgb.g = 255;
      rgb.b = 0;
    }
  }
  LED.set_crgb_at(1, rgb);
  LED.sync();

  timer.in(333, [](void *) -> bool
           {
            rgb.r = 32;
            rgb.g = 32;
            rgb.b = 32;
            LED.set_crgb_at(1, rgb);
            LED.sync();
            return false; });
}

void setup()
{
  bus.strategy.set_pin(CONSUMER_COMMUNICATION_PIN);

  LED.setOutput(LED_PIN);

  if (IS_CONSUMER)
  {
    // FastLED.addLeds<WS2811, 3, GRB>(leds, 2);
    // leds[0] = CRGB::DarkBlue;
    rgb.r = 8;
    rgb.g = 16;
    rgb.b = 64;
    LED.set_crgb_at(0, rgb);
    // leds[1] = CRGB::DarkGray;
    rgb.r = 32;
    rgb.g = 32;
    rgb.b = 32;
    LED.set_crgb_at(1, rgb);

    bus.begin();
    bus.set_receiver(CommsReceived);
  }
  else
  {

    // FastLED.addLeds<WS2811, 5, GRB>(leds, 2);
    // leds[0] = CRGB::GhostWhite;
    rgb.r = 120;
    rgb.g = 140;
    rgb.b = 130;
    LED.set_crgb_at(0, rgb);
    rgb.r = 16;
    rgb.g = 8;
    rgb.b = 8;
    LED.set_crgb_at(1, rgb);

    bus.begin();
    bus.send_repeatedly(44, "B", 1, 1000000);
    timer.every(1000, [](void *) -> bool
                {
            rgb.r = 16;
            rgb.g = 96;
            rgb.b = 213;
            LED.set_crgb_at(1, rgb);
            LED.sync();
            timer.in(200, [](void *) -> bool
                    {
                      rgb.r = 16;
                      rgb.g = 32;
                      rgb.b = 16;
                      LED.set_crgb_at(1, rgb);
                      LED.sync();
                      return false; });
            return true; });
  }

  rgb.r = 0;
  rgb.g = 0;
  rgb.b = 0;
  LED.set_crgb_at(2, rgb);

  LED.sync();

  // FastLED.setBrightness(90);
  // FastLED.show();
}

void loop()
{

  timer.tick();

  if (IS_CONSUMER)
  {
    bus.receive(1000);
  }
  else
  {
    bus.update();
  }
}
/**/