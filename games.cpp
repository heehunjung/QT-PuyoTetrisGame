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

int PuyopuyoGame::move(Points* points, int xPlus, int yPlus)
{
    Point* p1= points->getPoint(0);
    Point* p2= points->getPoint(1);
    // 기존 위치 초기화
    if ((xPlus != 0 || yPlus != 0) && isLast == false )
    {
        if( p2->y <2)  board[p2->y][p2->x] = "Gray";
        else board[p2->y][p2->x] = "White";

        if(p1->y < 2 ) board[p1->y][p1->x] = "Gray";
        else board[p1->y][p1->x] = "White";
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
            initPuyo =false;
            delete p1;
            delete p2;
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
        initPuyo =false;
        delete p1;
        delete p2;
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

void PuyopuyoGame::lastPang(){
    axis_row = 1;
    axis_col = 2;
    this->p1 = new Point(axis_col, axis_row);
    this->p2 = new Point(axis_col, axis_row - 1);
    // if(points)
    // {
    //     delete points;
    // }
    points = new Points();
    points->addPoint(p1);
    points->addPoint(p2);
    initPuyo = true;
}

void PuyopuyoGame::xz(Points* points, int check)
{

    Point* p1 = points->getPoint(0);
    Point* p2 = points->getPoint(1);
    // 기존 위치 초기화

    if( p2->y <2)  board[p2->y][p2->x] = "Gray";
    else board[p2->y][p2->x] = "White";

    boardInt[p2->y][p2->x] = 0;
\
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
    Point pivot = *p1; // p1을 중심으로 회전

    // z 축 회전
    if(check == 1)
    {
        rotateCounterClockwise(points,p1);
    }
    else //x 축 회줜
    {
        rotateClockwise(points,p1);

    }
    if (block2)
    {
        board[p2->y][p2->x] = block2->color;
        boardInt[p2->y][p2->x] = block2->value;
    }
    if (p1->y == ROW + 1 || p2->y == ROW + 1
        || boardInt[p1->y+1][p1->x] < 0 || boardInt[p2->y+1][p2->x] < 0)
    {
        isLast = true;
    }
}

int PuyopuyoGame::bfs() {
    // 방문 확인용 2차원 배열
    int **visited = new int*[ROW+2];
    // 삭제할 위치 저장하는 2차원 배열
    int **deletePoint = new int*[ROW+2];
    int check = 0;
    for(int i = 0; i < ROW+2; i++) {
        deletePoint[i] = new int[COL]();
        visited[i] = new int[COL]();
    }

    // 상하좌우 x축 및 y축 방향
    int x_dir[4] = {1, -1, 0, 0};
    int y_dir[4] = {0, 0, -1, 1};

    // 전체 보드를 탐색
    for(int start_y = 0; start_y < ROW+2; start_y++) {
        for(int start_x = 0; start_x < COL; start_x++) {
            if(boardInt[start_y][start_x] < 0 && !visited[start_y][start_x]) {
                // 탐색 좌표 저장용 큐
                queue<pair<int, int>> q;
                vector<pair<int, int>> group; // 그룹을 저장할 벡터
                q.push(make_pair(start_x, start_y));     // 큐에 삽입

                int currentValue = boardInt[start_y][start_x];

                while(!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    if(visited[y][x]) continue;

                    visited[y][x] = 1;
                    group.push_back(make_pair(x, y));

                    for(int i = 0; i < 4; ++i) {
                        // 현재 좌표와 상하좌우로 인접한 좌표
                        int x_new = x + x_dir[i];
                        int y_new = y + y_dir[i];
                        if(x_new >= 0 && x_new < COL && y_new >= 0 && y_new < ROW+2) {
                            if(!visited[y_new][x_new] && boardInt[y_new][x_new] == currentValue) {
                                q.push(make_pair(x_new, y_new));  // 인접 좌표를 큐에 삽입
                            }
                        }
                    }
                }

                // 그룹 크기가 4개 이상이면 삭제 처리
                if(group.size() >= 4) {
                    for(auto &point : group) {
                        deletePoint[point.second][point.first] = 1;
                    }
                }
            }
        }
    }

    // deletePoint 배열에 따라 보드 업데이트
    for(int i = 0; i < ROW+2; i++) {
        for(int k = 0; k < COL; k++) {
            if(deletePoint[i][k] == 1) {
                board[i][k] = "White";
                boardInt[i][k] = 0;
                check = 1;
            }
        }
    }
    if(check == 1){
        score++;
        bfsState = true;
        return 1;
    }
    else{
        bfsState = false;
        return 0;
    }
}

int PuyopuyoGame::gravity() {
    moved=false;
    for (int col = 0; col < COL; col++) {
        for (int row = ROW; row >= 0; row--) {
            if (boardInt[row][col] < 0) {
                // 한 칸 아래로 이동할 수 있으면 이동
                if (row + 1 <= ROW + 1 && boardInt[row + 1][col] == 0) {
                    board[row + 1][col] = board[row][col];
                    boardInt[row + 1][col] = boardInt[row][col];
                    board[row][col] = "White";
                    boardInt[row][col] = 0;
                    moved = true;  // 이동이 발생했음을 기록
                }
            }
        }
    }

    // row가 0과 1일 때는 이동하지 않아도 1을 반환
    for (int col = 0; col < COL; col++) {
        if ((boardInt[0][col] > 0 || boardInt[1][col] > 0)) {
            return 0;
        }
    }
    if (moved) {
        return 0;
    }
    else{
    return 1;
    }
}

PuyopuyoGame::PuyopuyoGame() : Game(12, 6, 2)
{
    // Initialize random seed
    srand(time(0));
    isLast = false;
    bfsState = false;
    initPuyo = true;
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
    p1 = new Point(axis_col,axis_row);
    p2 = new Point(axis_col,axis_row-1);
    points = new Points();
    points->addPoint(p1);
    points->addPoint(p2);
    score = 0;
}

PuyopuyoGame::~PuyopuyoGame()
{
    delete p1;
    delete p2;
    delete points;
}

TetrisGame::TetrisGame() : Game(15, 10, 5) {
    // Initialize random seed
    srand(time(0));
    isLast = false;
    bfsState = false;
    initPuyo = true;

    // Initialize the board
    for (int i = 0; i < ROW+2 ; i++) {
        for (int j = 0; j < COL; j++) {
            boardInt[i][j] = 0;
            board[i][j] = "White";
        }
    }

    // Initialize next blocks
    for (int i = 0; i < 5; ++i) {
        char shapes[] = {'O', 'I', 'T', 'S', 'Z', 'J', 'L'};
        next[i] = shapes[rand() % 7];
    }

    axis_row = 1;
    axis_col = 4;


    char currentShape = next[0][0]; // 첫 번째 모양을 가져옴
    pastShape = next[0];

    // Initialize points based on the shape
    switch (currentShape) {
    case 'O':
        // O shape
        axis_row = 0;
        axis_col = 4;
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col + 1, axis_row);
        p3 = new Point(axis_col, axis_row + 1);
        p4 = new Point(axis_col + 1, axis_row + 1);
        break;
    case 'I':
        // I shape
        axis_row = 1.5;
        axis_col = 4.5;
        p1 = new Point(axis_col-1.5, axis_row-0.5);
        p2 = new Point(axis_col-0.5, axis_row-0.5 );
        p3 = new Point(axis_col+0.5, axis_row-0.5 );
        p4 = new Point(axis_col+1.5, axis_row-0.5 );
        break;
    case 'T':
        // T shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col - 1, axis_row );
        p3 = new Point(axis_col, axis_row - 1);
        p4 = new Point(axis_col + 1, axis_row );
        break;
    case 'S':
        // S shape
        p1 = new Point(axis_col, axis_row );
        p2 = new Point(axis_col - 1, axis_row );
        p3 = new Point(axis_col , axis_row -1);
        p4 = new Point(axis_col + 1, axis_row -1);
        break;
    case 'Z':
        // Z shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col -1, axis_row -1);
        p3 = new Point(axis_col, axis_row - 1);
        p4 = new Point(axis_col + 1, axis_row );
        break;
    case 'J':
        // J shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col +1, axis_row );
        p3 = new Point(axis_col -1, axis_row );
        p4 = new Point(axis_col -1, axis_row -1);
        break;
    case 'L':
        // L shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col +1, axis_row);
        p3 = new Point(axis_col -1, axis_row);
        p4 = new Point(axis_col +1, axis_row -1);
        break;
    default:
        break;
    }
    points = new Points();
    points->addPoint(p1);
    points->addPoint(p2);
    points->addPoint(p3);
    points->addPoint(p4);

    score = 0;
}

TetrisGame::~TetrisGame()
{
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete points;
}
int TetrisGame::move(Points* points, int xPlus, int yPlus) {
    Point* p1 = points->getPoint(0);
    Point* p2 = points->getPoint(1);
    Point* p3 = points->getPoint(2);
    Point* p4 = points->getPoint(3);

    // 기존 위치 초기화
    if ((xPlus != 0 || yPlus != 0) && isLast == false) {
        for (auto p : {p1, p2, p3, p4}) {
            if (p->y < 2) {
                board[p->y][p->x] = "White";
            } else {
                board[p->y][p->x] = "White";
            }
            boardInt[p->y][p->x] = 0;
        }
    }

    // 새로운 위치 계산
    for (auto p : {p1, p2, p3, p4}) {
        p->x += xPlus;
        p->y += yPlus;
    }

    // 블록 초기화
    Board* shape = nullptr;
    switch (next[0][0]) {
    case 'O': shape = new Oshape(); break;
    case 'T': shape = new Tshape(); break;
    case 'S': shape = new Sshape(); break;
    case 'Z': shape = new Zshape(); break;
    case 'J': shape = new Jshape(); break;
    case 'L': shape = new Lshape(); break;
    case 'I': shape = new Ishape(); break;
    }
    // 좌표가 보드 범위 내에 있는지 확인
    bool inBounds = true;
    for (auto p : {p1, p2, p3, p4}) {
        if (!(p->y >= 0 && p->y <= ROW + 1 && p->x >= 0 && p->x < COL)) {
            inBounds = false;
            break;
        }
    }

    if (inBounds) {
        isLast = false;
        bool canMove = true;
        for (auto p : {p1, p2, p3, p4}) {
            if (boardInt[p->y][p->x] < 0) {
                canMove = false;
                break;
            }
        }

        if (canMove) {
            for (auto p : {p1, p2, p3, p4}) {
                if (shape) {
                    board[p->y][p->x] = shape->color;
                    boardInt[p->y][p->x] = shape->value;
                }
            }

            // 현재 이동한 위치에 작성할 수 있는데, x,y축 끝인 경우
            for (auto p : {p1, p2, p3, p4}) {
                if (p->y == ROW + 1 || boardInt[p->y + 1][p->x] < 0) {
                    isLast = true;
                }
            }

            delete shape;
            return 1;
        } else {
            for (auto p : {p1, p2, p3, p4}) {
                if (shape) {
                    boardInt[p->y - 1][p->x] = shape->afterValue;
                }
            }
            delete shape;
            initPuyo = false;
            delete p1;
            delete p2;
            delete p3;
            delete p4;
            return 0;
        }
    } else if ((p1->y > ROW) || (p2->y > ROW) || (p3->y > ROW) || (p4->y > ROW)) {
        for (auto p : {p1, p2, p3, p4}) {
            if (shape) {
                boardInt[p->y - 1][p->x] = shape->afterValue;
            }
        }
        delete shape;
        initPuyo = false;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        return 0;
    } else if (COL == p2->x || COL == p1->x || COL == p3->x || COL == p4->x) {
        delete shape;
        return 3;
    }

    delete shape;
    return -1;
}
void TetrisGame::xz(Points* points, int check)
{
    // Points 벡터에서 포인트들을 가져옴
    Point* p1 = points->getPoint(0);
    Point* p2 = points->getPoint(1);
    Point* p3 = points->getPoint(2);
    Point* p4 = points->getPoint(3);
    Point pivot = *p1; // 기본 피벗은 p1
    qDebug() << pastShape;
    // 현재 블록의 모양에 따라 피벗을 설정
    if (pastShape == "I") {
            pivot.x = axis_col;
            pivot.y = axis_row;
    } else if (pastShape == "O") {
        return; // O 블록은 회전하지 않음
    }

    // 기존 위치 초기화
    for (int i = 0; i < points->size(); ++i) {
        Point* p = points->getPoint(i);
        if (p->y < 2) {
            board[p->y][p->x] = "White";
        } else {
            board[p->y][p->x] = "White";
        }
        boardInt[p->y][p->x] = 0;
    }

    // 블록 초기화
    Board* block = nullptr;

    // z 축 회전
    if (check == 1) {
        rotateCounterClockwise(points, &pivot);
    } else { // x 축 회전
        rotateClockwise(points, &pivot);
    }

    for (int i = 0; i < points->size(); ++i) {
        Point* p = points->getPoint(i);
        if (block) {
            board[p->y][p->x] = "Gray";
            boardInt[p->y][p->x] = 6;
        }
    }

    // 회전 후에 보드 상태를 업데이트
    for (int i = 0; i < points->size(); ++i) {
        Point* p = points->getPoint(i);
        if (p->y == ROW + 1 || boardInt[p->y + 1][p->x] < 0) {
            isLast = true;
        }
    }

    // 보드 상태를 회전 후의 값으로 업데이트
    for (int i = 0; i < points->size(); ++i) {
        Point* p = points->getPoint(i);
        board[p->y][p->x] = "Gray"; // 블록의 색상을 업데이트
        boardInt[p->y][p->x] = 6;   // 블록의 값을 업데이트
    }
}

int TetrisGame::gravity() {
    moved=false;
    for (int col = 0; col < COL; col++) {
        for (int row = ROW; row >= 0; row--) {
            if (boardInt[row][col] < 0) {
                // 한 칸 아래로 이동할 수 있으면 이동
                if (row + 1 <= ROW + 1 && boardInt[row + 1][col] == 0) {
                    board[row + 1][col] = board[row][col];
                    boardInt[row + 1][col] = boardInt[row][col];
                    board[row][col] = "White";
                    boardInt[row][col] = 0;
                    moved = true;  // 이동이 발생했음을 기록
                }
            }
        }
    }

    // row가 0과 1일 때는 이동하지 않아도 1을 반환
    for (int col = 0; col < COL; col++) {
        if ((boardInt[0][col] > 0 || boardInt[1][col] > 0)) {
            return 0;
        }
    }
    if (moved) {
        return 0;
    }
    else{
        return 1;
    }
}

void TetrisGame::lastPang(){
    axis_row = 1;
    axis_col = 4;

    char currentShape = next[0][0]; // 첫 번째 모양을 가져옴
    pastShape = next[0];

    // Initialize points based on the shape
    switch (currentShape) {
    case 'O':
        // O shape
        axis_row = 0;
        axis_col = 4;
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col + 1, axis_row);
        p3 = new Point(axis_col, axis_row + 1);
        p4 = new Point(axis_col + 1, axis_row + 1);
        break;
    case 'I':
        // I shape
        axis_row = 1.5;
        axis_col = 4.5;
        p1 = new Point(axis_col-1.5, axis_row-0.5);
        p2 = new Point(axis_col-0.5, axis_row-0.5 );
        p3 = new Point(axis_col+0.5, axis_row-0.5 );
        p4 = new Point(axis_col+1.5, axis_row-0.5 );
        break;
    case 'T':
        // T shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col - 1, axis_row );
        p3 = new Point(axis_col, axis_row - 1);
        p4 = new Point(axis_col + 1, axis_row );
        break;
    case 'S':
        // S shape
        p1 = new Point(axis_col, axis_row );
        p2 = new Point(axis_col - 1, axis_row );
        p3 = new Point(axis_col , axis_row -1);
        p4 = new Point(axis_col + 1, axis_row -1);
        break;
    case 'Z':
        // Z shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col -1, axis_row -1);
        p3 = new Point(axis_col, axis_row - 1);
        p4 = new Point(axis_col + 1, axis_row );
        break;
    case 'J':
        // J shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col +1, axis_row );
        p3 = new Point(axis_col -1, axis_row );
        p4 = new Point(axis_col -1, axis_row -1);
        break;
    case 'L':
        // L shape
        p1 = new Point(axis_col, axis_row);
        p2 = new Point(axis_col +1, axis_row);
        p3 = new Point(axis_col -1, axis_row);
        p4 = new Point(axis_col +1, axis_row -1);
        break;
    default:
        break;
    }
    points = new Points();
    points->addPoint(p1);
    points->addPoint(p2);
    points->addPoint(p3);
    points->addPoint(p4);

}
int TetrisGame::bfs() {
    int linesCleared = 0;

    // Iterate over each row
    for (int row = 0; row < ROW + 2; ++row) {
        bool fullLine = true;

        // Check if the entire row is filled with -6
        for (int col = 0; col < COL; ++col) {
            if (boardInt[row][col] != -6) {
                fullLine = false;
                break;
            }
        }

        // If the line is full, clear it
        if (fullLine) {
            ++linesCleared;

            // Clear the row
            for (int col = 0; col < COL; ++col) {
                boardInt[row][col] = 0;
                board[row][col] = "White";
            }
        }
    }

    // Update the score and bfsState
    if (linesCleared > 0) {
        score += linesCleared;
        bfsState = true;
        return 1;  // 반환값이 1일 때
    } else {
        bfsState = false;
        return 0;  // 반환값이 0일 때
    }
}
// PuyopuyoTetrisGame::PuyopuyoTetrisGame() : Game(16, 8, 5)
// {

//     for(int i=0;i<5;i++)
//     {
//         if (rand() % 2 == 0)
//         {
//             char colors[] = {'R', 'Y', 'G', 'B', 'P'};
//             next[i] = colors[rand() % 5];
//             next[i] += colors[rand() % 5];
//         }
//         else
//         {
//             char shapes[] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
//             next[i] = shapes[rand() % 7];
//         }
//     }

//     for(int i = 0; i < ROW+2; i++)
//         for(int j = 0; j < COL; j++)
//         {
//             if(i < 2)
//                 board[i][j] = "Gray";
//             else
//                 board[i][j] = "White";
//         }

//     axis_row = 0.5;
//     axis_col = 4;

//     score = 2;
// }

// PuyopuyoTetrisGame::~PuyopuyoTetrisGame()
// {
//     ;
// }
