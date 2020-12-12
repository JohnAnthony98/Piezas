/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, X_Starts)
{
	Piezas game;

  Piece placed = game.dropPiece(1);//X
  ASSERT_TRUE(placed == X);
}

TEST(PiezasTest, O_GoesSecond)
{
	Piezas game;

  game.dropPiece(1);//X
  Piece placed = game.dropPiece(1);//O
  ASSERT_TRUE(placed == O);
}

TEST(PiezasTest, TurnOrderMaintained)
{
	Piezas game;

  game.dropPiece(1);//X
  game.dropPiece(1);//O
  Piece placed = game.dropPiece(2);
  ASSERT_TRUE(placed == X);
}

TEST(PiezasTest, testReset)
{
	Piezas game;

  //fill up game board
  for(int column = 0; column < BOARD_COLS; column++){
    for(int row = 0; row < BOARD_ROWS; row++){
      Piece move = game.dropPiece(column);
      if(move == Invalid || move == Blank){
        ASSERT_TRUE(false);
      }
    }
  }

  game.reset();
  //make sure all spaces are blank
  bool notBlank = false;
  for(int column = 0; column < BOARD_COLS; column++){
    for(int row = 0; row < BOARD_ROWS; row++){
      if(game.pieceAt(row, column) != Blank){
        notBlank = true;
      }
    }
  }
  ASSERT_FALSE(notBlank);
}

TEST(PiezasTest, dropPieceInNegativeColumn)
{
	Piezas game;

  Piece placed = game.dropPiece(-3);//X
  ASSERT_TRUE(placed == Invalid);
}

TEST(PiezasTest, dropPieceInColumnTooLarge)
{
	Piezas game;

  Piece placed = game.dropPiece(7);//X
  ASSERT_TRUE(placed == Invalid);
}

TEST(PiezasTest, dropPieceInFullColumn)
{
	Piezas game;

  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  Piece placed = game.dropPiece(1);//X
  ASSERT_TRUE(placed == Blank);
}

TEST(PiezasTest, pieceAtNegativeColumn){
  Piezas game;

  Piece move = game.pieceAt(2, -1);//X
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtColumnTooLarge){
  Piezas game;

  Piece move = game.pieceAt(2, 9);//X
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtNegativeRow){
  Piezas game;

  Piece move = game.pieceAt(-1, 3);//X
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtRowTooLarge){
  Piezas game;

  Piece move = game.pieceAt(9, 2);//X
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtBlank){
  Piezas game;

  game.dropPiece(0);//X
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == Blank);
}

TEST(PiezasTest, pieceAtFirstMove){
  Piezas game;

  game.dropPiece(2);//X
  Piece move = game.pieceAt(0, 2);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtSecondMove){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(3);//O
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == O);
}

TEST(PiezasTest, pieceAtX){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(1);//X
  game.dropPiece(2);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtXWithInvalidMove){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(3);//O
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtO){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(3);//X
  game.dropPiece(0);//O
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == O);
}

TEST(PiezasTest, pieceAtOWithInvalidMove){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(3);//X
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == O);
}

TEST(PiezasTest, invalidGameState_1){
  Piezas game;

  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(3);//X
  Piece state = game.gameState();
  ASSERT_TRUE(state == Invalid);
}

TEST(PiezasTest, invalidGameState_2){
  Piezas game;

  Piece state = game.gameState();
  ASSERT_TRUE(state == Invalid);
}

TEST(PiezasTest, invalidGameState_3){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Invalid);
}

TEST(PiezasTest, invalidGameState_4){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Invalid);
}

TEST(PiezasTest, winnerIsX_1){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == X);
}

TEST(PiezasTest, winnerIsX_2){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == X);
}

TEST(PiezasTest, winnerIsX_3){
  Piezas game;

  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(3);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(1);//X
  game.dropPiece(2);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == X);
}

TEST(PiezasTest, winnerIsX_4){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(1);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == X);
}

TEST(PiezasTest, winnerIsO_1){
  Piezas game;

  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(1);//X
  game.dropPiece(2);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == O);
}

TEST(PiezasTest, winnerIsO_2){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(2);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O
  game.dropPiece(3);//X
  game.dropPiece(2);//O
  game.dropPiece(3);//X
  game.dropPiece(1);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == O);
}

TEST(PiezasTest, winnerIsO_3){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O
  game.dropPiece(3);//X
  game.dropPiece(2);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == O);
}

TEST(PiezasTest, winnerIsO_4){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(0);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(0);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == O);
}

TEST(PiezasTest, noWinnerIsTie_1){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Blank);
}

TEST(PiezasTest, winnerIsTie_2){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  game.dropPiece(2);//O
  game.dropPiece(3);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(2);//O
  game.dropPiece(1);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Blank);
}

TEST(PiezasTest, winnerIsTie_3){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(0);//X
  game.dropPiece(3);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O
  game.dropPiece(2);//X
  game.dropPiece(1);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Blank);
}

TEST(PiezasTest, winnerIsTie_4){
  Piezas game;

  game.dropPiece(0);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(3);//O
  game.dropPiece(0);//X
  game.dropPiece(0);//O
  game.dropPiece(1);//X
  game.dropPiece(1);//O
  game.dropPiece(2);//X
  game.dropPiece(2);//O
  game.dropPiece(3);//X
  game.dropPiece(3);//O

  Piece state = game.gameState();
  ASSERT_TRUE(state == Blank);
}
