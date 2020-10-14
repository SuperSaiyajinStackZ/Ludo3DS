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

#include "game.hpp"
#include <unistd.h>

/*
	Der Spiel Konstruktor.

	uint8_t playerAmount: Die Spieler-Anzahl.
	uint8_t figurAmount: Die Figuren-Anzahl.
*/
Game::Game(uint8_t playerAmount, uint8_t figurAmount) { this->InitNewGame(playerAmount, figurAmount); }

/*
	Initialisiere ein neues Spiel.

	uint8_t playerAmount: Die Spieler-Anzahl.
	uint8_t figurAmount: Die Figuren-Anzahl.
*/
void Game::InitNewGame(uint8_t playerAmount, uint8_t figurAmount) {
	/* Setze Spieler zurück. */
	for (uint8_t i = 0; i < MAX_FIGURES; i++) {
		this->Players[i] = nullptr;
	}

	if ((playerAmount > MAX_FIGURES) || (playerAmount <= 0)) playerAmount = 2; // 0 und 5+ sind zu viel und werden als 2 gesetzt.
	if ((figurAmount > MAX_FIGURES) || (figurAmount <= 0)) figurAmount = 1; // 0 und 5+ sind zu viel und werden als 1 gesetzt.

	this->CurrentPlayer = 0;
	this->PlayerAmount = playerAmount;
	this->FigurAmount = figurAmount;

	for (uint8_t i = 0; i < playerAmount; i++) {
		this->Players[i] = std::make_unique<Player>(figurAmount);
	}

	this->GameData = std::unique_ptr<uint8_t[]>(new uint8_t[_GAME_SIZE]);
	this->SaveConversion();
}

/*
	Lade ein Spiel von Spiel-Daten.
*/
void Game::LoadGameFromFile() {
	this->ValidGame = false; // Setze das immer zu falsch, wenn die Funktion startet.
	if (access(_GAME_DATA_FILE, F_OK) != 0) return; // Datei existiert nicht.

	FILE *file = fopen(_GAME_DATA_FILE, "r");

	if (file) {
		fseek(file, 0, SEEK_END);
		uint32_t size = ftell(file); // Teile uns die größe der Datei mit.
		fseek(file, 0, SEEK_SET);

		if (size == _GAME_SIZE) {
			this->GameData = nullptr;
			this->GameData = std::unique_ptr<uint8_t[]>(new uint8_t[_GAME_SIZE]);
			fread(this->GameData.get(), 1, _GAME_SIZE, file);
			this->ValidGame = true;
		}

		fclose(file);
	}
}

/*
	Konvertiere die Daten zu einem Spiel.
*/
void Game::convertDataToGame() {
	if (this->GameData && this->ValidGame) {
		/* Bereinige alles. */
		for (uint8_t i = 0; i < MAX_FIGURES; i++) {
			this->Players[i] = nullptr;
		}


		this->CurrentPlayer = this->GameData.get()[_GAME_CURRENT_PLAYER]; // Der Aktuelle Spieler.

		/* Die Spieler-Anzahl. */
		if ((this->GameData.get()[_GAME_PLAYER_AMOUNT] > MAX_FIGURES) || (this->GameData.get()[_GAME_PLAYER_AMOUNT] <= 0)) {
			this->PlayerAmount = MAX_FIGURES; // Setze zu 4, weil 0 / 5+ ist verboten.

		} else {
			this->PlayerAmount = this->GameData.get()[_GAME_PLAYER_AMOUNT];
		}

		/* Die Figuren-Anzahl. */
		if ((this->GameData.get()[_GAME_FIGUR_AMOUNT] > MAX_FIGURES) || (this->GameData.get()[_GAME_FIGUR_AMOUNT] <= 0)) {
			this->FigurAmount = MAX_FIGURES; // Setze zu 4, weil 5+ ist verboten.

		} else {
			this->FigurAmount = this->GameData.get()[_GAME_FIGUR_AMOUNT];
		}

		/* Initialisiere die Spieler-Zeiger. */
		for (uint8_t i = 0; i < this->PlayerAmount; i++) {
			this->Players[i] = std::make_unique<Player>(this->FigurAmount);
		}

		/* Der Spieler Teil. */
		for (uint8_t player = 0; player < this->PlayerAmount; player++) {
			for (uint8_t figur = 0; figur < this->FigurAmount; figur++) {

				/* Position. */
				this->Players[player]->SetPosition(figur, this->GameData[_GAME_PLAYER_1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)]);

				/* Benutzt. */
				this->Players[player]->SetUsed(figur, this->GameData[_GAME_PLAYER_1 + 1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)]);

				/* Ziel. */
				this->Players[player]->SetDone(figur, this->GameData[_GAME_PLAYER_1 + 2 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)]);

			}
		}
	}
}


