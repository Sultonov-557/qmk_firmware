/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "process_leader.h"
#include "autocorrect_data.h"

#define LEADER KC_APP

enum layers {
    _BASE,
    _GAME,
    _CS2,
    _SYM,
};

enum custom_keycodes {
    CS2_A = SAFE_RANGE,
    CS2_D,
    CS2_JT,
    CS2_BDROP,
};

static uint8_t cs2_random_delay(uint8_t min_ms, uint8_t max_ms) {
    uint8_t span = max_ms - min_ms + 1;
    return min_ms + (timer_read() % span);
}

static void cs2_random_tap_hold(uint16_t keycode, uint8_t min_ms, uint8_t max_ms) {
    register_code16(keycode);
    wait_ms(cs2_random_delay(min_ms, max_ms));
    unregister_code16(keycode);
}

static bool cs2_a_held = false;
static bool cs2_d_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CS2_A:
            if (record->event.pressed) {
                cs2_a_held = true;
                unregister_code(KC_D);
                register_code(KC_A);
            } else {
                cs2_a_held = false;
                unregister_code(KC_A);
                if (cs2_d_held) {
                    register_code(KC_D);
                } else {
                    cs2_random_tap_hold(KC_D, 80, 120);
                }
            }
            return false;
        case CS2_D:
            if (record->event.pressed) {
                cs2_d_held = true;
                unregister_code(KC_A);
                register_code(KC_D);
            } else {
                cs2_d_held = false;
                unregister_code(KC_D);
                if (cs2_a_held) {
                    register_code(KC_A);
                } else {
                    cs2_random_tap_hold(KC_A, 80, 120);
                }
            }
            return false;
        case CS2_JT:
            if (record->event.pressed) {
                tap_code(KC_SPC);
                wait_ms(15);
                tap_code(MS_BTN1);
            }
            return false;
        case CS2_BDROP:
            if (record->event.pressed) {
                tap_code(KC_5);
                wait_ms(15);
                tap_code(KC_G);
            }
            return false;
    }

    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,                               KC_F1,            KC_F2,            KC_F3,            KC_F4,  KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  QK_LOCK,  KC_PAUS,
        KC_GRV,             KC_1,             KC_2,             KC_3,             KC_4,             KC_5,   KC_6,    KC_7,     KC_8,     KC_9,   KC_0,                 KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,             KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,   KC_Y,    KC_U,     KC_I,     KC_O,   KC_P,                 KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        MT(MOD_LCTL,KC_ESC), MT(MOD_LSFT,KC_A), MT(MOD_LCTL,KC_S), MT(MOD_LGUI,KC_D), MT(MOD_LALT,KC_F), KC_G,   KC_H,    MT(MOD_RALT,KC_J), MT(MOD_RGUI,KC_K),     MT(MOD_RCTL,KC_L),     MT(MOD_RSFT,KC_SCLN),  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,             KC_X,             KC_C,             KC_V,             KC_B,   KC_N,    KC_M,     KC_COMM,  KC_DOT, KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(_SYM), KC_APP,     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_GAME] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  QK_LOCK,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        CS2_JT,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_SYM) ,KC_APP,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_CS2] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  QK_LOCK,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        CS2_JT,   CS2_A,    KC_S,     CS2_D,    KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_SYM), CS2_BDROP,KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_SYM] = LAYOUT_tkl_ansi(
        _______,            KC_BRID,  KC_BRIU,  _______,  _______,  LM_BRID,  LM_BRIU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  BL_STEP,
        _______,  KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  LM_BRIU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  MS_BTN1,  MS_BTN3,  MS_BTN2,
        KC_OSSW,  _______,  LM_BRID,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              MS_WHLL,            MS_UP,
        DF(_BASE),  DF(_GAME),  DF(_CS2),                               _______,                                _______,  _______,  MS_WHLD,    MS_WHLU,  MS_LEFT  ,  MS_DOWN,  MS_RGHT),


};
