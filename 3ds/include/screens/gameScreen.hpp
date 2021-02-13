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

#ifndef _LUDO3DS_GAME_SCREEN_HPP
#define _LUDO3DS_GAME_SCREEN_HPP

#include "common.hpp"
#include "game.hpp"
#include "structs.hpp"
#include <vector>

class GameScreen : public Screen {
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	GameScreen();
private:
	/* Alle Zeichnungen. */
	void DrawPlayers() const;
	void DrawSelection(uint8_t selection) const;
	void DrawPlayer(uint8_t player, bool doesAnim = false) const;
	void DisplaySub(void) const;
	void DisplayGame(void) const;

	/* Haupt Logiken. */
	void RoundLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void FigureSelection(u32 hDown, u32 hHeld, touchPosition touch);
	void SubLogic(u32 hDown, u32 hHeld, touchPosition touch);

	/* Ein paar Utilities. */
	bool Play();
	void NextPHandle();
	void NextFigur();
	void PreviousFigur();
	void GetFirstAvlFigur();
	void AIHandle();
	Structs::ButtonPos GetFigurTouchIndex(uint8_t player, uint8_t figur) const;

	/* Animation. */
	void FigurMovement(uint8_t player, uint8_t figur, uint8_t movement);

	/* Variablen und so. */
	std::unique_ptr<Game> currentGame = nullptr; // Der Spiel-Zeiger.
	bool isSub = false, gameOver = false, awaitFigurSelect = false, shouldMove = false;
	uint8_t subSel = 0;

	uint16_t xPos = 0, yPos = 0; // Für die Animation.

	/* Unter-Menü Button Positionen. */
	const std::vector<Structs::ButtonPos> subBtn = {
		{ 90, 12, 140, 35 }, // Spiel Laden.
		{ 90, 57, 140, 35 }, // Spiel Speichern.
		{ 90, 102, 140, 35 }, // Spiel Einstellungen.
		{ 90, 147, 140, 35 }, // Sprache Ändern.
		{ 90, 192, 140, 35 }, // Credits.
		{ 246, 29, 48, 48 } // WürfelIcon.
	};

	/*
		Haupt-Feld Positionen für die Figuren.

		Beinhaltet nur die Äußeren Felder.
	*/
	const std::vector<Structs::ButtonPos> MainField = {
		{ 92, 206, 18, 18 },
		{ 92, 187, 18, 18 },
		{ 92, 168, 18, 18 },
		{ 92, 149, 18, 18 },
		{ 92, 130, 18, 18 },

		{ 73, 130, 18, 18 },
		{ 54, 130, 18, 18 },
		{ 35, 130, 18, 18 },
		{ 16, 130, 18, 18 },

		{ 16, 111, 18, 18 },
		{ 16, 92, 18, 18 },

		{ 35, 92, 18, 18 },
		{ 54, 92, 18, 18 },
		{ 73, 92, 18, 18 },
		{ 92, 92, 18, 18 },

		{ 92, 73, 18, 18 },
		{ 92, 54, 18, 18 },
		{ 92, 35, 18, 18 },
		{ 92, 16, 18, 18 },

		{ 111, 16, 18, 18 },
		{ 130, 16, 18, 18 },

		{ 130, 35, 18, 18 },
		{ 130, 54, 18, 18 },
		{ 130, 73, 18, 18 },
		{ 130, 92, 18, 18 },

		{ 149, 92, 18, 18 },
		{ 168, 92, 18, 18 },
		{ 187, 92, 18, 18 },
		{ 206, 92, 18, 18 },

		{ 206, 111, 18, 18 },
		{ 206, 130, 18, 18 },

		{ 187, 130, 18, 18 },
		{ 168, 130, 18, 18 },
		{ 149, 130, 18, 18 },
		{ 130, 130, 18, 18 },

		{ 130, 149, 18, 18 },
		{ 130, 168, 18, 18 },
		{ 130, 187, 18, 18 },
		{ 130, 206, 18, 18 },

		{ 111, 206, 18, 18 }
	};

	/*
		Haus-Felder der Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> PlayerField = {
		{ 32, 166, 18, 18 },
		{ 56, 166, 18, 18 },
		{ 32, 190, 18, 18 },
		{ 56, 190, 18, 18 },

		{ 32, 32, 18, 18 },
		{ 56, 32, 18, 18 },
		{ 32, 56, 18, 18 },
		{ 56, 56, 18, 18 },

		{ 166, 32, 18, 18 },
		{ 190, 32, 18, 18 },
		{ 166, 56, 18, 18 },
		{ 190, 56, 18, 18 },

		{ 166, 166, 18, 18 },
		{ 190, 166, 18, 18 },
		{ 166, 190, 18, 18 },
		{ 190, 190, 18, 18 }
	};

	/*
		Die Eingangs-Felder Positionen für die Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> EingangField = {
		{ 111, 187, 18, 18 },
		{ 111, 168, 18, 18 },
		{ 111, 149, 18, 18 },
		{ 111, 130, 18, 18 },

		{ 35, 111, 18, 18 },
		{ 54, 111, 18, 18 },
		{ 73, 111, 18, 18 },
		{ 92, 111, 18, 18 },

		{ 111, 35, 18, 18 },
		{ 111, 54, 18, 18 },
		{ 111, 73, 18, 18 },
		{ 111, 92, 18, 18 },

		{ 187, 111, 18, 18 },
		{ 168, 111, 18, 18 },
		{ 149, 111, 18, 18 },
		{ 130, 111, 18, 18 }
	};
};

#endif