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

extern bool touching(touchPosition touch, Structs::ButtonPos button);
const std::vector<Structs::ButtonPos> langBlocks = {
	{ 37, 32, 18, 18 },
	{ 37, 72, 18, 18 },
	{ 37, 112, 18, 18 },
	{ 37, 152, 18, 18 },
	{ 37, 188, 18, 18 },
	{ 177, 32, 18, 18 },
	{ 177, 72, 18, 18 },
	{ 177, 112, 18, 18 },
	{ 177, 152, 18, 18 },
	{ 177, 188, 18, 18 }
};

/*
	Zeichne das Sprachen-Auswahl Overlay.

	const uint8_t sltLang: Die aktuelle ausgewählte Sprache.
*/
static void Draw(const uint8_t sltLang) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	C2D_TargetClear(Bottom, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("SELECT_LANG"));

	GFX::DrawBaseBottom();
	Gui::Draw_Rect(0, 0, 320, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 320, 25, BAR_COLOR);

	uint8_t clrIndex = 0;
	for (uint8_t language = 0; language < 2; language++) {
		if (clrIndex < 4) clrIndex++;
		else clrIndex = 1;

		GFX::DrawSet(set_chip_1_idx + (clrIndex - 1), langBlocks[language].x, langBlocks[language].y);
		if (sltLang == language) GFX::DrawSet(set_chip_selector_idx, langBlocks[language].x, langBlocks[language].y);
	}

	Gui::DrawString(langBlocks[0].x + 25, langBlocks[0].y - 2, 0.7f, TEXT_COLOR, "Deutsch", 320);
	Gui::DrawString(langBlocks[1].x + 25, langBlocks[1].y - 2, 0.7f, TEXT_COLOR, "English", 320);
	C3D_FrameEnd(0);
}

/* Zeige das Sprach-Auswahl Overlay. */
void Overlays::LanguageOverlay() {
	uint8_t selectedLang = 0;
	bool doOut = false;

	while(!doOut) {
		Draw(selectedLang);

		hidScanInput();
		touchPosition touch;
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_DOWN) {
			if (selectedLang < 1) selectedLang++;
		}

		if (hidKeysDown() & KEY_UP) {
			if (selectedLang > 0) selectedLang--;
		}

		if (hidKeysDown() & KEY_TOUCH) {
			for (uint8_t i = 0; i < 2; i++) {
				if (touching(touch, langBlocks[i])) {
					konfiguration->Language(i);
					Lang::load(konfiguration->Language());
					doOut = true;
					break;
				}
			}
		}

		if (hidKeysDown() & KEY_A) {
			konfiguration->Language(selectedLang);
			Lang::load(konfiguration->Language());
			doOut = true;
		}

		if (hidKeysDown() & KEY_B) doOut = true;
	}
}