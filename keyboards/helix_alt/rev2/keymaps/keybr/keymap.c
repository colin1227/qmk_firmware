#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ARROW 5
#define _ADJUST 16

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ARROW  MO(_ARROW)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(\
  KC_GRV,       KC_1,         KC_2,           KC_3,         KC_4,         KC_5,                                     KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_DEL, \
  KC_ESC,       KC_Q,         KC_W,           KC_E,         KC_R,         KC_T,                                     KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSPC,    \
  KC_TAB,       LCTL_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D),     LGUI_T(KC_F),       KC_G,               KC_H,               LGUI_T(KC_J), RSFT_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN),KC_QUOT,  \
  KC_LSFT,      KC_Z,         KC_X,           KC_C,         KC_V,         KC_B,         KC_LBRC,      KC_RBRC,      KC_N,         KC_M,         KC_COMM,      KC_DOT,       RSFT_T(KC_SLSH),KC_ENT,   \
  KC_MPLY,      KC_LCTL,      KC_LALT,        KC_LGUI,      LOWER,        LT(ARROW, KC_SPC),       KC_TAB,       KC_ENT,       LT(ARROW, KC_SPC),       RAISE,        KC_LEFT,      KC_PGDN,      KC_PGUP,          KC_RGHT    \
),
[_LOWER] = LAYOUT( \
  _______,      _______,      _______,        _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      _______, \
  KC_TILD,      KC_EXLM,      KC_AT,        KC_HASH,        KC_DLR,       KC_PERC,                                  KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      KC_BSPC,\
  _______,      G(KC_GRV),    _______,        C(S(KC_TAB)), C(KC_TAB),    _______,                                  _______,      KC_UNDS,      KC_PLUS,      KC_LCBR,      KC_RCBR,      KC_PIPE,\
  _______,      KC_GRV,       KC_TILD,      C(KC_LEFT),     C(KC_RGHT),   _______,      _______,      _______,      _______,      KC_QUOT,      KC_DQUO,      KC_PIPE,      KC_BSLS,      _______,\
  BL_INC,       BL_DEC,       BL_TOGG,        _______,      _______,      KC_MPLY,      _______,      _______,      KC_BSPC,      _______,      _______,      KC_VOLD,      KC_VOLU,      KC_MNXT \
),
[_RAISE] = LAYOUT( \
  _______,      _______,      _______,        _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      _______, \
  KC_GRV,       KC_1,         KC_2,         KC_3,           KC_4,         KC_5,                                     KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_DEL,      \
  _______,      _______,      _______,        _______,      _______,      _______,                                  _______,      KC_MINS,      KC_EQL,       KC_LBRC,      KC_RBRC,      KC_BSLS,      \
  G(KC_Z),      G(KC_X),      G(KC_C),        A(G(KC_BSLS)),_______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      G(KC_SLSH),\
  _______,      _______,      _______,        _______,      _______,      KC_BSPC,      _______,      _______,      KC_MPLY,      _______,      _______,      KC_VOLD,      KC_VOLU,      KC_MNXT \
),
// unused in this layout.  suggested to use LT(ARROW, KC_SPC) on space keys to get arrow / clipboard layer
[_ARROW] =  LAYOUT( \
  _______,      _______,      _______,        _______,      _______,      _______,                                  _______,      _______,      _______,      _______,      _______,      _______, \
  _______,      G(KC_Z),      G(KC_X),      G(KC_C),        G(KC_V),      A(G(KC_BSLS)),                            A(G(KC_BSLS)),G(KC_V),      G(KC_C),      G(KC_V),      G(KC_Z),      _______, \
  _______,      KC_LEFT,      KC_DOWN,      KC_UP,          KC_RGHT,      _______,                                  _______,      KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,      _______, \
  _______,      G(KC_Z),      G(KC_X),      G(KC_C),        G(KC_V),      A(G(KC_BSLS)),_______,      _______,      A(G(KC_BSLS)),G(KC_V),      G(KC_C),      G(KC_V),      G(KC_Z),      _______, \
  _______,      _______,      _______,        _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______,      _______ \
),
[_ADJUST] =  LAYOUT( \
_______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

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

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
