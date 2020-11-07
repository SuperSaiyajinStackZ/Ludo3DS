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

#include "player.hpp"

/*
	Spieler Konstruktor.

	uint8_t figurAmount: Die Anzahl der Figuren.
*/
Player::Player(uint8_t figurAmount) {
	uint8_t amount = 0;

	/* Wir setzen die Anzahl der Figuren auf benutzt. */
	for (uint8_t i = 0; i < figurAmount; i++) {
		this->Figuren[i] = std::make_unique<Figur>(true);
		amount++;
	}

	/* Falls die Anzahl kleiner als 4 ist.. setzen wir die restlichen Figuren auf nicht benutzt. */
	if (amount < 4) {
		for (uint8_t i = amount; i < 4; i++) {
			this->Figuren[i] = std::make_unique<Figur>(false);
		}
	}
}


/*
	Wiedergebe die Position einer Figur.

	uint8_t figur: Der Figuren-Index.
*/
uint8_t Player::GetPosition(uint8_t figur) const {
	if (figur > MAX_FIGURES - 1) return 0; // 0 - 3 sind erlaubt.

	return this->Figuren[figur]->GetPosition();
}

/*
	Setze die Position einer Figur.

	uint8_t figur: Der Figuren-Index.
	uint8_t position: Der Position der Figur.
*/
void Player::SetPosition(uint8_t figur, uint8_t position) {
	if (figur > MAX_FIGURES - 1) return; // 0 - 3 sind erlaubt.

	this->Figuren[figur]->SetPosition(position);
}


/*
	Wiedergebe, ob eine Figur benutzt wird.

	uint8_t figur: Der Figuren-Index.
*/
bool Player::GetUsed(uint8_t figur) const {
	if (figur > MAX_FIGURES - 1) return false; // 0 - 3 sind erlaubt.

	return this->Figuren[figur]->GetUsed();
}

/*
	Setze, ob eine Figur benutzt wird.

	uint8_t figur: Der Figuren-Index.
	bool used: Ob benutzt (true) oder nicht (false).
*/
void Player::SetUsed(uint8_t figur, bool used) {
	if (figur > MAX_FIGURES - 1) return; // 0 - 3 sind erlaubt.

	this->Figuren[figur]->SetUsed(used);
}


/*
	Wiedergebe ob eine Figur bereits am Ziel ist.

	uint8_t figur: Der Figuren-Index.
*/
bool Player::GetDone(uint8_t figur) const {
	if (figur > MAX_FIGURES - 1) return false; // 0 - 3 sind erlaubt.

	return this->Figuren[figur]->GetDone();
}

/*
	Setze, ob eine Figur bereits am Ziel ist.

	uint8_t figur: Der Figuren-Index.
	bool isDone: Ob am Ziel (true) oder nicht (false).
*/
void Player::SetDone(uint8_t figur, bool isDone) {
	if (figur > MAX_FIGURES - 1) return; // 0 - 3 sind erlaubt.

	this->Figuren[figur]->SetDone(isDone);
}