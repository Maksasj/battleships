#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

const int CHIP_COUNT_1X1 = 1; //3
const int CHIP_COUNT_2X1 = 1; //2
const int CHIP_COUNT_3X1 = 1; //2

const int MAX_GENERATION_STEPS = 25000;

const int RENDER_BUFFER_SIZE = 40;

void HowToPlay() {
    cout << "TODO !";
}

void Controls() {
    cout << "TODO !";
}

// ' '- Empty
//  W - water
//
//  O - 1x1 ship
//
//  //For 2x1 and 3x1 ships
//  T - Ship back
//  V - Ship front
//  0 - Chip middle

pair<vector<vector<char>>, bool> GenerateBoard(int size) {
    int steps = 0;
    vector<vector<char>> board;

    for(int i = 0; i < size; ++i) {
        vector<char> tmp;
        for(int j = 0; j < size; ++j) {
            tmp.push_back(' ');
        }
        board.push_back(tmp);
    }

    for(int i = 0; i < CHIP_COUNT_3X1; ++i) {
        int tmp = 1;

        while (tmp) {
            ++steps;
            if(steps > MAX_GENERATION_STEPS) return { vector<vector<char>>(), true };

            int x = rand() % size;
            int y = rand() % size;

            if( (x + 1 < size) && (board[x + 1][y] != ' ')) continue;
            if( (x - 1 >= 0) && (board[x - 1][y] != ' ')) continue;
            if( (y + 1 < size) && (board[x][y + 1] != ' ')) continue;
            if( (y - 1 >= 0) && (board[x][y - 1] != ' ')) continue;

            if(board[x][y] != ' ') continue;

            int rotation = rand() % 2; // 0 horizontal, 1 vertical

            int xFirst = x; int yFirst = y;
            int xSecond = x; int ySecond = y;

            if(rotation) {
                xFirst += 1;
                xSecond -= 1;
            } else {
                yFirst += 1;
                ySecond -= 1;
            }

            if(xFirst < 0 || xFirst >= size) continue;
            if(yFirst < 0 || yFirst >= size) continue;
            if(xSecond < 0 || xSecond >= size) continue;
            if(ySecond < 0 || ySecond >= size) continue;

            if((x + 1 < size) && (board[x + 1][y] != ' ')) continue;
            if((x - 1 >= 0)   && (board[x - 1][y] != ' ')) continue;
            if((y + 1 < size) && (board[x][y + 1] != ' ')) continue;
            if((y - 1 >= 0)   && (board[x][y - 1] != ' ')) continue;
            
            if( (xFirst + 1 < size) &&   (board[xFirst + 1][yFirst] != ' ')) continue;
            if( (xFirst - 1 >= 0)   &&   (board[xFirst - 1][yFirst] != ' ')) continue;
            if( (yFirst + 1 < size) &&   (board[xFirst][yFirst + 1] != ' ')) continue;
            if( (yFirst - 1 >= 0)   &&   (board[xFirst][yFirst - 1] != ' ')) continue;

            if( (xSecond + 1 < size) &&   (board[xSecond + 1][ySecond] != ' ')) continue;
            if( (xSecond - 1 >= 0)   &&   (board[xSecond - 1][ySecond] != ' ')) continue;
            if( (ySecond + 1 < size) &&   (board[xSecond][ySecond + 1] != ' ')) continue;
            if( (ySecond - 1 >= 0)   &&   (board[xSecond][ySecond - 1] != ' ')) continue;
            
            if(x + 1 < size)    board[x + 1][y] = 'W';
            if(x - 1 >= 0)      board[x - 1][y] = 'W';
            if(y + 1 < size)    board[x][y + 1] = 'W';
            if(y - 1 >= 0)      board[x][y - 1] = 'W';

            board[xFirst][yFirst] = 'V';
            if(xFirst + 1 < size)    board[xFirst + 1][yFirst] = 'W';
            if(xFirst - 1 >= 0)      board[xFirst - 1][yFirst] = 'W';
            if(yFirst + 1 < size)    board[xFirst][yFirst + 1] = 'W';
            if(yFirst - 1 >= 0)      board[xFirst][yFirst - 1] = 'W';

            board[xSecond][ySecond] = 'T';
            if(xSecond + 1 < size)    board[xSecond + 1][ySecond] = 'W';
            if(xSecond - 1 >= 0)      board[xSecond - 1][ySecond] = 'W';
            if(ySecond + 1 < size)    board[xSecond][ySecond + 1] = 'W';
            if(ySecond - 1 >= 0)      board[xSecond][ySecond - 1] = 'W';

            board[x][y] = '0';

            tmp = 0;
        }
    }

    for(int i = 0; i < CHIP_COUNT_2X1; ++i) {
        int tmp = 1;

        while (tmp) {
            ++steps;
            if(steps > MAX_GENERATION_STEPS) return { vector<vector<char>>(), true };

            int x = rand() % size;
            int y = rand() % size;

            if(board[x][y] != ' ') continue;

            if( (x + 1 < size) && (board[x + 1][y] != ' ')) continue;
            if( (x - 1 >= 0) && (board[x - 1][y] != ' ')) continue;
            if( (y + 1 < size) && (board[x][y + 1] != ' ')) continue;
            if( (y - 1 >= 0) && (board[x][y - 1] != ' ')) continue;

            for(int dX = -1; dX <= 1; ++dX) {
                for(int dY = -1; dY <= 1; ++dY) {
                    if((dX + dY == 0) || (dX + dY == 2) || (dX + dY == -2)) continue;
                    int fronX = x + dX;
                    int fronY = y + dY;

                    if( (fronX >= size)) continue;
                    if( (fronX < 0)) continue;
                    if( (fronY >= size)) continue;
                    if( (fronY < 0)) continue;

                    if( (fronX + 1 < size) &&   (board[fronX + 1][fronY] != ' ')) continue;
                    if( (fronX - 1 >= 0) &&     (board[fronX - 1][fronY] != ' ')) continue;
                    if( (fronY + 1 < size) &&   (board[fronX][fronY + 1] != ' ')) continue;
                    if( (fronY - 1 >= 0) &&     (board[fronX][fronY - 1] != ' ')) continue;
                    
                    board[x][y] = 'T';
                    board[fronX][fronY] = 'V';

                    if(x + 1 < size && dX != 1)     board[x + 1][y] = 'W';
                    if(x - 1 >= 0   && dX != -1)    board[x - 1][y] = 'W';
                    if(y + 1 < size && dY != 1)     board[x][y + 1] = 'W';
                    if(y - 1 >= 0   && dY != -1)    board[x][y - 1] = 'W';

                    if(fronX + 1 < size && dX != -1)     board[fronX + 1][fronY] = 'W';
                    if(fronX - 1 >= 0   && dX != 1)    board[fronX - 1][fronY] = 'W';
                    if(fronY + 1 < size && dY != -1)     board[fronX][fronY + 1] = 'W';
                    if(fronY - 1 >= 0   && dY != 1)    board[fronX][fronY - 1] = 'W';

                    tmp = 0;
                    dX = 2;
                    dY = 2;
                }
            }
        }
    }

    for(int i = 0; i < CHIP_COUNT_1X1; ++i) {
        while (true) {
            ++steps;
            if(steps > MAX_GENERATION_STEPS) return { vector<vector<char>>(), true };

            int x = rand() % size;
            int y = rand() % size;

            if(board[x][y] != ' ') continue;

            if( (x + 1 < size) && (board[x + 1][y] != ' ')) continue;
            if( (x - 1 >= 0) && (board[x - 1][y] != ' ')) continue;
            if( (y + 1 < size) && (board[x][y + 1] != ' ')) continue;
            if( (y - 1 >= 0) && (board[x][y - 1] != ' ')) continue;

            board[x][y] = 'O';

            if(x + 1 < size) board[x + 1][y] = 'W';
            if(x - 1 >= 0) board[x - 1][y] = 'W';
            if(y + 1 < size) board[x][y + 1] = 'W';
            if(y - 1 >= 0) board[x][y - 1] = 'W';

            break;
        }
    }

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            if(board[i][j] == ' ') board[i][j] = 'W';

    return { board, false };
}

