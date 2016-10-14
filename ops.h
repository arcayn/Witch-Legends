#pragma once
#include "player.h"
#include "Enemy.h"

void processInteraction(Player &player, int prevComm);
void getComm(Player &player);
void processCommand(Player &player, string command);
void processEnvironment(Player &player);
void gameWalk(string direction, Player &player, int comm, int distance);
void writeData(Player &player);
void processEnemies(Player &player, int prevComm);
void gameOpen(string toSearch, Player &player, int comm);
void gameSearch(Player &player, int comm);
void processAP(Player &player);
void metaProfile(Player &player, int comm);
void enemyMovement();
void enemyDetection(Player &player, int prevComm);
void reduceAP(Player &player);
void refundAP(Player &player, int refund);
void gameDrop(Player &player, string item, int quantity);
void gameEsp(Player &player);
void gameSleep(Player &player);
void gameClose(string toSearch, Player &player, int comm);
void gameTalk(Player &player, string entity);
void metaInv(Player &player);
void gameTake(Player &player, string item);


int castSpark(string target);

void talkEntity(string diFile, string genName, Player &player);