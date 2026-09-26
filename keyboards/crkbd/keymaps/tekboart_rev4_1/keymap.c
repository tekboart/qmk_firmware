/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "os_detection.h"  // Detect OS Mode automatically

enum layers {
    // TODO: BASE layers (e.g., Split, Typing, Standard, Gaming) must always be the lowest numbered layers.
    // I put a layer in betwwen so that MAC toggle selects Split Base layer and WIN toggle selects Standard Base layer.
    // Base Layers
    _QWERTY_3R,  // Split Layer (Base)
    /** _BASE_STD,  // Standard QWERTY Layer (Base): Disable all HRMs & Split Layout. Useful for keyboards with more than 3 rows. */
    // Overlay Layers (on top of Base Layers)
    _TYPING,    // Typing Layer (Base): Disable all HRMs.
    _GAMING,   // Gaming Layer
    _SYMBOL,   // Symbols Layer (Split Layout)
    _NAVIGATE, // Navigation Layer (Split Layout)
    _CURSOR,   // Cursor Layer (Split Layout)
    _MOUSE,    // Mouse Layer (Split Layout)
    _NUMBER,   // Number/Numpad Layer (Split Layout)
    // Shared Layers (accessed from Base and Overlay Layers)
    // NOTE: _FUNCTION and MAGIC must be placed as the last layers.
    // Refer to QMK's layer doc beginners guide: https://docs.qmk.fm/feature_layers#beginners 
    _FUNCTION,    // Function Layer (Split Layout). Hint: It's a combination of Function, Magic and Lower Layers in MoErgo
    _MAGIC,       // Magic Layer (Split Layout). Hint: It mimics MoErgo's Magic Layer
};

// ###############################################################
// Helper Functions
// ###############################################################

// ---------------------------------------------------------------
// Detect OS Mode (Windows or MacOS) based on CG_TOGG
// ---------------------------------------------------------------
// CG_TOGG / keymap_config.swap_lctl_lgui is being used as the MAC/WIN mode indicator.
static bool is_windows_mode(void) {
    // return true: Windows, return false: MacOS
    return !keymap_config.swap_lctl_lgui;
}

// detect the host OS and turn on/off CG_TOGG (swap_lctl_lgui) accordingly
void detect_host_os_and_set_cg_togg(void) {
    // Options: OS_UNSURE OS_LINUX OS_WINDOWS OS_MACOS OS_IOS
    // FIXME: Test if it works
    os_variant_t OPERATING_SYSTEM = detected_host_os();

    if (OPERATING_SYSTEM == OS_MACOS || OPERATING_SYSTEM == OS_IOS) {
        keymap_config.swap_lctl_lgui = true;
        eeconfig_update_keymap(&keymap_config);
    } else if (OPERATING_SYSTEM == OS_WINDOWS || OPERATING_SYSTEM == OS_LINUX) {
        keymap_config.swap_lctl_lgui = false;
        eeconfig_update_keymap(&keymap_config);
    } else if (OPERATING_SYSTEM == OS_UNSURE) {
        // OS detection failed, determine the OS
        if (is_windows_mode()) {
            OPERATING_SYSTEM = OS_WINDOWS;
        } else {
            OPERATING_SYSTEM = OS_MACOS;
        }
    } else {
        // OS detection failed, default to Windows
        keymap_config.swap_lctl_lgui = false;
        eeconfig_update_keymap(&keymap_config);
    }
}
// turn on NUMLOCK by default
void numlock_on(void) {
    if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM_LOCK);
    }
}

// global variables for the numlock_on func
static bool numlock_pending = false;
static uint16_t numlock_timer = 0;
#define NUMLOCK_STARTUP_DELAY 1000

/** This function runs "exactly" once when the keyboard is powered on or reset. */
void keyboard_post_init_user(void) {
    detect_host_os_and_set_cg_togg();

    // Wait until the host connection is established before
    // attempting to enable Num Lock.
    numlock_pending = true;
    numlock_timer = timer_read();
}

// ---------------------------------------------------------------
// Define Aliases
// ---------------------------------------------------------------
// ------- Define Aliases: Layers  -------
// (Base) QWERTY 3-Row Layout
#define TT_BASE TT(_QWERTY_3R)
#define TG_BASE TG(_QWERTY_3R)
#define DF_BASE DF(_QWERTY_3R)
// (Base) QWERTY 6-Row Layout
/** #define LT_STD  LT(_BASE_STD, KC_4) */
/** #define TT_STD  TT(_BASE_STD) */
/** #define TG_STD  TG(_BASE_STD) */
/** #define DF_STD  DF(_BASE_STD) */
// Typing Layer
#define TT_TYP TT(_TYPING)
#define TG_TYP TG(_TYPING)
// Magic Layer
#define MO_MGC   MO(_MAGIC)
#define TT_MGC   TT(_MAGIC)
#define TG_MGC   TG(_MAGIC)
// Gaming Layer
#define LT_GAME  LT(_GAMING, KC_1)
#define TT_GAME  TT(_GAMING)
#define TG_GAME  TG(_GAMING)
// -- Thumb Layers --
// Cursor Layer
#define LT_CSR   LT(_CURSOR, KC_ESC)
#define MO_CSR   MO(_CURSOR)
#define TT_CSR   TT(_CURSOR)
#define TG_CSR   TG(_CURSOR)
// Number Layer
#define LT_NUM  LT(_NUMBER, KC_TAB)
#define TT_NUM  TT(_NUMBER)
#define TG_NUM  TG(_NUMBER)
// Navigation Layer
#define LT_NAV   LT(_NAVIGATE, KC_SPC)
#define MO_NAV   MO(_NAVIGATE)
#define TT_NAV   TT(_NAVIGATE)
#define TG_NAV   TG(_NAVIGATE)
// Symbol Layer
#define LT_SYM  LT(_SYMBOL, KC_ENT)
#define TT_SYM  TT(_SYMBOL)
#define TG_SYM  TG(_SYMBOL)
// Function Layer
#define LT_FN   LT(_FUNCTION, KC_ESC)
#define MO_FN   MO(_FUNCTION)
#define TT_FN   TT(_FUNCTION)
#define TG_FN   TG(_FUNCTION)
// Mouse Layer
#define LT_MSE   LT(_MOUSE, KC_INS)
#define MO_MSE   MO(_MOUSE)
#define TT_MSE   TT(_MOUSE)
#define TG_MSE   TG(_MOUSE)

