#include "header.h"

void beginGame(struct GameSettings* gs) {
    gs->isComplete = 0;
    gs->consecutiveWin = -1;
    gs->firstTurn = getRandomNumberInRange(-1, 1);
    
    struct Player* player1 = gs->players[0];
    struct Player* player2 = gs->players[1];
    
    printf("\e[1;1H\e[2J");
    printf("Beginning Game! %s vs %s\n", player1->name, player2->name);
    printf("First Turn Will Be %s\n",gs->players[gs->firstTurn]->name);
    printf("Press Enter to Start");
    recieveBlankInput();
}

void endGame(struct GameSettings* gs) {
    for (int i = 0; i < gs->numPlayersEntered; i++) {
        free(gs->players[i]);
    }
    free(gs);
}

struct GameSettings* initializeGame() {
    struct GameSettings* gs = malloc(sizeof(struct GameSettings));
    
    gs->numPlayersEntered = 0;
    int numPlayers = 2;
    
    /*
    char numPlayersInput[BUFFER_LEN];
    int numPlayers;
    
    recieveInput(numPlayersInput, "1 or 2 Players? ", 0);
    numPlayers = checkValidRange(numPlayersInput,0,2);
    while (numPlayers == -1) {
        printf("Invalid Input!\n");
        recieveInput(numPlayersInput, "1 or 2 Players? ", 0);
        numPlayers = checkValidRange(numPlayersInput,1,2);
    }
     */
    int i = 0;
    for (; i < numPlayers; i++) {
        char playerNameInput[BUFFER_LEN];
        char symbolInput[BUFFER_LEN];
        char symbol;
        char prompt[128];
        
        snprintf(prompt, 128, "Enter Player %i's Name: ", i+1);
        recieveInput(playerNameInput, prompt, 0);
        while (!checkValidName(gs,playerNameInput, 12)) {
            printf("Name Invalid\n");
            recieveInput(playerNameInput, prompt, 0);
        }
        
        snprintf(prompt, 128, "Enter Player %i's Symbol: ", i+1);
        recieveInput(symbolInput, prompt, 0);
        while (!checkValidSymbol(gs, symbolInput)) {
            printf("Symbol Invalid\n");
            recieveInput(symbolInput, prompt, 0);
        }
        symbol = symbolInput[0];
        
        gs->players[i] = createPlayer(playerNameInput, symbol, i, 0);
        gs->numPlayersEntered++;
    }
    
    for ( ; i < 2; i++) {
        char* symbol = "X";
        char* name = "SkyNet";
        if (!checkValidSymbol(gs, symbol)) symbol = "O";
        if (!checkNameTaken(gs, name)) name = "Hal";
        gs->players[i] = createPlayer(name, symbol[0], i, 1);
        gs->numPlayersEntered++;
    }
    
    return gs;
}