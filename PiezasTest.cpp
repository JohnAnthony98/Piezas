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
