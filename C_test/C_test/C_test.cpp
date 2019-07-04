// miro.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

// 0 벽 1 길 2 시작점 3 도착점 
struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer {
	_tagPoint tPos;
	bool bWallPush;
	bool bPushOnOff;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;


void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos) {

	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111000000000");
	strcpy_s(Maze[2], "00000000011111110000");
	strcpy_s(Maze[3], "00000000000000010000");
	strcpy_s(Maze[4], "00000111111111110000");
	strcpy_s(Maze[5], "00000101000000000000");
	strcpy_s(Maze[6], "00000001111111100000");
	strcpy_s(Maze[7], "00111111000000111100");
	strcpy_s(Maze[8], "00000000000000011000");
	strcpy_s(Maze[9], "00000000111111110000");
	strcpy_s(Maze[10], "00011111100000000000");
	strcpy_s(Maze[11], "00011000111111111100");
	strcpy_s(Maze[12], "00111100000000001100");
	strcpy_s(Maze[13], "00001111111111000000");
	strcpy_s(Maze[14], "00111100000111110000");
	strcpy_s(Maze[15], "00011111100000111100");
	strcpy_s(Maze[16], "00000011111000001100");
	strcpy_s(Maze[17], "00001110111100000100");
	strcpy_s(Maze[18], "00111100001110011110");
	strcpy_s(Maze[19], "00000000000000000013");
}

void Output(char Maze[21][21], PPLAYER tPlayer) {

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {



			//if (pPlayerPos->x == j && pPlayerPos->y == i) {
			if (Maze[i][j] == '4') {
				cout << "＆";
			}
			else if (tPlayer->tPos.x == i && tPlayer->tPos.y == j) {
				cout << "☆";
			}
			else if (Maze[i][j] == '0') {
				cout << "■";
			}
			else if (Maze[i][j] == '1') {
				cout << "  ";
			}
			else if (Maze[i][j] == '2') {
				cout << "★";
			}
			else if (Maze[i][j] == '3') {
				cout << "□";
			}
			else if (Maze[i][j] == '5') {
				cout << "＃";
			}
			else if (Maze[i][j] == '6') {
				cout << "§";
			}
			else if (Maze[i][j] == '7') {
				cout << "※";
			}


		}
		cout << endl;
	}
	cout << "폭판파워 : " << tPlayer->iBombPower << endl;
	cout << "벽통과 : ";
	if (tPlayer->bTransparency) {
		cout << "ON";
	}
	else {
		cout << "OFF";
	}
	cout << "벽밀기 : ";
	if (tPlayer->bWallPush) {
		cout << "가능";
	}
	else {
		cout << "불가능";
	}
}

