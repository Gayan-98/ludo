#include "types.h"
#include "game_logic.c"

int main() {
    srand(time(NULL));  // Seed the random number generator
    Game game;
    initialize_game(&game);
    play_game(&game);
    return 0;
}
