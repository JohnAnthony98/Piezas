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

  Piece placed = game.dropPiece(1);
  ASSERT_TRUE(placed == X);
}

TEST(PiezasTest, O_GoesSecond)
{
	Piezas game;

  game.dropPiece(1);
  Piece placed = game.dropPiece(1);
  ASSERT_TRUE(placed == O);
}

TEST(PiezasTest, TurnOrderMaintained)
{
	Piezas game;

  game.dropPiece(1);
  game.dropPiece(1);
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
  for(int column; column < BOARD_COLS; column++){
    for(int row; row < BOARD_ROWS; row++){
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

  Piece placed = game.dropPiece(-3);
  ASSERT_TRUE(placed == Invalid);
}

TEST(PiezasTest, dropPieceInColumnTooLarge)
{
	Piezas game;

  Piece placed = game.dropPiece(7);
  ASSERT_TRUE(placed == Invalid);
}

TEST(PiezasTest, dropPieceInFullColumn)
{
	Piezas game;

  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  Piece placed = game.dropPiece(1);
  ASSERT_TRUE(placed == Blank);
}

TEST(PiezasTest, pieceAtNegativeColumn){
  Piezas game;

  Piece move = game.pieceAt(2, -1);
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtColumnTooLarge){
  Piezas game;

  Piece move = game.pieceAt(2, 9);
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtNegativeRow){
  Piezas game;

  Piece move = game.pieceAt(-1, 3);
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtRowTooLarge){
  Piezas game;

  Piece move = game.pieceAt(9, 2);
  ASSERT_TRUE(move == Invalid);
}

TEST(PiezasTest, pieceAtBlank){
  Piezas game;

  game.dropPiece(0);
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == Blank);
}

TEST(PiezasTest, pieceAtFirstMove){
  Piezas game;

  game.dropPiece(2);
  Piece move = game.pieceAt(0, 2);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtSecondMove){
  Piezas game;

  game.dropPiece(2);
  game.dropPiece(3);
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == O);
}

TEST(PiezasTest, pieceAtX){
  Piezas game;

  game.dropPiece(2);
  game.dropPiece(2);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(0);
  game.dropPiece(3);
  game.dropPiece(0);
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtXWithInvalidMove){
  Piezas game;

  game.dropPiece(2);
  game.dropPiece(2);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(3);
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == X);
}

TEST(PiezasTest, pieceAtO){
  Piezas game;

  game.dropPiece(2);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(0);
  game.dropPiece(3);
  game.dropPiece(0);
  Piece move = game.pieceAt(1, 0);
  ASSERT_TRUE(move == O);
}

TEST(PiezasTest, pieceAtOWithInvalidMove){
  Piezas game;

  game.dropPiece(2);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(3);
  Piece move = game.pieceAt(0, 3);
  ASSERT_TRUE(move == O);
}
