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
	void DrawPlayer(uint8_t player) const;
	void DisplaySub(void) const;
	void DisplayGame(void) const;

	/* Haupt Logiken. */
	void RoundLogic(u32 hDown, u32 hHeld);
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

	/* Variablen und so. */
	std::unique_ptr<Game> currentGame = nullptr; // Der Spiel-Zeiger.
	bool isSub = false, gameOver = false, awaitFigurSelect = false;
	uint8_t subSel = 0;

	/* Unter-Menü Button Positionen. */
	const std::vector<Structs::ButtonPos> subBtn = {
		{ 90, 12, 140, 35 }, // Spiel Laden.
		{ 90, 57, 140, 35 }, // Spiel Speichern.
		{ 90, 102, 140, 35 }, // Spiel Einstellungen.
		{ 90, 147, 140, 35 }, // Sprache Ändern.
		{ 90, 192, 140, 35 } // Credits.
	};

	/*
		Haupt-Feld Positionen für die Figuren.

		Beinhaltet nur die Äußeren Felder.
	*/
	const std::vector<Structs::ButtonPos> MainField = {
		{ 92, 206, 20, 20 },
		{ 92, 187, 20, 20 },
		{ 92, 168, 20, 20 },
		{ 92, 149, 20, 20 },
		{ 92, 130, 20, 20 },

		{ 73, 130, 20, 20 },
		{ 54, 130, 20, 20 },
		{ 35, 130, 20, 20 },
		{ 16, 130, 20, 20 },

		{ 16, 111, 20, 20 },
		{ 16, 92, 20, 20 },

		{ 35, 92, 20, 20 },
		{ 54, 92, 20, 20 },
		{ 73, 92, 20, 20 },
		{ 92, 92, 20, 20 },

		{ 92, 73, 20, 20 },
		{ 92, 54, 20, 20 },
		{ 92, 35, 20, 20 },
		{ 92, 16, 20, 20 },

		{ 111, 16, 20, 20 },
		{ 130, 16, 20, 20 },

		{ 130, 35, 20, 20 },
		{ 130, 54, 20, 20 },
		{ 130, 73, 20, 20 },
		{ 130, 92, 20, 20 },

		{ 149, 92, 20, 20 },
		{ 168, 92, 20, 20 },
		{ 187, 92, 20, 20 },
		{ 206, 92, 20, 20 },

		{ 206, 111, 20, 20 },
		{ 206, 130, 20, 20 },

		{ 187, 130, 20, 20 },
		{ 168, 130, 20, 20 },
		{ 149, 130, 20, 20 },
		{ 130, 130, 20, 20 },

		{ 130, 149, 20, 20 },
		{ 130, 168, 20, 20 },
		{ 130, 187, 20, 20 },
		{ 130, 206, 20, 20 },

		{ 111, 206, 20, 20 }
	};

	/*
		Haus-Felder der Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> PlayerField = {
		{ 32, 166, 18, 18 },
		{ 56, 166, 18, 40 },
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
		{ 111, 187, 20, 20 },
		{ 111, 168, 20, 20 },
		{ 111, 149, 20, 20 },
		{ 111, 130, 20, 20 },

		{ 35, 111, 20, 20 },
		{ 54, 111, 20, 20 },
		{ 73, 111, 20, 20 },
		{ 92, 111, 20, 20 },

		{ 111, 35, 20, 20 },
		{ 111, 54, 20, 20 },
		{ 111, 73, 20, 20 },
		{ 111, 92, 20, 20 },

		{ 187, 111, 20, 20 },
		{ 168, 111, 20, 20 },
		{ 149, 111, 20, 20 },
		{ 130, 111, 20, 20 }
	};
};

#endif