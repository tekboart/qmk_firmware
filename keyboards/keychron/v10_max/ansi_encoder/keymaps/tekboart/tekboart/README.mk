Follwing the Keychron's official guide:

https://github.com/Keychron/qmk_firmware/tree/2025q3/keyboards/keychron/v10_max

See my notion's "Customize “Keychron V10 MAX” using QMK" for the full guide.

# Set desired number of layers

> The V10_Max's left toggle (i.e., MAC) can have only two layers, as the Keychron's toggle set the MAC to layer 0 and WIN to layer 2. e.g., if mac has 3 layers, then the WIN toggle still sets the WIN to layer 2, which will be MAC's layer 2, not WIN's BASE layer.

tekboart/keymap.c

```c
enum layers {
    MAC_BASE,
    MAC_LAYER_1,
    WIN_BASE,
    WIN_LAYER_1,
    WIN_LAYER_2,
    WIN_LAYER_3,
    WIN_LAYER_4,
    WIN_LAYER_5,
    WIN_LAYER_6,
};
```

> Make sure to update the `DYNAMIC_KEYMAP_LAYER_COUNT` in `config.h` to match the number of layers you want to use.

> Make sure to update the PROGMEM keymaps in `keymap.c` to match the number of layers you want to use.


# Enable VIA

tekboart/rules.mk

```make
VIA_ENABLE = yes

# [ME] Remove the below line to keep Keychron's default [insecure] VIA implementation
# [ME] Removing the lines enables VIA_INSECURE, which might allow keyloaggers to read your keystrokes. Use at your own risk.
OPT_DEFS += -UVIA_INSECURE
```

tekboart/config.h

```c

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 9
```

> Setting the `DYNAMIC_KEYMAP_LAYER_COUNT 9` worked. However, using 15 layers failed as V10 MAX’s EEPROM could not fit as many layers.

> I belive the Max #layer for Keychron V10 Max is 11, including both MAC and WIN Toggles.

Hint: To avoid getting stuck in a MAC layer, without being able to switch to Split/Standard Layout, be sure to block the Split/Standard Layout Key in MAC layers.

> This is a safety measure to prevent accidentally switching to Split/Standard Layout while in a MAC layer, which could lead to confusion and difficulty in returning to the desired layout.

> With my workaround, one can only switch to Split/Standard Layout from the corresponding BASE layer, not from any MAC layer.

Look at the XXXXXXX on the left hand side of MAC layers.

```c
    [SPL_BASE] = LAYOUT_ansi_89(
        KC_MUTE,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_PSCR,  KC_CALC,
        TT_STD,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            KC_HOME,
        TT_MAC,   KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_GRV,   XXXXXXX,  XXXXXXX,  KC_DEL,
        XXXXXXX,  KC_ESC,             HRW_A,    HRW_S,    HRW_D,    HRW_F,    KC_G,               KC_H,     HRW_J,    HRW_K,    HRW_L,    HRW_SCLN, KC_QUOT,  XXXXXXX,            KC_END,
        XXXXXXX,  KC_BSPC,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_DEL,             KC_UP,
        XXXXXXX,  XXXXXXX,  XXXXXXX,            TT_NUM,   LT_NAV,   MO_FN,              LT_SYM,             MT_RALT,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [SPL_MAC] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            HRM_A,    HRM_S,    HRM_D,    HRM_F,    _______,            _______,  HRM_J,    HRM_K,    HRM_L,    HRM_SCLN, _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,            _______,  _______,  _______,            _______,            _______,                                          _______,  _______,  _______
    ),
```

```c
    [STD_BASE] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_CALC,
        _______,  KC_GRV,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
        TT_STDM,  KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
        MC_3,     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        MC_5,     KC_LCTL,  KC_LGUI,            KC_LALT,  KC_SPC,   MO_STDF,            KC_SPC,             KC_RALT,                                          KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [STD_MAC] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        XXXXXXX,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  KC_LALT,            KC_LGUI,  _______,  _______,            _______,            _______,                                          _______,  _______,  _______
    ),
```


# Extra

Layer Keymap Template

> my own rearragment for a more intuitive keymap modification)

```c

    /** [<Layer_Name>] = LAYOUT_ansi_89( */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,   */
    /**     _______,  _______,  _______,            _______,  _______,  _______,            _______,            _______,                                          _______,  _______,  _______ */
    /** ), */
```

The default Keymaps (by Keychron)

```c
    /** [BASE] = LAYOUT_ansi_89( */
    /**     KC_MUTE,  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_CALC, */
    /**     TG_TGLB,  KC_GRV,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME, */
    /**     TT_STDM,  KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL, */
    /**     MC_3,     KC_CAPS,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_END, */
    /**     MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP, */
    /**     MC_5,     KC_LCTL,  KC_LGUI,            KC_LALT,  KC_SPC,   MO(TGL_FN),         KC_SPC,             KC_RALT,                                          KC_LEFT,  KC_DOWN,  KC_RGHT */
    /** ), */

    /** [FN] = LAYOUT_ansi_89( */
    /**     UG_TOGG,  _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,  _______, */
    /**     _______,  _______,            BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_END, */
    /**     _______,  UG_TOGG,            UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, */
    /**     _______,  _______,            UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,            _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______, */
    /**     _______,  _______,            _______,  _______,  _______,  _______,  BAT_LVL,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,            KC_PGUP, */
    /**     _______,  _______,  _______,            _______,  _______,  _______,            _______,            _______,                                          KC_HOME,  KC_PGDN,  KC_END */
    /** ), */

```
