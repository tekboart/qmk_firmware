#pragma once

// ########################################################################
// Tap-Hold Configs
// ########################################################################

// ------------------------------------------------------------------------
// Set tapping TERMs
// ------------------------------------------------------------------------
// Sunsaku's suggested TAPPING_TERM, based on difficulty:
// LEVEL 0 => sunaku (150ms)
// LEVEL 1 => novice (500ms)
// LEVEL 2 => slower (400ms)
// LEVEL 3 => normal (300ms)
// LEVEL 4 => faster (200ms)
// LEVEL 5 => expert (100ms)

#define TAPPING_TERM   150                   // The duration, after which, a key is considered held. Default: 200 (ms)
#define QUICK_TAP_TERM (TAPPING_TERM + 150)  // Time after a tap, during which holding the same key results in auto-repeat. Default: = TAPPING_TERM
#define FLOW_TAP_TERM  (TAPPING_TERM - 50)   // Disables holds when typing quickly.
/** #define PERMISSIVE_HOLD                  // (~ZMK's balanced) Triggers hold if you tap another key while holding it. Bad for Legato typing style, but CHORDAL_HOLD can reduce its impact. */
/** #define HOLD_ON_OTHER_KEY                // (~ZMK's hold-preferred) Compared to the "permissive hold" mode, this mode selects the hold action in more cases. */
/** #define SPECULATIVE_HOLD                 // Bad for accidental modifier activation */
#define CHORDAL_HOLD                         // Constrains holds to opposite-hand combinations. It's intended to be used with either PERMISSIVE_HOLD or HOLD_ON_OTHER_KEY.
#define IGNORE_MOD_TAP_INTERRUPT             // For rolling on mod-tap keys. It's now the default behavior, hence uncommenting this.
#define TAPPING_TERM_PER_KEY                 // Allow different tapping terms for different keys, using get_tapping_term in keymap.c
#define PERMISSIVE_HOLD_PER_KEY              // Allow different permissive hold behavior for different keys, using get_permissive_hold in keymap.c
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY      // Allow different hold-on-other-key behavior for different keys, using get_hold_on_other_key_press in keymap.c

// Custom Tapping Terms
#define HRM_TAPPING_TERM  (TAPPING_TERM)  // Home Row Mods (HRM) keys tapping TERM

// --- Bilateral Combinations Configurations ---
// https://sunaku.github.io/home-row-mods.html
// https://github.com/manna-harbour/qmk_firmware/pull/56
// IGNORE_MOD_TAP_INTERRUPT is now the default behavior, hence commenting this.
// #define IGNORE_MOD_TAP_INTERRUPT [> for rolling on mod-tap keys <]

/* Miryoku */
#define BILATERAL_COMBINATIONS
#define BILATERAL_COMBINATIONS_LIMIT_CHORD_TO_N_KEYS 4 /* GUI, Alt, Ctrl, Shift */
#define BILATERAL_COMBINATIONS_DELAY_MODS_THAT_MATCH MOD_MASK_GUI
#define BILATERAL_COMBINATIONS_DELAY_MATCHED_MODS_BY 120  /* sunsaku's default: 120 */
#define BILATERAL_COMBINATIONS_ALLOW_CROSSOVER_AFTER 80   /* sunsaku's default: 80 */
#define BILATERAL_COMBINATIONS_ALLOW_SAMESIDED_AFTER 3000 /* sunsaku's default: 3000 */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_TIMEOUT 160  /* sunsaku's default: 160 */
#define BILATERAL_COMBINATIONS_TYPING_STREAK_MODMASK (~MOD_MASK_SHIFT)

// --- Split Keyboard Configurations ---
// Sync Layer State, so both halves know which layer is active.
#define SPLIT_LAYER_STATE_ENABLE
// Sync Host LED State (Caps Lock, Num Lock, etc.).
#define SPLIT_LED_STATE_ENABLE
// Mirror master matrix events to the slave.
// Useful for features that react to key events, including cosmetic RGB.
#define SPLIT_TRANSPORT_MIRROR
// This enables transmitting modifier state to the slave half.
#define SPLIT_MODS_ENABLE
// This enables transmitting the keyboard's OS to the slave half, so that the slave can use the correct OS-specific keycodes.
#define SPLIT_TRANSACTION_IDS_USER OS_SYNC

// -- CAPS WORD CONFIGURATION ---
// https://docs.qmk.fm/features/caps-word
// #define CAPS_WORD_INVERT_ON_SHIFT  // Shift does not break CapsWord
#define CAPS_WORD_IDLE_TIMEOUT 0  // default: 5 seconds. 0 disables timeout and caps word will stay active until you press a non-breaking key.
// Activation methods:
// [1] Activate by pressing Left Shift + Right Shift
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// [2] Activate by double tapping Left Shift
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// --- Auto OS Detection Configs ---
// The below settings can help when switching devices on some KVMs
#define OS_DETECTION_DEBOUNCE 250  // default: 250 (ms)
#define OS_DETECTION_KEYBOARD_RESET
#define OS_DETECTION_SINGLE_REPORT

// --- Mouse Configs ---
// Cursor
#define MOUSEKEY_DELAY               0   // Delay between key press and movement start. Default: 10 ms
#define MOUSEKEY_INTERVAL           16   // Time between cursor movements (ms), lower is faster. Default: 20 ms, use 16 ms for 60 Hz refresh rate (1/60 = 16.666 ms)
#define MOUSEKEY_MOVE_DELTA         16   // Step size. Default: 8
#define MOUSEKEY_MAX_SPEED           5   // Maximum speed. Default: 10. If you lower MOUSEKEY_INTERVAL, you'd better lower this too.
#define MOUSEKEY_TIME_TO_MAX        60   // Time until max speed is reached (ms). Default: 30 ms
// Wheel
#define MOUSEKEY_WHEEL_DELAY         0   // Delay between key press and wheel movment. Default: 10 ms
#define MOUSEKEY_WHEEL_INTERVAL     40   // Time between wheel movements (ms), lower is faster. Default: 80 ms
#define MOUSEKEY_WHEEL_DELTA         1   // Step size. Default: 1
#define MOUSEKEY_WHEEL_MAX_SPEED     8   // Maximum speed. Default: 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX  40   // Time until max speed is reached (ms). Default: 40 ms