// ------- Define Aliases: Mod-Tap Keys  -------
#define MT_LSFT MT(MOD_LSFT,KC_LBRC)
#define MT_RSFT MT(MOD_RSFT,KC_RBRC)
#define MT_RALT MT(MOD_RALT,KC_TAB)

// ------- Define Aliases: Sticky Keys  -------
// Sticky keys remain active until the next key is pressed.
// They are useful for one-handed typing, e.g., first letter capital.
// Sticky Mods (OSM)
#define ST_LSFT OSM(MOD_LSFT)
#define ST_RSFT OSM(MOD_RSFT)

// ------- Define Aliases: Home Row Mods (HRMs) -------
#define HRW_A    MT(MOD_LGUI, KC_A)
#define HRW_S    MT(MOD_LALT, KC_S)
#define HRW_D    MT(MOD_LCTL, KC_D)
#define HRW_F    MT(MOD_LSFT, KC_F)
#define HRW_G    MEH_T(KC_G)
#define HRW_H    MEH_T(KC_H)
#define HRW_J    MT(MOD_RSFT, KC_J)
#define HRW_K    MT(MOD_RCTL, KC_K)
#define HRW_L    MT(MOD_RALT, KC_L)
#define HRW_SCLN MT(MOD_RGUI, KC_SCLN)

// ------- Define Aliases: Symbols -------
#define SM_EXCL   S(KC_1)     // !
#define SM_ADS    S(KC_2)     // @
#define SM_HASH   S(KC_3)     // #
#define SM_DLR    S(KC_4)     // $
#define SM_PERC   S(KC_5)     // %
#define SM_CRET   S(KC_6)     // ^
#define SM_AMPS   S(KC_7)     // &
#define SM_ASTR   S(KC_8)     // *
#define SM_LPRN   S(KC_9)     // (
#define SM_RPRN   S(KC_0)     // )
#define SM_LBRC   KC_LBRC     // [
#define SM_RBRC   KC_RBRC     // ]
#define SM_LCBR   S(KC_LBRC)  // {
#define SM_RCBR   S(KC_RBRC)  // }
#define SM_TICK   KC_GRV      // `
#define SM_TILD   S(KC_GRV)   // ~
#define SM_COMM   KC_COMM     // ,
#define SM_LT     S(KC_COMM)  // <
#define SM_DOT    KC_DOT      // .
#define SM_GT     S(KC_DOT)   // >
#define SM_SLSH   KC_SLSH     // /
#define SM_QUES   S(KC_SLSH)  // ?
#define SM_BSLS   KC_BSLS     // \ Backslash
#define SM_PIPE   S(KC_BSLS)  // |
#define SM_COLN   S(KC_SCLN)  // :
#define SM_SCLN   KC_SCLN     // ;
#define SM_DQT    S(KC_QUOT)  // "
#define SM_QUOT   KC_QUOT     // '
#define SM_EQL    KC_EQL      // =
#define SM_PLUS   S(KC_EQL)   // +
#define SM_MINS   KC_MINS     // -
#define SM_UNDS   S(KC_MINS)  // _

// ---------------------------------------------------------------
// Define Aliases: OS specific actions
// ---------------------------------------------------------------

#define CUT      C(KC_X)
#define COPY     C(KC_C)
#define PASTE    C(KC_V)
#define UNDO     C(KC_Z)
#define REDO     S(C(KC_Z))
#define FIND     C(KC_F)
#define SEL_ALL  C(KC_A)

// ---------------------------------------------------------------
// Define Aliases: Community Modules
// ---------------------------------------------------------------
// ------- Getreuer's Select Word  -------
#define SEL_WRD SELECT_WORD
#define SEL_WRB SELECT_WORD_BACK
#define SEL_LNE SELECT_LINE
#define SEL_LNU SELECT_LINE_UP

// ---------------------------------------------------------------
// Define Aliases: App Shortcuts
// ---------------------------------------------------------------
#define SCUT_FFOX  MEH(KC_1)  // Open Firefox Browser
#define URL_AI_CHATBOT "https://chat.openai.com/chat"

// ---------------------------------------------------------------
// Define Custom Keycodes (e.g., Macros, OS-specific Window Management, etc.)
// ---------------------------------------------------------------
enum custom_keycodes {
    // Macros
    MC_TICK = SAFE_RANGE,

    // OS-specific window/application management
    WM_SWTCH,
    WM_CLOSE,
    WM_NEW,
    WM_TCLS,
    WM_MINIM,
    WM_MAXIM,
    WM_DESK,
    WM_SPOT,

    // File Management
    RENAME,
    DEL_NORM,
    DEL_PERM,

    // Applications
    AP_FEXP,  // Open File Explorer
    AP_TERM,  // Open Terminal
    AP_FFOX,  // Open Firefox Browser
    AP_CHRM,  // Open Google Chrome Browser
    AP_SSHT,  // Open Screenshot Tool

    // URLs/Websites
    UR_GPT,   // Open ChatGPT in a browser (e.g., Firefox)

    // Text Editing
    TX_HOME,
    TX_END,
     
    // Mod-Tap Keys: MT_<HOLD><TAP>
    MT_TEMPLATE  // Tap: <Action_A>, Hold: <Action_B>

