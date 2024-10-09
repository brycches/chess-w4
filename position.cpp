/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Bryce Chesley
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>

/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream& operator << (ostream& out, const Position& rhs)
{
   out << "error";
   return out;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator >> (istream& in, Position& rhs)
{
   return in;
}

/*************************************
 * POSITION CONSTRUCTOR GIVEN CHAR
 **************************************/
Position::Position(const char* s) : colRow(0x99) {
   if (s != nullptr && strlen(s) >= 2) {
      char colChar = s[0];
      char rowChar = s[1];

      // Handle column character
      int col;
      if (colChar >= 'a' && colChar <= 'h') {
         col = colChar - 'a';
      }
      else if (colChar >= 'A' && colChar <= 'H') {
         col = colChar - 'A';
      }
      else {
         colRow = 0xff;
         return;
      }

      // Handle row character
      int row;
      if (rowChar >= '1' && rowChar <= '8') {
         row = rowChar - '1';
      }
      else {
         colRow = 0xff;
         return;
      }

      // Set colRow
      colRow = (col << 4) | row;
   }
   else {
      colRow = 0xff;
   }
}

const Position& Position:: operator=(const char* rhs)
{
   colRow = 0x99; // Initialize to invalid
   if (rhs != nullptr && strlen(rhs) >= 2) {
      char colChar = rhs[0];
      char rowChar = rhs[1];

      // Handle column character
      int col;
      if (colChar >= 'a' && colChar <= 'h') {
         col = colChar - 'a';
      }
      else if (colChar >= 'A' && colChar <= 'H') {
         col = colChar - 'A';
      }
      else {
         return *this;
      }

      // Handle row character
      int row;
      if (rowChar >= '1' && rowChar <= '8') {
         row = rowChar - '1';
      }
      else {
         return *this;
      }

      // Set colRow if both col and row are valid
      colRow = (col << 4) | row;
   }
   return *this;
}

const Position& Position:: operator=(const string& rhs)
{
   colRow = 0x99; // Initialize to invalid
   if (rhs.length() >= 2) {
      char colChar = rhs[0];
      char rowChar = rhs[1];

      // Handle column character
      int col;
      if (colChar >= 'a' && colChar <= 'h') {
         col = colChar - 'a';
      }
      else if (colChar >= 'A' && colChar <= 'H') {
         col = colChar - 'A';
      }
      else {
         return *this;
      }

      // Handle row character
      int row;
      if (rowChar >= '1' && rowChar <= '8') {
         row = rowChar - '1';
      }
      else {
         return *this;
      }

      // Set colRow if both col and row are valid
      colRow = (col << 4) | row;
   }
   return *this;
}

void Position::setXY(double x, double y)
{
   if (squareWidth > 0 && squareHeight > 0) {
      int col = static_cast<int>(x / squareWidth);
      int row = static_cast<int>(y / squareHeight);

      if (col >= 0 && col < 8 && row >= 0 && row < 8) {
         colRow = (col << 4) | row;
      }
      else {
         colRow = 0xff;
      }
   }
   else {
      colRow = 0xff;
   }
}

int Position::getCol() const
{
   if (isValid())
   {
      return (colRow & 0xF0) >> 4;
   }
   else
   {
      return -1;
   }
}
int Position::getRow() const
{
   if (isValid())
   {
      return colRow & 0x0F;
   }
   else
   {
      return -1;
   }
}

Position::Position(const Position& rhs, const Delta& delta)
{
   int col = rhs.getCol() + delta.dCol;
   int row = rhs.getRow() + delta.dRow;

   if (col >= 0 && col < 8 && row >= 0 && row < 8) {
      colRow = (col << 4) | row;
   }
   else {
      colRow = 0xff;
   }
}

void Position::adjustRow(int dRow)
{
   int row = getRow();
   row += dRow;
   int col = getCol();

   if (col >= 0 && col < 8 && row >= 0 && row < 8) {
      colRow = (col << 4) | row;
   }
   else {
      colRow = 0xff;
   }
}

void Position::adjustCol(int dCol)
{
   int row = getRow();
   int col = getCol() + dCol;

   if (col >= 0 && col < 8 && row >= 0 && row < 8) {
      colRow = (col << 4) | row;
   }
   else {
      colRow = 0x99;
   }
}

const Position& Position:: operator += (const Delta& rhs)
{
   int col = getCol() + rhs.dCol;
   int row = getRow() + rhs.dRow;

   if (col >= 0 && col < 8 && row >= 0 && row < 8) {
      this->colRow = (col << 4) | row;
      return *this;
   }
   else {
      this->colRow = 0xff;
      return *this;
   }
}

Position Position:: operator + (const Delta& rhs)
{
   int col = getCol() + rhs.dCol;
   int row = getRow() + rhs.dRow;

   if (col >= 0 && col < 8 && row >= 0 && row < 8)
   {
      this->colRow = (col << 4) | row;
      return *this;
   }
   else {
      this->colRow = 0xff;
      return *this;
   }
}