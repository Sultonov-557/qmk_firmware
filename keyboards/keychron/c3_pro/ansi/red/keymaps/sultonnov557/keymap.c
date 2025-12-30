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


enum layers{
    _BASE,
    _GAME,
    _SYM,
};

void leader_end_user(void) {
    // --- ADD / COMMIT ---
    if (leader_sequence_two_keys(KC_G, KC_A)) {
        SEND_STRING("git add .");
    }
    else if (leader_sequence_two_keys(KC_G, KC_C)) {
        SEND_STRING("git commit -m \"\"");
        SEND_STRING(SS_TAP(X_LEFT));
    }

    // --- PUSH / PULL / FETCH ---
    else if (leader_sequence_two_keys(KC_G, KC_P)) {
        SEND_STRING("git push");
    }
    else if (leader_sequence_two_keys(KC_G, KC_U)) {
        SEND_STRING("git pull");
    }
    else if (leader_sequence_two_keys(KC_G, KC_F)) {
        SEND_STRING("git fetch");
    }

        // --- BUN ---
    else if (leader_sequence_two_keys(KC_B, KC_I)) {
        SEND_STRING("bun install");
    }
    else if (leader_sequence_two_keys(KC_B, KC_A)) {
        SEND_STRING("bun add ");
    }
    else if (leader_sequence_two_keys(KC_B, KC_R)) {
        SEND_STRING("bun run ");
    }
    else if (leader_sequence_two_keys(KC_B, KC_D)) {
        SEND_STRING("bun dev");
    }
    else if (leader_sequence_two_keys(KC_B, KC_U)) {
        SEND_STRING("bun upgrade\n");
    }
    else if (leader_sequence_two_keys(KC_B, KC_X)) {
        SEND_STRING("bunx ");
    }
    else if (leader_sequence_two_keys(KC_B, KC_C)) {
        SEND_STRING("bun create ");
    }

        // --- DOCKER ---
    else if (leader_sequence_two_keys(KC_D, KC_P)) {
        SEND_STRING("docker ps");
    }
    else if (leader_sequence_two_keys(KC_D, KC_A)) {
        SEND_STRING("docker ps -a");
    }
    else if (leader_sequence_two_keys(KC_D, KC_I)) {
        SEND_STRING("docker images");
    }
    else if (leader_sequence_two_keys(KC_D, KC_B)) {
        SEND_STRING("docker build .");
    }
    else if (leader_sequence_two_keys(KC_D, KC_R)) {
        SEND_STRING("docker run ");
    }
    else if (leader_sequence_two_keys(KC_D, KC_S)) {
        SEND_STRING("docker stop ");
    }
    else if (leader_sequence_two_keys(KC_D, KC_K)) {
        SEND_STRING("docker kill ");
    }
    else if (leader_sequence_two_keys(KC_D, KC_L)) {
        SEND_STRING("docker logs ");
    }
    else if (leader_sequence_two_keys(KC_D, KC_E)) {
        SEND_STRING("docker exec -it ");
    }

    // --- DOCKER COMPOSE ---
    else if (leader_sequence_two_keys(KC_D, KC_C)) {
        SEND_STRING("docker compose up");
    }
    else if (leader_sequence_two_keys(KC_D, KC_D)) {
        SEND_STRING("docker compose down");
    }
    else if (leader_sequence_two_keys(KC_D, KC_U)) {
        SEND_STRING("docker compose up -d");
    }

}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,                               KC_F1,            KC_F2,            KC_F3,            KC_F4,  KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  QK_LOCK,  KC_PAUS,
        KC_GRV,             KC_1,             KC_2,             KC_3,             KC_4,             KC_5,   KC_6,    KC_7,     KC_8,     KC_9,   KC_0,                 KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,             KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,   KC_Y,    KC_U,     KC_I,     KC_O,   KC_P,                 KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        MT(MOD_LCTL,KC_ESC), MT(MOD_LSFT,KC_A), MT(MOD_LCTL,KC_S), MT(MOD_LGUI,KC_D), MT(MOD_LALT,KC_F), KC_G,   KC_H,    MT(MOD_RALT,KC_J), MT(MOD_RGUI,KC_K),     MT(MOD_RCTL,KC_L),     MT(MOD_RSFT,KC_SCLN),  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,             KC_X,             KC_C,             KC_V,             KC_B,   KC_N,    KC_M,     KC_COMM,  KC_DOT, KC_SLSH,              KC_BSPC,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(_SYM), QK_LEAD,     KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_GAME] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  QK_LOCK,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_SYM) ,KC_APP,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_SYM] = LAYOUT_tkl_ansi(
        _______,            KC_BRID,  KC_BRIU,  _______,  _______,  LM_BRID,  LM_BRIU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  BL_STEP,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        BL_TOGG,  BL_STEP,  LM_BRIU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  MS_BTN1,  MS_BTN3,  MS_BTN2,
        KC_OSSW,  _______,  LM_BRID,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              MS_WHLR,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              MS_WHLL,            MS_UP,
        DF(_BASE),  DF(_GAME),  _______,                                _______,                                _______,  _______,  MS_WHLD,    MS_WHLU,  MS_LEFT  ,  MS_DOWN,  MS_RGHT),

};

