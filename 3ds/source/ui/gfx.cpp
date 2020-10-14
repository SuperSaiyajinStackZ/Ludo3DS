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

#include "gfx.hpp"

extern C2D_SpriteSheet sprites;

/*
	Zeichne eine basis für den Top Screen.
*/
void GFX::DrawBaseTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 240, BG_COLOR);
}

/*
	Zeichne eine basis für den Touch Screen.
*/
void GFX::DrawBaseBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, BG_COLOR);
}

/*
	Zeichne einen Sprite von der sprites spritesheet.

	int index: Der index des Sprites.
	int x: Die X Position des Sprites.
	int y: Die Y Position des Sprites.
	float ScaleX: Breiten-Skalierung.
	float ScaleY: Höhen-Skalierung.
*/
void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}

/*
	Zeichne einem Spieler seine Figur.

	uint8_t player: Der Spieler-Index.
	int x: Die X Position der Figur.
	int y: Die Y Position der Figur.
*/
void GFX::DrawPlayer(uint8_t player, int x, int y) {
	GFX::DrawSprite(sprites_chip_p1_idx + player, x, y);
}

/*
	Wiedergebe die Selektor Farbe eines Spielers für den Spieler-Selektor.

	uint8_t player: Der Spieler.
*/
static uint32_t GetColor(uint8_t player) {
	switch(player) {
		case 0:
			return SELECTOR_P1;

		case 1:
			return SELECTOR_P2;

		case 2:
			return SELECTOR_P3;

		case 3:
			return SELECTOR_P4;
	}

	return NO_COLOR;
}

/*
	Zeichne den animierten Selektor für die Figur.

	uint8_t player: Der Spieler-Index.
	int x: Die X Position des Selektors.
	int y: Die Y Position des Selektors.
*/
void GFX::DrawPlayerSelector(uint8_t player, int x, int y) {
	static float timer					= 0.0f;
	const float highlight_multiplier	= fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	const u8 r							= GetColor(player) & 0xFF;
	const u8 g							= (GetColor(player) >> 8) & 0xFF;
	const u8 b							= (GetColor(player) >> 16) & 0xFF;
	const u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);

	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);

	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_chip_selector_idx), x, y, 0.5f, &tint, 1, 1);
	timer += .030;
}

/*
	Zeichne den Würfel.

	uint8_t ergebnis: Das Würfel-Ergebnis. 1 - 6 sind gültig.
	int x: Die X Position des Würfels.
	int y: Die Y Position des Würfels.
*/
void GFX::Dice(uint8_t ergebnis, int x, int y) {
	switch(ergebnis) {
		case 1:
			GFX::DrawSprite(sprites_dice_1_idx, x, y);
			break;

		case 2:
			GFX::DrawSprite(sprites_dice_2_idx, x, y);
			break;

		case 3:
			GFX::DrawSprite(sprites_dice_3_idx, x, y);
			break;

		case 4:
			GFX::DrawSprite(sprites_dice_4_idx, x, y);
			break;

		case 5:
			GFX::DrawSprite(sprites_dice_5_idx, x, y);
			break;

		case 6:
			GFX::DrawSprite(sprites_dice_6_idx, x, y);
			break;
	}
}