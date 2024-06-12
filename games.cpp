#include "games.h"

Game::Game(int row, int col, int length)
{
    ROW = row;
    COL = col;
    LENGTH = length;

    board = new string*[ROW+2];
    boardInt = new int*[ROW+2];
    for (int i = 0; i < ROW+2 ; i++)
    {
        board[i] = new string[COL];
        boardInt[i] = new int[COL];
    }

    next = new string[length];

    gameover = false;
}

Game::~Game(){
    delete[] next;

    for (int i = 0; i < ROW+2; i++)
    {
        delete[] board[i];
        delete[] boardInt[i];
    }
    delete[] board;
}

int PuyopuyoGame::puyopuyoMove(PointPuyopuyo* p1, PointPuyopuyo* p2, int xPlus, int yPlus)
{
    // 기존 위치 초기화
    if ((xPlus != 0 || yPlus != 0) && isLast == false )
    {
        board[p1->y][p1->x] = "White";
        board[p2->y][p2->x] = "White";
        boardInt[p1->y][p1->x] = 0;
        boardInt[p2->y][p2->x] = 0;
    }

    // 새로운 위치 계산
    p1->x += xPlus;
    p1->y += yPlus;
    p2->x += xPlus;
    p2->y += yPlus;

    // 블록 초기화
    Board* block1 = nullptr;
    Board* block2 = nullptr;

    switch (next[0][0])
    {
    case 'R': block1 = new Red(); break;
    case 'Y': block1 = new Yellow(); break;
    case 'G': block1 = new Green(); break;
    case 'B': block1 = new Blue(); break;
    case 'P': block1 = new Purple(); break;
    }

    switch (next[0][1])
    {
    case 'R': block2 = new Red(); break;
    case 'Y': block2 = new Yellow(); break;
    case 'G': block2 = new Green(); break;
    case 'B': block2 = new Blue(); break;
    case 'P': block2 = new Purple(); break;
    }

    // 좌표가 보드 범위 내에 있는지 확인
    if ((ROW + 1 >= p1->y && p1->y >= 0) && (COL - 1 >= p1->x && p1->x >= 0) &&
        (ROW + 1 >= p2->y && p2->y >= 0) && (COL - 1 >= p2->x && p2->x >= 0))
    {
        isLast = false;
        if (boardInt[p1->y][p1->x] >= 0 && boardInt[p2->y][p2->x] >= 0)
        {
            if (block1)
            {
                board[p1->y][p1->x] = block1->color;
                boardInt[p1->y][p1->x] = block1->value;
            }
            if (block2)
            {
                board[p2->y][p2->x] = block2->color;
                boardInt[p2->y][p2->x] = block2->value;
            }
            // 현재 이동한 위치에 작성 할 수 있는데, x,y축 끝인 경우
            if (p1->y == ROW + 1 || p2->y == ROW + 1
                || boardInt[p1->y+1][p1->x] < 0 || boardInt[p2->y+1][p2->x] < 0)
            {
                isLast = true;
            }
            delete block1;
            delete block2;
        return 1;
        }
        else
        {
            if (block1)
            {
                boardInt[p1->y-1][p1->x] = block1->afterValue;
                delete block1;
            }
            if (block2)
            {
                boardInt[p2->y-1][p2->x] = block2->afterValue;
                delete block2;
            }
            axis_row = 1;
            axis_col = 2;
            delete p1;
            delete p2;
            p1 = new PointPuyopuyo(axis_col, axis_row);
            p2 = new PointPuyopuyo(axis_col, axis_row - 1);
            return 0;
        }
    }
    else if ((ROW + 2 == p1->y) || (ROW + 2 == p2->y))
    {
        if (block1)
        {
            boardInt[p1->y-1][p1->x] = block1->afterValue;
            delete block1;
        }
        if (block2)
        {
            boardInt[p2->y-1][p2->x] = block2->afterValue;
            delete block2;
        }
        axis_row = 1;
        axis_col = 2;
        delete p1;
        delete p2;
        p1 = new PointPuyopuyo(axis_col, axis_row);
        p2 = new PointPuyopuyo(axis_col, axis_row - 1);
        return 0;
    }
    else if (COL == p2->x || COL == p1->x)
    {
        delete block1;
        delete block2;
        return 3;
    }
    delete block1;
    delete block2;
    return -1;
}
void PuyopuyoGame::puyopuyoXZ(PointPuyopuyo* p1, PointPuyopuyo* p2, int check)
{

    // 기존 위치 초기화
    board[p2->y][p2->x] = "White";
    boardInt[p2->y][p2->x] = 0;
    // 블록 초기화
    Board* block2 = nullptr;


    switch (next[0][1])
    {
    case 'R': block2 = new Red(); break;
    case 'Y': block2 = new Yellow(); break;
    case 'G': block2 = new Green(); break;
    case 'B': block2 = new Blue(); break;
    case 'P': block2 = new Purple(); break;
    }
    PointPuyopuyo pivot = *p1; // p1을 중심으로 회전

    // z 축 회전
    if(check == 1)
    {
        rotateCounterClockwise(p1, p2, pivot);
    }
    else
    {
        rotateClockwise(p1, p2, pivot);

    }
    if (block2)
    {
        board[p2->y][p2->x] = block2->color;
        boardInt[p2->y][p2->x] = block2->value;
    }

}

PuyopuyoGame::PuyopuyoGame() : Game(12, 6, 2)
{
    // Initialize random seed
    srand(time(0));
    isLast = false;

    // Generate random colors for next blocks
    for(int i = 0; i < 2; ++i)
    {
        char colors[] = {'R', 'Y', 'G', 'B', 'P'};
        next[i] = colors[rand() % 5];
        next[i] += colors[rand() % 5];
    }

    for(int i = 0; i < ROW+2; i++)
        for(int j = 0; j < COL; j++)
        {
            boardInt[i][j] = 0;
            if(i < 2)
                board[i][j] = "Gray";
            else
                board[i][j] = "White";
        }

    axis_row = 1;
    axis_col = 2;
    p1 = new PointPuyopuyo(axis_col,axis_row);
    p2 = new PointPuyopuyo(axis_col,axis_row-1);
    score = 0;
}

PuyopuyoGame::~PuyopuyoGame()
{
    delete p1;
    delete p2;
}

TetrisGame::TetrisGame() : Game(20, 10, 5)
{
    for(int i=0;i<5;i++)
    {
        char shapes[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
        next[i] = shapes[rand() % 7];
    }

    for(int i = 0; i < ROW+2; i++)
        for(int j = 0; j < COL; j++)
        {
            if(i < 2)
                board[i][j] = "Gray";
            else
                board[i][j] = "White";
        }


    axis_row = 0.5;
    axis_col = 5;

    score = 1;
}

TetrisGame::~TetrisGame()
{
    ;
}

PuyopuyoTetrisGame::PuyopuyoTetrisGame() : Game(16, 8, 5)
{
    for(int i=0;i<5;i++)
    {
        if (rand() % 2 == 0)
        {
            char colors[] = {'R', 'Y', 'G', 'B', 'P'};
            next[i] = colors[rand() % 5];
            next[i] += colors[rand() % 5];
        }
        else
        {
            char shapes[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
            next[i] = shapes[rand() % 7];
        }
    }

    for(int i = 0; i < ROW+2; i++)
        for(int j = 0; j < COL; j++)
        {
            if(i < 2)
                board[i][j] = "Gray";
            else
                board[i][j] = "White";
        }

    axis_row = 0.5;
    axis_col = 4;

    score = 2;
}

PuyopuyoTetrisGame::~PuyopuyoTetrisGame()
{
    ;
}
