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

#include "gameHelper.hpp"
#include "gameScreen.hpp"

extern uint8_t fadeAlpha;
extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

/*
	Zeichne alle Figuren eines Spielers.

	uint8_t player: Der Spieler-Index.
*/
void GameScreen::DrawPlayer(uint8_t player) const {
	for (uint8_t figur = 0; figur < this->currentGame->GetFigurAmount(); figur++) {
		const uint8_t position = this->currentGame->GetPosition(player, figur);

		/* 0 --> Startfeld. */
		if (position == 0) {
			GFX::DrawFigure(player,
				this->PlayerField[(player * 4) + figur].x,
				this->PlayerField[(player * 4) + figur].y);

		} else if (position > 0 && position < 41) {
			GFX::DrawFigure(player,
				this->MainField[GameHelper::PositionConvert(player, position) - 1].x,
				this->MainField[GameHelper::PositionConvert(player, position) - 1].y);

		/* Falls wir in den Eingangs-Bereich kommen. */
		} else if (position > 40) {
			GFX::DrawFigure(player,
				this->EingangField[(player * 4) + (position - 41)].x,
				this->EingangField[(player * 4) + (position - 41)].y);
		}
	}
}

/* Zeichne die Selektion der Figur. */
void GameScreen::DrawSelection(uint8_t selection) const {
	if (this->awaitFigurSelect) {
		const uint8_t player = this->currentGame->GetCurrentPlayer();
		const uint8_t figur = selection;
		const uint8_t position = this->currentGame->GetPosition(player, figur);

			/* 0 --> Startfeld. */
			if (position == 0) {
				GFX::DrawPlayerSelector(player,
					this->PlayerField[(player * 4) + figur].x,
					this->PlayerField[(player * 4) + figur].y);

			} else if (position > 0 && position < 41) {
				GFX::DrawPlayerSelector(player,
					this->MainField[GameHelper::PositionConvert(player, position) - 1].x,
					this->MainField[GameHelper::PositionConvert(player, position) - 1].y);

			/* Falls wir in den Eingangs-Bereich kommen. */
			} else if (position > 40) {
				GFX::DrawPlayerSelector(player,
					this->EingangField[(player * 4) + (position - 41)].x,
					this->EingangField[(player * 4) + (position - 41)].y);
			}
	}
}

/* Initialisiere den Spiel-Screen. */
GameScreen::GameScreen() {
	CoreHelper::GenerateSeed();

	GameData dt = Overlays::PrepareGame();
	this->currentGame = std::make_unique<Game>(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
	this->currentGame->SetAI(dt.UseAI);
}

/* Zeichne alle Figuren aller Spieler. */
void GameScreen::DrawPlayers() const {
	for (uint8_t i = 0; i < this->currentGame->GetPlayerAmount(); i++) {
		this->DrawPlayer(i);
	}
}

/* Zeige das Haupt-Spiel an. */
void GameScreen::DisplayGame(void) const {
	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("GAME_SCREEN"));

	Gui::DrawStringCentered(0, 40, 0.6f, TEXT_COLOR, Lang::get("CURRENT_PLAYER") +
							std::to_string(this->currentGame->GetCurrentPlayer() + 1), 390);

	/* Falls wir eine Figur Selektion erwarten. */
	if (this->awaitFigurSelect) {
		GFX::Dice(this->currentGame->GetErgebnis(), 160, 115);
		Gui::DrawStringCentered(0, 80, 0.6f, TEXT_COLOR, Lang::get("SELECT_FIGURE"), 390);

	} else {
		Gui::DrawStringCentered(0, 80, 0.6f, TEXT_COLOR, Lang::get("ROLL_DICE"), 390);
	}

	Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("SELECT_INSTRUCTIONS"), 390);
	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadeAlpha));

	Gui::ScreenDraw(Bottom);
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);
	GFX::DrawField();
	this->DrawPlayers();

	if (this->awaitFigurSelect) this->DrawSelection(this->currentGame->GetSelectedFigur());
	else {
		for (uint8_t i = 0; i < this->currentGame->GetFigurAmount(); i++) {
			this->DrawSelection(i);
		}
	}

	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadeAlpha));
}

