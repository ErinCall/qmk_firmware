#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define CONT 1 // control layer
#define QWER 2 // qwerty layer

static uint8_t   red_brightness = 0xff;
static uint8_t green_brightness = 0x44;
static uint8_t  blue_brightness = 0xff;
static void set_brightnesses(void);

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // ensure these codes start after the highest keycode defined in Quantum
  COLON_EQ,
  BANG_EQ,
  LITE_ON,
  LITE_OFF,
  RED_UP,
  GRN_UP,
  BLU_UP,
  RED_DOWN,
  GRN_DOWN,
  BLU_DOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |  '"  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |   /  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  :=  |   A  |   O  |   E  |   U  |   I  |                    |   D  |   H  |   T  |   N  |   S  |   -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   ;  |   Q  |   J  |   K  |   X  |                    |   B  |   M  |   W  |   V  |   Z  |RShift|
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * | Home |   `  |   =  | Left | Right|                                  |  Up  | Down |   [  |   ]  | End  |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      | LCtl | LAlt |  | RCtl | Ralt |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |  L1  |  |  L1  |      |      |
 *                               | Back |Delete|------|  |------|Enter |Space |
 *                               |Space |      | LGui |  | RGui |      |      |
 *                               `--------------------'  `--------------------'
 */
[BASE] = LAYOUT_dactyl(  // layer 0 : default
        // left hand
    KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,
    KC_TAB,  KC_QUOT,  KC_COMM,   KC_DOT,     KC_P,      KC_Y,
  COLON_EQ,     KC_A,     KC_O,     KC_E,     KC_U,      KC_I,
   KC_LSFT,  KC_SCLN,     KC_Q,     KC_J,     KC_K,      KC_X,
   KC_HOME,   KC_GRV,   KC_EQL,  KC_LEFT,  KC_RGHT,
                                                    KC_LCTRL,   KC_LALT,
                                                               MO(CONT),
                                          KC_BSPC,    KC_DEL,   KC_LGUI,
        // right hand
                      KC_F6,    KC_F7,     KC_F8,    KC_F9,   KC_F10,  KC_BSLS,
                       KC_F,     KC_G,      KC_C,     KC_R,     KC_L,  KC_SLSH,
                       KC_D,     KC_H,      KC_T,     KC_N,     KC_S,  KC_MINS,
                       KC_B,     KC_M,      KC_W,     KC_V,     KC_Z,  KC_RSFT,
                                 KC_UP,  KC_DOWN,  KC_LBRC,  KC_RBRC,   KC_END,
          KC_RALT,  KC_RCTL,
         MO(CONT),
          KC_RGUI,   KC_ENT,  KC_SPACE
    ),
/* Keymap 1: Control layer (media keys, Fkeys, numpad)
 *
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 | RESET|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | Mute | VolD | VolU |      |                    |      |   7  |   8  |   9  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  !=  |      | Prev |PPause| Next |      |                    |      |   4  |   5  |   6  |   =  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |   1  |   2  |   3  |   ,  |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |PageUp|      |      |      |      |                                  |   0  |   0  |   .  |   :  |PageDn|
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 */
// Control layer
[CONT] = LAYOUT_dactyl(
       // left hand
       KC_TRNS, LITE_OFF, RED_DOWN, GRN_DOWN, BLU_DOWN,    KC_F5,
       KC_TRNS,  KC_TRNS,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,
       BANG_EQ,  KC_TRNS,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_PGUP, TG(QWER),  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
       // right hand
                KC_F6,     RED_UP,  GRN_UP,  BLU_UP,     LITE_ON,    RESET,
                KC_TRNS,     KC_7,    KC_8,    KC_9,  KC_KP_PLUS,  KC_TRNS,
                KC_TRNS,     KC_4,    KC_5,    KC_6,      KC_EQL,  KC_TRNS,
                KC_TRNS,     KC_1,    KC_2,    KC_3,     KC_COMM,  KC_TRNS,
                             KC_0,    KC_0,  KC_DOT,    KC_COLON,  KC_PGDN,
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
      KC_TRNS,  KC_TRNS,  KC_TRNS
),
/* Keymap 2: QWERTY overlay
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |   [  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   ]  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '"  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  |      |
 * |------+------+------+------+------+------'                    `------+------+------+------+------+------|
 * |      |      |      |      |      |                                  |      |      |   -  |   \  |      |
 * `----------------------------------'                                  `----------------------------------'
 *                                      ,-------------.  ,-------------.
 *                                      |      |      |  |      |      |
 *                               ,------|------|------|  |------+------+------.
 *                               |      |      |      |  |      |      |      |
 *                               |      |      |------|  |------|      |      |
 *                               |      |      |      |  |      |      |      |
 *                               `--------------------'  `--------------------'
 *
 */
// QWERTY
[QWER] = LAYOUT_dactyl(
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
       KC_TRNS,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,
       KC_TRNS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
       KC_TRNS,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,
       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                         KC_TRNS,  KC_TRNS,
                                                                   KC_TRNS,
                                               KC_TRNS,  KC_TRNS,  KC_TRNS,
    // right hand
                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LBRC,
                   KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_RBRC,
                   KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
                   KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_TRNS,
                          KC_TRNS,  KC_TRNS,  KC_MINS,  KC_BSLS,  KC_TRNS,
      KC_TRNS,  KC_TRNS,
      KC_TRNS,
      KC_TRNS,  KC_TRNS,  KC_TRNS
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case COLON_EQ:
        SEND_STRING(":=");
        return false;
        break;
      case BANG_EQ:
        SEND_STRING("!=");
        return false;
        break;
      case LITE_ON:
        set_brightnesses();
        return false;
        break;
      case LITE_OFF:
        OCR1A = 0x00;
        OCR1B = 0x00;
        OCR1C = 0x00;
        return false;
        break;
      case RED_UP:
        red_brightness += 0x11;
        set_brightnesses();
        return false;
        break;
      case GRN_UP:
        green_brightness += 0x11;
        set_brightnesses();
        return false;
        break;
      case BLU_UP:
        blue_brightness += 0x11;
        set_brightnesses();
        return false;
        break;
      case RED_DOWN:
        red_brightness -= 0x11;
        set_brightnesses();
        return false;
        break;
      case GRN_DOWN:
        green_brightness -= 0x11;
        set_brightnesses();
        return false;
        break;
      case BLU_DOWN:
        blue_brightness -= 0x11;
        set_brightnesses();
        return false;
        break;
    }
  }

  return true;
}

static void set_brightnesses(void) {
  OCR1A = red_brightness;
  OCR1B = green_brightness;
  OCR1C = blue_brightness;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  DDRB |= (1 << 5 | 1 << 6 | 1 << 7);

  TCCR1A |= (1 << COM1A0) | (1 << COM1A1) | // PWM on B5; "on" = LO
            (1 << COM1B0) | (1 << COM1B1) | // PWM on B6; "on" = LO
            (1 << COM1C0) | (1 << COM1C1) | // PWM on B7; "on" = LO
            (1 << WGM10);                   // 8-bit PWM

  TCCR1B |= (1 << WGM12) | (1 << CS10);     // Fast PWM, no prescaling

  // Backlight on
  OCR1A = red_brightness;
  OCR1B = green_brightness;
  OCR1C = blue_brightness;
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {};
