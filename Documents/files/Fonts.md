# Fonts
Fonts saved in two separate files. PNG and NWF
For example:
Basic16.png
Basic16.nwf

## New World Font (.nwf)
Custom file that save the data about the font.
To create this file use "NewWorldPlugin create-font" command

## Atlas Font (.nwf.png)
Transparent image that save the font.

### Format:
* uint FamilyNameLength
* String FamilyName
* uint Size
* uint CharactersCount
* 4 arraies of Character

Character:
* char Name
* int AtlasX
* int AtlasY
* int Width
* int Height
* int OriginX
* int OriginY
* int PainterStepX