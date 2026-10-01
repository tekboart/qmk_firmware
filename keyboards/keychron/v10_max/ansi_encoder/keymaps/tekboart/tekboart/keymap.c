/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    // TODO: BASE layers (e.g., Split, Typing, Standard, Gaming) must always be the lowest numbered layers.
    // I put a layer in betwwen so that MAC toggle selects Split Base layer and WIN toggle selects Standard Base layer.
    _BASE_SPL,  // Split Layer (Base)
    _TYPING,    // Typing Layer (Base): Disable all HRMs.
    _BASE_STD,  // Standard QWERTY Layer (Base): Disable all HRMs & Split Layout.
    _GAMING,   // Gaming Layer
    _SYMBOL,   // Symbols Layer (Split Layout)
    _NUMBER,   // Number/Numpad Layer (Split Layout)
    _CURSOR,   // Cursor Layer (Split Layout)
    // NOTE: _FUNCTION must be placed as the last layer, as it may be used in many layers (if not all)--e.g., to enable/disable other layers (e.g., Gaming/Standard/etc.)
    // Refer to QMK's layer doc beginners guide: https://docs.qmk.fm/feature_layers#beginners 
    _FUNCTION,    // Function Layer (Split Layout). Hint: It's a combination of Function, Magic and Lower Layers in MoErgo
};

// ---------------------------------------------------------------
// Define Aliases
// ---------------------------------------------------------------
// ------- Define Aliases: Layers  -------
// (Base) Split Layer
#define TT_BASE TT(_BASE_SPL)
#define TG_BASE TG(_BASE_SPL)
#define DF_BASE DF(_BASE_SPL)
// Typing Layer
#define TT_TYP TT(_TYPING)
#define TG_TYP TG(_TYPING)
// Standard Layout
#define LT_STD  LT(_BASE_STD, KC_4)
#define TT_STD  TT(_BASE_STD)
#define TG_STD  TG(_BASE_STD)
#define DF_STD  DF(_BASE_STD)
// Function Layer
#define LT_FN   LT(_FUNCTION, KC_ENT)
#define MO_FN   MO(_FUNCTION)
#define TT_FN   TT(_FUNCTION)
#define TG_FN   TG(_FUNCTION)
// Number Layer
#define LT_NUM  LT(_NUMBER, KC_SPC)
#define TT_NUM  TT(_NUMBER)
#define TG_NUM  TG(_NUMBER)
// Gaming Layer
#define LT_GAME  LT(_GAMING, KC_1)
#define TT_GAME  TT(_GAMING)
#define TG_GAME  TG(_GAMING)
// Symbol Layer
#define LT_SYM  LT(_SYMBOL, KC_DEL)
#define TT_SYM  TT(_SYMBOL)
#define TG_SYM  TG(_SYMBOL)
// Cursor Layer
#define LT_CSR   LT(_CURSOR, KC_BSPC)
#define MO_CSR   MO(_CURSOR)
#define TT_CSR   TT(_CURSOR)
#define TG_CSR   TG(_CURSOR)

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

// ------- Define Aliases: File Management  -------
#define CUT      C(KC_X)
#define COPY     C(KC_C)
#define PASTE    C(KC_V)
#define UNDO     C(KC_Z)
#define REDO     S(C(KC_Z))
#define FIND     C(KC_F)
#define SEL_ALL  C(KC_A)

// ------- Define Aliases: Community Modules  -------
/* Getreuer's Select Word */
#define SEL_WRD SELECT_WORD
#define SEL_WRB SELECT_WORD_BACK
#define SEL_LNE SELECT_LINE
#define SEL_LNU SELECT_LINE_UP

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
    MT_CGLR,  // Tap: Swap Ctrl and GUI, Hold: Toggle Layer
    MT_CPCG,  // Tap: CAPS LOCK, Hold: LSHIFT

    // Tap Dance Keys: TD_<TAP_DANCE>
    /** TD_SFT,  // Tap: OSM(MOD_LSFT), Hold: KC_LSFT, Double Tap: KC_CAPS */

};