    // Tap Dance Keys: TD_<TAP_DANCE>
    /** TD_SFT,  // Tap: OSM(MOD_LSFT), Hold: KC_LSFT, Double Tap: KC_CAPS */

};

// Getreuer's Select Word module requires a OS Detection
// https://getreuer.info/posts/keyboards/select-word/index.html#mac-hotkeys
/** bool select_word_host_is_mac(void) { */
/**   return mod_config(MOD_LGUI) == MOD_LCTL;  // GUI/Ctrl swapped => Mac. */
/** } */

/** bool select_word_host_is_mac(void) { */
/**   // return true: MacOS, return false: Windows */
/**   return !is_windows_mode(); */
/** } */

// App Switcher State
static bool app_switch_active = false;
static uint16_t app_switch_timer = 0;
// How long after the last WM_SWTCH press before the app switcher
// is considered finished. 
// NOTE: If a window is selected before this timeout, the app switcher will close immediately.
#define APP_SWITCH_TIMEOUT 800  // default: 100ms

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// NOTE: The keycodes used inside this function, using tap_code16(kc), are treated literal even with CG_TOGG enabled.
// e.g., outside this func the CG_TOGG swapps C(KC_C) to G(KC_C), and vice versa, but it's not the case inside this func.
    switch (keycode) {

        // #######################################################
        // Windows Management
        // #######################################################
        // -------------------------------------------------------
        // App Switch
        // -------------------------------------------------------
        // FIXME: It was working before, but now we have a sticky Ctl (that needs keyboard disconnect to disable)
        case WM_SWTCH:
            if (record->event.pressed) {
                // First press: start the app switcher.
                if (!app_switch_active) {

                    app_switch_active = true;

                    if (is_windows_mode()) {
                        register_code(KC_LALT);
                    } else {
                        register_code(KC_LGUI);
                    }
                }

                // Every press of WM_SWTCH sends one Tab.
                tap_code(KC_TAB);

                // Restart the timeout after every press.
                app_switch_timer = timer_read();
            }

            return false;

        // -------------------------------------------------------
        // Close Window
        // -------------------------------------------------------
        case WM_CLOSE:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(A(KC_F4));
                } else {
                    tap_code16(G(KC_Q));
                }
            }
            return false;

        // -------------------------------------------------------
        // New Windows/Tab (Windows: Ctrl + N, macOS: Command + N)
        // -------------------------------------------------------
        case WM_NEW:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(C(KC_N));
                } else {
                    tap_code16(G(KC_N));
                }
            }
            return false;

        // -------------------------------------------------------
        // Close TAB/App Window (macOS: Command + W, Windows: Ctrl + W)
        // -------------------------------------------------------
        case WM_TCLS:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(C(KC_W));
                } else {
                    tap_code16(G(KC_W));
                }
            }
            return false;

        // -------------------------------------------------------
        // Minimize Window
        // -------------------------------------------------------
        case WM_MINIM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(G(KC_DOWN));
                } else {
                    tap_code16(G(KC_M));
                }
            }
            return false;


        // -------------------------------------------------------
        // Maximize Window
        // -------------------------------------------------------
        case WM_MAXIM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(G(KC_UP));
                } else {
                    tap_code16(A(G(KC_M)));
                }
            }
            return false;


        // -------------------------------------------------------
        // Show Desktop
        // -------------------------------------------------------
        case WM_DESK:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(G(KC_D));
                } else {
                    tap_code(KC_F11);
                }
            }
            return false;

        // -------------------------------------------------------
        // Spotlight Search (macOS: Command + Space, Windows: ALT + Space)
        // -------------------------------------------------------
        case WM_SPOT:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(A(KC_SPC));
                } else {
                    tap_code16(G(KC_SPC));
                }
            }
            return false;

        // #######################################################
        // File Management
        // #######################################################
        // -------------------------------------------------------
        // Rename File/Folder (Windows: F2, macOS: Enter)
        // -------------------------------------------------------
        case RENAME:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(KC_F2);
                } else {
                    tap_code16(KC_ENT);
                }
            }
            return false;

        // -------------------------------------------------------
        // Normal Delete (Delete key on Windows, Backspace key on macOS)
        // -------------------------------------------------------
        case DEL_NORM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(KC_DEL);
                } else {
                    tap_code16(G(KC_BSPC));
                }
            }
            return false;

        // -------------------------------------------------------
        // Permanent Delete (Shift + Delete on Windows, Command + Delete on macOS)
        // -------------------------------------------------------
        case DEL_PERM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(S(KC_DEL));
                } else {
                    tap_code16(S(G(KC_BSPC)));
                }
            }
            return false;

        // #######################################################
        // Text Editing
        // #######################################################
        // -------------------------------------------------------
        // HOME (Windows: Home, macOS: Command + Left Arrow)
        // -------------------------------------------------------
        case TX_HOME:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(KC_HOME);
                } else {
                    tap_code16(G(KC_LEFT));
                }
            }
            return false;

        // -------------------------------------------------------
        // END (Windows: End, macOS: Command + Right Arrow)
        // -------------------------------------------------------
        case TX_END:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(KC_END);
                } else {
                    tap_code16(G(KC_RGHT));
                }
            }
            return false;

        // #######################################################
        // Applications
        // #######################################################

        // -------------------------------------------------------
        // File Explorer (Windows: Win + E, macOS: Command + Shift + G)
        // -------------------------------------------------------
        case AP_FEXP:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(G(KC_E));
                } else {
                    tap_code16(MEH(KC_E));
                }
            }
            return false;

        // -------------------------------------------------------
        // Terminal (Windows: Ctrl+Alt+T, MacOS: ???)
        // -------------------------------------------------------
        case AP_TERM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(C(A(KC_T)));
                } else {
                    /** tap_code16(MEH(KC_3)); */
                    tap_code16(G(A(KC_T)));
                }
            }
            return false;

        // -------------------------------------------------------
        // Firefox Browser
        // -------------------------------------------------------
        case AP_FFOX:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(SCUT_FFOX);
                } else {
                    tap_code16(SCUT_FFOX);
                }
            }
            return false;

        // -------------------------------------------------------
        // Google Chrome Browser
        // -------------------------------------------------------
        case AP_CHRM:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(MEH(KC_2));
                } else {
                    tap_code16(MEH(KC_2));
                }
            }
            return false;

        // -------------------------------------------------------
        // Screenshot Tool
        // -------------------------------------------------------
        case AP_SSHT:
            if (record->event.pressed) {
                if (is_windows_mode()) {
                    tap_code16(S(G(KC_S)));
                } else {
                    tap_code16(KC_1);
                }
            }
            return false;

        // #######################################################
        // URLs/Websites
        // #######################################################
        // ------------------------------------------------------
        // Open AI chatbot in a browser (e.g., Firefox)
        // ------------------------------------------------------
        case UR_GPT:
            if (record->event.pressed) {
                // Launch Firefox using existing Firefox shortcut.
                tap_code16(SCUT_FFOX);

                // Allow Firefox to start/focus.
                wait_ms(1200);

                // Focus address bar.
                tap_code16(C(KC_L));
                wait_ms(50);

                // Enter URL and navigate.
                SEND_STRING(URL_AI_CHATBOT);
                tap_code(KC_ENT);
            }
            return false;

        // #######################################################
        // Macros
        // #######################################################
        // -------------------------------------------------------
        // Output three backticks (```) for code blocks in Markdown or other formats.
        // -------------------------------------------------------
        case MC_TICK:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            return false;

        // #######################################################
        // Misc
        // #######################################################
        // -------------------------------------------------------
        // TAP-HOLD (Tap: <Action_A> | Hold: <Action_B>
        // -------------------------------------------------------
        /** case MT_TEMPLATE: */
        /**     static uint16_t MT_timer = 0;  // Timer variable to track key press duration */
        /**     if (record->event.pressed) { */
        /**         // Start the timer when the key is pressed. */
        /**         MT_timer = timer_read(); */
        /**     } else { */
        /**         // Calculate the elapsed time since the key was pressed. */
        /**         uint16_t elapsed_time = timer_elapsed(MT_timer); */
        /**  */
        /**         if (elapsed_time < 200) { */
        /**             // If the key was held for less than 200ms, treat it as a tap */
        /**             // Do Action A */
        /**         } else { */
        /**             // If held for 200ms or more, treat it as a hold */
        /**             // Do Action B */
        /**         } */
        /**     } */
        /**     return false; */

        // #######################################################
        // Tap Dance
        // #######################################################

    }
    return true;
}

