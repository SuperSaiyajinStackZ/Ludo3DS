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

#ifndef _LUDO3DS_CORE_HELPER_HPP
#define _LUDO3DS_CORE_HELPER_HPP

#include <memory>
#include <random>
#include <string>

inline std::mt19937 randomGenerator; // Zufalls-Generator für den Würfel.
#define MAX_FIELD 44 // 0 -> Haus, 1 - 40 -> Feld, 41 - 44 - Eingang.
#define MAX_FIGURES 4 // 4 sind die maximale Anzahl an Figuren.

namespace CoreHelper {
	void GenerateSeed();
	uint8_t RollDice();
};

#endif