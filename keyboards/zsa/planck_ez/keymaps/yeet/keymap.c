#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

// KC_TRANSPARENT is *far* too long a name for something used so often
#define KC_ KC_TRANSPARENT

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

// the functional stack order of our layers is set here, though we define their
// keys below in a different order to group together the things that are
// conceptually related
enum planck_layers {
  // base layers
  _BASE,
  _XIV,
  _IJKL,
  _LOL,

  // lower layers
  _LOWER,
  _XIVLOWER,

  // raise layers
  _RAISE,
  // _XIVRAISE, // TODO: do we need one

  // adjust layers
  _ADJUST,
  _XIVADJUST,

  // other modifier layers
  _FN, // kept pretty high so media keys are still accessible from game modes

  // the mode select layer, which should always be the last one juuuust in case
  _MODE_SELECT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // normal typing layers. these are just the default planck keymap mostly
  [_BASE] = LAYOUT_planck_grid(
    KC_TAB,         KC_Q,     KC_W,         KC_E,         KC_R,        KC_T,      KC_Y,   KC_U,        KC_I,      KC_O,     KC_P,      KC_BSPC,
    KC_ESCAPE,      KC_A,     KC_S,         KC_D,         KC_F,        KC_G,      KC_H,   KC_J,        KC_K,      KC_L,     KC_SCLN,   KC_QUOTE,
    KC_LEFT_SHIFT,  KC_Z,     KC_X,         KC_C,         KC_V,        KC_B,      KC_N,   KC_M,        KC_COMMA,  KC_DOT,   KC_SLASH,  KC_ENTER,
    KC_LEFT_CTRL,   MO(_FN),  KC_LEFT_GUI,  KC_LEFT_ALT,  MO(_LOWER),  KC_SPACE,  KC_NO,  MO(_RAISE),  KC_LEFT,   KC_DOWN,  KC_UP,     KC_RIGHT
  ),
  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD,  KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,     KC_,
    KC_,      KC_F1,    KC_F2,  KC_F3,    KC_F4,   KC_F5,    KC_F6,    KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,     KC_PIPE,
    KC_,      KC_F7,    KC_F8,  KC_F9,    KC_F10,  KC_F11,   KC_F12,   KC_,      KC_,      KC_,      KC_,         KC_,
    KC_,      KC_,      KC_,    KC_,      KC_,     KC_,      KC_NO,    KC_,      KC_HOME,  KC_PGDN,  KC_PAGE_UP,  KC_END
  ),
  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,   KC_7,      KC_8,      KC_9,     KC_0,        KC_,
    KC_,       KC_,   KC_,   KC_,   KC_,   KC_,   KC_,    KC_MINUS,  KC_EQUAL,  KC_LBRC,  KC_RBRC,     KC_BSLS,
    KC_,       KC_,   KC_,   KC_,   KC_,   KC_,   KC_,    KC_,       KC_,       KC_,      KC_,         KC_,
    KC_,       KC_,   KC_,   KC_,   KC_,   KC_,   KC_NO,  KC_,       KC_HOME,   KC_PGDN,  KC_PAGE_UP,  KC_END
  ),

  // we use adjust for a bunch of common shortcuts:
  // - ctrl+` opens the vs code terminal
  // - ctrl+<number> does tab switching in many contexts
  // - gui+<number> does window/application switching
  // - ctrl+(-) and ctrl+(=) (and ctrl+0) do zoom in many contexts
  // - forward delete replaces backspace because it's easy to shove here
  [_ADJUST] = LAYOUT_planck_grid(
    LCTL(KC_GRAVE),  LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),        LCTL(KC_6),  LCTL(KC_7),  LCTL(KC_8),  LCTL(KC_9),      LCTL(KC_0),      KC_DELETE,
    KC_,             LGUI(KC_1),  LGUI(KC_2),  LGUI(KC_3),  LGUI(KC_4),  LGUI(KC_5),        KC_,         KC_,         KC_,         LCTL(KC_MINUS),  LCTL(KC_EQUAL),  KC_,
    KC_,             KC_,         KC_,         KC_,         KC_,         KC_,               KC_,         KC_,         KC_,         KC_,             KC_,             KC_,
    KC_,             KC_,         KC_,         KC_,         KC_,         TO(_MODE_SELECT),  KC_NO,       KC_,         KC_,         KC_,             KC_,             KC_
  ),

  // media controls, rgb controls, numpad
  [_FN] = LAYOUT_planck_grid(
    KC_,     KC_,                  KC_,                  KC_,                KC_,      RGB_HUD,  RGB_HUI,  KC_,               KC_KP_7,  KC_KP_8,  KC_KP_9,    KC_,
    KC_,     KC_MEDIA_PLAY_PAUSE,  KC_AUDIO_MUTE,        KC_AUDIO_VOL_UP,    KC_,      RGB_SAD,  RGB_SAI,  KC_,               KC_KP_4,  KC_KP_5,  KC_KP_6,    KC_NUM,
    KC_F15,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_NEXT_TRACK,  KC_AUDIO_VOL_DOWN,  RGB_SLD,  RGB_SPD,  RGB_SPI,  RGB_MODE_FORWARD,  KC_KP_1,  KC_KP_2,  KC_KP_3,    KC_KP_ENTER,
    KC_,     KC_,                  KC_,                  KC_,                RGB_VAD,  RGB_TOG,  KC_NO,    RGB_VAI,           KC_KP_0,  KC_,      KC_KP_DOT,  KC_KP_ENTER
  ),

  // layout mostly for playing tetris, moves arrows to the IJKL keys and
  // replaces LALT with another space key that's more comfortable to press with
  // fingers on the Z and X keys (the rotate keys in tetr.io)
  [_IJKL] = LAYOUT_planck_grid(
    KC_,  KC_,  KC_,  KC_,       KC_,  KC_,  KC_,    KC_,      KC_UP,    KC_,       KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,       KC_,  KC_,  KC_,    KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,       KC_,  KC_,  KC_,    KC_,      KC_,      KC_,       KC_,  KC_,
    KC_,  KC_,  KC_,  KC_SPACE,  KC_,  KC_,  KC_NO,  KC_,      KC_,      KC_,       KC_,  KC_
  ),

  // league. i don't know why i still have this i will probably never use it
  [_LOL] = LAYOUT_planck_grid(
    KC_,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,   KC_7,  KC_,  KC_,  KC_,  KC_,
    KC_,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_,    KC_,   KC_,  KC_,  KC_,  KC_,
    KC_,  KC_A,  KC_S,  KC_D,  KC_F,  KC_,   KC_,    KC_,   KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,   KC_,   KC_,   KC_,   KC_,   KC_NO,  KC_,   KC_,  KC_,  KC_,  KC_
  ),

  // this layer is entirely transparent, with the exception of having the
  // lower/raise keys activate the XIV-specific lower/raise layers instead. we
  // also have an XIV-specific adjust layer which is activated by additional
  // tri-state logic below
  [_XIV] = LAYOUT_planck_grid(
    KC_,  KC_,  KC_,  KC_,  KC_,            KC_,  KC_,    KC_,            KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  KC_,            KC_,  KC_,    KC_,            KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  KC_,            KC_,  KC_,    KC_,            KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  MO(_XIVLOWER),  KC_,  KC_NO,  MO(_RAISE),  KC_,  KC_,  KC_,  KC_
  ),

  // this is the normal lower layer, except that layer has all the hotbar
  // keybinds on it. my in-game hotbar binds look like this for reference:
  //   [1]     `      1      2      3      4      5      6  q     e  r  t
  //   [2] alt+`  alt+1  alt+2  alt+3  alt+4  alt+5  alt+6           f  g
  //   [3] ctl+`  ctl+1  ctl+2  ctl+3  ctl+4  ctl+5  ctl+6  z  x  c  v  b
  // note that the keymap sends shift+{`,1-6} on the top row even though my
  // hotbars keybinds don't expect the shift modifier for hotbar 1. this still
  // works because i don't have any other things mapped to shift+{`,1-6}, and
  // doing it this way lets me use this like a normal lower layer for typing
  // symbols in chat. similarly, i can't map 7890- across because i want to be
  // able to type _+{} normally, so i need to leave the right four columns
  // identical to the normal lower layer
  [_XIVLOWER] = LAYOUT_planck_grid(
    LSFT(KC_GRAVE),  LSFT(KC_1),  LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),  LSFT(KC_6),  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,     KC_,
    LALT(KC_GRAVE),  LALT(KC_1),  LALT(KC_2),  LALT(KC_3),  LALT(KC_4),  LALT(KC_5),  LALT(KC_6),  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,     KC_PIPE,
    LCTL(KC_GRAVE),  LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),  LCTL(KC_6),  KC_,      KC_,      KC_,      KC_,         KC_,
    KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_,         KC_,         KC_NO,       KC_,      KC_HOME,  KC_PGDN,  KC_PAGE_UP,  KC_END
  ),

  // this layer is only ever going to be touched while typing because the raise
  // key isn't easy to get at with the left hand on WASD. it will maybe be
  // useful eventually, but not yet
  // [_XIVRAISE] = LAYOUT_planck_grid(...),

  // this will definitely be useful later as an emote macro board or something,
  // but for now it has nothing but the key to trigger the mode select layer. it
  // doesn't include any of the other shortcuts that the normal select layer
  // does though, since none of those things really apply to XIV and
  // accidentally hitting combinations that interact with the windows key in a
  // game is annoying
  [_XIVADJUST] = LAYOUT_planck_grid(
    KC_,  KC_,  KC_,  KC_,  KC_,  KC_,               KC_,    KC_,  KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  KC_,  KC_,               KC_,    KC_,  KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  KC_,  KC_,               KC_,    KC_,  KC_,  KC_,  KC_,  KC_,
    KC_,  KC_,  KC_,  KC_,  KC_,  TO(_MODE_SELECT),  KC_NO,  KC_,  KC_,  KC_,  KC_,  KC_
  ),

  // the menu that lets us pick between our layers
  [_MODE_SELECT] = LAYOUT_planck_grid(
    QK_BOOT,           KC_NO,  KC_NO,  KC_NO,  KC_NO,         TO(_IJKL),  KC_NO,  KC_NO,  KC_NO,   KC_NO,     KC_NO,  KC_NO,
    KC_NO,             KC_NO,  KC_NO,  KC_NO,  TO(_XIV),  KC_NO,      KC_NO,  KC_NO,  KC_NO,   TO(_LOL),  KC_NO,  KC_NO,
    KC_NO,             KC_NO,  KC_NO,  KC_NO,  KC_NO,         KC_NO,      KC_NO,  KC_NO,  KC_NO,   KC_NO,     KC_NO,  KC_NO,
    RGB_MODE_FORWARD,  KC_NO,  KC_NO,  KC_NO,  KC_NO,         TO(_BASE),  KC_NO,  KC_NO,  KC_NUM,  KC_NO,     KC_,    KC_
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

// enumerate our LED maps separately from our layers, since several share colors
enum led_maps {
  LED_FN,
  LED_MODE_SELECT,
  LED_XIV,
  LED_XIV_LOWER,
  LED_XIV_BGONLY,
  LED_LOL,
  LED_IJKL,
};

// define the colors for each (this is HSV)
const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
  [LED_FN] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {44,138,254}, {44,138,254}, {0,0,0}, {83,84,255}, {83,84,255}, {83,84,255}, {0,0,0},
    {0,0,0}, {83,221,255}, {83,221,255}, {83,221,255}, {0,0,0}, {44,138,254}, {44,138,254}, {0,0,0}, {83,84,255}, {83,84,255}, {83,84,255}, {83,88,84},
    {0,255,255}, {83,221,255}, {83,221,255}, {83,221,255}, {44,138,254}, {44,138,254}, {44,138,254}, {44,138,254}, {83,84,255}, {83,84,255}, {83,84,255}, {0,0,0},
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {44,138,254}, {44,138,254}, {44,138,254}, {83,84,255}, {0,0,0}, {83,84,255}, {0,0,0}
  },
  [LED_MODE_SELECT] = {
    {0,245,245}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {206,178,189}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {171,219,210}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {32,255,255}, {0,0,0}, {0,0,0},
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {83,84,255}, {0,0,0}, {83,221,255}, {0,0,0}, {0,0,0}, {0,0,0}
  },
  [LED_IJKL] = {
    {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,178,189}, {206,177,115}, {206,177,115}, {206,177,115},
    {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,178,189}, {206,178,189}, {206,178,189}, {206,177,115}, {206,177,115},
    {206,178,189}, {206,178,189}, {206,178,189}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115},
    {206,177,115}, {206,177,115}, {206,177,115}, {206,178,189}, {206,177,115}, {206,177,115},                {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}, {206,177,115}
  },
  [LED_LOL] = {
    {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115},
    {32,255,115}, {32,255,248}, {32,255,248}, {32,255,248}, {32,255,248}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115},
    {32,255,115}, {33,255,182}, {32,255,115}, {32,255,115}, {32,255,115}, {33,255,182}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115},
    {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115},               {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}, {32,255,115}
  },
  [LED_XIV_LOWER] = {
    {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,178,255}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},                {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}
  },
  [LED_XIV_BGONLY] = {
    {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},
    {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115},                {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}, {171,219,115}
  }
};

