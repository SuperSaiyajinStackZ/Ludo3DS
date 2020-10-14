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

#define _DICE_DELAY 10 // Die Würfel-Verzögerung.
#define _AI_ROLL_DL 60 // AI Würfel-Verzögerung.

/*
	Zeichne die Würfel-Animation vom Overlay.

	const uint8_t diceRes: Eine Referenz zum Würfel-Ergebnis.
	const bool &AI: Ob mit einem Computer gewürfelt wird.
*/
static void Draw(const uint8_t &diceRes, const bool &AI) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	GFX::Dice(diceRes, 160, 80);
	if (!AI) Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("STOP_DICE"), 390);

	C3D_FrameEnd(0);
}

/*
	Zeige das Würfel-Overlay und wiedergebe ein Würfel-Ergebnis als einen uint8_t.
*/
uint8_t Overlays::RollDiceOverlay(bool AIRoll) {
	uint8_t diceRes = CoreHelper::Würfeln(), diceDl = _DICE_DELAY, dl = _AI_ROLL_DL;
	bool doOut = false, AI = AIRoll;

	while(!doOut) {
		Draw(diceRes, AI);

		if (!AIRoll) {
			hidScanInput();
			if (hidKeysDown() & KEY_A) doOut = true;

			/* Würfel-Teil. */
			if (diceDl > 0) {
				diceDl--;

				if (diceDl == 0) {
					diceDl = _DICE_DELAY;

					if (diceRes < 6) diceRes++;
					else diceRes = 1;
				}
			}

		} else {
			/* Würfel-Teil. */
			if (diceDl > 0) {
				diceDl--;
				dl--;

				if (diceDl == 0) {
					diceDl = _DICE_DELAY;

					if (diceRes < 6) diceRes++;
					else diceRes = 1;
				}

				if (dl == 0) doOut = true;
			}
		}
	}

	return CoreHelper::Würfeln();
}