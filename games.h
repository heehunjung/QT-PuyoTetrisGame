#ifndef GAMES_H
#define GAMES_H
#include "puyopuyo.h"
#include <string>
#include <QDebug>
#include <queue>

using namespace std;
class Game
{
public:
    Game(int row, int col, int length);
    ~Game();

public:
    int ROW;
    int COL;
    int LENGTH;

    double axis_row;
    double axis_col;

    int score;

    bool gameover;
    bool isLast;
    bool bfsState;
    string** board;
    string* next;
    int** boardInt;
    bool moved = false;  // 뿌요가 이동했는지 추적
    virtual int puyopuyoMove(PointPuyopuyo*, PointPuyopuyo*, int, int){};
    virtual void puyopuyoXZ(PointPuyopuyo*, PointPuyopuyo*, int){;};
    virtual PointPuyopuyo* getPoint1(){};
    virtual PointPuyopuyo* getPoint2(){};
    virtual int bfs(){;};
    void rotateClockwise(PointPuyopuyo* p1, PointPuyopuyo* p2, PointPuyopuyo pivot) {
        // 중심(pivot)을 기준으로 시계방향 회전
        int tempX = p2->x - pivot.x;
        int tempY = p2->y - pivot.y;
        p2->x = pivot.x - tempY;
        p2->y = pivot.y + tempX;
    }
    void rotateCounterClockwise(PointPuyopuyo* p1, PointPuyopuyo* p2, PointPuyopuyo pivot) {
        // 중심(pivot)을 기준으로 시계 반대 방향 회전
        int tempX = p2->x - pivot.x;
        int tempY = p2->y - pivot.y;
        p2->x = pivot.x + tempY;
        p2->y = pivot.y - tempX;
    }
    virtual int gravity(){};
    virtual void lastPang(){};
};

class PuyopuyoGame : public Game
{
public:
    PointPuyopuyo *p1;
    PointPuyopuyo *p2;
    virtual int puyopuyoMove(PointPuyopuyo*,PointPuyopuyo*,int,int);
    virtual void puyopuyoXZ(PointPuyopuyo*, PointPuyopuyo*, int);
    virtual int gravity();
    virtual PointPuyopuyo* getPoint1(){return p1;}
    virtual PointPuyopuyo* getPoint2(){return p2;}
    virtual int bfs();
    virtual void lastPang();

    PuyopuyoGame();
    ~PuyopuyoGame();
};

class TetrisGame : public Game
{
public:
    TetrisGame();
    ~TetrisGame();
};

class PuyopuyoTetrisGame : public Game
{
public:
    PuyopuyoTetrisGame();
    ~PuyopuyoTetrisGame();
};


#endif // GAMES_H
