/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    Arlo Jolley
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
	source = INVALID;
	dest = INVALID;
	promote = SPACE;
	capture = SPACE;
	moveType = MOVE_ERROR;
	isWhite = true;
	text = "";
}

Move::Move(string smith, bool white)
{
	source = smith.substr(0, 2);
	dest = smith.substr(2, 2);
	if (smith.length() > 4)
	{
		if (smith.length() == 5) // promote or capture
		{
			char action = smith[4];
			switch (action)
			{
			case 'p':
				promote = SPACE;
				capture = PAWN;
				moveType = MOVE;
				break;
			case 'n':
				promote = SPACE;
				capture = KNIGHT;
				moveType = MOVE;
				break;
			case 'b':
				promote = SPACE;
				capture = BISHOP;
				moveType = MOVE;
				break;
			case 'r':
				promote = SPACE;
				capture = ROOK;
				moveType = MOVE;
				break;
			case 'q':
				promote = SPACE;
				capture = QUEEN;
				moveType = MOVE;
				break;
			case 'k':  // place holder and end game condition
				promote = SPACE;
				capture = KING;
				moveType = MOVE;
				break;
			case 'c':
				promote = SPACE;
				capture = SPACE;
				moveType = CASTLE_KING;
				break;
			case 'C':
				promote = SPACE;
				capture = SPACE;
				moveType = CASTLE_QUEEN;
				break;
			case 'E':
				promote = SPACE;
				capture = PAWN;
				moveType = ENPASSANT;
				break;
			case 'N':
				promote = KNIGHT;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'B':
				promote = BISHOP;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'R':
				promote = ROOK;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'Q':
				promote = QUEEN;
				capture = SPACE;
				moveType = MOVE;
				break;
			default:
				promote = SPACE;
				capture = SPACE;
				moveType = MOVE_ERROR;
			}
		}
		else // capture and promote
		{
			string action = smith.substr(4, 2);
			if (action == "pQ" || action == "Qp")
			{
				promote = QUEEN;
				capture = PAWN;
				moveType = MOVE;
			}
			else if (action == "nQ" || action == "Qn")
			{
				promote = QUEEN;
				capture = KNIGHT;
				moveType = MOVE;
			}
			else if (action == "bQ" || action == "Qb")
			{
				promote = QUEEN;
				capture = BISHOP;
				moveType = MOVE;
			}
			else if (action == "rQ" || action == "Qr")
			{
				promote = QUEEN;
				capture = ROOK;
				moveType = MOVE;
			}
			else if (action == "qQ" || action == "Qq")
			{
				promote = QUEEN;
				capture = QUEEN;
				moveType = MOVE;
			}
		}
	}
	else // no promote or capture
	{
		promote = SPACE;
		capture = SPACE;
		moveType = MOVE;
	}
	isWhite = white;
	text = smith;
}

//Move::Move(Position s, Position d, MoveType m, PieceType cap, PieceType pro, bool white)
//{
//	isWhite = white;
//	source = s;
//	dest = d;
//	promote = pro;
//	capture = cap;
//	moveType = m;
//	//text = source + dest; //+ if cap, pro, move;
//}

Position Move::getSource()
{
	return source;
}

void Move::setSource(Position s)
{
	source = s;
}

Position Move::getDest()
{
	return dest;
}

void Move::setDest(Position d)
{
	dest = d;
	//text += d;
}

PieceType Move::getPromote()
{
	return promote;
}

void Move::setPromote(PieceType pro)
{
	promote = pro;
}

PieceType Move::getCapture()
{
	return capture;
}

void Move::setCapture(PieceType cap)
{
	capture = cap;
}

Move::MoveType Move::getMoveType()
{
	return moveType;
}

void Move::setMoveType(MoveType m)
{
	moveType = m;
}

bool Move::getIsWhite()
{
	return isWhite;
}

void Move::setIsWhite(bool w)
{
	isWhite = w;
}

string Move::getText()
{
	return text;
}

char Move::conv(int col)
{
	switch (col + 1)
	{
	case 1:
		return 'a';
		break;
	case 2:
		return 'b';
		break;
	case 3:
		return 'c';
		break;
	case 4:
		return 'd';
		break;
	case 5:
		return 'e';
		break;
	case 6:
		return 'f';
		break;
	case 7:
		return 'g';
		break;
	case 8:
		return 'h';
		break;
	}
}

string Move::getText(Position sour, Position des, MoveType type, PieceType cap, PieceType pro)
{
	string s;
	string d;
	string t;

	int sc = sour.getCol();
	int sr = sour.getRow();
	int dc = des.getCol();
	int dr = des.getRow();

	s = conv(sc) + to_string(sr + 1);
	d = conv(dc) + to_string(dr + 1);
	if (type == MOVE)
	{
		if (cap != SPACE)
		{
			switch (cap)
			{
			case PAWN:
				t = 'p';
				break;
			case KNIGHT:
				t = 'n';
				break;
			case BISHOP:
				t = 'b';
				break;
			case ROOK:
				t = 'r';
				break;
			case QUEEN:
				t = 'q';
				break;
			case KING:    //not posible
				t = 'k';
				break;
			}
		}
		else
		{
			t = "";
		}
	}
	else if (type == ENPASSANT)
	{
		t = 'E';
	}
	else if (type == CASTLE_KING)
	{
		t = 'c';
	}
	else if (type == CASTLE_QUEEN)
	{
		t = 'C';
	}


	text = s + d + t;
	//std::cout << "getText return:" << text << std::endl;  // debugging
	return text;
}

