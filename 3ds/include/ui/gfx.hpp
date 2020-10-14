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

#ifndef _LUDO3DS_GFX_HPP
#define _LUDO3DS_GFX_HPP

#include "common.hpp"
#include "coreHelper.hpp"
#include "sprites.h"
#include <citro2d.h>

/* Definiere die Farben hier. */
#define TEXT_COLOR C2D_Color32(255, 255, 255, 255) // Text Farbe.
#define BAR_COLOR C2D_Color32(140, 80, 30, 255) // Balken Farbe.
#define BG_COLOR C2D_Color32(118, 62, 9, 255) // Hintergrund Farbe.
#define BOX_COLOR C2D_Color32(130, 70, 20, 255) // TextBox Farbe.

#define BUTTON_SELECTED C2D_Color32(160, 100, 50, 255) // Ausgewählte Schaltflächen Farbe.
#define BUTTON_UNSELECTED C2D_Color32(160, 100, 50, 255) // Nicht Ausgewählte Schaltflächen Farbe.

#define DIM_COLOR C2D_Color32(0, 0, 0, 170) // Gedunkelter Bildschirm Farbe.
#define NO_COLOR C2D_Color32(0, 0, 0, 0) // Transparente Farbe.

#define SELECTOR_P1 C2D_Color32(255, 0, 0, 255) // Spieler 1 Selektor Farbe.
#define SELECTOR_P2 C2D_Color32(0, 132, 255, 255) // Spieler 2 Selektor Farbe.
#define SELECTOR_P3 C2D_Color32(255, 211, 0, 255) // Spieler 3 Selektor Farbe.
#define SELECTOR_P4 C2D_Color32(0, 255, 138, 255) // Spieler 4 Selektor Farbe.

namespace GFX {
	/* Basiszeug. */
	void DrawBaseTop();
	void DrawBaseBottom();

	/* Spritezeug. */
	void DrawSprite(int index, int x, int y, float ScaleX = 1, float ScaleY = 1);

	void DrawFigure(uint8_t player, int x, int y);
	void DrawPlayerSelector(uint8_t player, int x, int y);

	void Dice(uint8_t ergebnis, int x, int y);
};

#endif