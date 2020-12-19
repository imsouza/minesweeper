/**
 * @file minesweeper.c
 * @brief A minesweeper game made in C  
 * @author Mateus Almeida
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "start.h"

//! Matrix size
#define TAM 10

/**
 * Static array with the messages that will be displayed
 */
static const char * const messages[] = {
  "\nBOOOM! Game Over...\n",                                                  // 0
  "\n-[ You win!!! ]-\n",                                                     // 1
  "\n-=-=-=-=-=--=-=-=-=-=-\n",                                               // 2
  "\n[!] Error, out of range.\n",                                             // 3
  "\n[!] Error, try other coordinates.\n",                                    // 4
  "\t\t  -[ Minesweeper ]-\n\t- [(1) Easy | (2) Medium | (3) Hard] -\n\n",    // 5
  "\n[+] Select your level: ",                                                // 6
  "\n[!] Select the correct level!\n",                                        // 7
  "\nTry again [Y|N] ?\b",                                                    // 8
  "\n[+] New coordinate (X, Y): ",                                            // 9
  "\n\n[-] Remaining fields: "                                                // 10
};


/**
 * This function calculates the remaining fields and their 
 * neighbors that have bombs
 * @param board: matrix
 * @param posX: x coordenate
 * @param posY: y coordenate
 */
int countFields (int board[][TAM], int posX, int posY) {
  int i, j, count=0;

  if (board[posX + 1][posY + 1] == 9) count++;
  if (board[posX + 1][posY] == 9)     count++;
  if (board[posX][posY + 1] == 9)     count++;
  if (board[posX - 1][posY - 1] == 9) count++;
  if (board[posX - 1][posY] == 9)     count++;
  if (board[posX][posY - 1] == 9)     count++;
  if (board[posX + 1][posY - 1] == 9) count++;
  if (board[posX - 1][posY + 1] == 9) count++;

  return count;
}


/**
 * This function checks the coordinates entered by 
 * the user in the field
 * @param board: matrix
 * @param posX: x coordenate
 * @param posY: y coordenate
 * @param count: auxiliary variable for counting
 */
void checkBoard (int board[][TAM], int posX, int posY, int count) {
  int newPosX, newPosY;

  //! Base case
  checkVictory(board, posX, posY, count);
  plotBoard(board, posX, posY);

  printf("%s%d\n", messages[10], count);
  printf("%s", messages[2]);
  printf("%s", messages[9]);

  scanf("%d %d", &newPosX, &newPosY);

  //! Checks for errors in positions
  if (newPosX > 8 || newPosY > 8 || newPosX < 1 || newPosY < 1) {
    printf("%s", messages[3]);
    return checkBoard(board, newPosX=0, newPosY=0, count);
  } if (board[newPosX][newPosY] == 1) {
    printf("%s", messages[4]);
    return checkBoard(board, newPosX=0, newPosY=0, count);
  }

  return checkBoard(board, newPosX, newPosY, count-1);
}


/**
 * This function checks whether the player has won or not
 * @param board: matrix
 * @param posX: x coordenate
 * @param posY: y coordenate
 * @param count: auxiliary variable for counting
 */
void checkVictory (int board[][TAM], int posX, int posY, int count) {
  if (board[posX][posY] == 9 && count != 0) {
    printf("%s", messages[0]);
    continueGame();
  } if (count == 0) {
    printf("%s", messages[1]);
    continueGame();
  }
}


/**
 * This function displays the game on the screen
 * @param board: matrix
 * @param posX: x coordenate
 * @param posY: y coordenate
 */
void plotBoard (int board[][TAM], int posX, int posY) {
  int i, j;
  for (i = 0; i < 11; i++) {
    putchar('\n');
    for (j = 0; j < 10; j++) {
      board[posX][posY] = 1;
      if (i == 10 && j != 0 && j < 9) printf("%d ", j);
      if (j == 0 && i < 9) printf("%d ", i);
      if (i > 8 && j < 1) printf("  ");
      if (i == 0 || j == 0 || i == 9 || j == 9) printf("%s", i == 0 || i == 9 ? "=-" : "| ");
      else if (board[i][j] == 1) printf("%d ", countFields(board, i, j));
      else if (i != 10) printf("o ");
    }
  }
}


/**
 * This function creates the board with bombs at 
 * random locations according to the selected level 
 * and gives the number of fields without bombs
 * @param level: variable indicating the difficulty level of the game
 */
void generateBombs (int level) {
  int board[TAM][TAM], amount=level+4;
  
  while (level >= 0) {
    board[rand() % 9][rand() % 10] = 9;
    level--;
  }

  checkBoard(board, 0, 0, amount);
}


/**
 * This function displays a game continuation message
 */
void continueGame () {
  char resp;

  do {
    printf("%s", messages[2]);
    printf("%s", messages[8]);
    getchar();
    scanf("%c", &resp);

    switch (resp) {
      case 'y':
      case 'Y': levelSelector(); break;
      case 'n':
      case 'N': exit(0); break;
    }

  } while (resp != 'N' || resp != 'n');
}


/**
 * This function displays a level selection message
 */
void levelSelector () {
  int level;

  system("clear");

  do {
    printf("%s", messages[5]);
    printf("%s", messages[6]);

    scanf("%d", &level);

    if (level < 1 || level > 3) {
      printf("%s", messages[7]);
      sleep(2); 
      system("clear");
    }

  } while (level < 1 || level > 3);

  generateBombs(level*8);
}


//! Start
void main () {
  levelSelector();
}