/*
	Konvertiere das aktuelle Spiel zu einer Speicher-Datei.
*/
void Game::SaveConversion() {
	if (!this->GameData) return; // Damit wir keine Probleme verursachen. Sollte jedoch nicht passieren.

	this->GameData[_GAME_CURRENT_PLAYER] = this->CurrentPlayer;
	this->GameData[_GAME_PLAYER_AMOUNT] = this->PlayerAmount;
	this->GameData[_GAME_FIGUR_AMOUNT] = this->FigurAmount;

	/* Der Spieler Teil. */
	for (uint8_t player = 0; player < MAX_FIGURES; player++) {
		if (player < this->PlayerAmount) {

			for (uint8_t figur = 0; figur < MAX_FIGURES; figur++) {
				if (figur < this->FigurAmount) {

					/* Position. */
					this->GameData[_GAME_PLAYER_1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = this->Players[player]->GetPosition(figur);

					/* Benutzt. */
					this->GameData[_GAME_PLAYER_1 + 1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = this->Players[player]->GetUsed(figur);

					/* Ziel. */
					this->GameData[_GAME_PLAYER_1 + 2 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = this->Players[player]->GetDone(figur);

				} else {
					/* Position. */
					this->GameData[_GAME_PLAYER_1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = 0;

					/* Benutzt. */
					this->GameData[_GAME_PLAYER_1 + 1 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = 0;

					/* Ziel. */
					this->GameData[_GAME_PLAYER_1 + 2 + (figur * _GAME_FIGUR_SIZE) +
						(player * _GAME_PLAYER_SIZE)] = 0;
				}
			}

		} else {
			for (uint8_t figur = 0; figur < MAX_FIGURES; figur++) {
				/* Position. */
				this->GameData[_GAME_PLAYER_1 + (figur * _GAME_FIGUR_SIZE) +
					(player * _GAME_PLAYER_SIZE)] = 0;

				/* Benutzt. */
				this->GameData[_GAME_PLAYER_1 + 1 + (figur * _GAME_FIGUR_SIZE) +
					(player * _GAME_PLAYER_SIZE)] = 0;

				/* Ziel. */
				this->GameData[_GAME_PLAYER_1 + 2 + (figur * _GAME_FIGUR_SIZE) +
					(player * _GAME_PLAYER_SIZE)] = 0;
			}
		}
	}
}

/*
	Schreibe die Daten zu einer datei.
*/
void Game::SaveToFile(bool update) {
	if (update) this->SaveConversion(); // Konvertiere, falls update ist gewollt (true).

	FILE *out = fopen(_GAME_DATA_FILE, "w");
	fwrite(this->GameData.get(), 1, _GAME_SIZE, out);
	fclose(out);
}

/*
	Wiedergebe die Position einer Figur eines Spielers.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
uint8_t Game::GetPosition(uint8_t player, uint8_t figur) const {
	if (player > this->PlayerAmount) return 0;

	return this->Players[player]->GetPosition(figur);
}

/*
	Setze die Position einer Figur eines Spielers.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
	uint8_t position: Die Position der Figur.
*/
void Game::SetPosition(uint8_t player, uint8_t figur, uint8_t position) {
	if (player > this->PlayerAmount) return;

	this->Players[player]->SetPosition(figur, position);
}


/*
	Wiedergebe ob eine figur eines Spielers benutzt wird.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
bool Game::GetUsed(uint8_t player, uint8_t figur) const {
	if (player > this->PlayerAmount) return false;

	return this->Players[player]->GetUsed(figur);
}

/*
	Setze ob eine figur eines Spielers benutzt wird.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
	bool used: Ob benutzt (true) oder nicht (false).
*/
void Game::SetUsed(uint8_t player, uint8_t figur, bool used) {
	if (player > this->PlayerAmount) return;

	this->Players[player]->SetUsed(figur, used);
}


/*
	Wiedergebe ob eine Figur eines Spielers bereits am Ziel ist.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
bool Game::GetDone(uint8_t player, uint8_t figur) const {
	if (player > this->PlayerAmount) return false;

	return this->Players[player]->GetDone(figur);
}

/*
	Setze, ob eine Figur eines Spielers bereits am Ziel ist.

	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
	bool isDone: Ob am Ziel (true) oder nicht (false).
*/
void Game::SetDone(uint8_t player, uint8_t figur, bool isDone) {
	if (player > this->PlayerAmount) return;

	this->Players[player]->SetDone(figur, isDone);
}