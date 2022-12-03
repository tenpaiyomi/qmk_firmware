#undef TAPPING_TERM
#define TAPPING_TERM 175

#define TAPPING_TERM_PER_KEY

enum {
  TD_MUTE_F18,
  TD_PSCR_F17,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap once for Play/Pause, twice for F18 to mute microphone
  [TD_MUTE_F18] = ACTION_TAP_DANCE_DOUBLE(KC_MUTE, KC_F18),

  // Tap once for Printscreen, twice for F17 to switch inputs
  [TD_PSCR_F17] = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, KC_F17),
};