void RenderBoard(vector<vector<char>> visibleBoard, vector<vector<char>> board, int size) {
    char renderBuffer[RENDER_BUFFER_SIZE][RENDER_BUFFER_SIZE];
    int activeZoneHeight = 0;

    for(int i = 0; i < RENDER_BUFFER_SIZE; ++i)
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            renderBuffer[i][j] = ' ';


    for(int i = 0; i < size*2 + 1; ++i) {
        renderBuffer[1][i] = '-';
        renderBuffer[size + 2][i] = '-';
    }

    for(int i = 0; i < size + 2; ++i) {
        renderBuffer[i][1] = '|';
        renderBuffer[i][size*2 + 1] = '|';
    }

    renderBuffer[1][1] = '+';
    renderBuffer[2 + size][1] = '+';
    renderBuffer[1][1 + size * 2] = '+';
    renderBuffer[2 + size][1 + size * 2] = '+';

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            renderBuffer[2 + i][2 + j * 2] = visibleBoard[i][j];

    for(int i = 0; i < size; ++i) {
        int rowCount = 0;

        for(int j = 0; j < size; ++j)
            if(board[i][j] != 'W') rowCount++;

        renderBuffer[i + 2][0] = rowCount + 48;
    }

    for(int i = 0; i < size; ++i) {
        int rowCount = 0;

        for(int j = 0; j < size; ++j)
            if(board[j][i] != 'W') rowCount++;

        renderBuffer[0][2 + i*2] = rowCount + 48;
    }

    //Find activeZoneHeight
    for(int i = 0; i < RENDER_BUFFER_SIZE; ++i)
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            if(renderBuffer[i][j] != ' ')
                if(activeZoneHeight < i)
                    activeZoneHeight = i + 1;

    //Rendering
    for(int i = 0; i < std::min(RENDER_BUFFER_SIZE, activeZoneHeight); ++i) {
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            cout << renderBuffer[i][j];
        cout << "\n";
    }
}

