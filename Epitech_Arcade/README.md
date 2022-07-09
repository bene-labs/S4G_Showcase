# arcade

## A project developed during the second year at Epitech.

Arcade is program that loads self-made graphic- and game logic libraries and links them together to play games.

This allows both games and graphics to be swapped on the fly while the program is running.

https://user-images.githubusercontent.com/62158116/178120831-d427ccf5-5599-4353-98bf-0e7832b0a1a4.mp4

As an additional challenge, the program had to support the libraries of all other current student groups as well.

https://user-images.githubusercontent.com/62158116/178120920-7c36e0f9-e09e-4892-a9a2-97779f50c583.mp4

To Make this possible we agreed on a documentation, which can be found in the doc folder.

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
