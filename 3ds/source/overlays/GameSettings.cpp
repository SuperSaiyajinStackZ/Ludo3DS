/*
	Diese Datei ist Teil von Ludo3DS.
	Copyright (C) 2020-2021 bei SuperSaiyajinStackZ.

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

extern bool touching(touchPosition touch, Structs::ButtonPos pos);

const std::vector<std::string> DESCS = { "FIGURE_AMOUNT_SCROLL", "PLAYER_AMOUNT_SCROLL", "ENABLE_COMPUTER_SCROLL", "DICE_ROLLS_SCROLL", "FIGURE_ANIMATE" };

const std::vector<Structs::ButtonPos> Positions = {
	/* Figuren. */
	{ 120, 30, 40, 40 },
	{ 165, 30, 40, 40 },
	{ 210, 30, 40, 40 },
	{ 255, 30, 40, 40 },

	/* Spieler. */
	{ 165, 100, 40, 40 },
	{ 210, 100, 40, 40 },
	{ 255, 100, 40, 40 },

	/* Computer. */
	{ 210, 170, 40, 40 },
	{ 255, 170, 40, 40 },

	/* Abbrechen und Weiter. */
	{ 4, 216, 20, 20 },
	{ 296, 216, 20, 20 },

	/* Würfel-Rolls. */
	{ 210, 30, 40, 40 },
	{ 255, 30, 40, 40 },

	/* Figuren Bewegung. */
	{ 210, 100, 40, 40 },
	{ 255, 100, 40, 40 },
};

static void DrawGameSettings(const uint8_t selectedPlayer, const uint8_t selectedFigur, const bool useAI, const bool firstPage, const bool ThreeRolls, const int descScroll, const int desc, const int scrollAM, const uint8_t index, const bool allowCancel) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 20, BAR_COLOR);
	Gui::DrawStringCentered(0, 0, 0.6f, TEXT_COLOR, Lang::get("GAME_SETTINGS"), 390);
	Gui::Draw_Rect(0, 220, 400, 20, BAR_COLOR);
	Gui::DrawString((scrollAM >= 400 ? 400 - descScroll : scrollAM - descScroll), 220, 0.6f, TEXT_COLOR, Lang::get(DESCS[desc]));

	GFX::DrawSprite(sprites_banner_idx, 72, 50);
	Gui::ScreenDraw(Bottom);
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);
	GFX::DrawSet(set_titlebar_idx, 0, 0);

	/* Erste Seite. */
	if (firstPage) {
		/* Figuren Anzahl. */
		Gui::DrawStringCentered(0, 2, 0.6f, TEXT_COLOR, Lang::get("GENERAL_SETTINGS"), 310);
		Gui::DrawString(14, Positions[0].y + 13, 0.5f, TEXT_COLOR, Lang::get("FIGURE_AMOUNT") + ": ", 102);
		GFX::DrawSet(set_figure_Amount_idx, Positions[0].x, Positions[0].y);
		GFX::DrawSet(set_selector_idx, Positions[selectedFigur - 1].x, Positions[0].y);

		/* Spieler Anzahl. */
		Gui::DrawString(14, Positions[4].y + 13, 0.5f, TEXT_COLOR, Lang::get("PLAYER_AMOUNT") + ": ", 102);
		GFX::DrawSet(set_player_Amount_idx, Positions[4].x, Positions[4].y);
		GFX::DrawSet(set_selector_idx, Positions[4 + (selectedPlayer) - 2].x, Positions[4].y);

		/* Computer. */
		Gui::DrawString(14, Positions[7].y + 13, 0.5f, TEXT_COLOR, Lang::get("ENABLE_COMPUTER") + ": ", 102);
		GFX::DrawSet(set_use_ai_idx, Positions[7].x, Positions[7].y);
		GFX::DrawSet(set_selector_idx, Positions[(useAI ? 8 : 7)].x, Positions[7].y);

	/* Zweite Seite. */
	} else {
		/* Würfel Roll Anzahl falls alle spielbaren Figuren im Haus. */
		Gui::DrawStringCentered(0, 2, 0.6f, TEXT_COLOR, Lang::get("OPTIONAL_SETTINGS"), 310);
		Gui::DrawString(14, Positions[0].y + 13, 0.5f, TEXT_COLOR, Lang::get("DICE_ROLLS") + ": ", 102);
		GFX::DrawSet(set_dice_rolls_idx, Positions[11].x, Positions[11].y);
		GFX::DrawSet(set_selector_idx, Positions[(ThreeRolls ? 12 : 11)].x, Positions[(ThreeRolls ? 12 : 11)].y);

		/* Figur Animation. */
		Gui::DrawString(14, Positions[13].y + 13, 0.5f, TEXT_COLOR, Lang::get("ANIMATE_FIGURE") + ": ", 102);
		GFX::DrawSet(set_use_ai_idx, Positions[13].x, Positions[13].y);
		GFX::DrawSet(set_selector_idx, Positions[(konfiguration->Animate() ? 14 : 13)].x, Positions[(konfiguration->Animate() ? 14 : 13)].y);
	}

	GFX::DrawSet(set_selected_idx, 6, 46 + (index * 70));
	if (allowCancel) GFX::DrawSet(set_prev_idx, Positions[9].x, Positions[9].y);
	GFX::DrawSet(set_next_idx, Positions[10].x, Positions[10].y);
	C3D_FrameEnd(0);
}

