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
#include "kbd.hpp"

/*
	Lasse eine Eingabe vom System-Keyboard wiedergeben.

	int maxValue: Die Maximale anzahl, welche erlaubt ist.
	std::string Text: Der Text, welcher angezeigt werden soll.
	int oldVal: Alter Wert.
*/
int KBD::SetAmount(int maxValue, std::string Text, int oldVal) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 70, 400, 110, BOX_COLOR);
	Gui::DrawStringCentered(0, (240 - Gui::GetStringHeight(0.7f, Text)) / 2 - 10, 0.7f, TEXT_COLOR, Text, 390, 90);
	C3D_FrameEnd(0);

	SwkbdState state;
	swkbdInit(&state, SWKBD_TYPE_NUMPAD, 2, 3);
	swkbdSetFeatures(&state, SWKBD_FIXED_WIDTH);
	swkbdSetValidation(&state, SWKBD_NOTBLANK_NOTEMPTY, 0, 0);
	char input[4]   = {0};
	SwkbdButton ret = swkbdInputText(&state, input, sizeof(input));
	input[3] = '\0';

	return (ret == SWKBD_BUTTON_CONFIRM ? (int)std::min(std::stoi(input), maxValue) : oldVal);
}