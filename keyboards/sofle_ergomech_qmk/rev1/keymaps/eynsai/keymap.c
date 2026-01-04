#include QMK_KEYBOARD_H
#include "eynsai_statemachine.h"

const key_override_t key_override_9 = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_PIPE);
const key_override_t key_override_0 = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_BSLS);

const key_override_t *key_overrides[] = {
	&key_override_9,
    &key_override_0,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_WORK] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                                           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_D,           KC_R,           KC_W,           KC_B,                                           KC_J,           KC_F,           KC_U,           KC_P,           KC_SCLN,        KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_H,           KC_T,           KC_G,                                           KC_Y,           KC_N,           KC_E,           KC_O,           KC_I,           KC_QUOT,
    KC_SSFT,        KC_Z,           KC_X,           KC_M,           KC_C,           KC_V,                                           KC_K,           KC_L,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                    KC_NO,          KC_DOWN,        KC_UP,          KC_SALT,        KC_SPC,         KC_SCTL,        KC_BASE,        MO(LAYER_SYMB), KC_SGUI,        KC_LEFT,        KC_RIGHT,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_QWER] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                                           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    KC_TRNS,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_TRNS,
                    KC_NO,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_GAME] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                                           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_ENT,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_TAB,
    KC_BSPC,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                    KC_NO,          KC_ESC,         KC_LALT,        KC_SPC,         KC_LCTL,        KC_TAB,         KC_TRNS,        KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_SYMB] = LAYOUT(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_LCBR,        KC_RCBR,        KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_TILD,        KC_GRV,         KC_LPRN,        KC_RPRN,        KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_TRNS,        KC_NO,          KC_NO,          KC_LBRC,        KC_RBRC,        KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRNS,
                    KC_NO,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_UTIL] = LAYOUT(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_ENT,         KC_NO,          KC_ESC,         KC_DEL,         KC_BWIG,        KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_BSPC,        KC_PSCR,        G(KC_LEFT),     KC_RGUI,        G(KC_RIGHT),    KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_TRNS,        KC_NO,          KC_NO  ,        A(KC_F10),      KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRNS,
                    KC_NO,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_MOVE] = LAYOUT(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_LAZY,        KC_RCTL,        KC_NO,          KC_NO,                                          KC_NO,          KC_HOME,        KC_UP,          KC_END,         KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_VSAC,        KC_CCTL,        KC_RSFT,        KC_NO,                                          KC_NO,          KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_NO,          KC_NO,
    KC_TRNS,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_DLN,         KC_NO,          KC_NO,          KC_TRNS,
                    KC_NO,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
[LAYER_FUNC] = LAYOUT(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,                                          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
    KC_F13,         KC_F14,         KC_F15,         KC_F16,         KC_F17,         KC_F18,                                         KC_F19,         KC_F20,         KC_F21,         KC_F22,         KC_F23,         KC_F24,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_TRNS,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRNS,
                    KC_NO,          QK_BOOT,        KC_RSTO,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_NO,          KC_NO,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
};
// clang-format on