/** This function gets called at every matrix scan, which is basically as often as the MCU can handle. */
/** Be careful what you put here, as it will get run a lot--even when user doesn't type. */
void matrix_scan_user(void) {
    // -------------------------------------------------------
    // Num Lock startup
    // -------------------------------------------------------
    if (numlock_pending &&
        timer_elapsed(numlock_timer) >= NUMLOCK_STARTUP_DELAY) {

        numlock_pending = false;

        if (!host_keyboard_led_state().num_lock) {
            tap_code(KC_NUM_LOCK);
        }
    }

    // -------------------------------------------------------
    // App Switcher (CMD+TAB) Timeout Handling
    // -------------------------------------------------------
    if (app_switch_active &&
        timer_elapsed(app_switch_timer) >= APP_SWITCH_TIMEOUT) {

        app_switch_active = false;

        if (is_windows_mode()) {
            unregister_code(KC_LALT);
        } else {
            unregister_code(KC_LGUI);
        }
    }
}

// ------------------------------------------------------
// Customize CAPS WORD behavior
// ------------------------------------------------------
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        /** case KC_MINS: */
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        // Numbers
        case KC_1 ... KC_0:
        // symbols on the base layer
        case KC_MINS:
        case KC_UNDS:
        case KC_COMM:
        case KC_DOT:
        case KC_SLSH:
        case KC_BSLS:
        case KC_SCLN:
        case KC_QUOT:
        case KC_LBRC:
        case KC_RBRC:
        // Text Editing keys
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

// ------------------------------------------------------
// Cutomize Tapping Term behavior
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Guide: longer tapping terms (ms) means: a key must be held longer to be registered as a hold, and vice versa.
        // If you want to avoid accedental hold, set a longer tapping term.
        // If you want to avoid accedental tap, set a shorter tapping term.
        // A caveat: Set high tapping terms leads to delays, as the keyboard waits as long as the tapping term to determine if a key is a tap or a hold.

        // Layer hold keye, i.e., LT(layer, kc)
        // As we use these layers for numbers, symbols, navigation, etc., it's better to make taps more deliberate by setting a smaller tapping term.
        case LT_NAV:
        case LT_SYM:
        /** case LT_FN: */
        /** case LT_NUM: */
        /** case LT_CSR: */
        /** case LT_MSE: */
            return TAPPING_TERM - 50;

        // Set a shorter tapping term for ENT to avoid accidental ENT trigger when typing fast.
        // Standard keys
        /** case KC_SPC: */
        /**     return TAPPING_TERM - 50; */

        // Mod-Tap keys, i.e., MT(mod, kc)
        case HRW_A:
        case HRW_S:
        case HRW_D:
        case HRW_F:
        case HRW_G:
        case HRW_H:
        case HRW_J:
        case HRW_K:
        case HRW_L:
        case HRW_SCLN:
            return TAPPING_TERM;

        default:
            return TAPPING_TERM; // Uses the default value in config.h
    }
}

// ------------------------------------------------------
// Keymap Layout Configuration
// ------------------------------------------------------
// clang-format off

