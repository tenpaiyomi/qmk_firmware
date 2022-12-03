#include QMK_KEYBOARD_H
#include "analog.h"
#include "print.h"

static bool encoder_pressed;

int16_t max_pot_val = 950;
int16_t max_ticks = 50;
int16_t pot_oldVal = 0;
int16_t pot_val    = 0;
bool moving     = false;
#define POT_TOLERANCE 12

// const uint16_t encoder_press_map[NUM_ENCODERS][2] = { 
//   KC_F18,
//   KC_MUTE
// };

void matrix_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
        #ifdef DRIVER_1_PW_EN
        wait_ms(2000);
        setPinOutput(DRIVER_1_PW_EN);
        writePinHigh(DRIVER_1_PW_EN);
        #endif
    #endif

    setPinInputLow(ENCODER_PIN);
}

void matrix_scan_user(void) {
  if (readPin(ENCODER_PIN)) {
    encoder_pressed = false;
  } else {
    if (!encoder_pressed) {
      if(layer_state_is(NUMPAD)) {
        tap_code(KC_MUTE);
      } else if(layer_state_is(MACROS)) {
        tap_code(KC_F18);
      }
    }
    encoder_pressed = true;
  }

  pot_val = analogReadPin(SLIDER_PIN);
  if (abs(pot_val - pot_oldVal) > POT_TOLERANCE) {
    moving = true;
    pot_oldVal = pot_val;
  } else {
    if (moving) {
      // Do some fancy conversion to get 'absolute' position to num tap_codes to send
      // Reset moving to 0 so that we don't get multiple attempts to do this
      int num_ticks = ((float) pot_val / max_pot_val) * max_ticks;
      uprintf("%u - %u - %u\n", pot_oldVal, pot_val, num_ticks);

      for (int i = 0; i < max_ticks; ++i) {
        tap_code(KC_VOLD);
      }

      for (int i = 0; i < num_ticks; ++i) {
        tap_code(KC_VOLU);
      }

      moving = false;
    }
  }
}