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

#include "gameHelper.hpp"

/*
	Konvertiere die Position eines Spielers zu der Haupt-Perspektive.

	uint8_t Player: Der Spieler-Index. ( 0 - 3 ).
	uint8_t Position: Die Position.
*/
uint8_t GameHelper::PositionConvert(uint8_t Player, uint8_t Position) {
	if (Position == 0) return 0; // 0.. ist immer 0.
	if (Position > 40) return Position; // Über 40.. ist immer über 40.

	switch(Player) {
		case 0:
			return Position; // Wir haben die Haupt-Position von der Spieler 1 Perspektive.

		case 1:
			if (Position < 31) return 10 + Position;
			else if (Position > 30 && Position < 41) return Position - 30;

		case 2:
			if (Position < 21) return 20 + Position;
			else if (Position > 20 && Position < 41) return Position - 20;

		case 3:
			if (Position < 11) return 30 + Position;
			else if (Position > 10 && Position < 41) return Position - 10;
	}

	return 0;
}

/*
	Wiedergebe, ob ein Spieler schon gewonnen hat.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
*/
bool GameHelper::HasFinished(std::unique_ptr<Game> &game, uint8_t player) {
	if (!game) return false; // Spiel-Zeiger ist nicht gültig.

	for (uint8_t figur = 0; figur < game->GetFigurAmount(); figur++) {
		if (!game->GetDone(player, figur)) return false; // Ein Spieler ist nocht nicht am Ende.
	}

	return true;
}

/*
	Wiedergebe, ob die eigene Figur einen blockiert.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
	uint8_t ergebnis: Das Ergebnis des Würfels, welches überprüft werden soll.
*/
bool GameHelper::DoesOwnFigurBlock(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur, uint8_t ergebnis) {
	if (!game) return true; // Spiel-Zeiger ist nicht gültig.

	const uint8_t Position = GameHelper::PositionConvert(player, game->GetPosition(player, figur) + ergebnis);

	/* Überprüfe für alle Figuren eines Spielers. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = GameHelper::PositionConvert(player, game->GetPosition(player, figur2));

			if (Position == Position2) return true; // Position passt zu Position2 -> Blockiert!
		}
	}

	return false;
}

/*
	Wiedergebe, ob alle Spieler am Anfangs-Bereich sind. (Haus)

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
*/
bool GameHelper::AllFiguresInHouse(std::unique_ptr<Game> &game, uint8_t player) {
	if (!game) return true; // Spiel-Zeiger ist nicht gültig.

	for (uint8_t figur = 0; figur < game->GetFigurAmount(); figur++) {
		if (game->GetPosition(player, figur) != 0) return false; // Mindestens ein Spieler ist nicht am Anfang.
	}

	return true;
}

/*
	Die Kick Aktion!

	Kicke Spieler ins eigene Startfeld zurück, falls sie auf dem aktuellen Feld standen.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
void GameHelper::KickAction(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur) {
	if (!game) return; // Spiel-Zeiger ist nicht gültig.
	const uint8_t test = game->GetPosition(player, figur);
	if (test == 0 || test > 40) return; // 0 und 40 + können nicht gekickt werden.


	const uint8_t Position = GameHelper::PositionConvert(player, game->GetPosition(player, figur));

	for (uint8_t player2 = 0; player2 < game->GetPlayerAmount(); player2++) {
		if (player2 != player) {
			for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
				const uint8_t Position2 = GameHelper::PositionConvert(player2,
											game->GetPosition(player2, figur2));

				if (Position2 < 41) {
					if (Position == Position2) {
						game->SetPosition(player2, figur2, 0);
						break; // Nur ein Spieler kann jeweils draufgewesen sein.
					}
				}
			}
		}
	}
}

/*
	Wiedergebe, ob ein handle vom Spieler-Haus getätigt werden muss.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
*/
bool GameHelper::NeedsToHandleFromHouse(std::unique_ptr<Game> &game, uint8_t player) {
	if (!game) return true; // Spiel-Zeiger ist nicht gültig.

	for (uint8_t figur = 0; figur < game->GetFigurAmount(); figur++) {
		if (!game->GetDone(player, figur)) {
			const uint8_t position = game->GetPosition(player, figur);

			if (position > 0 && position < 44) return false; // Die Figur lässt sich noch außerhalb steuern.
		}
	}

	return true;
}


/*
	Markiere als "Fertig", wenn möglich.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
void GameHelper::MarkAsDone(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur) {
	if (!game) return; // Der Spiel-Zeiger ist nicht gültig.
	if (game->GetDone(player, figur)) return; // Bereits am Ziel.
	if (game->GetPosition(player, figur) < 41) return; // Erst ab 41 überprüfen!!!

	const uint8_t Position = game->GetPosition(player, figur);
	bool alreadyUsed = false; // Check variable.

	/* Checke für 44. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 44) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 44) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}

	alreadyUsed = false; // Setze status zurück.
	/* Checke für 43. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 43) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 43) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}

	alreadyUsed = false; // Setze status zurück.
	/* Checke für 42. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 42) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 42) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}


	if (Position == 41) game->SetDone(player, figur, true); // Wir sind fertig.
}

/*
	Wiedergebe, ob die Figur sich bewegen kann.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
	uint8_t ergebnis: Das Ergebnis des Würfels, welche überprüft werden soll.
*/
bool GameHelper::CanMove(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur, uint8_t ergebnis) {
	if (!game) return false; // Der Spiel-Zeiger ist nicht gültig.
	if (game->GetDone(player, figur)) return false; // Bereits am Ziel.
	if (game->GetPosition(player, figur) + ergebnis > 44) return false; // Größer als 44.

	/* Überprüfe vom Haus. */
	if (game->GetPosition(player, figur) == 0) {
		if (ergebnis == 6) {
			const uint8_t TempPos = GameHelper::PositionConvert(player, game->GetPosition(player, figur) + 1);

			/* Überprüfe für alle Figuren aller Spielers. */
			for (uint8_t player2 = 0; player2 < game->GetPlayerAmount(); player2++) {
				for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {

					if (player2 != player && figur2 != figur) { // Überprüfe nicht die aktuell benutzte Figur!
						const uint8_t Position = GameHelper::PositionConvert(player2,
													game->GetPosition(player2, figur2));

						if (TempPos == Position) return false; // TempPos passt zu Position -> Blockiert!
					}
				}
			}

			return true;

		} else {
			return false;
		}

		return false;
	}

	/* Überprüfe Innerhalb des Außen-Feldes. */
	if (game->GetPosition(player, figur) + ergebnis < 41) {
		const uint8_t Position = GameHelper::PositionConvert(player, game->GetPosition(player, figur) + ergebnis);

		/* Überprüfe außerhalb des Hauses. */
		for (uint8_t player2 = 0; player2 < game->GetPlayerAmount(); player2++) {
			for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {

				if (player2 != player && figur2 != figur) { // Überprüfe nicht die aktuell benutzte Figur!

					const uint8_t Position2 = GameHelper::PositionConvert(player2, game->GetPosition(player2, figur2));

					if (Position == Position2) return false; // Position passt zu Position2 -> Blockiert!
				}
			}
		}

		return true;
	}

	/* Überprüfe im Eingang. */
	if (game->GetPosition(player, figur) + ergebnis > 40) {
		const uint8_t Position = game->GetPosition(player, figur) + ergebnis;

		for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
			if (figur2 != figur) {

				const uint8_t Position2 = game->GetPosition(player, figur2);

				if (Position2 == Position) return false; // Position bereits benutzt.
			}
		}

		return true;
	}

	return false;
}

