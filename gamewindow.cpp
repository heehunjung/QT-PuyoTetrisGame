#include "GameWindow.h"

GameWindow::GameWindow(QString gamename, QWidget *parent) : QWidget(parent)
{
    timer=startTimer(SPPED_MS);
    GAMENAME = gamename;

    if (GAMENAME == "Puyopuyo")
    {
        p_game = new PuyopuyoGame();
        p_game->puyopuyoMove(p_game->getPoint1(), p_game->getPoint2(), 0, 0);
        resize(500, 800);
    }
    else if (GAMENAME == "Tetris")
    {
        p_game = new TetrisGame();
        resize(700, 1100);
    }
    else if (GAMENAME == "PuyopuyoTetris")
    {
        p_game = new PuyopuyoTetrisGame();
        resize(700, 900);
    }
    setWindowTitle(gamename);
}

GameWindow::~GameWindow()
{
    delete p_game;
    delete gameoverwindow;
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    int ROW = p_game->ROW;
    int COL = p_game->COL;
    int LENGTH = p_game->LENGTH;

    string** board = p_game->board;
    string* next = p_game->next;

    double axis_row = p_game->axis_row;
    double axis_col = p_game->axis_col;

    int score = p_game->score;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,COL*BLOCK_SIZE,ROW*BLOCK_SIZE);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial",14));
    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,BLOCK_SIZE,BLOCK_SIZE),Qt::AlignCenter,"NEXT");
    painter.setPen(Qt::black);
    for(int k = 0; k < LENGTH; k++)
    {
        std::string current_color = next[k];

        int current_col = MARGIN*10+COL*(BLOCK_SIZE/1)+0*(BLOCK_SIZE/1);
        int current_row = MARGIN*10+0*(BLOCK_SIZE/2) + 100 * k + 100;
        int one = (BLOCK_SIZE/2);

        if (next[k].length() == 2)
        {
            for (int l = 0; l < 2; l++)
            {
                if (next[k][l] == 'R')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'Y')
                {
                    painter.setBrush(QBrush(QColor(255, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'G')
                {
                    painter.setBrush(QBrush(QColor(0, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'B')
                {
                    painter.setBrush(QBrush(QColor(0, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (next[k][l] == 'P')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }
            }
        }
        //X
        //X

        if (next[k] == "O")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        //OO
        //OO

        else if (next[k] == "T")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        // T
        //TTT

        else if (next[k] == "S")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        // SS
        //SS

        else if (next[k] == "Z")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //ZZ
        // ZZ

        else if (next[k] == "J")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //J
        //JJJ

        else if (next[k] == "L")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        //  L
        //LLL

        else if (next[k] == "I")
        {
            painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
            painter.drawRect(current_col + 3 * one, current_row + one, one, one);
        }
        //
        //IIII
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial",14));
    if (GAMENAME == "Puyopuyo")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current chain : " + QString::number(score));
    if (GAMENAME == "Tetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current line : " + QString::number(score));
    if (GAMENAME == "PuyopuyoTetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current chain&line : " + QString::number(score));
    painter.setPen(Qt::black);

    for(int i=0; i<ROW+2; i++)
        for(int j=0; j<COL; j++)
        {
                painter.setBrush(QBrush(QColor(255, 255, 255),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
        }

    for(int i=0;i<ROW+2;i++)
    {
        for(int j=0;j<COL;j++)
        {
            if(board[i][j] == "BlackPuyo")
            {
                painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            if(board[i][j] == "BlackBlock")
            {
                painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Gray")
            {
                painter.setBrush(QBrush(QColor(128, 128, 128),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "White")
            {
                painter.setBrush(QBrush(QColor(255, 255, 255),Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Red")
            {
                painter.setBrush(QBrush((QColor(255, 0, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Yellow")
            {
                painter.setBrush(QBrush((QColor(255, 255, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Green")
            {
                painter.setBrush(QBrush((QColor(0, 255, 0)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Blue")
            {
                painter.setBrush(QBrush((QColor(0, 0, 255)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }

            else if(board[i][j] == "Purple")
            {
                painter.setBrush(QBrush((QColor(255, 0, 255)),Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
    }

    painter.setBrush(QBrush(QColor(0, 0, 0),Qt::SolidPattern));
    painter.drawRect(axis_col*BLOCK_SIZE+MARGIN + BLOCK_SIZE/4,axis_row*BLOCK_SIZE+MARGIN + BLOCK_SIZE/4,BLOCK_SIZE/2,BLOCK_SIZE/2);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (p_game->gameover == true)
        return;
    switch(event->key())
    {
    case Qt::Key_Down:
    {
        if(p_game->moved==true)
        {
            p_game->gravity();
        }
        else{
            int result;
            result= p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),0,1);
            if (result == 1)
            {
                p_game->axis_row++;
            }
            else if(result == 0)
            {
                update();
                int check = p_game->bfs();
                p_game->lastPang();
                if(check == 0 && !p_game->moved )
                {
                    p_game->bfsState=false;
                    update();
                    drawNext();
                    p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),0,0);
                }
            }
        }
        update();
        break;
    }
    case Qt::Key_Left:
    {
        if(p_game->getPoint1()->x == 0 || p_game->getPoint2()->x == 0
            || p_game->boardInt[p_game->getPoint1()->y][p_game->getPoint1()->x-1] < 0
            || p_game->boardInt[p_game->getPoint2()->y][p_game->getPoint2()->x-1] < 0 )
        {break;}
        int result;
        p_game->isLast = false;
        result= p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),-1,0);
        if (result == 1)
        {
            p_game->axis_col--;
        }
        else if (result == 3)
        {
            ;
        }
        update();
        break;
    }
    case Qt::Key_Right:
    {
        if(p_game->getPoint1()->x == p_game->COL-1 || p_game->getPoint2()->x == p_game->COL-1
            || p_game->boardInt[p_game->getPoint1()->y][p_game->getPoint1()->x+1] < 0
            || p_game->boardInt[p_game->getPoint2()->y][p_game->getPoint2()->x+1] < 0)
        {break;}
        int result;
        p_game->isLast = false;
        result= p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),1,0);
        if (result == 1)
        {
            p_game->axis_col++;
        }
        else if (result == 3)
        {
            ;
        }
        update();
        break;
    }
    case Qt::Key_Space:
    {
        gameoverwindow = new GameoverWindow;
        gameoverwindow->show();
        break;
    }
    case Qt::Key_Z:
    {
        PointPuyopuyo tempP1 = *p_game->getPoint1();
        PointPuyopuyo tempP2 = *p_game->getPoint2();

        // 반시계 방향 회전
        int tempX = tempP2.x - tempP1.x;
        int tempY = tempP2.y - tempP1.y;
        tempP2.x = tempP1.x + tempY;
        tempP2.y = tempP1.y - tempX;

        PointPuyopuyo p3(tempP2.x, tempP2.y);
        if (tempP1.x == tempP2.x) {
            // tempP1과 tempP2가 세로로 위치할 때
            if (tempP1.y > tempP2.y) {
                p3.x++;
            } else {
                p3.x--;
            }
        } else {
            // tempP1과 tempP2가 가로로 위치할 때
            if (tempP1.x > tempP2.x) {
                p3.y--;
            } else {
                p3.y++;
            }
        }

        if (tempP2.x > p_game->COL-1 || tempP2.x < 0
            || tempP2.y > p_game->ROW+1 || tempP2.y < 0
            || p3.x > p_game->COL-1 || p3.x < 0
            || p3.y > p_game->ROW+1 || p3.y < 0
            || p_game->boardInt[tempP2.y][tempP2.x] < 0
            || p_game->boardInt[p3.y][p3.x] < 0)
        {
            if( p_game->boardInt[tempP2.y][tempP2.x] < 0
                || p_game->boardInt[p3.y][p3.x] < 0)
                p_game->isLast = true;
            break;
        }

        p_game->puyopuyoXZ(p_game->getPoint1(), p_game->getPoint2(), 1);
        update();
        break;
    }
    case Qt::Key_X:
    {
        PointPuyopuyo tempP1 = *p_game->getPoint1();
        PointPuyopuyo tempP2 = *p_game->getPoint2();
        int tempX = tempP2.x - tempP1.x;
        int tempY = tempP2.y - tempP1.y;
        tempP2.x = tempP1.x - tempY;
        tempP2.y = tempP1.y + tempX;

        PointPuyopuyo p3(tempP2.x, tempP2.y);
        if (tempP1.x == tempP2.x) {
            // tempP1과 tempP2가 세로로 위치할 때
            if (tempP1.y > tempP2.y) {
                p3.x--;
            } else {
                p3.x++;
            }
        } else {
            // tempP1과 tempP2가 가로로 위치할 때
            if (tempP1.x > tempP2.x) {
                p3.y++;
            } else {
                p3.y--;
            }
        }

        if (tempP2.x > p_game->COL-1 || tempP2.x < 0
            || tempP2.y > p_game->ROW+1 || tempP2.y < 0
            || p3.x > p_game->COL-1 || p3.x < 0
            || p3.y > p_game->ROW+1 || p3.y < 0
            || p_game->boardInt[tempP2.y][tempP2.x] < 0
            || p_game->boardInt[p3.y][p3.x] < 0)
        {
            if( p_game->boardInt[tempP2.y][tempP2.x] < 0
                || p_game->boardInt[p3.y][p3.x] < 0)
                p_game->isLast = true;
            break;
        }

        p_game->puyopuyoXZ(p_game->getPoint1(), p_game->getPoint2(), 0);
        update();
        break;
    }

    default:
        break;
    }

}

void GameWindow::timerEvent(QTimerEvent* event)
{
    if (p_game->gameover == true)
        return;

    if(event->timerId()==timer)
    {
        update();
        p_game->bfs();
        if(p_game->bfsState)
        {
            int check =p_game->gravity();
            update();
            if(check ==1)
            {
                p_game->bfsState=false;
                p_game->bfs();
                update();
                p_game->lastPang();
                update();
                drawNext();
                p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),0,0);
            }
        }
        else{
            int result;
            result= p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),0,1);
            if (result == 1)
            {
                p_game->axis_row++;
            }
            else if(result == 0)
            {
                update();
                int check = p_game->bfs();
                p_game->lastPang();
                if(check == 0 && !p_game->moved )
                {
                    p_game->bfsState=false;
                    update();
                    drawNext();
                    p_game->puyopuyoMove(p_game->getPoint1(),p_game->getPoint2(),0,0);
                }
            }
        }
    }
}

void GameWindow::drawNext()
{
    int ROW = p_game->ROW;
    int COL = p_game->COL;

    string** board = p_game->board;
    string* next = p_game->next;

    int LENGTH = p_game->LENGTH;

    if (p_game->gameover == true)
    {
        for (int i = 0; i < ROW+2; i++)
            for (int j = 0; j < COL; j++)
            {
                if (board[i][j] == "Red" || board[i][j] == "Yellow" || board[i][j] == "Green" || board[i][j] == "Blue" || board[i][j] == "Purple")
                    board[i][j] = "BlackPuyo";

                else if (board[i][j] == "Gray")
                    board[i][j] = "BlackBlock";
            }

        return;
    }

    if (LENGTH == 2)
    {
        for (int i = 0; i < LENGTH; i++)
        {
            if (i == 0)
            {
                // 두 번째 블록을 첫 번째 블록으로 이동
                next[i] = next[i + 1];
            }
            else if (i == 1)
            {
                // 새 블록을 두 번째 위치에 생성
                char colors[] = {'R', 'Y', 'G', 'B', 'P'};
                next[i] = "";
                next[i] += colors[rand() % 5];
                next[i] += colors[rand() % 5];
            }
        }
    }
    else
    {
        // 다음 블록을 설정 (4개 블록 이동 및 새 블록 생성)
        for (int i = 0; i < LENGTH - 1; i++)
        {
            next[i] = next[i + 1];
        }
        if (GAMENAME == "Tetris")
        {
            // 테트리스 블록 생성
            char shapes[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
            next[LENGTH - 1] = shapes[rand() % 7];
        }
        else if (GAMENAME == "PuyopuyoTetris")
        {
            // 뿌요 또는 테트리스 블록을 랜덤으로 생성
            if (rand() % 2 == 0)
            {
                char colors[] = {'R', 'Y', 'G', 'B', 'P'};
                next[LENGTH - 1] = "";
                next[LENGTH - 1] += colors[rand() % 5];
                next[LENGTH - 1] += colors[rand() % 5];
            }
            else
            {
                char shapes[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
                next[LENGTH - 1] = shapes[rand() % 7];
            }
        }
    }
    (p_game->score)++;
}
