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
	void FigureSelection(u32 hDown, u32 hHeld);
	void SubLogic(u32 hDown, u32 hHeld, touchPosition touch);

	/* Ein paar Utilities. */
	bool Play();
	void NextPHandle();
	void NextFigur();
	void PreviousFigur();
	void GetFirstAvlFigur();
	void AIHandle();

	/* Variablen und so. */
	std::unique_ptr<Game> currentGame = nullptr; // Der Spiel-Zeiger.
	bool isSub = false, gameOver = false, awaitFigurSelect = false, canContinue = false;
	uint8_t ergebnis = 0, subSel = 0, figurSelection = 0;

	/* Unter-Menü Button Positionen. */
	const std::vector<Structs::ButtonPos> subBtn = {
		{ 10, 10, 140, 40 },
		{ 10, 55, 140, 40 },
		{ 10, 100, 140, 40 },
		{ 10, 145, 140, 40 },
		{ 10, 190, 140, 40 },

		{ 170, 10, 140, 40 },
		{ 170, 55, 140, 40 },
		{ 170, 100, 140, 40 },
		{ 170, 145, 140, 40 },
		{ 170, 190, 140, 40 }
	};

	/*
		Haupt-Feld Positionen für die Figuren.

		Beinhaltet nur die Äußeren Felder.
	*/
	const std::vector<Structs::ButtonPos> MainField = {
		{ 132, 206, 20, 20 },
		{ 132, 187, 20, 20 },
		{ 132, 168, 20, 20 },
		{ 132, 149, 20, 20 },
		{ 132, 130, 20, 20 },

		{ 113, 130, 20, 20 },
		{ 94, 130, 20, 20 },
		{ 75, 130, 20, 20 },
		{ 56, 130, 20, 20 },

		{ 56, 111, 20, 20 },
		{ 56, 92, 20, 20 },

		{ 75, 92, 20, 20 },
		{ 94, 92, 20, 20 },
		{ 113, 92, 20, 20 },
		{ 132, 92, 20, 20 },

		{ 132, 73, 20, 20 },
		{ 132, 54, 20, 20 },
		{ 132, 35, 20, 20 },
		{ 132, 16, 20, 20 },

		{ 151, 16, 20, 20 },
		{ 170, 16, 20, 20 },

		{ 170, 35, 20, 20 },
		{ 170, 54, 20, 20 },
		{ 170, 73, 20, 20 },
		{ 170, 92, 20, 20 },

		{ 189, 92, 20, 20 },
		{ 208, 92, 20, 20 },
		{ 227, 92, 20, 20 },
		{ 246, 92, 20, 20 },

		{ 246, 111, 20, 20 },
		{ 246, 130, 20, 20 },

		{ 227, 130, 20, 20 },
		{ 208, 130, 20, 20 },
		{ 189, 130, 20, 20 },
		{ 170, 130, 20, 20 },

		{ 170, 149, 20, 20 },
		{ 170, 168, 20, 20 },
		{ 170, 187, 20, 20 },
		{ 170, 206, 20, 20 },

		{ 151, 206, 20, 20 }
	};

	/*
		Haus-Felder der Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> PlayerField = {
		{ 72, 166, 18, 18 },
		{ 96, 166, 18, 40 },
		{ 72, 190, 18, 18 },
		{ 96, 190, 18, 18 },

		{ 72, 32, 18, 18 },
		{ 96, 32, 18, 18 },
		{ 72, 56, 18, 18 },
		{ 96, 56, 18, 18 },

		{ 206, 32, 18, 18 },
		{ 230, 32, 18, 18 },
		{ 206, 56, 18, 18 },
		{ 230, 56, 18, 18 },

		{ 206, 166, 18, 18 },
		{ 230, 166, 18, 18 },
		{ 206, 190, 18, 18 },
		{ 230, 190, 18, 18 }
	};

	/*
		Die Eingangs-Felder Positionen für die Figuren.

		Spieler * 4.. von 0 - 3.
	*/
	const std::vector<Structs::ButtonPos> EingangField = {
		{ 151, 187, 20, 20 },
		{ 151, 168, 20, 20 },
		{ 151, 149, 20, 20 },
		{ 151, 130, 20, 20 },

		{ 75, 111, 20, 20 },
		{ 94, 111, 20, 20 },
		{ 113, 111, 20, 20 },
		{ 132, 111, 20, 20 },

		{ 151, 35, 20, 20 },
		{ 151, 54, 20, 20 },
		{ 151, 73, 20, 20 },
		{ 151, 92, 20, 20 },

		{ 227, 111, 20, 20 },
		{ 208, 111, 20, 20 },
		{ 189, 111, 20, 20 },
		{ 170, 111, 20, 20 }
	};
};

#endif