// Clear keymap template:
/**
    [<Layer_Name>] = LAYOUT_split_3x6_3_ex2(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
                                      _______,  _______,  _______,                      _______,  _______,  _______
    ),
*/

/**
    [_FACTORY] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  XXXXXXX,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                      KC_DEL,   KC_BSPC,  KC_SPC,                       KC_ENT,   KC_INS,   KC_PRT
    ),
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY_3R] = LAYOUT_split_3x6_3_ex2(
    KC_LBRC,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_RBRC,
    KC_BSPC,  HRW_A,    HRW_S,    HRW_D,    HRW_F,    HRW_G,    MO_MGC,   MO_MGC,   HRW_H,    HRW_J,    HRW_K,    HRW_L,    HRW_SCLN, KC_QUOT,
    ST_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_BSLS,
                                  MO_CSR,   LT_NUM,   LT_NAV,                       LT_SYM,   LT_FN,    MO_MSE
),

/** [_BASE_STD] = LAYOUT_split_3x6_3_ex2( */
/**     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  XXXXXXX,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS, */
/**     KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     MO_MGC,   MO_MGC,   KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT, */
/**     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, */
/**                                   KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,   KC_RALT,  MO_FN */
/** ), */

[_TYPING] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     _______,  _______,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,                      _______,  _______,  _______
),

[_GAMING] = LAYOUT_split_3x6_3_ex2(
    KC_M,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     XXXXXXX,  XXXXXXX,  _______,  _______,  KC_UP,    _______,  _______,  _______,
    KC_I,     KC_LSFT,  KC_A,     KC_S,     KC_D,     KC_F,     _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,
    KC_G,     KC_LCTL,  KC_Z,     KC_X,     KC_C,     KC_V,                         _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,                      _______,  _______,  _______
),

[_SYMBOL] = LAYOUT_split_3x6_3_ex2(
    SM_EXCL,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  XXXXXXX,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,
    SM_HASH,  SM_CRET,  SM_EQL,   SM_UNDS,  SM_DLR,   SM_ASTR,  _______,  _______,  XXXXXXX,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,  MC_TICK,
    SM_AMPS,  SM_LT,    SM_PIPE,  SM_MINS,  SM_GT,    SM_PLUS,                      KC_TAB,   KC_SPC,   KC_ENT,   KC_BSPC,  KC_DEL,   _______,
                                  _______,  SM_PERC,  SM_ADS,                       _______,  _______,  _______
),

[_NAVIGATE] = LAYOUT_split_3x6_3_ex2(
    XXXXXXX,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  XXXXXXX,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,
    DEL_NORM, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  SEL_WRD,  _______,  _______,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_END,
    XXXXXXX,  UNDO,     CUT,      COPY,     PASTE,    SEL_LNE,                      SM_LBRC,  SM_LCBR,  SM_LPRN,  SM_RPRN,  SM_RCBR,  SM_RBRC,
                                  _______,  _______,  _______,                      SM_TILD,  SM_TICK,  _______
),

[_CURSOR] = LAYOUT_split_3x6_3_ex2(
    WM_SWTCH, WM_CLOSE, WM_TCLS,  AP_FEXP,  RENAME,   WM_NEW,   XXXXXXX,  XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,
    DEL_NORM, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  FIND,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  UNDO,     CUT,      COPY,     PASTE,    _______,                      _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  WM_SPOT,                      _______,  _______,  _______
),

[_NUMBER] = LAYOUT_split_3x6_3_ex2(
    _______,  KC_DEL,   KC_BSPC,  KC_ENT,   KC_SPC,   KC_TAB,    XXXXXXX,  XXXXXXX,  KC_NUM,   KC_P7,   KC_P8,    KC_9,     SM_COLN,  SM_PERC,
    KC_CALC,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_MEH,    _______,  _______,  SM_LPRN,  KC_P4,   KC_P5,    KC_6,     SM_MINS,  SM_PLUS,
    _______,  SEL_ALL,  SEL_LNE,  SEL_WRD,  FIND,     XXXXXXX,                       SM_RPRN,  KC_P1,   KC_P2,    KC_3,     SM_ASTR,  SM_SLSH,
                                  _______,  _______,  _______,                       KC_P0,    KC_PDOT, XXXXXXX
),

[_MOUSE] = LAYOUT_split_3x6_3_ex2(
    _______,  _______,  _______,  MS_WHLU,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,  _______,  MS_UP,    _______,  _______,  _______,
    _______,  _______,  MS_WHLL,  MS_WHLD,  MS_WHLR,  _______,  _______,  _______,  _______,  MS_LEFT,  MS_DOWN,  MS_RGHT,  _______,  _______,
    _______,  _______,  MS_ACL0,  MS_ACL1,  MS_ACL2,  _______,                      _______,  MS_BTN1,  MS_BTN3,  MS_BTN2,  _______,  _______,
                                  MS_BTN3,  MS_BTN1,  MS_BTN2,                      _______,  _______,  _______
),

[_FUNCTION] = LAYOUT_split_3x6_3_ex2(
    KC_INS,   KC_VOLD,  KC_MUTE,  KC_VOLU,  XXXXXXX,  AP_TERM,  XXXXXXX,  XXXXXXX,  AP_SSHT,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F13,
    KC_CAPS,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  AP_CHRM,  _______,  _______,  _______,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   KC_F14,
    TG_TYP,   KC_MPRV,  KC_MPLY,  KC_MNXT,  UR_GPT,   AP_FFOX,                      AP_FEXP,  KC_F1,    KC_F2,    KC_F3,    KC_F12,   KC_F15,
                                  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  _______,  XXXXXXX
),

