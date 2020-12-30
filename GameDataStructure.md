# Ludo3DS Spieldaten Struktur

Dies Beinhaltet eine Dokumentation zur Spieldaten Struktur von Ludo3DS v0.1.0 bis zur aktuellsten (Derzeit: v0.3.0).

Die Spieldaten Datei kann im Unter-Menü mit `Spiel Speichern` in `sdmc:/3ds/Ludo3DS/GameData.dat` gefunden werden. Das Laden funktioniert ebenfalls mit `Spiel Laden` falls diese Datei verfügbar ist.

<details>
	<summary>Version 0.1.0 - 0.2.0</summary>

## Figuren Struktur

| Offset    | DataType | Size | Content                                                           |
| --------- | -------- | ---- | ----------------------------------------------------------------- |
| 0x0 - 0x2 | uint8_t  | 0x3  | Figuren-Größe                                                     |
|           |          |      |                                                                   |
| 0x0 - 0x0 | uint8_t  | 0x1  | Position der Figur ( 0 - 44 )                                     |
| 0x1 - 0x1 | Boolean  | 0x1  | Ob bereits am Ziel (1) oder nicht (0)                             |
| 0x2 - 0x2 | Boolean  | 0x1  | Ob benutzt oder nicht (Wurde mit v0.3.0 + entfernt weil unnötig). |

## Spieler Struktur

| Offset    | DataType        | Size | Content       |
| --------- | --------------- | ---- | ------------- |
| 0x0 - 0xB | uint8_t         | 0xC  | Spieler-Größe |
|           |                 |      |               |
| 0x0 - 0x2 | Figur_Struktur  | 0x3  | Figur 1       |
| 0x3 - 0x5 | Figur_Struktur  | 0x3  | Figur 2       |
| 0x6 - 0x8 | Figur_Struktur  | 0x3  | Figur 3       |
| 0x9 - 0xB | Figur_Struktur  | 0x3  | Figur 4       |

## Spiel Struktur

| Offset      | DataType         | Size | Content                                                           |
| ----------- | ---------------- | ---- | ----------------------------------------------------------------- |
| 0x0 - 0x32  | uint8_t          | 0x33 | Spiel-Größe (51 byte)                                             |
|             |                  |      |                                                                   |
| 0x0 - 0x0   | uint8_t          | 0x1  | Aktueller Spieler (0 - 3)                                         |
| 0x1 - 0x1   | uint8_t          | 0x1  | Spieler Anzahl (2 - 4)                                            |
| 0x2 - 0x2   | uint8_t          | 0x1  | Figuren Anzahl (1 - 4)                                            |
| 0x3 - 0xE   | Spieler_Struktur | 0xC  | Spieler 1                                                         |
| 0xF - 0x1A  | Spieler_Struktur | 0xC  | Spieler 2                                                         |
| 0x1B - 0x26 | Spieler_Struktur | 0xC  | Spieler 3                                                         |
| 0x27 - 0x32 | Spieler_Struktur | 0xC  | Spieler 4                                                         |
</details>

<details>
	<summary>Version 0.3.0</summary>

## Figuren Struktur

| Offset    | DataType | Size | Content                               |
| --------- | -------- | ---- | ------------------------------------- |
| 0x0 - 0x1 | uint8_t  | 0x2  | Figuren-Größe                         |
|           |          |      |                                       |
| 0x0 - 0x0 | uint8_t  | 0x1  | Position der Figur ( 0 - 44 )         |
| 0x1 - 0x1 | Boolean  | 0x1  | Ob bereits am Ziel (1) oder nicht (0) |

## Spieler Struktur

| Offset    | DataType        | Size | Content       |
| --------- | --------------- | ---- | ------------- |
| 0x0 - 0x7 | uint8_t         | 0x8  | Spieler-Größe |
|           |                 |      |               |
| 0x0 - 0x1 | Figur_Struktur  | 0x2  | Figur 1       |
| 0x2 - 0x3 | Figur_Struktur  | 0x2  | Figur 2       |
| 0x4 - 0x5 | Figur_Struktur  | 0x2  | Figur 3       |
| 0x6 - 0x7 | Figur_Struktur  | 0x2  | Figur 4       |

## Spiel Struktur

| Offset      | DataType         | Size | Content                                                           |
| ----------- | ---------------- | ---- | ----------------------------------------------------------------- |
| 0x0 - 0x22  | uint8_t          | 0x23 | Spiel-Größe (35 byte)                                             |
|             |                  |      |                                                                   |
| 0x0 - 0x0   | uint8_t          | 0x1  | Aktueller Spieler (0 - 3)                                         |
| 0x1 - 0x1   | uint8_t          | 0x1  | Spieler Anzahl (2 - 4)                                            |
| 0x2 - 0x2   | uint8_t          | 0x1  | Figuren Anzahl (1 - 4)                                            |
| 0x3 - 0xA   | Spieler_Struktur | 0x8  | Spieler 1                                                         |
| 0xB - 0x12  | Spieler_Struktur | 0x8  | Spieler 2                                                         |
| 0x13 - 0x1A | Spieler_Struktur | 0x8  | Spieler 3                                                         |
| 0x1B - 0x22 | Spieler_Struktur | 0x8  | Spieler 4                                                         |
</details>