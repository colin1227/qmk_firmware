#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _NUMBERS 2
#define _ARROW 3

#define _ADJUST 16



enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define LOWER  MO(_LOWER) 
#define RAISE  MO(_NUMBERS)
#define ARROW  MO(_ARROW)
#define NUMBERS MO(_NUMBERS)
#define ADJUST MO(_ADJUST)

// full
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(\
  LT(TG(NUMBERS), KC_ESC),       KC_Q,         KC_W,           KC_E,           KC_R,               KC_T,               KC_Y,               KC_U,         KC_I,         KC_O,                    KC_P,         KC_BSPC,    \
  KC_TAB,            KC_A,      KC_S,      KC_D,          KC_F,            KC_G,                    KC_H,                    KC_J,      KC_K,      KC_L,               KC_SCLN,           KC_QUOT,       \
  KC_LSFT,      KC_Z,         KC_X,           KC_C,           KC_V,               KC_B,               KC_N,               KC_M,         KC_COMM,      KC_DOT,       RSFT_T(KC_SLSH),           KC_ENT,   \
  KC_CAPS,      KC_LCTL,      KC_LALT,        KC_LGUI,        LT(TG(LOWER),KC_MINS),   LT(TG(ARROW), KC_SPC),        LT(TG(NUMBERS), KC_SPC),  KC_LEFT,        KC_DOWN,      KC_UP,      KC_RIGHT,          KC_EQUAL    \
),


// blue
[_LOWER] = LAYOUT( \
  KC_TILD,      KC_EXLM,      KC_AT,        KC_HASH,        KC_DLR,       KC_PERC,     KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      KC_DEL,\
  _______,      G(KC_GRV),    _______,      C(S(KC_TAB)),   C(KC_TAB),    _______,     _______,      KC_UNDS,      KC_PLUS,      KC_LCBR,      KC_RCBR,      KC_PIPE,\
  _______,      KC_GRV,       KC_TILD,      C(KC_LEFT),     C(KC_RGHT),   _______,     _______,      KC_QUOT,      KC_DQUO,      KC_PIPE,      KC_BSLS,      _______,\
  _______,     _______,       _______,        _______,      DF(QWERTY),      DF(QWERTY),     DF(QWERTY),      DF(QWERTY),      _______,      KC_VOLD,      KC_VOLU,      KC_MNXT \
),

// red
[_NUMBERS] = LAYOUT( \
  KC_GRV,       KC_1,         KC_2,           KC_3,         KC_4,         KC_5,         KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_DEL,      \
  _______,      _______,      _______,        _______,      _______,      _______,      _______,      KC_MINS,      KC_EQL,       KC_LBRC,      KC_RBRC,      KC_BSLS,      \
  _______,      _______,      _______,        _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      G(KC_SLSH),\
  _______,      _______,      _______,        _______,      DF(QWERTY),      DF(QWERTY),      DF(QWERTY),      DF(QWERTY),      _______,      KC_VOLD,      KC_VOLU,      KC_MNXT \
),

// not listed
[_ARROW] =  LAYOUT( \
  _______,      G(KC_Z),      G(KC_X),      G(KC_C),        G(KC_V),      A(G(KC_BSLS)),A(G(KC_BSLS)),G(KC_V),      G(KC_C),      G(KC_V),      G(KC_Z),      _______, \
  _______,      KC_LEFT,      KC_DOWN,      KC_UP,          KC_RGHT,      _______,      _______,      KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,      _______, \
  _______,      G(KC_Z),      G(KC_X),      G(KC_C),        G(KC_V),      A(G(KC_BSLS)),A(G(KC_BSLS)),G(KC_V),      G(KC_C),      G(KC_V),      G(KC_Z),      _______, \
  _______,     _______,      _______,      _______,        DF(QWERTY),      DF(QWERTY),     DF(QWERTY),      DF(QWERTY),      _______,      _______,      _______,      _______ \
),

// not listed
[_ADJUST] =  LAYOUT( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______ \
)


};



bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ESC):
            return false;
        case RAISE:
            return false;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _NUMBERS, _ADJUST);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_D):
            return 150;
        case RSFT_T(KC_K):
            return 150;
        case LGUI_T(KC_F):
            return 150;
        case LGUI_T(KC_J):
            return 150;
        default:
            return TAPPING_TERM;
    }
}