void apply_led_map(int map) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[map][i][0]),
      .s = pgm_read_byte(&ledmap[map][i][1]),
      .v = pgm_read_byte(&ledmap[map][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
      rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
      RGB rgb = hsv_to_rgb( hsv );
      float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
      rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
    return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case _FN:
      apply_led_map(LED_FN);
      break;
    case _MODE_SELECT:
      apply_led_map(LED_MODE_SELECT);
      break;
    case _IJKL:
      apply_led_map(LED_IJKL);
      break;
    case _LOL:
      apply_led_map(LED_LOL);
      break;
      apply_led_map(LED_XIV);
      break;
    case _XIV:
    // case _XIVRAISE:
    case _XIVADJUST:
      apply_led_map(LED_XIV_BGONLY);
      break;
    case _XIVLOWER:
      apply_led_map(LED_XIV_LOWER);
      break;

    // raise doesn't normally get any special handling, but we do want it to use
    // the LED setting for XIV if the XIV base layer is active underneath it
    case _RAISE:
      if (layer_state & (1 << _XIV)) {
        apply_led_map(LED_XIV_BGONLY);
        break;
      }
      // else case intentionally falls through to default behavior

    default:
      if (rgb_matrix_get_flags() == LED_FLAG_NONE)
        rgb_matrix_set_color_all(0, 0, 0);
      break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case RGB_SLD:
      if (rawhid_state.rgb_control) {
        return false;
      }
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint16_t layer_state_set_user(uint16_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  // this handles the logic of our special additional raise/lower combo for XIV
  state = update_tri_layer_state(state, _XIVLOWER, _RAISE, _XIVADJUST);

  // update the status LEDs according to the top active layer in the new state
  planck_ez_left_led_off();
  planck_ez_right_led_off();
  switch (get_highest_layer(state)) {
    case _LOWER:
    case _XIVLOWER:
      planck_ez_left_led_on();
      break;
    case _RAISE:
    // case _XIVRAISE:
      planck_ez_right_led_on();
      break;
    case _ADJUST:
    case _XIVADJUST:
      planck_ez_left_led_on();
      planck_ez_right_led_on();
      break;
  }

  return state;
}