// CG_TOGG / keymap_config.swap_lctl_lgui is being used as the MAC/WIN mode indicator.
static bool is_windows_mode(void) {
    // return true: Windows, return false: MacOS
    return !keymap_config.swap_lctl_lgui;
}

// Getreuer's Select Word module requires a OS Detection
// https://getreuer.info/posts/keyboards/select-word/index.html#mac-hotkeys
/** bool select_word_host_is_mac(void) { */
/**   return mod_config(MOD_LGUI) == MOD_LCTL;  // GUI/Ctrl swapped => Mac. */
/** } */

bool select_word_host_is_mac(void) {
  // return true: MacOS, return false: Windows
  return !is_windows_mode();
}

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
        // FIX: It was working before, but now we have a sticky Ctl (that needs keyboard disconnect to disable)
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
                    tap_code16(MEH(KC_1));
                } else {
                    tap_code16(MEH(KC_1));
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
        // Open ChatGPT in a browser (e.g., Firefox)
        // ------------------------------------------------------
        case UR_GPT:
            if (record->event.pressed) {
                // Launch Firefox using existing Firefox shortcut.
                tap_code16(AP_FFOX);

                // Allow Firefox to start/focus.
                wait_ms(1200);

                // Focus address bar.
                tap_code16(C(KC_L));
                wait_ms(50);

                // Enter URL and navigate.
                SEND_STRING("https://chatgpt.com/");
                tap_code(KC_ENT);
            }
            break;

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
            break;

        // #######################################################
        // Misc
        // #######################################################
        // -------------------------------------------------------
        // TAP-HOLD (Tap: Swap Ctrl and GUI, Hold: Toggle Layer)
        // -------------------------------------------------------
        case MT_CGLR:
            static uint16_t MT_CGLR_timer = 0;  // Timer variable to track key press duration
            if (record->event.pressed) {
                // Start the timer when the key is pressed.
                MT_CGLR_timer = timer_read();
            } else {
                // Calculate the elapsed time since the key was pressed.
                uint16_t elapsed_time = timer_elapsed(MT_CGLR_timer);

                // If the key was held for less than 200ms, treat it as a tap
                if (elapsed_time < 200) {
                    keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
                    eeconfig_update_keymap(&keymap_config);
                } else {
                    // If held for 200ms or more, treat it as a hold
                    layer_invert(_GAMING);
                }
            }
            return false;

        // -------------------------------------------------------
        // TAP-HOLD (Tap: CAPS LOCK, Hold: LSHIFT)
        // -------------------------------------------------------
        case MT_CPCG:
            static uint16_t MT_CPCG_timer = 0;  // Timer variable to track key press duration
            if (record->event.pressed) {
                // Start the timer when the key is pressed.
                MT_CPCG_timer = timer_read();
            } else {
                // Calculate the elapsed time since the key was pressed.
                uint16_t elapsed_time = timer_elapsed(MT_CPCG_timer);

                // If the key was held for less than 200ms, treat it as a tap
                if (elapsed_time < 200) {
                    tap_code(KC_CAPS);
                } else {
                    // If held for 200ms or more, treat it as a hold
                    keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
                    eeconfig_update_keymap(&keymap_config);
                }
            }
            return false;

        // #######################################################
        // Tap Dance
        // #######################################################

    }
    return true;
}