/* Zeige das Unter-Menü an. */
void GameScreen::DisplaySub(void) const {
	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("GAME_PAUSED"));

	/* Zeige Spiel-Informationen an. */
	Gui::DrawStringCentered(0, 30, 0.6f, TEXT_COLOR, Lang::get("PLAYER_AMOUNT") + ": " +
							std::to_string(this->currentGame->GetPlayerAmount()), 390);

	Gui::DrawStringCentered(0, 50, 0.6f, TEXT_COLOR, Lang::get("FIGURE_AMOUNT") + ": " +
							std::to_string(this->currentGame->GetFigurAmount()), 390);

	Gui::DrawStringCentered(0, 70, 0.6f, TEXT_COLOR, Lang::get("CURRENT_PLAYER") +
							std::to_string(this->currentGame->GetCurrentPlayer() + 1), 390);

	Gui::DrawStringCentered(0, 90, 0.6f, TEXT_COLOR, Lang::get("COMPUTER_ENABLED") +
							(this->currentGame->GetAI() ? Lang::get("YES") : Lang::get("NO")), 390);

	Gui::DrawStringCentered(0, 110, 0.6f, TEXT_COLOR, Lang::get("DICE_ROLLS") + ": " +
							std::to_string(this->currentGame->GetDiceRolls()), 390);


	Gui::DrawStringCentered(0, 160, 0.6f, TEXT_COLOR, Lang::get("SELECT_EXIT"), 390);
	Gui::DrawStringCentered(0, 180, 0.6f, TEXT_COLOR, Lang::get("B_BACK"), 390);
	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadeAlpha));

	Gui::ScreenDraw(Bottom);
	GFX::DrawSet(set_bottom_bg_idx, 0, 0);

	/* Zeige Schaltflächen. */
	for (int i = 0; i < 5; i++) {
		GFX::DrawSet(set_button_idx, this->subBtn[i].x, this->subBtn[i].y);
		if (this->subSel == i) GFX::DrawSet(set_button_selector_idx, this->subBtn[i].x, this->subBtn[i].y);
	}

	/* Schaltflächen Texte. */
	Gui::DrawStringCentered(0, this->subBtn[0].y + 10, 0.5f, TEXT_COLOR, Lang::get("LOAD_GAME"), 135);
	Gui::DrawStringCentered(0, this->subBtn[1].y + 10, 0.5f, TEXT_COLOR, Lang::get("SAVE_GAME"), 135);
	Gui::DrawStringCentered(0, this->subBtn[2].y + 10, 0.5f, TEXT_COLOR, Lang::get("GAME_SETTINGS"), 135);
	Gui::DrawStringCentered(0, this->subBtn[3].y + 10, 0.5f, TEXT_COLOR, Lang::get("LANGUAGE"), 135);
	Gui::DrawStringCentered(0, this->subBtn[4].y + 10, 0.5f, TEXT_COLOR, Lang::get("CREDITS"), 135);

	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadeAlpha));
}

/* Der Haupt-Zeichnungs teil. */
void GameScreen::Draw(void) const {
	if (!this->isSub) this->DisplayGame();
	else this->DisplaySub();
}

/* Die HauptLogik des Spiel-Screen's. */
void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	/* Falls das Spiel vorbei ist. */
	if (this->gameOver) {
		if (Msg::promptMsg(Lang::get("NEXT_GAME"))) {
			const GameData dt = Overlays::PrepareGame(true);

			if (dt.FAmount == -1) exiting = true; // -1 == Abgebrochen.

			this->currentGame->InitNewGame(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
			this->currentGame->SetAI(dt.UseAI);
			this->gameOver = false;

		} else {
			exiting = true;
		}
	}

	/* Nur wenn das Spiel noch nicht vorbei ist. */
	if (!this->gameOver) {
		if (hDown & KEY_START) this->isSub = true;

		if (this->isSub) {
			this->SubLogic(hDown, hHeld, touch);

		} else {
			if (!this->awaitFigurSelect) {
				this->RoundLogic(hDown, hHeld);

			} else {
				this->FigureSelection(hDown, hHeld, touch);
			}
		}
	}
}

