#ifndef header_h
#define header_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#endif /* header_h */

#define NUM_TRIADS 8
#define NUM_SPACES 9

#define BUFFER_LEN 128

static const char* SPACE_NAMES[] = {
    "TL","TM","TR",
    "CL","CM","CR",
    "BL","BM","BR"
};

static const char* SPACE_NAMES_REVERSED[] = {
    "LT","MT","RT",
    "LC","MC","RC",
    "LB","MB","RB"
};

static const int TRIADS[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},
    {0,3,6}, {1,4,7}, {2,5,8},
    {0,4,8}, {2,4,6}
};

struct Player {
    char name[64];
    char symbol;
    int idNumber;
    int score;
    int isComputer;
};

struct TicBoard {
    char spaces[9];
    int free;
    int canPlacePiece;
    int winnerID;
};

struct GameSettings {
    struct Player* players[2];
    int numPlayersEntered;
    int isComplete;
    int consecutiveWin;
    int firstTurn;
};

struct Match {
    struct GameSettings* gs;
    struct TicBoard* board;
    int playerWhoWon;
    int isComplete;
    int turn;
};

struct Player* createPlayer(char*,char,int, int);
struct TicBoard* initializeEmptyBoard();
struct GameSettings* initializeGame();
struct Match* initializeMatch(struct GameSettings*);

void place(struct TicBoard*, struct Player*, int);
void recieveInput(char*, char*, int);
void recieveBlankInput();
void nextTurn(struct Match*);
void printBoard(struct TicBoard*);
void beginGame(struct GameSettings*);
void endGame(struct GameSettings*);

int checkValidSpace(char*, struct TicBoard*);
int checkValidSymbol(struct GameSettings*, char*);
int checkValidName(struct GameSettings*, char*, int);
int checkValidSymbol(struct GameSettings*, char*);
int checkNameTaken(struct GameSettings*, char*);
int checkValidRange(char*, int, int);
int endMatch(struct Match*);
int getRandomNumberInRange(int, int);