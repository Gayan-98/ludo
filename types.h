
#ifndef TYPES_H
#define TYPES_H

#define MAX_PIECES 4
#define MAX_PLAYERS 4
#define BOARD_SIZE 52

// Enum for player colors
typedef enum { RED, GREEN, YELLOW, BLUE } PlayerColor;

// Enum for direction
typedef enum { CLOCKWISE, COUNTERCLOCKWISE } Direction;

// Struct for a piece
typedef struct {
    int id;             // Piece ID (1 to 4)
    PlayerColor color;  // Color of the piece
    int position;       // Position on the board (0 to 51) or -1 if in the base
    int in_base;        // 1 if in base, 0 if on the board
} Piece;

// Struct for a player
typedef struct {
    PlayerColor color;          // Color of the player
    Piece pieces[MAX_PIECES];   // Array of pieces
    Direction direction;        // Current direction of movement
    int pieces_in_base;         // Number of pieces still in base
} Player;

// Struct for the game
typedef struct {
    Player players[MAX_PLAYERS];  // Array of players
    int current_player;           // Index of the current player (0 to 3)
    int mystery_cell;             // Position of the mystery cell
    int rounds_passed;            // Number of rounds passed
} Game;

#endif