void GameScreen::SubLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) this->isSub = false;
	if (hDown & KEY_SELECT) exiting = true; // Sollen wir dies auf SELECT setzen?

	if (hDown & KEY_DOWN) {
		if (this->subSel < 4) this->subSel++;
	}

	if (hDown & KEY_UP) {
		if (this->subSel > 0) this->subSel--;
	}

	if (hDown & KEY_A) {
		switch(this->subSel) {
			case 0:
				/* Spiel Laden. */
				if (Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"))) {
					this->currentGame->LoadGameFromFile();
					if (this->currentGame->validLoaded()) {
						Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
						this->currentGame->convertDataToGame();
						this->awaitFigurSelect = false;
						this->isSub = false;

					} else {
						Msg::DisplayWaitMsg(Lang::get("NOT_VALID_GAME"));
						return;
					}
				}
				break;

			case 1:
				/* Spiel Speichern. */
				if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
					Msg::DisplayMsg(Lang::get("SAVING_GAME"));
					this->currentGame->SaveToFile(true);
					Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
					this->isSub = false;
				}
				break;

			case 2: {
					/* Spiel Einstellungen. */
					if (Msg::promptMsg(Lang::get("GAME_SETTINGS_PROMPT"))) {
						const GameData dt = Overlays::PrepareGame(true);

						if (dt.FAmount == -1) return; // -1 == Abgebrochen.

						this->currentGame->InitNewGame(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
						this->currentGame->SetAI(dt.UseAI);
						this->isSub = false;
					}
				}
				break;

			case 3:
				/* Sprache Ändern. */
				Overlays::LanguageOverlay();
				break;

			case 4:
				/* Credits Anzeigen. */
				Overlays::CreditsOverlay();
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		/* Spiel Laden. */
		if (touching(touch, this->subBtn[0])) {
			if (Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"))) {
				this->currentGame->LoadGameFromFile();
				if (this->currentGame->validLoaded()) {
					Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
					this->currentGame->convertDataToGame();
					this->awaitFigurSelect = false;
					this->isSub = false;

				} else {
					Msg::DisplayWaitMsg(Lang::get("NOT_VALID_GAME"));
					return;
				}
			}

		/* Spiel Speichern. */
		} else if (touching(touch, this->subBtn[1])) {
			if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
				Msg::DisplayMsg(Lang::get("SAVING_GAME"));
				this->currentGame->SaveToFile(true);
				Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
				this->isSub = false;
			}

		/* Spiel Einstellungen. */
		} else if (touching(touch, this->subBtn[2])) {
			if (Msg::promptMsg(Lang::get("GAME_SETTINGS_PROMPT"))) {
				const GameData dt = Overlays::PrepareGame(true);

				if (dt.FAmount == -1) return; // -1 == Abgebrochen.

				this->currentGame->InitNewGame(dt.PAmount, dt.FAmount, (dt.ThreeRolls ? 3 : 1));
				this->currentGame->SetAI(dt.UseAI);
				this->isSub = false;
			}

		/* Sprache Ändern. */
		} else if (touching(touch, this->subBtn[3])) {
			Overlays::LanguageOverlay();

		/* Credits Anzeigen. */
		} else if (touching(touch, this->subBtn[4])) {
			Overlays::CreditsOverlay();
		}
	}
}

/*
	Der Runden-Teil.

	Rolle den Würfel.
*/
void GameScreen::RoundLogic(u32 hDown, u32 hHeld) {
	if (this->currentGame->GetAI() && this->currentGame->GetCurrentPlayer() != 0) {
		this->AIHandle();

	} else {
		if (hHeld & KEY_SELECT) Msg::HelperBox(Lang::get("GAME_INSTR_1"));

		if (hDown & KEY_X) {
			this->currentGame->SetErgebnis(Overlays::RollDiceOverlay()); // Würfeln!

			bool confirmation = false;

			/* Bestätige das Ergebnis. */
			while(!confirmation) {
				Gui::clearTextBufs();
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				C2D_TargetClear(Top, NO_COLOR);

				GFX::DrawBaseTop();
				Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
				Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);

				Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("CURRENT_PLAYER") +
								std::to_string(this->currentGame->GetCurrentPlayer() + 1), 390);

				GFX::Dice(this->currentGame->GetErgebnis(), 160, 80);
				Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("A_CONFIRM"), 390);
				C3D_FrameEnd(0);

				hidScanInput();
				if (hidKeysDown() & KEY_A) confirmation = true;
			}

			gspWaitForVBlank();

			for (uint8_t figur = 0; figur < this->currentGame->GetFigurAmount(); figur++) {
				if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), figur, this->currentGame->GetErgebnis())) {
					this->GetFirstAvlFigur();
					this->awaitFigurSelect = true;
					return;
				}
			}

			GameHelper::SetContinue(this->currentGame, this->currentGame->GetCurrentPlayer());
			this->NextPHandle();
		}
	}
}

