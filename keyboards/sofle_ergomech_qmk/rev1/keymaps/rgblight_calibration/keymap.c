#include QMK_KEYBOARD_H
#include "quantum.h"
#include "rgblight.h"
#include "printf.h"
#include "math.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
    KC_6,           KC_5,           KC_4,           KC_3,           KC_2,           KC_1,                                           KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,
    KC_EQL,         KC_MINS,        KC_0,           KC_9,           KC_8,           KC_7,                                           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,        KC_EQL,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,        QK_BOOT,        KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                                                                                                    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO
),
};

// clang-format on

static float hue_f = 0.0f;  // Range: [0.0, 360.0)
static float sat_f = 1.0f;  // Range: [0.0, 1.0]
static float val_f = 1.0f;  // Range: [0.0, 1.0]
static float r_f = 1.0f;    // Range: [0.0, 1.0]
static float g_f = 1.0f;
static float b_f = 1.0f;

#define RGB_STEP (1.0f / 255.0f)
#define HUE_STEP (360.0f / 255.0f)

// HSV → RGB (float input/output)
void hsv_to_rgb_float(float h, float s, float v, float *r, float *g, float *b) {
    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2) - 1.0f));
    float m = v - c;

    float r1, g1, b1;
    if (h < 60) {
        r1 = c; g1 = x; b1 = 0;
    } else if (h < 120) {
        r1 = x; g1 = c; b1 = 0;
    } else if (h < 180) {
        r1 = 0; g1 = c; b1 = x;
    } else if (h < 240) {
        r1 = 0; g1 = x; b1 = c;
    } else if (h < 300) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    *r = r1 + m;
    *g = g1 + m;
    *b = b1 + m;
}

// RGB → HSV (float input/output)
void rgb_to_hsv_float(float r, float g, float b, float *h, float *s, float *v) {
    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float delta = max - min;

    *v = max;
    *s = (max == 0) ? 0 : (delta / max);

    if (delta == 0) {
        *h = 0;
    } else if (max == r) {
        *h = 60.0f * fmodf(((g - b) / delta), 6.0f);
    } else if (max == g) {
        *h = 60.0f * (((b - r) / delta) + 2.0f);
    } else {
        *h = 60.0f * (((r - g) / delta) + 4.0f);
    }

    if (*h < 0) *h += 360.0f;
}

// Synchronize RGB from current HSV state
void sync_rgb_from_hsv(void) {
    hsv_to_rgb_float(hue_f, sat_f, val_f, &r_f, &g_f, &b_f);
}

// Synchronize HSV from current RGB state
void sync_hsv_from_rgb(void) {
    rgb_to_hsv_float(r_f, g_f, b_f, &hue_f, &sat_f, &val_f);
}

void update_color(void) {
    // Clamp values
    if (hue_f >= 360.0f) hue_f -= 360.0f;
    if (hue_f < 0.0f) hue_f += 360.0f;
    if (sat_f > 1.0f) sat_f = 1.0f;
    if (sat_f < 0.0f) sat_f = 0.0f;
    if (val_f > 1.0f) val_f = 1.0f;
    if (val_f < 0.0f) val_f = 0.0f;

    if (r_f > 1.0f) r_f = 1.0f;
    if (g_f > 1.0f) g_f = 1.0f;
    if (b_f > 1.0f) b_f = 1.0f;
    if (r_f < 0.0f) r_f = 0.0f;
    if (g_f < 0.0f) g_f = 0.0f;
    if (b_f < 0.0f) b_f = 0.0f;

    // Set RGB
    rgblight_setrgb_range(
        (uint8_t)(r_f * 255.0f),
        (uint8_t)(g_f * 255.0f),
        (uint8_t)(b_f * 255.0f),
        36, 72
    );

    uprintf("RGB: R=%d G=%d B=%d | HSV: H=%d S=%d V=%d\n",
        (uint8_t)(r_f * 255.0f),
        (uint8_t)(g_f * 255.0f),
        (uint8_t)(b_f * 255.0f),
        (uint8_t)((hue_f / 360.0f) * 255.0f),
        (uint8_t)(sat_f * 255.0f),
        (uint8_t)(val_f * 255.0f)
    );
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return false;

    switch (keycode) {
        // RGB controls (R± G± B±)
        case KC_1: r_f += RGB_STEP; sync_hsv_from_rgb(); break;
        case KC_2: r_f -= RGB_STEP; sync_hsv_from_rgb(); break;
        case KC_3: g_f += RGB_STEP; sync_hsv_from_rgb(); break;
        case KC_4: g_f -= RGB_STEP; sync_hsv_from_rgb(); break;
        case KC_5: b_f += RGB_STEP; sync_hsv_from_rgb(); break;
        case KC_6: b_f -= RGB_STEP; sync_hsv_from_rgb(); break;

        // HSV controls (H± S± V±)
        case KC_7: hue_f += HUE_STEP; sync_rgb_from_hsv(); break;
        case KC_8: hue_f -= HUE_STEP; sync_rgb_from_hsv(); break;
        case KC_9: sat_f += RGB_STEP; sync_rgb_from_hsv(); break;
        case KC_0: sat_f -= RGB_STEP; sync_rgb_from_hsv(); break;
        case KC_EQUAL: val_f += RGB_STEP; sync_rgb_from_hsv(); break;
        case KC_MINUS: val_f -= RGB_STEP; sync_rgb_from_hsv(); break;
    }

    update_color();
    return false;
}
