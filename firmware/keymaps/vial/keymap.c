// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_7,KC_8,KC_9,KC_0,
        KC_4,KC_5,KC_6,
        KC_1,KC_2,KC_3
    )
};

//
// modify
//

int osinfo = 0;

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    osinfo = detected_host_os();

    return true;
}

enum custom_keycodes {
    MY_CMD = 0x7E00,
    MY_CTRL,
    MY_HYPER,
    MY_COPY,
    MY_PASTE,
    MY_CUT,
    MY_UNDO,
    MY_REDO
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* Cmd側の物理キー */
        case MY_CMD:
            if (record->event.pressed) {
                switch (osinfo) {
                    case OS_MACOS:
                        register_code(KC_LGUI); // Cmd
                        break;
                    case OS_WINDOWS:
                        register_code(KC_LCTL); // Ctrl
                        break;
                    case OS_LINUX:
                        register_code(KC_LCTL); // Ctrl
                        break;
                    default:
                        break;
                }
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
            }
            return false;

        /* Ctrl側の物理キー */
        case MY_CTRL:
            if (record->event.pressed) {
                switch (osinfo) {
                    case OS_MACOS:
                        register_code(KC_LCTL);
                        break;
                    case OS_WINDOWS:
                        register_code(KC_LGUI);
                        break;
                    case OS_LINUX:
                        register_code(KC_LGUI);
                        break;
                    default:
                        break;
                }
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;
        case MY_HYPER:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                register_code(KC_LALT);
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LGUI);
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            }
            return false;

        case MY_COPY:
            if (record->event.pressed) {
                if (osinfo == OS_MACOS) {
                    tap_code16(LGUI(KC_C));
                } else {
                    tap_code16(LCTL(KC_C));
                }
            }
            return false;

        case MY_PASTE:
            if (record->event.pressed) {
                if (osinfo == OS_MACOS) {
                    tap_code16(LGUI(KC_V));
                } else {
                    tap_code16(LCTL(KC_V));
                }
            }
            return false;

        case MY_CUT:
            if (record->event.pressed) {
                if (osinfo == OS_MACOS) {
                    tap_code16(LGUI(KC_X));
                } else {
                    tap_code16(LCTL(KC_X));
                }
            }
            return false;

        case MY_UNDO:
            if (record->event.pressed) {
                if (osinfo == OS_MACOS) {
                    tap_code16(LGUI(KC_Z));
                } else {
                    tap_code16(LCTL(KC_Z));
                }
            }
            return false;

        case MY_REDO:
            if (record->event.pressed) {
                if (osinfo == OS_MACOS) {
                    tap_code16(SGUI(KC_Z));  // Shift + Cmd + Z
                } else {
                    tap_code16(LCTL(KC_Y));  // Ctrl + Y
                }
            }
            return false;
    }
    return true;
}
