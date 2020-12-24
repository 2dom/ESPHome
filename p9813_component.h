// This creates Home Assistant monochromatic lamps using every channel of P9813 RGB PWM modules individually. Hence on module gives you three lights / splitting the RGB channels 
https://github.com/2dom/ESPHome
#include "esphome.h"
#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN 2
#define CLOCK_PIN 1

CRGB leds[NUM_LEDS];





class MyCustomLightOutput : public Component, public LightOutput {
public:
  uint8_t _output_no;
  void setup() override {
    // This will be called by App.setup()
    FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    
  }

  void set_output (uint8_t output_no)
  {
    _output_no=output_no;
  }

  LightTraits get_traits() override {
    // return the traits this light supports
    auto traits = LightTraits();
    traits.set_supports_brightness(true);
    traits.set_supports_rgb(false);
    traits.set_supports_rgb_white_value(false);
    traits.set_supports_color_temperature(false);
    return traits;
  }

  void write_state(LightState *state) override {
    // This will be called by the light to get a new state to be written.
    float brightness;
    // use any of the provided current_values methods
    state->current_values_as_brightness(&brightness);
    // Write red, green and blue to HW
    // ...

    
    int value = brightness * 255;
    int channel_no=_output_no%3;
    int board_no=_output_no/3;
    
    if (channel_no==0)
      leds[board_no].red=value;
    if (channel_no==1)
      leds[board_no].green=value;
    if (channel_no==2)
      leds[board_no].blue=value;
    FastLED.show();

  }
};
