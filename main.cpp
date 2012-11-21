#include <iostream>
#include <cstdlib>
using namespace std;
class figure
{
char color;
public:
	figure(char clr) : color(clr) {}
	~figure() {}
	virtual char GetPiece() = 0;
	char GetColor() {
		return color;
	}
	bool IsLegalMove(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		figure* destFig = board[desty][destx];
		if ((destFig == 0) || (color != destFig->GetColor())) {
			return AreSquaresLegal(starty, startx, desty, destx, board);
		}
		return false;
	}
	virtual bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) = 0;
};

class pawn : public figure
{
public:
	short boost;
	void SetBoost(short x) {boost = x;}
	pawn(char clr) : figure(clr) {boost = 1;}
	~pawn() {}
private:
	virtual char GetPiece() {
		return 'P';
	}
	
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		figure* destFig = board[desty][destx];
		if (destFig == 0) {
			// Destination is free
			if (startx == destx) {
				if (GetColor() == 'W') {
					if ((desty == starty + 1 + boost) || (desty == starty + 1)) {
						this->boost = 0;
						return true;
					}
				} else {
					if ((desty == starty - 1 - boost) || (desty == starty - 1)) {
						this->boost = 0;
						return true;
					}
				}
			}
		} else {
			// Dest has opposite color
			if ((startx == destx + 1) || (startx == destx - 1)) {
				if (GetColor() == 'W') {
					if ((desty == starty + 1 + boost) || (desty == starty + 1)) {
						this->boost = 0;
						return true;
					}
				} else {
					if ((desty == starty - 1 - boost) || (desty == starty - 1)) {
						this->boost = 0;
						return true;
					}
				}
			}
		}
		return false;
	}
};

class knight : public figure
{
public:
	knight(char clr) : figure(clr) {}
	~knight() {}
private:
	virtual char GetPiece() {
		return 'H';
	}
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		// Destination square is unoccupied or occupied by opposite color
		if ((startx == destx + 1) || (startx == destx - 1)) {
			if ((starty == desty + 2) || (starty == desty - 2)) {
				return true;
			}
		}
		if ((startx == destx + 2) || (startx == destx - 2)) {
			if ((starty == desty + 1) || (starty == desty - 1)) {
				return true;
			}
		}
		return false;
	}
};

