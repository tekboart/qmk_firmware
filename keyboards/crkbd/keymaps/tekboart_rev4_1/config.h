#pragma once

// Define the #layers in your keymap.c file.
// #define DYNAMIC_KEYMAP_LAYER_COUNT 11

// --- Home Row Mods (HRMs) Configurations --- 
// ME + Internet
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
/** #define PERMISSIVE_HOLD  // Bad for Legato typing style */
/** #define SPECULATIVE_HOLD  // Bad for accidental modifier activation */

// https://sunaku.github.io/home-row-mods.html
// https://github.com/manna-harbour/qmk_firmware/pull/56
/* QMK */
#define TAPPING_TERM 200
// IGNORE_MOD_TAP_INTERRUPT is now the default behavior, hence uncommenting this.
// #define IGNORE_MOD_TAP_INTERRUPT [> for rolling on mod-tap keys <]

/* Miryoku */
#define BILATERAL_COMBINATIONS
#define BILATERAL_COMBINATIONS_LIMIT_CHORD_TO_N_KEYS 4 /* GUI, Alt, Ctrl, Shift */
#define BILATERAL_COMBINATIONS_DELAY_MODS_THAT_MATCH MOD_MASK_GUI
#define BILATERAL_COMBINATIONS_DELAY_MATCHED_MODS_BY 120  /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_CROSSOVER_AFTER 80   /* ms */
#define BILATERAL_COMBINATIONS_ALLOW_SAMESIDED_AFTER 3000 /* ms, (sunsaku's default is 3000) */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_TIMEOUT 160  /* ms */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_MODMASK (~MOD_MASK_SHIFT)

// --- RGB Effects ---
#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

// Sync Layer State, so both halves know which layer is active.
#define SPLIT_LAYER_STATE_ENABLE
// Sync Host LED State (Caps Lock, Num Lock, etc.).
#define SPLIT_LED_STATE_ENABLE
// Mirror master matrix events to the slave.
// Useful for features that react to key events, including cosmetic RGB.
// #define SPLIT_TRANSPORT_MIRROR

// -- CAPS WORD CONFIGURATION ---
// https://docs.qmk.fm/features/caps-word
#define CAPS_WORD_INVERT_ON_SHIFT  // Shift does not break CapsWord
#define CAPS_WORD_IDLE_TIMEOUT 0  // default: 5 seconds. 0 disables timeout and caps word will stay active until you press a non-breaking key.
// Activation methods:
// Activate by pressing Left Shift + Right Shift
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Activate by double tapping Left Shift
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

