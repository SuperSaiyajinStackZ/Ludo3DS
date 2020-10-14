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

#include "figur.hpp"

/*
	Wiedergebe die Position der Figur.
*/
uint8_t Figur::GetPosition() const { return this->Position; }

/*
	Setze die Position einer Figur.

	uint8_t pos: Die Position. 0 - 44 sind erlaubt.
*/
void Figur::SetPosition(uint8_t pos) {
	if (pos > MAX_FIELD) return; // 0 - 44 sind erlaubt, höher nicht.

	this->Position = pos;
}


/*
	Wiedergebe ob diese Figur benutzt wird.
*/
bool Figur::GetUsed() const { return this->Used; }

/*
	Setze, ob die Figur benutzt wird.

	bool used: Ob benutzt (true) oder nicht (false).
*/
void Figur::SetUsed(bool used) { this->Used = used; }


/*
	Wiedergebe ob diese Figur bereits am Ziel ist.
*/
bool Figur::GetDone() const { return this->Done; }

/*
	Setze, ob die Figur bereits am Ziel ist.

	bool isDone: Ob am Ziel (true) oder nicht (false).
*/
void Figur::SetDone(bool isDone) { this->Done = isDone; }