/*
	Die Spiel-Einstellungen.

	bool allowCancel: Ob die Selektion abgebrochen werden kann oder nicht.
*/
GameData Overlays::PrepareGame(bool allowCancel) {
	GameData dt = { 2, 1, false, false };
	bool firstPage = true;
	int desc = 0, descScroll = 0, scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
	uint8_t index = 0;

	while(1) {
		DrawGameSettings(dt.PAmount, dt.FAmount, dt.UseAI, firstPage, dt.ThreeRolls, descScroll, desc, scrollAMT, index, allowCancel);

		touchPosition t;
		hidScanInput();
		hidTouchRead(&t);
		uint32_t hDown = hidKeysDown();

		if (descScroll < (scrollAMT * 2)) {
			descScroll++;

			if (descScroll == (scrollAMT * 2)) descScroll = 0;
		}

		if (allowCancel) {
			if (hDown & KEY_B) return { -1, -1, false, false };
		}

		if ((hDown & KEY_R) || (hDown & KEY_L)) {
			index = 0;
			firstPage = !firstPage;

			desc = (firstPage ? 0 : 3);
			scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
			descScroll = 0;
		}

		if (hDown & KEY_DOWN) {
			if (firstPage) {
				if (index < 2) {
					index++;
					desc = index;
					scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
					descScroll = 0;
				}

			} else {
				if (index < 1) {
					index++;
					desc = 3 + index;
					scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
					descScroll = 0;
				}
			}
		}

		if (hDown & KEY_UP) {
			if (firstPage) {
				if (index > 0) {
					index--;
					desc = index;
					scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
					descScroll = 0;
				}

			} else {
				if (index > 0) {
					index--;
					desc = 3 + index;
					scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
					descScroll = 0;
				}
			}
		}

		if (hDown & KEY_LEFT) {
			if (firstPage) {
				switch(index) {
					/* Figuren Anzahl. */
					case 0:
						if (dt.FAmount > 1) dt.FAmount--;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount > 2) dt.PAmount--;
						break;

					case 2:
						/* Computer. */
						if (dt.UseAI) dt.UseAI = false;
						break;
				}

			} else {
				switch(index) {
					/* Würfel-Roll Anzahl. */
					case 0:
						if (dt.ThreeRolls) dt.ThreeRolls = false;
						break;

					/* Figuren Animation. */
					case 1:
						if (konfiguration->Animate()) konfiguration->Animate(false);
						break;
				}
			}
		}

		if (hDown & KEY_RIGHT) {
			if (firstPage) {
				switch(index) {
					/* Figuren Anzahl. */
					case 0:
						if (dt.FAmount < 4) dt.FAmount++;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount < 4) dt.PAmount++;
						break;

					case 2:
						/* Computer. */
						if (!dt.UseAI) dt.UseAI = true;
						break;
				}

			} else {
				switch(index) {
					/* Würfel-Roll Anzahl. */
					case 0:
						if (!dt.ThreeRolls) dt.ThreeRolls = true;
						break;

					/* Figuren Animation. */
					case 1:
						if (!konfiguration->Animate()) konfiguration->Animate(true);
						break;
				}
			}
		}

		if (hDown & KEY_A) {
			if (firstPage) {
				switch(index) {
					/* Figuren Anzahl. */
					case 0:
						if (dt.FAmount < 4) dt.FAmount++;
						else dt.FAmount = 1;
						break;

					case 1:
						/* Spieler Anzahl. */
						if (dt.PAmount < 4) dt.PAmount++;
						else dt.PAmount = 2;
						break;

					case 2:
						/* Computer. */
						dt.UseAI = !dt.UseAI;
						break;
				}

			} else {
				switch(index) {
					/* Würfel-Roll Anzahl. */
					case 0:
						dt.ThreeRolls = !dt.ThreeRolls;
						break;

					/* Figuren Animation. */
					case 1:
						konfiguration->Animate(!konfiguration->Animate());
						break;
				}
			}
		}

		if (hDown & KEY_TOUCH) {
			if (allowCancel) {
				if (touching(t, Positions[9])) return { -1, -1, false, false };
			}

			if (touching(t, Positions[10])) break;

			if (firstPage) {
				bool didTouch = false;
				/* Figuren Anzahl. */
				for (uint8_t i = 0; i < 4; i++) {
					if (touching(t, Positions[i])) {
						dt.FAmount = i + 1;
						didTouch = true;

						index = 0;
						desc = 0;
						scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
						descScroll = 0;
						break;
					}
				}

				if (!didTouch) {
					/* Spieler Anzahl. */
					for (uint8_t i = 0; i < 3; i++) {
						if (touching(t, Positions[4 + i])) {
							dt.PAmount = i + 2;
							didTouch = true;

							index = 1;
							desc = 1;
							scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
							descScroll = 0;
							break;
						}
					}
				}

				if (!didTouch) {
					/* Computer. */
					for (uint8_t i = 0; i < 2; i++) {
						if (touching(t, Positions[7 + i])) {
							dt.UseAI = i;

							index = 2;
							desc = 2;
							scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
							descScroll = 0;
							break;
						}
					}
				}

			} else {
				bool didTouch = false;

				/* Würfel-Roll Anzahl. */
				for (uint8_t i = 0; i < 2; i++) {
					if (touching(t, Positions[11 + i])) {
						didTouch = true;
						dt.ThreeRolls = i;

						index = 0;
						desc = 3;
						scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
						descScroll = 0;
						break;
					}
				}

				if (!didTouch) {
					/* Figuren Animation. */
					for (uint8_t i = 0; i < 3; i++) {
						if (touching(t, Positions[13 + i])) {
							konfiguration->Animate(i);

							index = 1;
							desc = 4;
							scrollAMT = Gui::GetStringWidth(0.6f, Lang::get(DESCS[desc]));
							descScroll = 0;
							break;
						}
					}
				}
			}
		}

		if (hDown & KEY_START) break;
	}

	return dt;
}