[_MAGIC] = LAYOUT_split_3x6_3_ex2(
    UG_TOGG,  BT_PRF1,  BT_PRF2,  BT_PRF3,  OU_2P4G,  OU_USB,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    QK_BOOT,  UG_HUEU,  UG_VALU,  UG_SATU,  XXXXXXX,  TG_GAME,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  QK_BOOT,
    XXXXXXX,  UG_HUED,  UG_VALD,  UG_SATD,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  CG_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                  TG_CSR,   TG_NUM,   TG_NAV,                       TG_SYM,   TG_FN,    TG_MSE
),

};

// Define the encoder rotation map for each layer
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY_3R]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_TYPING]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    /** [_BASE_STD]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), }, */
    [_FUNCTION]    = { ENCODER_CCW_CW(UG_VALD, UG_VALU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_MAGIC]       = { ENCODER_CCW_CW(UG_VALD, UG_VALU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_SYMBOL]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_NUMBER]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_CURSOR]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [_GAMING]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif // ENCODER_MAP_ENABLE

// ------- RGB Light Configuration -------

// Corne v4.1 RGB LED Index Map
// NOTE: For split keyboards, the layout becomes vertical and indices jump between halves.
// https://docs.qmk.fm/features/split_keyboard#layout-macro
/**
                  KEY INDEX MAP

    00 01 02 03 04 05 06    07 08 09 10 11 12 13
    14 15 16 17 18 19 20    21 22 23 24 25 26 27
    28 29 30 31 32 33          34 35 36 37 38 39
             40 41 42          43 44 45
------------------------------------------------------------
                  LED INDEX MAP

    18 17 12 11 04 03 21    44 26 27 34 35 40 41
    19 16 13 10 05 02 22    45 25 28 33 36 39 42
    20 15 14 09 06 01          24 29 32 37 38 43
             08 07 00          23 30 31

*/

// Set RGB color for an array of LED indices.
static void set_rgb_color(
    const uint8_t *rgb_index,
    uint8_t rgb_index_size,
    rgb_t rgb_color
) {
    for (uint8_t i = 0; i < rgb_index_size; i++) {
        rgb_matrix_set_color(
            rgb_index[i],
            rgb_color.r,
            rgb_color.g,
            rgb_color.b
        );
    }
}

#define SET_RGB_COLOR(rgb_index, rgb_color) \
    set_rgb_color(rgb_index, ARRAY_SIZE(rgb_index), rgb_color)