class bishop : public figure
{
public:
	bishop(char clr) : figure(clr) {}
	~bishop() {}
private:
	virtual char GetPiece() {
		return 'B';
	}
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		if ((destx - startx == desty - starty) || (destx - startx == starty - desty)) {
			// Make sure that all intervening squares are empty
			int iRowOffset = (desty - starty > 0) ? 1 : -1;
			int iColOffset = (destx - startx > 0) ? 1 : -1;
			int iCheckRow;
			int iCheckCol;
			for (iCheckRow = starty + iRowOffset, iCheckCol = startx + iColOffset;
				iCheckRow !=  desty;
				iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
			{
				if (board[iCheckRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class rook : public figure
{
public:
	rook(char clr) : figure(clr) {}
	~rook() {}
private:
	virtual char GetPiece() {
		return 'R';
	}
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		if (starty == desty) {
			// Make sure that all intervening squares are empty
			int iColOffset = (destx - startx > 0) ? 1 : -1;
			for (int iCheckCol = startx + iColOffset; iCheckCol !=  destx; iCheckCol = iCheckCol + iColOffset) {
				if (board[starty][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		} else if (destx == startx) {
			// Make sure that all intervening squares are empty
			int iRowOffset = (desty - starty > 0) ? 1 : -1;
			for (int iCheckRow = starty + iRowOffset; iCheckRow !=  desty; iCheckRow = iCheckRow + iRowOffset) {
				if (board[iCheckRow][startx] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class queen : public figure
{
public:
	queen(char clr) : figure(clr) {}
	~queen() {}
private:
	virtual char GetPiece() {
		return 'Q';
	}
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		if (starty == desty) {
			// Make sure that all intervening squares are empty
			int iColOffset = (destx - startx > 0) ? 1 : -1;
			for (int iCheckCol = startx + iColOffset; iCheckCol !=  destx; iCheckCol = iCheckCol + iColOffset) {
				if (board[starty][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		} else if (destx == startx) {
			// Make sure that all intervening squares are empty
			int iRowOffset = (desty - starty > 0) ? 1 : -1;
			for (int iCheckRow = starty + iRowOffset; iCheckRow !=  desty; iCheckRow = iCheckRow + iRowOffset) {
				if (board[iCheckRow][startx] != 0) {
					return false;
				}
			}
			return true;
		} else if ((destx - startx == desty - starty) || (destx - startx == starty - desty)) {
			// Make sure that all intervening squares are empty
			int iRowOffset = (desty - starty > 0) ? 1 : -1;
			int iColOffset = (destx - startx > 0) ? 1 : -1;
			int iCheckRow;
			int iCheckCol;
			for (iCheckRow = starty + iRowOffset, iCheckCol = startx + iColOffset;
				iCheckRow !=  desty;
				iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
			{
				if (board[iCheckRow][iCheckCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class king : public figure
{
public:
	king(char clr) : figure(clr) {}
	~king() {}
private:
	virtual char GetPiece() {
		return 'K';
	}
	bool AreSquaresLegal(int starty, int startx, int desty, int destx, figure* board[8][8]) {
		int iRowDelta = desty - starty;
		int iColDelta = destx - startx;
		if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
			((iColDelta >= -1) && (iColDelta <= 1)))
		{
			return true;
		}
		return false;
	}
};

class board
{
public:
	board() {
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				fBoard[iRow][iCol] = 0;
			}
		}
		// Allocate and place black pieces
		for (int iCol = 0; iCol < 8; ++iCol) {
			fBoard[6][iCol] = new pawn('B');
		}
		
		fBoard[7][0] = new rook('B');
		fBoard[7][1] = new knight('B');
		fBoard[7][2] = new bishop('B');
		fBoard[7][3] = new king('B');
		fBoard[7][4] = new queen('B');
		fBoard[7][5] = new bishop('B');
		fBoard[7][6] = new knight('B');
		fBoard[7][7] = new rook('B');
		// Allocate and place white pieces
		for (int iCol = 0; iCol < 8; ++iCol) {
			fBoard[1][iCol] = new pawn('W');
		}
		fBoard[0][0] = new rook('W');
		fBoard[0][1] = new knight('W');
		fBoard[0][2] = new bishop('W');
		fBoard[0][3] = new king('W');
		fBoard[0][4] = new queen('W');
		fBoard[0][5] = new bishop('W');
		fBoard[0][6] = new knight('W');
		fBoard[0][7] = new rook('W');
		
	}
	~board() {
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				delete fBoard[iRow][iCol];
				fBoard[iRow][iCol] = 0;
			}
		}
	}

	void Print() {
		#ifdef _WIN32
		system("CLS");
		#else
		printf ("%c[2J", 27);
		#endif
		const int kiSquareWidth = 4;
		const int kiSquareHeight = 3;
		for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
			int iSquareRow = iRow/kiSquareHeight;
			// Print side border with numbering
			if (iRow % 3 == 1) {
				cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
			} else {
				cout << "---";
			}
			// Print the chess board
			for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
				int iSquareCol = iCol/kiSquareWidth;
				if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && fBoard[7-iSquareRow][iSquareCol] != 0) {
					if ((iCol % 4) == 1) {
						cout << fBoard[7-iSquareRow][iSquareCol]->GetColor();
					} else {
						cout << fBoard[7-iSquareRow][iSquareCol]->GetPiece();
					}
				} else {
					if ((iSquareRow + iSquareCol) % 2 == 1) {
						cout << '*';
					} else {
						cout << ' ';
					}
				}
			}
			cout << endl;
		}
		// Print the bottom border with numbers
		for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
			if (iRow % 3 == 1) {
				cout << "---";
				for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
					int iSquareCol = iCol/kiSquareWidth;
					if ((iCol % 4) == 1) {
						cout << (char)(iSquareCol + (int)'a');
					} else {
						cout << '-';
					}
				}
				cout << endl;
			} else {
				for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	bool IsInCheck(char clr) {
		// Find the king
		int iKingRow;
		int iKingCol;
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (fBoard[iRow][iCol] != 0) {
					if (fBoard[iRow][iCol]->GetColor() == clr) {
						if (fBoard[iRow][iCol]->GetPiece() == 'K') {
							iKingRow = iRow;
							iKingCol = iCol;
						}
					}
				}
			}
		}
		// Run through the opponent's pieces and see if any can take the king
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (fBoard[iRow][iCol] != 0) {
					if (fBoard[iRow][iCol]->GetColor() != clr) {
						if (fBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, fBoard)) {
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool CanMove(char clr) {
		// Run through all pieces
		for (int iRow = 0; iRow < 8; ++iRow) {
			for (int iCol = 0; iCol < 8; ++iCol) {
				if (fBoard[iRow][iCol] != 0) {
					// If it is a piece of the current player, see if it has a legal move
					if (fBoard[iRow][iCol]->GetColor() == clr) {
						for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
							for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
								if (fBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, fBoard)) {
									// Make move and check whether king is in check
									figure* qpTemp					= fBoard[iMoveRow][iMoveCol];
									fBoard[iMoveRow][iMoveCol]	= fBoard[iRow][iCol];
									fBoard[iRow][iCol]			= 0;
									bool bCanMove = !IsInCheck(clr);
									// Undo the move
									fBoard[iRow][iCol]			= fBoard[iMoveRow][iMoveCol];
									fBoard[iMoveRow][iMoveCol]	= qpTemp;
									if (bCanMove) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	figure* fBoard[8][8];
};

class game
{
public:
	game() : playerColor('W') {}
	~game() {}

	void Start() {
		do {
			GetNextMove(ChessBoard.fBoard);
			AlternateTurn();
		} while (!IsGameOver());
		ChessBoard.Print();
	}

	void GetNextMove(figure* board[8][8]) {
		
		bool bValidMove		= false;
		do {
			ChessBoard.Print();

			// Get input and convert to coordinates
			cout << playerColor << "'s Move: (ex.: e 2)";
			char iStartX;
			cin >> iStartX;
			int iStartCol = (int)iStartX - (int)'a';

			int iStartY;
			cin >> iStartY;
			int iStartRow = iStartY - 1;

			cout << "To: (ex.: e 3)";
			char iEndX;
			cin >> iEndX;
			int iEndCol = (int)iEndX - (int)'a';
			
			int iEndY;
			cin >> iEndY;
			int iEndRow = iEndY - 1;

	
			//cout << iStartRow<<' ' << iStartCol<<' ' << iEndRow<<' ' << iEndCol;
			// Check that the indices are in range
			// and that the source and destination are different
			if ((iStartRow >= 0 && iStartRow <= 7) &&
				(iStartCol >= 0 && iStartCol <= 7) &&
				(iEndRow >= 0 && iEndRow <= 7) &&
				(iEndCol >= 0 && iEndCol <= 7)) {
				// Additional checks in here
				figure* qpCurrPiece = board[iStartRow][iStartCol];
				// Check that the piece is the correct color
				if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == playerColor)) {
					// Check that the destination is a valid destination
					if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, board)) {
						// Make the move
						figure* qpTemp				= board[iEndRow][iEndCol];
						board[iEndRow][iEndCol]		= board[iStartRow][iStartCol];
						board[iStartRow][iStartCol]	= 0;
						// Make sure that the current player is not in check
						if (!ChessBoard.IsInCheck(playerColor)) {
							delete qpTemp;
							bValidMove = true;
						} else { // Undo the last move
							board[iStartRow][iStartCol] = board[iEndRow][iEndCol];
							board[iEndRow][iEndCol]		= qpTemp;
						}
						//Is under attack
						for (int iRow = 0; iRow < 8; ++iRow) {
							for (int iCol = 0; iCol < 8; ++iCol) {
								figure* f = board[iRow][iCol];
									if( f != 0 && board[iEndRow][iEndCol] != 0
										&& (f->GetColor() != playerColor) 
										&& f->IsLegalMove(iRow, iCol, iEndRow, iEndCol, board)) {
											cout << "You are under attack!" << endl;
											system("PAUSE");
											iRow = 8;
											iCol = 8;
								}

							}
						}
					}
				}
			}
			if (!bValidMove) {
				cout << "Invalid Move!" << endl;
				system("PAUSE");
			}

		} while (!bValidMove);
	}

	void AlternateTurn() {
		playerColor = (playerColor == 'W') ? 'B' : 'W';
	}

	bool IsGameOver() {
		// Check that the current player can move
		// If not, we have a stalemate or checkmate
		bool bCanMove = false;
		bCanMove = ChessBoard.CanMove(playerColor);
		if (!bCanMove) {
			if (ChessBoard.IsInCheck(playerColor)) {
				AlternateTurn();
				std::cout << "Checkmate, " << playerColor << " Wins!" << std::endl;
				system("PAUSE");
			} else {
				std::cout << "Stalemate!" << std::endl;
				system("PAUSE");
			}
		}
		return !bCanMove;
	}
private:
	board ChessBoard;
	char playerColor;
};

int main() {
	game qGame;
	qGame.Start();
	return 0;
}