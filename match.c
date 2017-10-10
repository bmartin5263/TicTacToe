#include "header.h"

void nextTurn(struct Match* m) {
    printf("\e[1;1H\e[2J");
    struct TicBoard* board = m->board;
    struct Player* player = m->gs->players[m->turn];
    
    int turnComplete = 0;
    char userInput[BUFFER_LEN];
    int space;
    //char prompt[BUFFER_LEN];
    
    while(!turnComplete) {
    
        printBoard(board);
        printf("%s please select a space.\n",player->name);
        recieveInput(userInput, "Space: ", 1);
        space = checkValidSpace(userInput, board);
        
        while(space == -1 || space == -2) {
            if (space == -1) printf("Invalid Space!\n");
            else printf("Space Already Taken!\n");
            printf("%s please select a space.\n",player->name);
            recieveInput(userInput, "Space: ", 1);
            space = checkValidSpace(userInput, board);
        }
        
        place(board, player, space);
        turnComplete = 1;
        
    }
    
    if (!board->canPlacePiece) {
        m->isComplete = 1;
        m->playerWhoWon = m->board->winnerID;
    } else {
        if (m->turn == 0) m->turn = 1;
        else m->turn = 0;
    }
}

struct Match* initializeMatch(struct GameSettings* gs) {
    struct Match* m = malloc(sizeof(struct Match));
    struct TicBoard* b = initializeEmptyBoard();
    
    m->gs = gs;
    m->board = b;
    m->isComplete = 0;
    m->turn = gs->firstTurn;
    m->playerWhoWon = -1;
    return m;
}

int endMatch(struct Match* m) {
    printf("\e[1;1H\e[2J");
    printBoard(m->board);
    int winner = m->playerWhoWon;
    free(m->board);
    free(m);
    return winner;
}
