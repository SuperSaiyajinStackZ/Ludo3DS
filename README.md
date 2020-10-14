# Ludo3DS
<p align="center">
	<a href="https://github.com/SuperSaiyajinStackZ/Ludo3DS/releases/latest"><img src="https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/3ds/app/Banner.png"></a><br>
	<b>Ludo3DS ist ein 'Work in progress' `Ludo` klon für den Nintendo 3DS.</b><br>
</p>

Dieses Spiel ist ebenso als [Mensch ärger Dich nicht](https://de.wikipedia.org/wiki/Mensch_%C3%A4rgere_Dich_nicht) bekannt.

Ludo3DS' Core wurde geschrieben von [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ).

Ludo3DS wird ein Teil von [StackGames](https://github.com/SuperSaiyajinStackZ/Stack-Game-Template) in der Zukunft werden.

[3DElf](https://github.com/SuperSaiyajinStackZ/3DElf)'s code wurde als basis für dieses Spiel benutzt. Du kannst dies auch auschecken, falls du an einem `Elfer raus!` klon interessiert bist.

## Screenshots

Hier findest du ein paar Screenshots zum aktuellen Fortschritt.

### Credits Overlay
![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/credits_en.png)

### Spiel Screen
![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/instructions1_en.png) ![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/instructions2_en.png) ![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/game_screen_en.png) ![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/sub_menu_en.png)

### Splash Overlay
![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/splash_en.png)

### Sprachauswahl Overlay
![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/language_overlay_en.png)

### Würfel Overlay
![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/dice_overlay_en.png) ![](https://github.com/SuperSaiyajinStackZ/Ludo3DS/blob/main/screenshots/dice_overlay2_en.png)

## Kompilieren
### Die Umgebung aufsetzen

Um Ludo3DS vom quellcode zu kompilieren, musst du deine Umgebung mit devkitARM, Libctru, Citro2D und Citro3D aufsetzen. Folge devkitPro's [Getting Started](https://devkitpro.org/wiki/Getting_Started) Seite um pacman zu installieren, dann führe `(sudo dkp-)pacman -S 3ds-dev` aus. Du wirst ebenfalls [bannertool](https://github.com/Steveice10/bannertool/releases/latest) und [makerom](https://github.com/profi200/Project_CTR/releases/latest) im `3ds` Ordner benötigen.

### Klonen der Repository

Um den quellcode herunterzuladen, musst du dies mit submodulen klonen, das kann gemacht werden in dem du folgendes ausführst:
```
git clone --recursive https://github.com/SuperSaiyajinStackZ/Ludo3DS.git
```
Oder falls du es bereits geklont hast:
```
git submodule update --init --recursive
```
um alle submodule zu aktualisieren.


Danach führe einfach `make` im `3ds` Ordner aus.

## Credits
### Haupt-Entwicklers
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Haupt-Entwickler von Ludo3DS.

### Andere
- [devkitPro](https://github.com/devkitPro): Für devkitARM, Libctru, Citro2D & Citro3D.
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Für die Grafiken.
- [Universal-Team](https://github.com/Universal-Team): Für Universal-Core.