void Move::setText(string smith)
{
	text = smith;
	source = smith.substr(0, 2);
	dest = smith.substr(2, 2);
	if (smith.length() > 4)
	{
		if (smith.length() == 5) // promote or capture
		{
			char action = smith[4];
			switch (action)
			{
			case 'p':
				promote = SPACE;
				capture = PAWN;
				moveType = MOVE;
				break;
			case 'n':
				promote = SPACE;
				capture = KNIGHT;
				moveType = MOVE;
				break;
			case 'b':
				promote = SPACE;
				capture = BISHOP;
				moveType = MOVE;
				break;
			case 'r':
				promote = SPACE;
				capture = ROOK;
				moveType = MOVE;
				break;
			case 'q':
				promote = SPACE;
				capture = QUEEN;
				moveType = MOVE;
				break;
			case 'k':  // place holder and end game condition
				promote = SPACE;
				capture = KING;
				moveType = MOVE;
				break;
			case 'c':
				promote = SPACE;
				capture = SPACE;
				moveType = CASTLE_KING;
				break;
			case 'C':
				promote = SPACE;
				capture = SPACE;
				moveType = CASTLE_QUEEN;
				break;
			case 'E':
				promote = SPACE;
				capture = PAWN;
				moveType = ENPASSANT;
				break;
			case 'N':
				promote = KNIGHT;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'B':
				promote = BISHOP;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'R':
				promote = ROOK;
				capture = SPACE;
				moveType = MOVE;
				break;
			case 'Q':
				promote = QUEEN;
				capture = SPACE;
				moveType = MOVE;
				break;
			default:
				promote = SPACE;
				capture = SPACE;
				moveType = MOVE_ERROR;
			}
		}
		else // capture and promote
		{
			string action = smith.substr(4, 2);
			if (action == "pQ" || action == "Qp")
			{
				promote = QUEEN;
				capture = PAWN;
				moveType = MOVE;
			}
			else if (action == "nQ" || action == "Qn")
			{
				promote = QUEEN;
				capture = KNIGHT;
				moveType = MOVE;
			}
			else if (action == "bQ" || action == "Qb")
			{
				promote = QUEEN;
				capture = BISHOP;
				moveType = MOVE;
			}
			else if (action == "rQ" || action == "Qr")
			{
				promote = QUEEN;
				capture = ROOK;
				moveType = MOVE;
			}
			else if (action == "qQ" || action == "Qq")
			{
				promote = QUEEN;
				capture = QUEEN;
				moveType = MOVE;
			}
		}
	}
	else // no promote or capture
	{
		promote = SPACE;
		capture = SPACE;
		moveType = MOVE;
	}
}

char Move::letterFromPieceType(PieceType pt) const
{
	switch (pt) {
	case PAWN:    return 'p';
	case KNIGHT:  return 'n';
	case BISHOP:  return 'b';
	case ROOK:    return 'r';
	case QUEEN:   return 'q';
	case KING:    return 'k';
	default:      return ' ';
	}
}

PieceType Move::pieceTypeFromLetter(char letter) const
{
	switch (letter) {
	case 'p': return PAWN;
	case 'n': return KNIGHT;
	case 'b': return BISHOP;
	case 'r': return ROOK;
	case 'q': return QUEEN;
	case 'k': return KING;
	default:  return SPACE;
	}
}

bool Move::equal(string smith1, string smith2) // compares the numbers of location known as start and dest
{
	Move smithOne(smith1);
	Move smithTwo(smith2);

	Position sor1;
	Position sor2;
	Position des1;
	Position des2;

	sor1 = smithOne.getSource();
	des1 = smithOne.getDest();
	sor2 = smithTwo.getSource();
	des2 = smithTwo.getDest();

	/*string sorc1 = smith1.substr(0, 2);
	string dest1 = smith1.substr(2, 2);
	string sorc2 = smith2.substr(0, 2);
	string dest2 = smith2.substr(2, 2);

	Position sor1(sorc1);
	Position des1(dest1);
	Position sor2(sorc2);
	Position des2(dest2);*/

	int sor1c = sor1.getCol();
	int sor1r = sor1.getRow();
	int sor2c = sor2.getCol();
	int sor2r = sor2.getRow();
	int des1c = des1.getCol();
	int des1r = des1.getRow();
	int des2c = des2.getCol();
	int des2r = des2.getRow();

	int sor1p = (sor1r * 8) + sor1c;
	int sor2p = (sor2r * 8) + sor2c;
	int des1p = (des1r * 8) + des1c;
	int des2p = (des2r * 8) + des2c;

	if (sor1p == sor2p && des1p == des2p)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Move::less_than(string smith1, string smith2)
{
	Move smithOne(smith1);
	Move smithTwo(smith2);

	Position sor1;
	Position sor2;
	Position des1;
	Position des2;

	sor1 = smithOne.getSource();
	des1 = smithOne.getDest();
	sor2 = smithTwo.getSource();
	des2 = smithTwo.getDest();

	/*string sorc1 = smith1.substr(0, 2);
	string dest1 = smith1.substr(2, 2);
	string sorc2 = smith2.substr(0, 2);
	string dest2 = smith2.substr(2, 2);

	Position sor1(sorc1);
	Position des1(dest1);
	Position sor2(sorc2);
	Position des2(dest2);*/

	int sor1c = sor1.getCol();
	int sor1r = sor1.getRow();
	int sor2c = sor2.getCol();
	int sor2r = sor2.getRow();
	int des1c = des1.getCol();
	int des1r = des1.getRow();
	int des2c = des2.getCol();
	int des2r = des2.getRow();

	int sor1p = (sor1r * 8) + sor1c;
	int sor2p = (sor2r * 8) + sor2c;
	int des1p = (des1r * 8) + des1c;
	int des2p = (des2r * 8) + des2c;

	if (sor1p == sor2p && des1p < des2p)
	{
		return true;
	}
	else
	{
		return false;
	}
}