/* Gehe zur nächsten Figur, falls verfügbar. */
void GameScreen::NextFigur() {
	if (this->currentGame->GetSelectedFigur() == this->currentGame->GetFigurAmount() - 1) return; // Bereits an der letzten Figur.

	for (uint8_t cFigur = this->currentGame->GetSelectedFigur() + 1; cFigur < this->currentGame->GetFigurAmount(); cFigur++) {
		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);
			break;
		}
	}
}

/* Gehe zur vorherigen Figur, falls verfügbar. */
void GameScreen::PreviousFigur() {
	if (this->currentGame->GetSelectedFigur() == 0) return; // Es gibt kein -1.

	for (uint8_t cFigur = this->currentGame->GetSelectedFigur() - 1; cFigur >= 0; cFigur--) {
		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);
			break;
		}
	}
}

/* Gehe zur ersten verfügbaren Figur-Selektion. */
void GameScreen::GetFirstAvlFigur() {
	for (uint8_t cFigur = 0; cFigur < this->currentGame->GetFigurAmount(); cFigur++) {
		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), cFigur, this->currentGame->GetErgebnis())) {
			this->currentGame->SetSelectedFigur(cFigur);
			break;
		}
	}
}

/* Touch Handling für die Figuren. */
Structs::ButtonPos GameScreen::GetFigurTouchIndex(uint8_t player, uint8_t figur) const {
	const uint8_t position = this->currentGame->GetPosition(player, figur);

	/* 0 und 41+ haben eine spezielle handlung für die Touch Position. */
	if (position == 0) return this->PlayerField[(player * 4) + figur];

	/* Feld Handling. */
	if (position > 0 && position < 41) return this->MainField[GameHelper::PositionConvert(player, position) - 1];

	if (position > 40) return this->EingangField[(player * 4) + (position - 41)];

	return { 0,  0,  0,  0 };
}


/* Der Selektion Teil für die Figur. */
void GameScreen::FigureSelection(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hHeld & KEY_SELECT) Msg::HelperBox(Lang::get("GAME_INSTR_2"));

	if ((hDown & KEY_RIGHT) || (hDown & KEY_R)) this->NextFigur();

	if ((hDown & KEY_LEFT) || (hDown & KEY_L)) this->PreviousFigur();

	if (hDown & KEY_TOUCH) {
		for (uint8_t i = 0; i < this->currentGame->GetFigurAmount(); i++) {
			if (touching(touch, this->GetFigurTouchIndex(this->currentGame->GetCurrentPlayer(), i))) {
				this->currentGame->SetSelectedFigur(i);

				const bool canCont = this->Play();
				if (canCont) this->awaitFigurSelect = false; // Weil wir spielen konnten, erwarten wir keine Figur Selektion.

				if (canCont) {
					/* Führe die Kick Aktion aus. */
					GameHelper::KickAction(this->currentGame,
						this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());
				}

				if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
					char msg[100];
					snprintf(msg, sizeof(msg), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
					Msg::DisplayWaitMsg(msg);

					this->gameOver = true;
					return;
				}

				if (!this->awaitFigurSelect) this->NextPHandle();
				return;
			}
		}
	}

	if (hDown & KEY_A) {
		const bool canCont = this->Play();
		if (canCont) this->awaitFigurSelect = false; // Weil wir spielen konnten, erwarten wir keine Figur Selektion.

		if (canCont) {
			/* Führe die Kick Aktion aus. */
			GameHelper::KickAction(this->currentGame,
				this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());
		}

		if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
			char msg[100];
			snprintf(msg, sizeof(msg), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::DisplayWaitMsg(msg);

			this->gameOver = true;
			return;
		}

		if (!this->awaitFigurSelect) this->NextPHandle();
	}
}

