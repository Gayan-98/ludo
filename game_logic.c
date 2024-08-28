#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize the game
void initialize_game(Game *game) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        game->players[i].color = i;
        game->players[i].direction = CLOCKWISE;
        game->players[i].pieces_in_base = MAX_PIECES;
        for (int j = 0; j < MAX_PIECES; j++) {
            game->players[i].pieces[j].id = j + 1;
            game->players[i].pieces[j].color = i;
            game->players[i].pieces[j].position = -1;  // -1 indicates in the base
            game->players[i].pieces[j].in_base = 1;
        }
    }
    game->current_player = 0;
    game->mystery_cell = -1;  // No mystery cell at start
    game->rounds_passed = 0;
}

// Roll the dice
int roll_dice() {
    return rand() % 6 + 1;  // Returns a number between 1 and 6
}

// Print the current state of the game
void print_game_state(Game *game) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player *player = &game->players[i];
        printf("Player %d (%d pieces in base):\n", i, player->pieces_in_base);
        for (int j = 0; j < MAX_PIECES; j++) {
            Piece *piece = &player->pieces[j];
            printf("Piece %d is at position %d\n", piece->id, piece->position);
        }
        printf("\n");
    }
}

// Move a piece
void move_piece(Game *game, Player *player, Piece *piece, int roll) {
    if (piece->in_base) {
        if (roll == 6) {
            piece->position = 0;  // Move to starting position
            piece->in_base = 0;
            player->pieces_in_base--;
            printf("Player %d moves piece %d to the starting position.\n", player->color, piece->id);
        }
    } else {
        int new_position = piece->position + roll;
        
        // Check if the piece reaches home
        if (new_position > 51) {
            new_position = 52; // Mark piece as at home
        } else {
            new_position %= BOARD_SIZE;
        }
        
        piece->position = new_position;
        printf("Player %d moves piece %d to position %d.\n", player->color, piece->id, new_position);
    }
}

// Function to check if a player has won
int check_winner(Player *player) {
    int pieces_at_home = 0;
    for (int i = 0; i < MAX_PIECES; i++) {
        if (player->pieces[i].position == 52) {  // 52 indicates home
            pieces_at_home++;
        }
    }
    return pieces_at_home == MAX_PIECES;
}

// Main game loop
void play_game(Game *game) {
    int game_over = 0;
    while (!game_over) {
        Player *current_player = &game->players[game->current_player];
        int roll = roll_dice();
        printf("Player %d rolls a %d.\n", current_player->color, roll);

        // Move the first piece that can be moved
        for (int i = 0; i < MAX_PIECES; i++) {
            if (current_player->pieces[i].in_base && roll == 6) {
                move_piece(game, current_player, &current_player->pieces[i], roll);
                break;
            } else if (!current_player->pieces[i].in_base && current_player->pieces[i].position < 52) {
                move_piece(game, current_player, &current_player->pieces[i], roll);
                break;
            }
        }

        // Print the state of the game
        print_game_state(game);

        // Check if the current player has won
        if (check_winner(current_player)) {
            printf("Player %d wins the game!\n", current_player->color);
            game_over = 1;
        }

        // Move to the next player
        game->current_player = (game->current_player + 1) % MAX_PLAYERS;
    }
}