// Change RGB Color per Layer
bool rgb_matrix_indicators_user(void) {

    // ---------------------------------------------------------------
    // Define Aliases: Colors
    // ---------------------------------------------------------------
    /** Current RGB brightness. */
    uint8_t val = rgb_matrix_get_val();

    /** Color Aliases */
    hsv_t hsv_off = (hsv_t){0, 0, 0};
    rgb_t rgb_off = hsv_to_rgb(hsv_off);

    /** hsv_t hsv_grey = (hsv_t){0, 0, val / 2}; */
    /** rgb_t rgb_grey = hsv_to_rgb(hsv_grey); */

    hsv_t hsv_white = (hsv_t){0, 0, val};
    rgb_t rgb_white = hsv_to_rgb(hsv_white);

    hsv_t hsv_white_warm = (hsv_t){25, 200, val};
    rgb_t rgb_white_warm = hsv_to_rgb(hsv_white_warm);

    hsv_t hsv_red = (hsv_t){0, 255, val};
    rgb_t rgb_red = hsv_to_rgb(hsv_red);

    /** hsv_t hsv_pink = (hsv_t){0, 220, val};  // Pink (Pale) */
    hsv_t hsv_pink = (hsv_t){245, 255, val};  // Pink (Deep): Rose
    rgb_t rgb_pink = hsv_to_rgb(hsv_pink);

    hsv_t hsv_green = (hsv_t){85, 255, val};
    rgb_t rgb_green = hsv_to_rgb(hsv_green);

    hsv_t hsv_lime = (hsv_t){85, 101, val};
    rgb_t rgb_lime = hsv_to_rgb(hsv_lime);

    hsv_t hsv_blue = (hsv_t){170, 255, val};
    rgb_t rgb_blue = hsv_to_rgb(hsv_blue);

    hsv_t hsv_cyan = (hsv_t){150, 255, val};
    rgb_t rgb_cyan = hsv_to_rgb(hsv_cyan);

    /** hsv_t hsv_orange = (hsv_t){20, 255, val}; */
    /** rgb_t rgb_orange = hsv_to_rgb(hsv_orange); */
    hsv_t hsv_yellow = (hsv_t){43, 255, val};
    rgb_t rgb_orange = hsv_to_rgb(hsv_yellow);

    hsv_t hsv_purple = (hsv_t){190, 255, val};
    rgb_t rgb_purple = hsv_to_rgb(hsv_purple);

    /** Home Row Mods (HRMs) Color */
    rgb_t rgb_hrm = hsv_to_rgb(hsv_blue);

    // ---------------------------------------------------------------
    // Setup RGB Lighting per Layer
    // ---------------------------------------------------------------
    /** Turn off all RGB LEDs first. */
    rgb_matrix_set_color_all(rgb_off.r, rgb_off.g, rgb_off.b);

    /** Get the highest active layer. */
    uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);

    // ---------------------------------------------------------------
    // Layer-Specific RGB Lighting
    // ---------------------------------------------------------------
    switch (active_layer) {

        // ---------------------------------------------------------------
        // BASE STANDARD
        // ---------------------------------------------------------------
        /** case _BASE_STD: { */
        /**     rgb_matrix_set_color_all( */
        /**         rgb_pink.r, */
        /**         rgb_pink.g, */
        /**         rgb_pink.b */
        /**     ); */
        /**  */
        /**     break; */
        /** } */

        // ---------------------------------------------------------------
        // BASE SPLIT / TYPING
        // ---------------------------------------------------------------
        case _QWERTY_3R:
        case _TYPING: {
            static const uint8_t base_spl_rgb_idx[] = {
                18, 17, 12, 11, 4, 3, 21,     44, 26, 27, 34, 35, 40, 41,
                19, 16, 13, 10, 5, 2, 22,     45, 25, 28, 33, 36, 39, 42,
                20, 15, 14,  9, 6, 1,             24, 29, 32, 37, 38, 43,
                         8,  7, 0,                23, 30, 31
            };

            SET_RGB_COLOR(base_spl_rgb_idx, rgb_white_warm);

            /** Set diff color for HRMs only on _QWERTY_3R. */
            if (active_layer == _QWERTY_3R) {
                static const uint8_t hrm_rgb_idx[] = {
                    16, 13, 10, 5,  // Left HRMs
                    28, 33, 36, 39   // Right HRMs
                };
                SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);
            }

            break;
        }

        // ---------------------------------------------------------------
        // NUMBER
        // ---------------------------------------------------------------
        case _NUMBER: {
            /** 3x3 keypad + 0: */
            static const uint8_t rgb_idx_number[] = {
                27, 34, 35,
                28, 33, 36,
                29, 32, 37,
                23, 30
            };
            SET_RGB_COLOR(rgb_idx_number, rgb_green);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                16, 13, 10, 5  // Left HRMs
            };
            SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);

            /** if Numlock in ON, Turn its key on */
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(26, rgb_red.r, rgb_red.g, rgb_red.b);
            }

            break;
        }

        // ---------------------------------------------------------------
        // FUNCTION
        // ---------------------------------------------------------------
        case _FUNCTION: {
            /** F1-F12: */
            static const uint8_t rgb_idx_funcs[] = {
                27, 34, 35, 38,
                28, 33, 36, 39,
                29, 32, 37, 40
            };
            SET_RGB_COLOR(rgb_idx_funcs, rgb_orange);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                16, 13, 10, 5  // Left HRMs
            };
            SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);

            /** Set diff color for Volume and Media control */
            /** VOLDN/MPRV */
            rgb_matrix_set_color(17, rgb_orange.r, rgb_orange.g, rgb_orange.b);
            rgb_matrix_set_color(15, rgb_orange.r, rgb_orange.g, rgb_orange.b);
            /** MUTE/MPLY */
            rgb_matrix_set_color(12, rgb_red.r, rgb_red.g, rgb_red.b);
            rgb_matrix_set_color(14, rgb_red.r, rgb_red.g, rgb_red.b);
            /** VOLUP/MNXT */
            rgb_matrix_set_color(11, rgb_green.r, rgb_green.g, rgb_green.b);
            rgb_matrix_set_color(9, rgb_green.r, rgb_green.g, rgb_green.b);

            break;
        }

        // ---------------------------------------------------------------
        // MAGIC
        // ---------------------------------------------------------------
        case _MAGIC: {
            /** Bluetooth */
            static const uint8_t rgb_idx_bluetooth[] = {
                17, 12, 11
            };
            SET_RGB_COLOR(rgb_idx_bluetooth, rgb_blue);

            /** Wireless 2.4 G */
            rgb_matrix_set_color(4, rgb_green.r, rgb_green.g, rgb_green.b);

            /** RGB Toggle */
            rgb_matrix_set_color(18, rgb_purple.r, rgb_purple.g, rgb_purple.b);
            
            /** RGB Brightness/Saturation/Hue */
            static const uint8_t rgb_idx_rgb_ctrl_increase[] = {
                16, 13, 10
            };

            static const uint8_t rgb_idx_rgb_ctrl_decrease[] = {
                15, 14, 9
            };
            SET_RGB_COLOR(rgb_idx_rgb_ctrl_increase, rgb_green);
            SET_RGB_COLOR(rgb_idx_rgb_ctrl_decrease, rgb_orange);

            /** Bootloader */
            static const uint8_t rgb_idx_bootloader[] = {
                19, 42
            };
            SET_RGB_COLOR(rgb_idx_bootloader, rgb_red);

            /** Mac/Win Toggle (CG_TOGG) */
            rgb_matrix_set_color(29, rgb_blue.r, rgb_blue.g, rgb_blue.b);

            /** Gaming Mode Toggle (TG_GAME) */
            rgb_matrix_set_color(2, rgb_red.r, rgb_red.g, rgb_red.b);

            break;
        }

        // ---------------------------------------------------------------
        // NAVIGATE
        // ---------------------------------------------------------------
        case _NAVIGATE: {
            static const uint8_t rgb_idx_nav[] = {
                28, 33, 36, 39      // Arow keys (jkl;)
            };
            SET_RGB_COLOR(rgb_idx_nav, rgb_purple);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                16, 13, 10, 5  // Left HRMs
            };
            SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);

            /** Symbol-Groups keys LED Colors  **/
            static const uint8_t led_idx_sym_groups[] = {
                24, 29, 32, 36, 37, 43
            };
            SET_RGB_COLOR(led_idx_sym_groups, rgb_cyan);

            // Set color for the number row
            static const uint8_t rgb_idx_num_row[] = {
                17, 12, 11, 4, 3,     26, 27, 34, 35, 40
            };
            SET_RGB_COLOR(rgb_idx_num_row, rgb_white_warm);

            // Set color for DEL
            rgb_matrix_set_color(19, rgb_red.r, rgb_red.g, rgb_red.b);

            // Set color for Getreuer's Select_WORD keys (SEL_ALL, SEL_WRD, SEL_LNE, FIND)
            static const uint8_t rgb_idx_gesture[] = {
                1, 2
            };
            SET_RGB_COLOR(rgb_idx_gesture, rgb_lime);
            
            break;
        }

        // ---------------------------------------------------------------
        // CURSOR
        // ---------------------------------------------------------------
        case _CURSOR: {
            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                16, 13, 10, 5  // Left HRMs
            };
            SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);

            /** Set diff color for CUT/COPY/PASTE/UNDO */
            /** UNDO */
            rgb_matrix_set_color(15, rgb_orange.r, rgb_orange.g, rgb_orange.b);
            /** CUT */
            rgb_matrix_set_color(14, rgb_red.r, rgb_red.g, rgb_red.b);
            /** COPY */
            rgb_matrix_set_color(9, rgb_orange.r, rgb_orange.g, rgb_orange.b);
            /** PASTE */
            rgb_matrix_set_color(6, rgb_green.r, rgb_green.g, rgb_green.b);

            // Set color for DEL
            rgb_matrix_set_color(19, rgb_red.r, rgb_red.g, rgb_red.b);

            break;
        }

        // ---------------------------------------------------------------
        // MOUSE
        // ---------------------------------------------------------------
        case _MOUSE: {
            static const uint8_t rgb_idx_nav[] = {
                    34,
                28, 33, 36
            };
            SET_RGB_COLOR(rgb_idx_nav, rgb_purple);

            static const uint8_t rgb_idx_clicks[] = {
                29, 32, 37,      // Left, Middle and Right Mouse Buttons
                7, 0
            };
            SET_RGB_COLOR(rgb_idx_clicks, rgb_orange);

            static const uint8_t rgb_idx_scroll[] = {
                    11,
                13, 10, 5
            };
            SET_RGB_COLOR(rgb_idx_scroll, rgb_blue);

            /** Mouse Speed Control */
            rgb_matrix_set_color(14, rgb_red.r, rgb_red.g, rgb_red.b);
            rgb_matrix_set_color(9, rgb_orange.r, rgb_orange.g, rgb_orange.b);
            rgb_matrix_set_color(6, rgb_green.r, rgb_green.g, rgb_green.b);

            break;
        }
        // ---------------------------------------------------------------
        // Gaming
        // ---------------------------------------------------------------
        case _GAMING:
        {
            /** Left, Down, Up, Right. */
            static const uint8_t rgb_idx_gaming[] = {
                    11,        //   W
                13, 10, 5,     // A S D

                    34,        //      Up
                28, 33, 36     // Left Down Right

            };
            SET_RGB_COLOR(rgb_idx_gaming, rgb_red);

            break;
        }

        // ---------------------------------------------------------------
        // SYMBOL
        // ---------------------------------------------------------------
        case _SYMBOL: {
            /** ALL Symbol Kyes LED Color */
            
            // Use Sunsau's red (quotes), green (arrows), blue (groups), purple (flips), and yellow (Vim) colors for symbols
            /** Quotes keys LED Colors  **/
            static const uint8_t led_idx_sym_quotes[] = {
            };
            SET_RGB_COLOR(led_idx_sym_quotes, rgb_pink);

            /** Symbol-Arrows keys LED Colors  **/
            static const uint8_t led_idx_sym_arrows[] = {
                    13,
                15, 14, 9, 6
            };
            SET_RGB_COLOR(led_idx_sym_arrows, rgb_green);

            /** Symbol-Flips keys LED Colors  **/
            static const uint8_t led_idx_sym_flips[] = {
                18
            };
            SET_RGB_COLOR(led_idx_sym_flips, rgb_purple);

            /** Symbol-VIM keys LED Colors  **/
            static const uint8_t led_idx_sym_vim[] = {
                19, 16, 5, 2,
                0, 7
            };
            SET_RGB_COLOR(led_idx_sym_vim, rgb_orange);

            /** Symbol-Misc keys LED Colors  **/
            static const uint8_t led_idx_sym_misc[] = {
            };
            SET_RGB_COLOR(led_idx_sym_misc, rgb_white);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                28, 33, 36, 39   // Right HRMs
            };
            SET_RGB_COLOR(hrm_rgb_idx, rgb_hrm);

            // Set color for the number row
            static const uint8_t rgb_idx_num_row[] = {
                17, 12, 11, 4, 3,     26, 27, 34, 35, 40
            };
            SET_RGB_COLOR(rgb_idx_num_row, rgb_white_warm);

            break;
        }

        // ---------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------
        default: {
            rgb_matrix_set_color_all(
                rgb_pink.r,
                rgb_pink.g,
                rgb_pink.b
            );

            break;
        }
    }

    // ---------------------------------------------------------------
    // CTRL/GUI SWAP INDICATOR
    // ---------------------------------------------------------------
    /** Change the color of  a specific key, whenever CG_TOGG is active. */
    if (keymap_config.swap_lctl_lgui) {
        /** LED 80 is the LALT/LCMD key. */
        rgb_matrix_set_color(8, rgb_blue.r, rgb_blue.g, rgb_blue.b);
    }

    // ---------------------------------------------------------------
    // CAPS LOCK INDICATOR
    // ---------------------------------------------------------------
    /** Change the Color of a specific key, when CAPS LOCK is active */
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(19, rgb_red.r, rgb_red.g, rgb_red.b);
    }

    // ---------------------------------------------------------------
    // CAPS WORD INDICATOR
    // ---------------------------------------------------------------
    if (is_caps_word_on()) {
        // Single LED indicator
        /** rgb_matrix_set_color(20, rgb_red.r, rgb_red.g, rgb_red.b); */
        // Multiple LED indicator
        static const uint8_t led_idx_caps_word[] = {
                18, 17, 12, 11, 4, 3,     26, 27, 34, 35, 38, 43,
                19, 16, 13, 10, 5, 2,     25, 28, 33, 36, 39, 42,
                20, 15, 14,  9, 6, 1,     24, 29, 32, 37, 40, 41,
        };
        SET_RGB_COLOR(led_idx_caps_word, rgb_red);
        // Whole Keyboard indicator
        /** rgb_matrix_set_color_all(rgb_red.r, rgb_red.g, rgb_red.b); */
    }

    return false;
}