/*
	Die Spiel-Logik.

	Wiedergibt (false), falls nicht spielbar.
*/
bool GameScreen::Play() {
	const uint8_t position = this->currentGame->GetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

	/* 0 --> Auf Feld 1, falls das Ergebnis eine 6 war, ansonsten ungültig. */
	if (position == 0) {
		if (this->currentGame->GetErgebnis() == 6) {
			if (!GameHelper::DoesOwnFigurBlock(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), 1)) {
				this->currentGame->SetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), 1);
				this->currentGame->SetCanContinue(true);
				return true;

			} else {
				return false; // Die Eigene Figur blockt.
			}

		} else {
			return false; // Position 0 und keine 6 -> Ungültig!
		}

		/* Falls die Position nicht 0 ist. */
	} else {
		if (position + this->currentGame->GetErgebnis() < 45) {
			if (!GameHelper::DoesOwnFigurBlock(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), this->currentGame->GetErgebnis())) {
				this->currentGame->SetPosition(this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur(), position + this->currentGame->GetErgebnis());

				GameHelper::MarkAsDone(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());

				for (uint8_t i = 0; i < this->currentGame->GetFigurAmount(); i++) {
					GameHelper::AdditionalDoneCheck(this->currentGame, this->currentGame->GetCurrentPlayer(), i);
				}

				this->currentGame->SetCanContinue(this->currentGame->GetErgebnis() == 6);
				return true;

			} else {
				return false; // Die Eigene Figur blockt.
			}

		} else {
			return false; // Größer als 44.
		}
	}

	return false;
}

/* Nächster Spieler Handle. */
void GameScreen::NextPHandle() {
	/* Setze Werte zurück für den nächsten Zug. */
	this->currentGame->SetErgebnis(0);
	this->currentGame->SetSelectedFigur(0);

	if (this->currentGame->GetCanContinue()) {
		this->currentGame->SetCanContinue(false);
		return;
	}

	if (this->currentGame->GetCurrentPlayer() < this->currentGame->GetPlayerAmount() - 1) {
		this->currentGame->SetCurrentPlayer(this->currentGame->GetCurrentPlayer() + 1);

	} else {
		this->currentGame->SetCurrentPlayer(0);
	}

	this->currentGame->SetAVLDiceRolls(this->currentGame->GetDiceRolls()); // Setze standard Würfel-Rolls.
}

void GameScreen::AIHandle() {
	this->currentGame->SetErgebnis(Overlays::RollDiceOverlay(true)); // Würfel mit Verzögerung.

	bool canMove = false, confirmation = false;
	int8_t res = -1; // int8_t.. damit wir -1 benutzen können.

	for (uint8_t figur = 0; figur < this->currentGame->GetFigurAmount(); figur++) {
		if (GameHelper::CanMove(this->currentGame, this->currentGame->GetCurrentPlayer(), figur, this->currentGame->GetErgebnis())) {
			/* Fokussiert aufs kicken. ;P */
			if (GameHelper::CanKick(this->currentGame,
				this->currentGame->GetCurrentPlayer(), figur)) {

				this->currentGame->SetSelectedFigur(figur);
				canMove = true;
				break;

			} else {
				res = figur;
			}
		}
	}

	/* Bestätige das Ergebnis. */
	while(!confirmation) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, NO_COLOR);

		GFX::DrawBaseTop();
		Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
		Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);

		Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("CURRENT_PLAYER") +
						std::to_string(this->currentGame->GetCurrentPlayer() + 1), 390);

		GFX::Dice(this->currentGame->GetErgebnis(), 160, 80);
		Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("A_CONFIRM"), 390);
		C3D_FrameEnd(0);

		hidScanInput();
		if (hidKeysDown() & KEY_A) confirmation = true;
	}

	if (!canMove) {
		if (res != -1) {
			this->currentGame->SetSelectedFigur(res);
			canMove = true;
		}
	}

	if (canMove) {
		const bool canCont = this->Play();

		if (canCont) {
			/* Führe die Kick Aktion aus. */
			GameHelper::KickAction(this->currentGame, this->currentGame->GetCurrentPlayer(), this->currentGame->GetSelectedFigur());
		}

		if (GameHelper::HasFinished(this->currentGame, this->currentGame->GetCurrentPlayer())) {
			char msg[100];
			snprintf(msg, sizeof(msg), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::DisplayWaitMsg(msg);

			this->gameOver = true;
			return;
		}

		this->NextPHandle();
		return;

	} else {
		GameHelper::SetContinue(this->currentGame, this->currentGame->GetCurrentPlayer());
	}

	this->NextPHandle();
}