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

static void Draw(const uint16_t xPos, const uint16_t yPos, const uint8_t diceRes, const bool shine, const uint8_t fade) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	C2D_TargetClear(Bottom, NO_COLOR);
	Gui::ScreenDraw(Top);

	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(132, 60, 0, 255));
	GFX::DrawField(75, 15);
	GFX::Dice(diceRes, 300, 80);

	GFX::DrawFigure(0, xPos, yPos);
	GFX::DrawFigure(1, 133, 111);
	GFX::DrawFigure(2, 171, 54);
	GFX::DrawFigure(3, 247, 111);
	if (shine) GFX::DrawPlayerSelector(0, xPos, yPos);

	if (fade > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fade));

	GFX::DrawBaseBottom();
	if (!shine) GFX::DrawSprite(sprites_universal_core_idx, 0, 26);
	else GFX::DrawSprite(sprites_Ludo3DS_idx, 63, 35);
	if (fade > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fade));
	C3D_FrameEnd(0);
}

void Overlays::SplashOverlay() {
	bool doOut = false, firstX = true, shine = false, doDice = true;

	uint8_t xTODO = 19, yTODO = 19 * 4, diceRes = 1, fade = 252;
	uint16_t xPos = 190, yPos = 206, shineDelay = 100;

	while(!doOut) {
		/* Fade in effekt. */
		if (fade > 0) {
			fade -= 6;

			if (fade <= 0) fade = 0;
		}

		Draw(xPos, yPos, diceRes, shine, fade);
		hidScanInput();
		if (hidKeysDown()) doOut = true;


		if (!fade && doDice) {
			if (diceRes < 5) {
				for (int i = 0; i < 15; i++) { gspWaitForVBlank(); };
				diceRes++;

				if (diceRes == 5) doDice = false;
			}
		}

		if (!fade && !doDice && firstX) {
			if (xTODO > 0) {
				for (int i = 0; i < 1; i++) { gspWaitForVBlank(); };
				xPos--;
				xTODO--;

				if (xTODO == 0) firstX = false;
			}
		}

		if (!fade && !doDice && !firstX) {
			if (yTODO > 0) {
				for (int i = 0; i < 1; i++) { gspWaitForVBlank(); };
				yTODO--;
				yPos--;

				if (yTODO == 0) shine = true;
			}
		}

		if (shine) {
			if (shineDelay > 0) {
				for (int i = 0; i < 2; i++) { gspWaitForVBlank(); };
				shineDelay--;

				if (shineDelay == 0) doOut = true;
			}
		}
	}
}