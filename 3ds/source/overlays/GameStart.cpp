/*
	Diese Datei ist Teil von Ludo3DS.
	Copyright (C) 2020 bei SuperSaiyajinStackZ.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Additional Terms 7.b and 7.c of GPLv3 apply to this file:
		* Requiring preservation of specified reasonable legal notices or
		  author attributions in that material or in the Appropriate Legal
		  Notices displayed by works containing it.
		* Prohibiting misrepresentation of the origin of that material,
		  or requiring that modified versions of such material be marked in
		  reasonable ways as different from the original version.
*/

#include "common.hpp"
#include "overlay.hpp"
#include "structs.hpp"

static int bPos = 50;
static bool goUp = true;
extern bool touching(touchPosition touch, Structs::ButtonPos pos);

const std::vector<Structs::ButtonPos> Positions = {
	/* Figuren. */
	{ 120, 25, 40, 40 },
	{ 165, 25, 40, 40 },
	{ 210, 25, 40, 40 },
	{ 255, 25, 40, 40 },

	/* Spieler. */
	{ 165, 95, 40, 40 },
	{ 210, 95, 40, 40 },
	{ 255, 95, 40, 40 },

	/* Computer. */
	{ 210, 165, 40, 40 },
	{ 255, 165, 40, 40 },

	/* Abbrechen und Weiter. */
	{ 4, 216, 20, 20 },
	{ 296, 216, 20, 20 }
};

static void DrawGameStart(const uint8_t selectedPlayer, const uint8_t selectedFigur, const bool useAI, bool allowCancel) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 20, BAR_COLOR);
	Gui::DrawStringCentered(0, 0, 0.6f, TEXT_COLOR, Lang::get("GAME_SETTINGS"), 390);

	GFX::DrawSprite(sprites_banner_idx, 72, bPos);
	Gui::ScreenDraw(Bottom);
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);

	Gui::DrawString(10, Positions[0].y + 13, 0.5f, TEXT_COLOR, Lang::get("FIGURE_AMOUNT") + ": ", 105);
	GFX::DrawSet(set_figure_Amount_idx, Positions[0].x, Positions[0].y);
	GFX::DrawSet(set_selector_idx, Positions[selectedFigur - 1].x, Positions[0].y);

	Gui::DrawString(10, Positions[4].y + 13, 0.5f, TEXT_COLOR, Lang::get("PLAYER_AMOUNT") + ": ", 105);
	GFX::DrawSet(set_player_Amount_idx, Positions[4].x, Positions[4].y);
	GFX::DrawSet(set_selector_idx, Positions[4 + (selectedPlayer) - 2].x, Positions[4].y);

	Gui::DrawString(10, Positions[7].y + 13, 0.5f, TEXT_COLOR, Lang::get("ENABLE_COMPUTER") + ": ", 105);
	GFX::DrawSet(set_use_ai_idx, Positions[7].x, Positions[7].y);
	GFX::DrawSet(set_selector_idx, Positions[(useAI ? 8 : 7)].x, Positions[7].y);

	if (allowCancel) GFX::DrawSet(set_prev_idx, Positions[9].x, Positions[9].y);
	GFX::DrawSet(set_next_idx, Positions[10].x, Positions[10].y);
	C3D_FrameEnd(0);
}

/*
	GameStart.. aber auch bekannt als "Spiel-Einstellungen".

	bool allowCancel: Ob die Selektion abgebrochen werden kann oder nicht.
*/
GameData Overlays::PrepareGame(bool allowCancel) {
	GameData dt = { 2, 1, false };
	bPos = 50;
	goUp = true;

	while(1) {
		DrawGameStart(dt.pAmount, dt.fAmount, dt.useAI, allowCancel);

		touchPosition t;
		hidScanInput();
		hidTouchRead(&t);
		uint32_t hDown = hidKeysDown();

		/* Banner auf und ab. */
		if (goUp) {
			if (bPos > 30) {
				bPos--;

				if (bPos == 30) goUp = false;
			}
		}

		if (!goUp) {
			if (bPos < 110) {
				bPos++;

				if (bPos == 110) goUp = true;
			}
		}

		if (allowCancel) {
			if (hDown & KEY_B) return { -1, -1, false };
		}

		if (hDown & KEY_TOUCH) {
			if (allowCancel) {
				if (touching(t, Positions[9])) return { -1, -1, false };
			}

			if (touching(t, Positions[10])) break;

			bool didTouch = false;
			for (uint8_t i = 0; i < 4; i++) {
				if (touching(t, Positions[i])) {
					dt.fAmount = i + 1;
					didTouch = true;
					break;
				}
			}

			if (!didTouch) {
				for (uint8_t i = 0; i < 3; i++) {
					if (touching(t, Positions[4 + i])) {
						dt.pAmount = i + 2;
						didTouch = true;
						break;
					}
				}
			}

			if (!didTouch) {
				for (uint8_t i = 0; i < 2; i++) {
					if (touching(t, Positions[7 + i])) {
						dt.useAI = i;
						break;
					}
				}
			}
		}

		if (hDown & KEY_START) break;
	}

	return dt;
}