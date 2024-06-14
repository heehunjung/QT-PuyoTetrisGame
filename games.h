#ifndef GAMES_H
#define GAMES_H
#include "element.h"
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
    bool initPuyo;
    bool moved = false;
    string pastShape;
    string** board;
    string* next;
    int** boardInt;
    Points* points;
    // 통합된 가상 메서드
    virtual int move(Points*, int, int) = 0;
    virtual void xz(Points*, int) = 0;

    virtual Point* getPoint1() = 0;
    virtual Point* getPoint2() = 0;
    virtual Point* getPoint3() = 0;
    virtual Point* getPoint4() = 0;
    virtual int bfs() = 0;
    virtual int gravity() = 0;
    virtual void lastPang() = 0;

    void rotateClockwise(Points* points,Point* pivot) {
        for (int i = 0; i < points->size(); ++i) {
            Point* p = points->getPoint(i);
            double tempX = (double)p->x -pivot->x;
            double tempY = (double)p->y - pivot->y;
            p->x = pivot->x - tempY;
            p->y = pivot->y + tempX;
        }
    }

    void rotateCounterClockwise(Points* points,Point* pivot) {
        for (int i = 0; i < points->size(); ++i) {
            Point* p = points->getPoint(i);
            double tempX = (double)p->x -pivot->x;
            double tempY = (double)p->y - pivot->y;
            p->x = pivot->x + tempY;
            p->y = pivot->y - tempX;
        }
    }
};

class PuyopuyoGame : public Game
{
public:
    Point *p1;
    Point *p2;
    virtual int move(Points*, int, int) override;
    virtual void xz(Points*, int) override;
    virtual Point* getPoint1() override { return p1; }
    virtual Point* getPoint2() override { return p2; }
    virtual Point* getPoint3() override { return nullptr; }
    virtual Point* getPoint4() override { return nullptr; }
    virtual int bfs() override;
    virtual int gravity() override;
    virtual void lastPang() override;
    PuyopuyoGame();
    ~PuyopuyoGame();
};

class TetrisGame : public Game
{
public:
    Point *p1;
    Point *p2;
    Point *p3;
    Point *p4;
    virtual int move(Points*, int, int) override;
    virtual void xz(Points*, int) override;
    virtual Point* getPoint1() override { return p1; }
    virtual Point* getPoint2() override { return p2; }
    virtual Point* getPoint3() override { return nullptr; }
    virtual Point* getPoint4() override { return nullptr; }
    virtual int bfs() override;
    virtual int gravity() override;
    virtual void lastPang() override;
    TetrisGame();
    ~TetrisGame();
};

class PuyopuyoTetrisGame : public Game
{
public:
    Point *p1;
    Point *p2;
    Point *p3;
    Point *p4;
    virtual int move(Points*, int, int) override;
    virtual void xz(Points*, int) override;
    virtual Point* getPoint1() override { return p1; }
    virtual Point* getPoint2() override { return p2; }
    virtual Point* getPoint3() override { return nullptr; }
    virtual Point* getPoint4() override { return nullptr; }
    virtual int bfs() override;
    virtual int gravity() override;
    virtual void lastPang() override;
    PuyopuyoTetrisGame();
    ~PuyopuyoTetrisGame();
};


#endif // GAMES_H
