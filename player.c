#include "header.h"

struct Player* createPlayer(char* name, char symbol, int idNum, int isComputer) {
    struct Player* p = malloc(sizeof(struct Player));
    strcpy(p->name, name);
    p -> symbol = symbol;
    p -> idNumber = idNum;
    p -> isComputer = isComputer;
    return p;
}
