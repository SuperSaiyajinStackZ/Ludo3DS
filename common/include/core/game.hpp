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

#define _GAME_FIGUR_SIZE		0x3 // 0x0 -> Position, 0x1 -> Ob Benutzt, 0x2 ob fertig. 0x3 pro Figur.
#define _GAME_PLAYER_SIZE		_GAME_FIGUR_SIZE * 4 // Jeweils 4 Figuren, was 0xC entspricht.

#define _GAME_PLAYER_1			0x3 // 0x3 - 0xE.
#define _GAME_PLAYER_2			0xF // 0xF - 0x1A.
#define _GAME_PLAYER_3			0x1B // 0x1B - 0x26.
#define _GAME_PLAYER_4			0x27 // 0x27 - 0x32.

#define _GAME_SIZE				0x33 // 0x33 --> 51 byte.

#define _GAME_DATA_FILE "sdmc:/3ds/Ludo3DS/GameData.dat"

/*
	Spiel-Daten Struktur.

	0x0: Aktueller Spieler.
	0x1: Spieler-Anzahl.
	0x2: Figuren-Anzahl.

	- Eine Figur ist 0x3 groß. 0x0 ist die Position, während 0x1 beinhaltet, ob sie benutzt wird und 0x2 ob sie fertig ist.
	- Ein Spieler besitzt 4 solcher Figuren, egal ob sie benutzt wird oder nicht.
	- Es gibt 4 Spieler in der Spiel-Datei. Egal ob benutzt oder nicht.

	0x3 - 0xE: Spieler 1.
	0xF - 0x1A: Spieler 2.
	0x1B - 0x26: Spieler 3.
	0x27 - 0x32: Spieler 4.

	- Die Größe der Spiel-Datei ist 0x33, was 51 byte entspricht.
*/

class Game {
public:
	Game(uint8_t playerAmount = 2, uint8_t figurAmount = 2);
	~Game() { }

	/* Spiel-Utilities. */
	void InitNewGame(uint8_t playerAmount = 2, uint8_t figurAmount = 2);
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

	/* Wiedergebe und Setze, ob eine Figur benutzt wird. */
	bool GetUsed(uint8_t player, uint8_t figur) const;
	void SetUsed(uint8_t player, uint8_t figur, bool used);

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
private:
	std::unique_ptr<Player> Players[4];

	/*
		Variablen für das Spiel.
	*/
	uint8_t CurrentPlayer = 0, FigurAmount = 1, PlayerAmount = 2;
	bool ValidGame = false, UseAI = false;

	std::unique_ptr<uint8_t[]> GameData = nullptr; // Spiel-Daten Buffer.
};

#endif