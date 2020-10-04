#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "output.h"
#include "start.h"

// This function calculates the remaining fields and their neighbors that have bombs
int countFields (int board[10][10], int x, int y) {
  int i, j, count=0;

  if (board[x + 1][y + 1] == 9) count++;
  if (board[x + 1][y] == 9)     count++;
  if (board[x][y + 1] == 9)     count++;
  if (board[x - 1][y - 1] == 9) count++;
  if (board[x - 1][y] == 9)     count++;
  if (board[x][y - 1] == 9)     count++;
  if (board[x + 1][y - 1] == 9) count++;
  if (board[x - 1][y + 1] == 9) count++;

  return count;
}


// This function checks the coordinates entered by the user in the field
void checkBoard (int board[10][10], int posX, int posY, int count) {
  int newPosX, newPosY;

  // Base case
  checkVictory(board, posX, posY, count);
  plotBoard(board, posX, posY);

  showRemainingFieldsMessage;
  showSeparator;
  showNewCoordinatesMessage;
  scanf("%d %d", &newPosX, &newPosY);

  // Checks for errors in positions
  if (newPosX > 8 || newPosY > 8 || newPosX < 1 || newPosY < 1) {
    showRangeErrorMessage;
    return checkBoard(board, newPosX=0, newPosY=0, count);
  } if (board[newPosX][newPosY] == 1) {
    showCoordinatesErrorMessage;
    return checkBoard(board, newPosX=0, newPosY=0, count);
  }

  return checkBoard(board, newPosX, newPosY, count-1);
}


// This function checks whether the player has won or not
void checkVictory (int board[10][10], int posX, int posY, int count) {
  if (board[posX][posY] == 9 && count != 0) {
    showGameOverMessage;
    continueGame();
  } if (count == 0) {
    showWinMessage;
    continueGame();
  }
}


// This function displays the game on the screen
void plotBoard (int board[10][10], int posX, int posY) {
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

  return;
}


// This function creates the board with bombs at random locations according to 
// the selected level and gives the number of fields without bombs
void generateBombs (int level) {
  int board[10][10], amount=level+4;
  
  while (level >= 0) {
    board[rand() % 9][rand() % 10] = 9;
    level--;
  }

  checkBoard(board, 0, 0, amount);
}


// This function displays a game continuation message
void continueGame () {
  char resp;

  do {
    showSeparator;
    showTryAgainMessage;
    getchar();
    scanf("%c", &resp);

    switch (resp) {
      case 'y':
      case 'Y': levelSelector(); break;
      case 'n':
      case 'N': exit(0); break;
    }

  } while (resp != 'N' || resp != 'n');

  return;
}


// This function displays a level selection message
void levelSelector () {
  int level;

  system("clear");

  do {
    showHeaderGame;
    showSelectLevelMessage;

    scanf("%d", &level);

    if (level < 1 || level > 3) {
      showSelectLevelAlertMessage;
      sleep(2); 
      system("clear");
    }

  } while (level < 1 || level > 3);

  generateBombs(level*8);
}


// Start
void main () {
  levelSelector();
}

