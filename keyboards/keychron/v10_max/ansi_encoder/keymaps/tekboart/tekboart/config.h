#pragma once

// Define the #layers in your keymap.c file.
// V10 Max supports up to 11 layers.
#define DYNAMIC_KEYMAP_LAYER_COUNT 11

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