/** This function gets called at every matrix scan, which is basically as often as the MCU can handle. */
/** Be careful what you put here, as it will get run a lot--even when user doesn't type. */
void matrix_scan_user(void) {
    // App Switcher (CMD+TAB) Timeout Handling
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
// Keymap Layout Configuration
// ------------------------------------------------------
// clang-format off

// Clear keymap template:
    /** [<Layer_Name>] = LAYOUT_ansi_89( */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,  _______,            _______,  _______,  _______,            _______,            _______,                                          _______,  _______,  _______ */
    /** ), */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /** NOTE: Don't use LT for layers like cursor, which work on same side chords. */
    [_BASE_SPL] = LAYOUT_ansi_89(
        KC_MUTE,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_ESC,             HRW_A,    HRW_S,    HRW_D,    HRW_F,    HRW_G,              HRW_H,    HRW_J,    HRW_K,    HRW_L,    HRW_SCLN, KC_QUOT,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  ST_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  ST_RSFT,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            LT_CSR,   LT_NUM,   KC_TAB,             LT_SYM,             LT_FN,                                            XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_TYPING] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            KC_A,     KC_S,     KC_D,     KC_F,     _______,            _______,  KC_J,     KC_K,     KC_L,     KC_SCLN,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,            KC_BSPC,  KC_SPC,   KC_TAB,             KC_DEL,             KC_ENT,                                           _______,  _______,  _______
    ),

    [_SYMBOL] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  SM_EXCL,            SM_LBRC,  SM_LCBR,  SM_RCBR,  KC_RBRC,  SM_AMPS,            SM_LPRN,  KC_BSPC,  KC_SPC,   KC_ENT,   KC_DEL,   KC_TAB,   XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  SM_HASH,            SM_CRET,  SM_EQL,   SM_UNDS,  SM_DLR,   SM_ASTR,            SM_TICK,  KC_RSFT,  KC_RCTL,  KC_RALT,  KC_RGUI,  MC_TICK,  XXXXXXX,            XXXXXXX,
        /** XXXXXXX,  SM_TILD,            SM_LT,    SM_PLUS,  SM_MINS,  SM_GT,    SM_PIPE,  XXXXXXX,  SM_RPRN,  KC_BSPC,  KC_TAB,   KC_SPC,   KC_ENT,   KC_RSFT,            XXXXXXX, */
        XXXXXXX,  SM_TILD,            SM_LPRN,  SM_PLUS,  SM_MINS,  SM_RPRN,  SM_PIPE,  XXXXXXX,  SM_RPRN,  KC_BSPC,  KC_TAB,   KC_SPC,   KC_ENT,   KC_RSFT,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            SM_PERC,  SM_ADS,   _______,            _______,            _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_NUMBER] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            KC_DEL,   KC_ENT,   KC_SPC,   KC_BSPC,  XXXXXXX,            SM_LPRN,  KC_7,     KC_8,     KC_9,     SM_COLN,  SM_PERC,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_CALC,            KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_MEH,             KC_DOT,   KC_4,     KC_5,     KC_6,     SM_MINS,  SM_PLUS,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  _______,            SEL_ALL,  SEL_LNE,  SEL_WRD,  FIND,     XXXXXXX,  XXXXXXX,  SM_RPRN,  KC_1,     KC_2,     KC_3,     SM_ASTR,  SM_SLSH,            KC_UP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  _______,  _______,            KC_0,               _______,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_CURSOR] = LAYOUT_ansi_89(
        _______,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  WM_SWTCH,           WM_CLOSE, WM_TCLS,  AP_FEXP,  RENAME,   SEL_ALL,            AP_FFOX,  UNDO,     KC_UP,    REDO,     KC_ESC,   KC_TAB,   XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  DEL_NORM,           KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  SEL_WRD,            AP_CHRM,  KC_LEFT,  KC_DOWN,  KC_RGHT,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,            UNDO,     CUT,      COPY,     PASTE,    SEL_LNE,  XXXXXXX,  WM_NEW,   TX_HOME,  KC_PGDN,  KC_PGUP,  TX_END,   C(KC_L),            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  WM_SPOT,   _______,           SEL_WRD,            _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_GAMING] = LAYOUT_ansi_89(
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_TAB,             _______,  KC_W,     _______,  _______,  _______,            _______,  _______,  KC_UP,    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_LSFT,            KC_A,     KC_S,     KC_D,     _______,  _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_LCTL,            _______,  _______,  _______,  _______,  _______,  XXXXXXX,  _______,  _______,  _______,  _______,  _______,  _______,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            _______,  KC_SPC,   _______,            KC_ENT,             _______,                                          XXXXXXX,  XXXXXXX,  XXXXXXX
    ),


    [_BASE_STD] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_CALC,
        MC_1,     KC_GRV,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
        MC_2,     KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
        MC_3,     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        MC_5,     KC_LCTL,  KC_LGUI,            KC_LALT,  KC_SPC,   KC_RALT,            KC_SPC,             MO_FN,                                            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [_FUNCTION] = LAYOUT_ansi_89(
        UG_TOGG,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  TG_STD,             BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    AP_TERM,            AP_SSHT,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F13,   XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  MT_CPCG,            KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  AP_CHRM,            _______,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   KC_F14,   XXXXXXX,            KC_END,
        XXXXXXX,  TG_TYP,             KC_MPRV,  KC_MPLY,  KC_MNXT,  UR_GPT,   AP_FFOX,  BAT_LVL,  AP_FEXP,  KC_F1,    KC_F2,    KC_F3,    KC_F12,   KC_F15,             KC_PGUP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            TG_CSR,   TG_NUM,   TG_GAME,            TG_SYM,             _______,                                          KC_HOME,  KC_PGDN,  KC_END
    ),

};

