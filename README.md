# Tic Tac Toe
A tic-tac-toe game featuring an advanced artificial intelligence and a configurable grid up to 20x20 cells.  
This game is designed to be played in a VT100 terminal.

## Rules
The player or the computer must align 5 consecutive cells to win.  
The cells can be aligned vertically, horizontally or diagonally.  
The specificity of this game is that a cell can be placed only close to another cell.

## Installation
Clone the repository :
```
git clone https://github.com/RICCIARDI-Adrien/Tic_Tac_Toe
```

Compile the game :
```
cd Tic_Tac_Toe
make
```

Install the game :
```
sudo make install
```

## Uninstallation
You can remove the game using :
```
sudo make uninstall
```

## Playing the game
Open a terminal large enough for the grid you want to play and type :
```
Tic_Tac_Toe 15
```
If you want to play with a 15x15 grid. Allowed grid values are 10, 15 and 20.  
Use Z, Q, S and D to move the cursor (non AZERTY keyboards can adapt the keys in the source code), Space to insert a circle, and X to exit.