bool AddItem(char cItemType, PPLAYER pPlayer) {
	if (cItemType == '5') {
		if (pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;
		return true;
	}else if(cItemType == '6') {
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;
	}else if (cItemType == '7') {
		pPlayer->bTransparency = true;
		return true;
	}
	return false;
}

void MoveUp(char Maze[21][21], PPLAYER tPlayer) {
	if (tPlayer->tPos.x - 1 >= 0) {

		if (Maze[tPlayer->tPos.x - 1][tPlayer->tPos.y] != '0' &&
			Maze[tPlayer->tPos.x - 1][tPlayer->tPos.y] != '4') {
			--tPlayer->tPos.x;
		}
		else if (tPlayer->bWallPush && Maze[tPlayer->tPos.x - 1][tPlayer->tPos.y] == '0') {
			if (tPlayer->bPushOnOff) {
				if (tPlayer->tPos.x - 2 >= 0) {
					if (Maze[tPlayer->tPos.x - 2][tPlayer->tPos.y] == '0') {
						if (tPlayer->bTransparency) {
							--tPlayer->tPos.x;
						}
					}
					else if(Maze[tPlayer->tPos.x - 2][tPlayer->tPos.y] == '1'){
						Maze[tPlayer->tPos.x - 2][tPlayer->tPos.y] = '0';
						Maze[tPlayer->tPos.x - 1][tPlayer->tPos.y] = '1';
						--tPlayer->tPos.x;
					}
				}
				else if (tPlayer->bTransparency) {
					--tPlayer->tPos.x;
				}

			}

			else if (tPlayer->bTransparency) {
				--tPlayer->tPos.x;
			} 

		}
		else if (tPlayer->bTransparency) {
			--tPlayer->tPos.x;
		}

		if (AddItem(Maze[tPlayer->tPos.x][tPlayer->tPos.y], tPlayer)) {
			Maze[tPlayer->tPos.x][tPlayer->tPos.y] = '1';
		};

	}
}


void MoveDown(char Maze[21][21], PPLAYER tPlayer) {
	if (tPlayer->tPos.x + 1 < 20) {

		if (Maze[tPlayer->tPos.x + 1][tPlayer->tPos.y] != '0' &&
			Maze[tPlayer->tPos.x + 1][tPlayer->tPos.y] != '4') {
			++tPlayer->tPos.x;
		}
		else if (tPlayer->bWallPush && Maze[tPlayer->tPos.x + 1][tPlayer->tPos.y] == '0') {
			if (tPlayer->bPushOnOff) {
				if (tPlayer->tPos.x + 2 <20) {
					if (Maze[tPlayer->tPos.x + 2][tPlayer->tPos.y] == '0') {
						if (tPlayer->bTransparency) {
							++tPlayer->tPos.x;
						}
					}
					else if (Maze[tPlayer->tPos.x + 2][tPlayer->tPos.y] == '1') {
						Maze[tPlayer->tPos.x + 2][tPlayer->tPos.y] = '0';
						Maze[tPlayer->tPos.x + 1][tPlayer->tPos.y] = '1';
						++tPlayer->tPos.x;
					}
				}
				else if (tPlayer->bTransparency) {
					++tPlayer->tPos.x;
				}

			}

			else if (tPlayer->bTransparency) {
				++tPlayer->tPos.x;
			}

		}
		else if (tPlayer->bTransparency) {
			++tPlayer->tPos.x;
		}

		if (AddItem(Maze[tPlayer->tPos.x][tPlayer->tPos.y], tPlayer)) {
			Maze[tPlayer->tPos.x][tPlayer->tPos.y] = '1';
		};
	}
}

void MoveLeft(char Maze[21][21], PPLAYER tPlayer) {
	if (tPlayer->tPos.y - 1 < 20) {
		if (Maze[tPlayer->tPos.x][tPlayer->tPos.y - 1] != '0' &&
			Maze[tPlayer->tPos.x][tPlayer->tPos.y - 1] != '4') {
			--tPlayer->tPos.y;
		}
		else if (tPlayer->bWallPush && Maze[tPlayer->tPos.x][tPlayer->tPos.y-1] == '0') {
			if (tPlayer->bPushOnOff) {
				if (tPlayer->tPos.y - 2 <20) {
					if (Maze[tPlayer->tPos.x ][tPlayer->tPos.y-2] == '0') {
						if (tPlayer->bTransparency) {
							--tPlayer->tPos.y;
						}
					}
					else if (Maze[tPlayer->tPos.x][tPlayer->tPos.y-2] == '1') {
						Maze[tPlayer->tPos.x][tPlayer->tPos.y-2] = '0';
						Maze[tPlayer->tPos.x][tPlayer->tPos.y-1] = '1';
						--tPlayer->tPos.y;
					}
				}
				else if (tPlayer->bTransparency) {
					--tPlayer->tPos.y;
				}

			}

			else if (tPlayer->bTransparency) {
				--tPlayer->tPos.y;
			}

		}
		else if (tPlayer->bTransparency) {
			--tPlayer->tPos.y;
		}

		if (AddItem(Maze[tPlayer->tPos.x][tPlayer->tPos.y], tPlayer)) {
			Maze[tPlayer->tPos.x][tPlayer->tPos.y] = '1';
		};
	}
}

void MoveRight(char Maze[21][21], PPLAYER tPlayer) {

	if (tPlayer->tPos.y + 1 < 20) {
		if (Maze[tPlayer->tPos.x][tPlayer->tPos.y + 1] != '0' &&
			Maze[tPlayer->tPos.x][tPlayer->tPos.y + 1] != '4') {
			++tPlayer->tPos.y;
		}
		else if (tPlayer->bWallPush && Maze[tPlayer->tPos.x][tPlayer->tPos.y + 1] == '0') {
			if (tPlayer->bPushOnOff) {
				if (tPlayer->tPos.y + 2 < 20) {
					if (Maze[tPlayer->tPos.x][tPlayer->tPos.y + 2] == '0') {
						if (tPlayer->bTransparency) {
							++tPlayer->tPos.y;
						}
					}
					else if (Maze[tPlayer->tPos.x][tPlayer->tPos.y + 2] == '1') {
						Maze[tPlayer->tPos.x][tPlayer->tPos.y + 2] = '0';
						Maze[tPlayer->tPos.x][tPlayer->tPos.y + 1] = '1';
						++tPlayer->tPos.y;
					}
				}
				else if (tPlayer->bTransparency) {
					++tPlayer->tPos.y;
				}

			}

			else if (tPlayer->bTransparency) {
				++tPlayer->tPos.y;
			}

		}
		else if (tPlayer->bTransparency) {
			++tPlayer->tPos.y;
		}

		if (AddItem(Maze[tPlayer->tPos.x][tPlayer->tPos.y], tPlayer)) {
			Maze[tPlayer->tPos.x][tPlayer->tPos.y] = '1';
		};
	}



}


void MovePlayer(char Maze[21][21], PPLAYER tPlayer, char clnput) {

	//w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : 
	switch (clnput)
	{
	case 'w':
	case 'W':;
		MoveUp(Maze, tPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, tPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, tPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, tPlayer);
		break;
	default:
		break;
	}
}

void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount) {

	if (*pBombCount == 5) {
		return;
	}
	else if (Maze[pPlayer->tPos.x][pPlayer->tPos.y] == '0') {
		return;
	}

	for (int i = 0; i < *pBombCount; ++i) {
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
			return;
		}
	}

	pBombArr[*pBombCount] = pPlayer->tPos;

	++(*pBombCount);

	Maze[pPlayer->tPos.x][pPlayer->tPos.y] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount) {
	for (int i = 0; i < *pBombCount; ++i) {

		Maze[pBombArr[i].x][pBombArr[i].y] = '1';

		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}

		for (int j = 1; j <= pPlayer->iBombPower; ++j) {



			if (pBombArr[i].x - j >= 0) {
				if (Maze[pBombArr[i].x - j][pBombArr[i].y] == '0') {

					if (rand() % 100 < 30) {
						int iPercent = rand() % 100;
						if (iPercent < 80) {
							Maze[pBombArr[i].x - j][pBombArr[i].y] = '5';
						}
						else if (iPercent < 90) {
							Maze[pBombArr[i].x - j][pBombArr[i].y] = '6';
						}else
							Maze[pBombArr[i].x - j][pBombArr[i].y] = '7';
					}else
						Maze[pBombArr[i].x - j][pBombArr[i].y] = '1';
				}
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + j < 20) {
				if (Maze[pBombArr[i].x + j][pBombArr[i].y] == '0') {

					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70) {
							Maze[pBombArr[i].x + j][pBombArr[i].y] = '5';
						}
						else if (iPercent < 80) {
							Maze[pBombArr[i].x + j][pBombArr[i].y] = '6';
						}
						else
							Maze[pBombArr[i].x + j][pBombArr[i].y] = '7';
					}
					else
						Maze[pBombArr[i].x + j][pBombArr[i].y] = '1';
				}
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y - j < 20) {
				if (Maze[pBombArr[i].x][pBombArr[i].y - j] == '0') {
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70) {
							Maze[pBombArr[i].x][pBombArr[i].y -j] = '5';
						}
						else if (iPercent < 80) {
							Maze[pBombArr[i].x][pBombArr[i].y - j] = '6';
						}
						else
							Maze[pBombArr[i].x][pBombArr[i].y - j] = '7';
					}
					else
						Maze[pBombArr[i].x][pBombArr[i].y - j] = '1';
				}
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20) {
				if (Maze[pBombArr[i].x][pBombArr[i].y + j] == '0') {
					if (rand() % 100 < 20) {
						int iPercent = rand() % 100;
						if (iPercent < 70) {
							Maze[pBombArr[i].x][pBombArr[i].y + j] = '5';
						}
						else if (iPercent < 80) {
							Maze[pBombArr[i].x][pBombArr[i].y + j] = '6';
						}
						else
							Maze[pBombArr[i].x][pBombArr[i].y + j] = '7';
					}
					else
						Maze[pBombArr[i].x][pBombArr[i].y + j] = '1';
				}
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j) {
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}
	*pBombCount = 0;
}

int main()
{
	srand((unsigned int)time(0));

	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;


	POINT tBombPos[5];


	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
			cout << "도착" << endl;
			break;
		}

		//cout << "t : 폭탄 설치 u : 터트리기 i : 벽밀기 ON/OFF " << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
		char clnput = _getch();

		if (clnput == 'Q' || clnput == 'q') {
			break;
		}
		else if (clnput == 'T' || clnput == 't') {
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else if (clnput == 'u' || clnput == 'U') {
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else if (clnput == 'i' || clnput == 'I') {
			if (tPlayer.bWallPush) {
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
			}
		}

		MovePlayer(strMaze, &tPlayer, clnput);

	}



	return 0;
}