// Define the encoder rotation map for each layer
// The encoder map defines the behavior of the rotary encoder (aka Knob) for each layer
// Examples: KC_VOLD: Volume Down, KC_VOLU: Volume Up, UG_VALD: Underglow Brightness Down, UG_VALU: Underglow Brightness Up
// TODO: Add diff for layers, e.g., SPL_LAYER_2 + turn_right --> Screen Brightness Up, turn_left --> Screen Brightness Down
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    /** [TGL_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, */
    /** [TGL_FN]   = {ENCODER_CCW_CW(UG_VALD, UG_VALU)}, */
    [_BASE_SPL]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_TYPING]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_BASE_STD]    = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_FUNCTION]    = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [_SYMBOL]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_NUMBER]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_CURSOR]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [_GAMING]      = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};
#endif // ENCODER_MAP_ENABLE

// ------- RGB Light Configuration -------

// V10_Mac RGB-Key Layout
/** __:KNOB    0:ESC              1:F1       2:F2      3:F3      4:F4      5:F5      6:F6      7:F7      8:F8      9:F9     10:F10    11:F11    12:F12             13:XXXX  14:XXXX  */
/** 15:M_1    16:GRV              17:1      18:2      19:3      20:4      21:5      22:6      23:7      24:8      25:9      26:0      27:MINS   28:EQL    xx_BSPC           30:HOME  */
/** 31:M_2    32:TAB              33:Q      34:W      35:E      36:R      37:T                38:Y      39:U      40:I      41:O      42:P      43:[      44:]     45:\     46:DEL   */
/** 47:M_3    48:CAPS             49:A      50:S      51:D      52:F      53:G                54:H      55:J      56:K      57:L      58:;      59:QUOT   60:ENT            61:END   */
/** 62:M_4    63:LSFT             64:Z      65:X      66:C      67:V      68:B      69:B      70:N      71:M      72:,      73:.      74:/      75:RSFT            76:UP             */
/** 77:M_5    78:LCTL   79:LGUI             80:LALT   81:SPC    82:RALT             83:SPC              84:FN                                             85:LEFT  86:DOWN  87:RGHT  */


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

    hsv_t hsv_grey = (hsv_t){0, 0, val / 2};
    rgb_t rgb_grey = hsv_to_rgb(hsv_grey);

    hsv_t hsv_white = (hsv_t){0, 0, val};
    rgb_t rgb_white = hsv_to_rgb(hsv_white);

    hsv_t hsv_white_warm = (hsv_t){25, 200, val};
    rgb_t rgb_white_warm = hsv_to_rgb(hsv_white_warm);

    hsv_t hsv_red = (hsv_t){0, 255, val};
    rgb_t rgb_red = hsv_to_rgb(hsv_red);

    hsv_t hsv_pink = (hsv_t){0, 220, val};
    rgb_t rgb_pink = hsv_to_rgb(hsv_pink);

    hsv_t hsv_green = (hsv_t){85, 255, val};
    rgb_t rgb_green = hsv_to_rgb(hsv_green);

    hsv_t hsv_blue = (hsv_t){170, 255, val};
    rgb_t rgb_blue = hsv_to_rgb(hsv_blue);

    hsv_t hsv_cyan = (hsv_t){150, 255, val};
    rgb_t rgb_cyan = hsv_to_rgb(hsv_cyan);

    hsv_t hsv_orange = (hsv_t){20, 255, val};
    rgb_t rgb_orange = hsv_to_rgb(hsv_orange);

    hsv_t hsv_purple = (hsv_t){190, 255, val};
    rgb_t rgb_purple = hsv_to_rgb(hsv_purple);

    /** Turn off all RGB LEDs first. */
    rgb_matrix_set_color_all(rgb_off.r, rgb_off.g, rgb_off.b);

    /** Get the highest active layer. */
    uint8_t active_layer = get_highest_layer(layer_state | default_layer_state);

    switch (active_layer) {

        // ---------------------------------------------------------------
        // BASE STANDARD
        // ---------------------------------------------------------------
        case _BASE_STD: {
            rgb_matrix_set_color_all(
                rgb_white_warm.r,
                rgb_white_warm.g,
                rgb_white_warm.b
            );

            break;
        }

        // ---------------------------------------------------------------
        // BASE SPLIT / TYPING
        // ---------------------------------------------------------------
        case _BASE_SPL:
        case _TYPING: {
            static const uint8_t base_spl_rgb_idx[] = {
                32, 33, 34, 35, 36, 37,
                38, 39, 40, 41, 42, 43,
                48, 49, 50, 51, 52, 53,
                54, 55, 56, 57, 58, 59,
                63, 64, 65, 66, 67, 68,
                70, 71, 72, 73, 74, 75,
                80, 81, 82,
                83, 84
            };

            SET_RGB_COLOR(base_spl_rgb_idx, rgb_white_warm);

            /** Set diff color for HRMs only on _BASE_SPL. */
            if (active_layer == _BASE_SPL) {
                static const uint8_t hrm_rgb_idx[] = {
                    49, 50, 51, 52,  // Left HRMs
                    55, 56, 57, 58   // Right HRMs
                };

                SET_RGB_COLOR(hrm_rgb_idx, rgb_red);
            }

            break;
        }

        // ---------------------------------------------------------------
        // NUMBER
        // ---------------------------------------------------------------
        case _NUMBER: {
            /** 3x3 keypad + 0: */
            static const uint8_t rgb_idx_number[] = {
                39, 40, 41,
                55, 56, 57,
                71, 72, 73,
                83
            };

            SET_RGB_COLOR(rgb_idx_number, rgb_green);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                49, 50, 51, 52,  // Left HRMs
            };

            SET_RGB_COLOR(hrm_rgb_idx, rgb_red);

            break;
        }

        // ---------------------------------------------------------------
        // FUNCTION
        // ---------------------------------------------------------------
        case _FUNCTION: {
            /** F1-F12: */
            static const uint8_t rgb_idx_funcs[] = {
                39, 40, 41, 42,
                55, 56, 57, 58,
                71, 72, 73, 74
            };

            SET_RGB_COLOR(rgb_idx_funcs, rgb_orange);

            /** Bluetooth */
            /** Keychron's BT_HST1/2/3 */
            static const uint8_t rgb_idx_bluetooth[] = {
                33, 34, 35
            };

            SET_RGB_COLOR(rgb_idx_bluetooth, rgb_blue);

            /** Wireless 2.4 G */
            /** Keychron's P2P4G */
            rgb_matrix_set_color(36, rgb_green.r, rgb_green.g, rgb_green.b);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                49, 50, 51, 52,  // Left HRMs
            };

            SET_RGB_COLOR(hrm_rgb_idx, rgb_red);

            break;
        }

        // ---------------------------------------------------------------
        // CURSOR
        // ---------------------------------------------------------------
        case _CURSOR: {
            /** Cursor/editing keys. */
            static const uint8_t rgb_idx_cursor[] = {
                /** 37, 53, 68,       // Cut, Copy, Paste */
                /** 54, 55, 56, 57,   // Arow keys (hjkl) */
                /** 55, 56, 57, 58,   // Arow keys (jkl;) */
                55, 56, 57, 40,   // Arow keys (jkli)
            };

            SET_RGB_COLOR(rgb_idx_cursor, rgb_purple);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                49, 50, 51, 52,  // Left HRMs
            };

            SET_RGB_COLOR(hrm_rgb_idx, rgb_red);

            break;
        }

        // ---------------------------------------------------------------
        // Gaming
        // ---------------------------------------------------------------
        case _GAMING:
        {
            /** Left, Down, Up, Right. */
            static const uint8_t rgb_idx_gaming[] = {
                    40,          // Up
                55, 56, 57,    // Left Down Right

                81,             // LSPC

                34,             // W
                49, 50, 51      // A S D
            };

            SET_RGB_COLOR(rgb_idx_gaming, rgb_red);

            break;
        }

        // ---------------------------------------------------------------
        // SYMBOL
        // ---------------------------------------------------------------
        case _SYMBOL: {
            /** ALL Symbol Kyes LED Color */
            /** static const uint8_t rgb_idx_symbols[] = { */
            /**     32, 33, 34, 35, 36, 37, */
            /**     48, 49, 50, 51, 52, 53, */
            /**     63, 64, 65, 66, 67, 68, */
            /**     80, 81, 82 */
            /** }; */
            /** SET_RGB_COLOR(rgb_idx_symbols, rgb_purple); */
            
            // Use Sunsau's red (quotes), green (arrows), blue (groups), purple (flips), and yellow (Vim) colors for symbols
            /** Quotes keys LED Colors  **/
            static const uint8_t led_idx_sym_quotes[] = {
                54, 59,
                71, 72, 73
            };

            SET_RGB_COLOR(led_idx_sym_quotes, rgb_pink);

            /** Arrows keys LED Colors  **/
            static const uint8_t led_idx_sym_arrows[] = {
                50,
                64, 66, 67, 68,
                54,
            };

            SET_RGB_COLOR(led_idx_sym_arrows, rgb_green);

            /** Groups keys LED Colors  **/
            static const uint8_t led_idx_sym_groups[] = {
                33, 34, 35, 36,
                38,
                70
            };

            SET_RGB_COLOR(led_idx_sym_groups, rgb_cyan);

            /** Flips keys LED Colors  **/
            static const uint8_t led_idx_sym_flips[] = {
                32,
                63,
                74
            };

            SET_RGB_COLOR(led_idx_sym_flips, rgb_purple);

            /** VIM keys LED Colors  **/
            static const uint8_t led_idx_sym_vim[] = {
                48, 49, 52, 53,
                80, 81

            };

            SET_RGB_COLOR(led_idx_sym_vim, rgb_orange);

            /** Misc keys LED Colors  **/
            static const uint8_t led_idx_sym_misc[] = {
                37,
                51,
                65
            };

            SET_RGB_COLOR(led_idx_sym_misc, rgb_white);

            /** Set diff color for HRMs */
            static const uint8_t hrm_rgb_idx[] = {
                55, 56, 57, 58   // Right HRMs
            };

            SET_RGB_COLOR(hrm_rgb_idx, rgb_red);


            break;
        }

        // ---------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------
        default: {
            rgb_matrix_set_color_all(
                rgb_grey.r,
                rgb_grey.g,
                rgb_grey.b
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
        rgb_matrix_set_color(80, rgb_blue.r, rgb_blue.g, rgb_blue.b);
    }

    // ---------------------------------------------------------------
    // CAPS LOCK INDICATOR
    // ---------------------------------------------------------------
    /** Change the Color of a specific key, when CAPS LOCK is active */
    if (host_keyboard_led_state().caps_lock) {
        /** LED 48 is the CAPS LOCK key. */
        rgb_matrix_set_color(48, rgb_blue.r, rgb_blue.g, rgb_blue.b);
    }

    return false;
}

