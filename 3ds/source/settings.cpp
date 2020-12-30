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

#include "common.hpp"
#include <unistd.h>

#define CONF_PATH "sdmc:/3ds/Ludo3DS/Config.json"

/* Falls die Konfigurations-Datei nicht existiert, erstelle sie und setze die Sprache auf Englisch. */
void Settings::Initialize() {
	FILE *file = fopen(CONF_PATH, "w");
	this->SetInt("Language", 1);
	this->SetInt("ShowRules", 1);

	const std::string dump = this->config.dump(1, '\t');
	fwrite(dump.c_str(), 1, this->config.dump(1, '\t').size(), file);
	fclose(file);
}

/* Konfiguration Konstruktor. */
Settings::Settings() {
	if (access(CONF_PATH, F_OK) != 0) this->Initialize(); // Da die Konfiguration nicht existiert, erstelle sie.

	FILE *file = fopen(CONF_PATH, "r");
	this->config = nlohmann::json::parse(file, nullptr, false);
	fclose(file);

	/* Sprache. */
	if (!this->config.contains("Language")) this->Language(1); // 1 ist Englisch, was die Standard Sprache ist.
	else this->Language(this->GetInt("Language"));

	/* Regeln ansehen. */
	if (!this->config.contains("ShowRules")) this->Rules(1); // 1 ist ja, also zeige Regeln an.
	else this->Rules(this->GetInt("ShowRules"));

	this->changesMade = false;
}

/* Schreibe in die Konfiguration, falls Änderungen gemacht worden sind. */
void Settings::Save() {
	if (this->changesMade) {
		FILE *file = fopen(CONF_PATH, "w");
		this->SetInt("Language", this->Language());
		this->SetInt("ShowRules", this->Rules());

		/* Scrhreibe Änderungen in die Konfigurations-Datei. */
		const std::string dump = this->config.dump(1, '\t');
		fwrite(dump.c_str(), 1, this->config.dump(1, '\t').size(), file);
		fclose(file);
	}
}

/*
	Wiedergebe einen Integer von der Konfiguration.

	const std::string &key: Wovon abgerufen werden soll.
*/
int Settings::GetInt(const std::string &key) const {
	if (!this->config.contains(key)) return 0;

	return this->config[key].get_ref<const int64_t &>();
}

/*
	Setze einen Integer in die Konfiguration.

	const std::string &key: Wohin dies gesetzt werden soll.
	int v: Der Wert.
*/
void Settings::SetInt(const std::string &key, int v) { this->config[key] = v; };