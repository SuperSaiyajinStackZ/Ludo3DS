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

#ifndef _LUDO3DS_GAME_HPP
#define _LUDO3DS_GAME_HPP

#include "coreHelper.hpp"
#include "player.hpp"

#define _GAME_CURRENT_PLAYER	0x0
#define _GAME_PLAYER_AMOUNT		0x1
#define _GAME_FIGUR_AMOUNT		0x2

#define _GAME_FIGUR_SIZE		0x2 // 0x0 -> Position, 0x1 -> ob fertig. 0x2 pro Figur.
#define _GAME_PLAYER_SIZE		_GAME_FIGUR_SIZE * 4 // Jeweils 4 Figuren, was 0x8 entspricht.

#define _GAME_PLAYER_1			0x3 // 0x3 - 0xA.
#define _GAME_PLAYER_2			0xB // 0xB - 0x12.
#define _GAME_PLAYER_3			0x13 // 0x13 - 0x1A.
#define _GAME_PLAYER_4			0x1B // 0x1B - 0x22.

#define _GAME_DICE_ROLL			0x23
#define _GAME_AVL_DICE_ROLL		0x24
#define _GAME_SIZE				0x25 // 0x25 --> 37 byte.

#define _GAME_DATA_FILE "sdmc:/3ds/Ludo3DS/GameData.dat"

/*
	Spiel-Daten Struktur.

	0x0: Aktueller Spieler.
	0x1: Spieler-Anzahl.
	0x2: Figuren-Anzahl.

	- Eine Figur ist 0x2 groß. 0x0 ist die Position, während 0x1 beinhaltet, ob sie fertig ist.
	- Ein Spieler besitzt 4 solcher Figuren, egal ob sie benutzt wird oder nicht.
	- Es gibt 4 Spieler in der Spiel-Datei. Egal ob benutzt oder nicht.

	0x3 - 0xA: Spieler 1.
	0xB - 0x12: Spieler 2.
	0x13 - 0x1A: Spieler 3.
	0x1B - 0x22: Spieler 4.
	0x23 - 0x23: Die Würfel-Roll Anzahl.
	0x24 - 0x24: Die verbleibende Würfel-Roll Anzahl.

	- Die Größe der Spiel-Datei ist 0x25, was 37 byte entspricht.
*/

class Game {
public:
	Game(uint8_t playerAmount = 2, uint8_t figurAmount = 2, uint8_t diceRolls = 1);
	~Game() { };

	/* Spiel-Utilities. */
	void InitNewGame(uint8_t playerAmount = 2, uint8_t figurAmount = 2, uint8_t diceRolls = 1);
	void LoadGameFromFile(); // Lade die Spiel-Daten von der Datei.
	void convertDataToGame(); // Konvertiere die Spiel-Daten zu einem Spiel.
	void SaveConversion(); // Konvertiere das aktuelle Spiel zu einem Buffer.
	void SaveToFile(bool update = true); // Konvertiere wenn true und schreibe zur Datei.

	/* Wiedergebe die Spieler-Anzahl und Figuren-Anzahl. */
	uint8_t GetPlayerAmount() const { return this->PlayerAmount; };
	uint8_t GetFigurAmount() const { return this->FigurAmount; };

	/* Wiedergebe und Setze, die Position einer Figur. */
	uint8_t GetPosition(uint8_t player, uint8_t figur) const;
	void SetPosition(uint8_t player, uint8_t figur, uint8_t position);

	/* Wiedergebe und Setze, ob eine Figur schon am Ziel ist. */
	bool GetDone(uint8_t player, uint8_t figur) const;
	void SetDone(uint8_t player, uint8_t figur, bool isDone);

	/* Wiedergebe und Setze den Aktuellen Spieler. */
	uint8_t GetCurrentPlayer() const { return this->CurrentPlayer; };
	void SetCurrentPlayer(uint8_t p) { this->CurrentPlayer = p; };

	/* Wiedergebe ob das Spiel gültig ist. */
	bool validLoaded() const { return this->ValidGame; };

	/* Computer part. */
	bool GetAI() const { return this->UseAI; };
	void SetAI(bool AI) { this->UseAI = AI; };

	/* Ergebnis part. */
	uint8_t GetErgebnis() const { return this->Ergebnis; };
	void SetErgebnis(uint8_t v) { this->Ergebnis = v; };

	/* Kann Fortfahren part. */
	bool GetCanContinue() const { return this->CanContinue; };
	void SetCanContinue(bool v) { this->CanContinue = v; };

	/* Ausgewählte Figur part. */
	uint8_t GetSelectedFigur() const { return this->SelectedFigur; };
	void SetSelectedFigur(uint8_t v) { this->SelectedFigur = v; };

	/* Würfel-Roll Anzahl. */
	uint8_t GetDiceRolls() const { return this->DiceRolls; };
	void SetDiceRolls(uint8_t rolls) { this->DiceRolls = rolls; };

	/* Verbleibende Würfel-Roll Anzahl. */
	uint8_t GetAVLDiceRolls() const { return this->AVLDiceRolls; };
	void SetAVLDiceRolls(uint8_t rolls) { this->AVLDiceRolls = rolls; };
private:
	std::unique_ptr<Player> Players[4];

	/*
		Variablen für das Spiel.
	*/
	uint8_t CurrentPlayer = 0, FigurAmount = 1, PlayerAmount = 2, Ergebnis = 0,
			SelectedFigur = 0, DiceRolls = 1, AVLDiceRolls = 0;
	bool ValidGame = false, UseAI = false, CanContinue = false;

	std::unique_ptr<uint8_t[]> GameData = nullptr; // Spiel-Daten Buffer.
};

#endif