# arcade

## setup:

`cmake .`

`make`

## usage:

`./arcade [path to initial graphical intermediate dynamic library]`

`e.g.: "./arcade lib/arcade_sfml.so"`

## authors:

### code authors:

- Benedikt Mertes -> benedikt.mertes@epitech.eu
- Emile Hanau -> emile.hanau@epitech.de

### contact data - representatives from every group (documentation):

- Emile Hanau -> emile.hanau@epitech.de
- Niklas Scheffler  -> niklas.scheffler@epitech.eu
- Marcel Taubert    -> marcel.taubert@epitech.eu
- Ugur Hasan Güzel  -> ugur-hasan.guezel@epitech.eu

## sidenote ncurses:

- if ncurses displays a rectangle, it is required to adjust terminal size to the rectangle to continue
- Hint `[ctrl] + [-]`



# Controls:

## Menu:
- `1`: load prev graphic-library
- `2`: load next graphic-library
- `Escape`: quit application
- `W`:  select prev game-library
- `S`:  select next game-library
- `↑ (up-key)`: select prev graphic-library
- `↓ (down-key)`: select next graphic-library
- `spacebar`: start/stop entering username
- `enter`: confirm all selections


## In-game:
- `1`: load prev game-library
- `2`: load next game-library
- `3`: load prev graphic-library
- `4`: load next graphic-library
- `X`: quit application
- `Escape`: back to menu

## Nibbler:
- `↑ (up-key)`: move up
- `↓ (down-key)`: move down
- `→ (right-key)`: move right
- `← (left-key)`: move left
- `spacebar`: sprint (locks controls)

## Centipede:
- `↑ (up-key)` or `W`: move up
- `↓ (down-key)` or `S`: move down
- `→ (right-key)` or `D`: move right
- `← (left-key)` or `A`: move left