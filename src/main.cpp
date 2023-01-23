#include <Arduino.h>
// #include <FastLED.h>
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

#define SOURCE_COMMUNICATION_PIN 10
#define CONSUMER_COMMUNICATION_PIN 9

Timer<1> timer;

// CRGB leds[2];

void CommsReceived(uint8_t *payload, uint16_t length,
                   const PJON_Packet_Info &packet_info)
{
  // packet received
  if (packet_info.rx.id != 45)
  {
    // leds[1] = CRGB::Yellow;
  }
  else
  {
    if ((String)payload[1] != "B")
    {
      // leds[1] = CRGB::Red;
    }
    else
    {
      // leds[1] = CRGB::Green;
    }
  }

  timer.in(333, [](void *) -> bool
           { 
            // leds[1] = CRGB::DarkGray; 
            return false; });
}

void setup()
{
  // bus.strategy.set_pin(CONSUMER_COMMUNICATION_PIN);

  // if (IS_CONSUMER)
  // {
  //   // FastLED.addLeds<WS2811, 3, GRB>(leds, 2);
  //   // leds[0] = CRGB::DarkBlue;
  //   // leds[1] = CRGB::DarkGray;

  //   bus.begin();
  //   bus.set_receiver(CommsReceived);
  // }
  // else
  // {

  //   // FastLED.addLeds<WS2811, 5, GRB>(leds, 2);
  //   // leds[0] = CRGB::GhostWhite;

  //   bus.begin();
  //   bus.send_repeatedly(44, "B", 1, 1000000);
  // }

  // FastLED.setBrightness(90);
  // FastLED.show();
}

void loop()
{

  timer.tick();

  // if (IS_CONSUMER)
  // {
  //   bus.receive(1000);
  // }
  // else
  // {
  //   bus.update();
  // }
}

// void IncrementTimers() {
//   // TestLEDTimer.tick();
// }