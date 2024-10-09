/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Bryce Chesley
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dRow;
   int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;

public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position& rhs) { this->colRow = rhs.colRow; }
   Position() : colRow(0x99) { colRow = 0x00; }
   bool isInvalid() const { return colRow & 0x88; }
   bool isValid()   const { return !(colRow & 0x88); }
   void setValid() {              }
   void setInvalid() {              }
   bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
   bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
   bool operator != (const Position& rhs) const { return colRow != rhs.colRow; }
   const Position& operator =  (const Position& rhs) { this->colRow = rhs.colRow; return *this; }

   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) : colRow(0x99) {
      if (isValid()) {
         uint8_t row = location / 8; uint8_t col = location % 8; this->colRow = (col << 4) | row;
      }
   }
   int getLocation() const {
      int row = colRow & 0x0F; int col = (colRow & 0xF0) >> 4; int position = row * 8 + col; return position;
   }
   void setLocation(int location) {
      if (isValid()) {
         uint8_t row = location / 8; uint8_t col = location % 8; this->colRow = (col << 4) | row;
      }
   }


   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r) : colRow(0x99) {
      if (c >= 0 && c < 8 && r >= 0 && r < 8) { colRow = (c << 4) | r; }
      else colRow = 0x99;
   }
   virtual int getCol() const;
   virtual int getRow() const;
   void setRow(int r) { colRow = (0 << 4) | r; }
   void setCol(int c) { colRow = (c << 4) | 0; }
   void set(int c, int r) { if (c >= 0 && c < 8 && r >= 0 && r < 8) { colRow = (c << 4) | r; } else colRow = 0x99; }

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"

   Position(const char* s);   //: colRow(0x99)
   const Position& operator =  (const char* rhs);
   const Position& operator =  (const string& rhs);



   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const { return getCol() * getSquareWidth(); }
   int getY()   const { return getRow() * getSquareHeight(); }
   void setXY(double x, double y);
   double getSquareWidth()  const { return squareWidth; }
   double getSquareHeight() const { return squareHeight; }
   void setSquareWidth(double width = 0) { this->squareWidth = width; }
   void setSquareHeight(double height = 0) { this->squareHeight = height; }

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   Position(const Position& rhs, const Delta& delta);  //: colRow(-1)
   void adjustRow(int dRow);
   void adjustCol(int dCol);
   const Position& operator += (const Delta& rhs);
   Position operator + (const Delta& rhs);

private:
   void set(uint8_t colRowNew) { }

   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};


ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);

