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
#include "structs.hpp"
#include <vector>

const std::vector<Structs::ButtonPos> promptBtn = {
	{ 90, 137, 140, 35 }, // Nein.
	{ 90, 92, 140, 35 } // Ja.
};

extern touchPosition touch;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

/*
	Zeige eine Prompt Nachricht an.

	const std::string &msg: Die Nachricht.
	const uint8_t p: Die Spieler-Chip Farbe.
*/
bool Msg::promptMsg(const std::string &msg, const uint8_t p) {
	bool res = true;

	while(1) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, NO_COLOR);
		C2D_TargetClear(Bottom, NO_COLOR);

		GFX::DrawBaseTop();
		Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
		GFX::DrawSet(set_msgBox_idx, 10, 33);
		Gui::DrawStringCentered(0, (240 - Gui::GetStringHeight(0.6f, msg)) / 2 - 10, 0.6f, TEXT_COLOR, msg, 370, 110);

		GFX::DrawBaseBottom();
		GFX::DrawSet(set_bottom_bg_idx, 0, 0);
		for (int i = 0; i < 2; i++) {
			GFX::DrawSet(set_button_idx, promptBtn[i].x, promptBtn[i].y);

			if (res == i) {
				GFX::DrawFigure(p, 64, promptBtn[i].y + 8);
				GFX::DrawFigure(p, 238, promptBtn[i].y + 8);
			}
		}

		Gui::DrawStringCentered(0, promptBtn[0].y + 10, 0.5f, TEXT_COLOR, Lang::get("NO"), 135);
		Gui::DrawStringCentered(0, promptBtn[1].y + 10, 0.5f, TEXT_COLOR, Lang::get("YES"), 135);

		C3D_FrameEnd(0);

		gspWaitForVBlank();
		hidScanInput();
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_UP) res = true;

		if (hidKeysDown() & KEY_DOWN) res = false;

		if (hidKeysDown() & KEY_A) return res;

		if (hidKeysDown() & KEY_TOUCH && touching(touch, promptBtn[0])) return false;
		if (hidKeysDown() & KEY_TOUCH && touching(touch, promptBtn[1])) return true;
	}
}

/*
	Zeight eine Nachricht an, welche mit A übersprungen werden kann.

	const std::string &waitMsg: Die Nachricht.
*/
void Msg::DisplayWaitMsg(const std::string &waitMsg, ...) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	C2D_TargetClear(Bottom, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	GFX::DrawSet(set_msgBox_idx, 10, 33);
	Gui::DrawStringCentered(0, (240 - Gui::GetStringHeight(0.6f, waitMsg)) / 2 - 10, 0.6f, TEXT_COLOR, waitMsg, 370, 110);
	Gui::DrawStringCentered(0, 217, 0.6f, TEXT_COLOR, Lang::get("A_CONTINUE"), 390);

	GFX::DrawBaseBottom();
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);
	C3D_FrameEnd(0);

	while(1) {
		hidScanInput();

		if ((hidKeysDown() & KEY_A) || (hidKeysDown() & KEY_TOUCH)) break;
		gspWaitForVBlank();
	}
}

/*
	Zeigt eine Nachricht an.

	const std::string &Message: Die Nachricht.
*/
void Msg::DisplayMsg(const std::string &Message) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	C2D_TargetClear(Bottom, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	GFX::DrawSet(set_msgBox_idx, 10, 33);
	Gui::DrawStringCentered(0, (240 - Gui::GetStringHeight(0.6f, Message)) / 2 - 10, 0.6f, TEXT_COLOR, Message, 370, 110);

	GFX::DrawBaseBottom();
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);
	C3D_FrameEnd(0);
}

/*
	Zeigt eine noch nicht implementierte Nachricht an.
*/
void Msg::NotImplementedYet(void) { Msg::DisplayWaitMsg(Lang::get("NOT_IMPLEMENTED_YET")); };

/*
	Zeige eine Hilfsbox an.

	const std::string &Msg: Die Nachricht.
*/
void Msg::HelperBox(const std::string &Msg) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 240, DIM_COLOR);
	GFX::DrawSet(set_msgBox_idx, 10, 33);
	Gui::DrawStringCentered(0, (240 - Gui::GetStringHeight(0.6f, Msg)) / 2 - 10, 0.6f, TEXT_COLOR, Msg, 370, 110);
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, DIM_COLOR);
	C3D_FrameEnd(0);
}