/*
	Additionale Checks, ob eine Figur fertig ist.

	Dies wird benutzt, falls eine Figur eventuell eine überspringt.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
void GameHelper::AdditionalDoneCheck(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur) {
	if (!game) return; // Der Spiel-Zeiger ist nicht gültig.
	if (game->GetDone(player, figur)) return; // Bereits am Ziel.
	if (game->GetPosition(player, figur) < 41) return; // Erst ab 41 überprüfen!!!

	const uint8_t Position = game->GetPosition(player, figur);
	bool alreadyUsed = false; // Check variable.

	/* Checke für 44. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 44) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 44) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}


	alreadyUsed = false; // Setze status zurück.
	/* Checke für 43. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 43) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 43) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}


	alreadyUsed = false; // Setze status zurück.
	/* Checke für 42. */
	for (uint8_t figur2 = 0; figur2 < game->GetFigurAmount(); figur2++) {
		if (figur2 != figur) {
			const uint8_t Position2 = game->GetPosition(player, figur2);

			if (Position2 == 42) {
				alreadyUsed = true; // Position bereits benutzt.
				break;
			}
		}
	}

	if (!alreadyUsed) {
		if (Position == 42) {
			game->SetDone(player, figur, true); // Wir sind fertig.
			return;

		} else {
			return;
		}
	}

	if (Position == 41) game->SetDone(player, figur, true); // Wir sind fertig.
}

/*
	Wiedergebe, ob eine Figur gekickt werden kann.

	std::unique_ptr<Game> &game: Eine Referenz zum aktuellen Spiel.
	uint8_t player: Der Spieler-Index.
	uint8_t figur: Der Figuren-Index.
*/
bool GameHelper::CanKick(std::unique_ptr<Game> &game, uint8_t player, uint8_t figur) {
	if (!game) return false; // Spiel-Zeiger ist nicht gültig.
	const uint8_t test = game->GetPosition(player, figur);
	if (test == 0 || test > 40) return false; // 0 und 40 + können nicht gekickt werden.


	const uint8_t Position = GameHelper::PositionConvert(player, game->GetPosition(player, figur));

	for (uint8_t pl = 0; pl < game->GetPlayerAmount(); pl++) {
		if (pl != player) {
			for (uint8_t fg = 0; fg < game->GetFigurAmount(); fg++) {
				const uint8_t Position2 = GameHelper::PositionConvert(pl, game->GetPosition(pl, fg));

				if (Position2 < 41) {
					if (Position == Position2) return true;
				}
			}
		}
	}

	return false;
}