void Puzzle() {
    int size;

    string choosePuzzleSizeScreenBuffer = 
        "       Available sizes        \n"
        "1. 6x6                        \n"
        "2. 7x7                        \n"
        "3. 8x8                        \n"
        "4. 10x10                      \n"
        "5. 12x12                      \n"
        "6. 15x15                      \n";

    cout << choosePuzzleSizeScreenBuffer;

    while(true) {
        string tmp;
        cout << ">> ";
        cin >> tmp;

        if(tmp == "1")
            size = 6;
        else if(tmp == "2")
            size = 7;
        else if(tmp == "3")
            size = 8;
        else if(tmp == "4")
            size = 10;
        else if(tmp == "5")
            size = 12;
        else if(tmp == "6")
            size = 15;
        else {
            cout << "Please enter one of the valid options (1, 2, 3, 4, 5, 6)\n";
            continue;
        }

        break;
    }

    pair<vector<vector<char>>, bool> boardRes = GenerateBoard(size);
    
    if(boardRes.second == true) {
        cout << "Failed to generate board, probably can't fit all ship on provided board (board size to small)";
        return;
    } 

    vector<vector<char>> board = boardRes.first;
    vector<vector<char>> visibleBoard;

    for(int i = 0; i < size; ++i) {
        vector<char> tmp;
        for(int j = 0; j < size; ++j)
            tmp.push_back(' ');
        visibleBoard.push_back(tmp);
    }

    //Open a fiew random tiles
    for(int i = 0; i < size / 2; ++i) {
        int x = rand() % size;
        int y = rand() % size;

        visibleBoard[x][y] = board[x][y];
    }
 
    RenderBoard(visibleBoard, board, size);
}

int main() {
    srand(time(NULL));

    string welcomeScreenBuffer =
        "       Daily Battleships     \n"
        "1. Begin Puzzle              \n"
        "2. How to play               \n"
        "3. Controls                  \n"
        "4. Exit                      \n";

    cout << welcomeScreenBuffer;

    while(true) {
        string tmp;
        cout << ">> ";
        cin >> tmp;

        if(tmp == "1") {
            Puzzle();
            return 0;
        } else if(tmp == "2")
            HowToPlay();
        else if(tmp == "3")
            Controls();
        else if(tmp == "4")
            return 0;
        else
            cout << "Please enter one of the following options 1, 2, 3, 4.\n";
    }
    
    return 0;
}
