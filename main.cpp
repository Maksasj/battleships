#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

const int CHIP_COUNT_1X1 = 3; //3
const int CHIP_COUNT_2X1 = 2; //2
const int CHIP_COUNT_3X1 = 2; //2

const int MAX_GENERATION_STEPS = 100000;

const int RENDER_BUFFER_SIZE = 80;

void HowToPlay() {
    string howToPlayScreenBuffer =
        "\n"
        "Objective / Rules                                                                                                 \n"
        "Find all of the hidden ships.                                                                                     \n"
        "The numbers across the top and down the side tell you how many ship pieces are in the respective row / column.    \n"
        "The small ships across the top tell you which ships are hidden in the grid.                                       \n"
        "A ship can only be found horizontally or vertically.                                                              \n"
        "Ships are never adjacent to each other, neither vertically, horizontally, nor diagonally.                         \n"
        "                                                                                                                  \n"
        "Tiles:                                                                                                            \n"
        "' '- Empty                                                                                                        \n"
        "W - water                                                                                                         \n"
        "O - 1x1 ship                                                                                                      \n"
        "                                                                                                                  \n"
        "T - Ship back                                                                                                     \n"
        "V - Ship front                                                                                                    \n"
        "0 - Chip middle                                                                                                   \n";

    cout << howToPlayScreenBuffer;
}

void Controls() {
    string controlsScreenBuffer = 
        "\n"
        "Controls          \n"
        "Arrows - Move     \n"
        "Q - quit game     \n"
        "C - Check board   \n"
        "M - Mark tile     \n"
        "A - Answer        \n";

    cout << controlsScreenBuffer;
}

void ClearConsole() {
    cout << "\x1B[2J\x1B[H" << flush;
}

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

            if(x + 1 >= size) continue;
            if(x - 1 < 0) continue;
            if(x + 1 >= size) continue;
            if(x - 1 < 0) continue;

            if(board[x + 1][y] != ' ') continue;
            if(board[x - 1][y] != ' ') continue;
            if(board[x][y + 1] != ' ') continue;
            if(board[x][y - 1] != ' ') continue;

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

vector<vector<char>> RenderBoard(vector<vector<char>> renderBuffer, vector<vector<char>> visibleBoard, vector<vector<char>> board, int size) {
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

    return renderBuffer;
}

void RenderRenderingBuffer(vector<vector<char>> renderBuffer) {
    int activeZoneHeight = 0;

    //Find activeZoneHeight
    for(int i = 0; i < RENDER_BUFFER_SIZE; ++i)
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            if(renderBuffer[i][j] != ' ')
                if(activeZoneHeight <= i)
                    activeZoneHeight = i + 1;

    //Rendering
    for(int i = 0; i < min(RENDER_BUFFER_SIZE, activeZoneHeight); ++i) {
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            cout << renderBuffer[i][j];
        cout << "\n";
    }
}

bool CheckBoard(vector<vector<char>> visibleBoard, vector<vector<char>> board, int size) {
    for(int x = 0; x < size; ++x) {
        for(int y = 0; y < size; ++y) {
            char requiredTile = board[x][y];
            char availableTile = visibleBoard[x][y];

            if(requiredTile == 'T' || requiredTile == 'V' || requiredTile == '0' || requiredTile == 'O')
                requiredTile == 'S';

            if(availableTile == 'T' || availableTile == 'V' || availableTile == '0' || availableTile == 'O')
                availableTile == 'S';

            if(requiredTile != availableTile)
                return false;
        }   
    }

    return true;
}

vector<vector<char>> RenderTextOnRenderingBuffer(vector<vector<char>> renderBuffer, int x, int y, std::string text) {
    if(y < 0 || y >= RENDER_BUFFER_SIZE) return renderBuffer;
    
    for(auto letter : text) {
        if(x < 0 || x >= RENDER_BUFFER_SIZE) return renderBuffer;

        renderBuffer[y][x] = letter;
        ++x;
    }

    return renderBuffer;
}

bool Puzzle() {
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
    
    for(int i = 0; i < 500; ++i) {
        boardRes = GenerateBoard(size);
        if(boardRes.second == false) break; 
    }

    if(boardRes.second == true) {
        cout << "Failed to generate board, probably can't fit all ship on provided board (board size to small), please try again \n";
        return false;
    }

    vector<vector<char>> board = boardRes.first;
    vector<vector<char>> visibleBoard;

    for(int i = 0; i < size; ++i) {
        vector<char> tmp;
        for(int j = 0; j < size; ++j)
            tmp.push_back(' ');
        visibleBoard.push_back(tmp);
    }

    vector<pair<int, int>> blockedTiles;

    //Open a fiew random tiles
    for(int i = 0; i < size / 2; ++i) {
        int x = rand() % size;
        int y = rand() % size;

        visibleBoard[x][y] = board[x][y];
        blockedTiles.push_back({x, y});
    }

    //Open a fiew tiles with ships
    for(int i = 0; i < size / 3; ++i) {
        while(true) {
            int x = rand() % size;
            int y = rand() % size;

            if(board[x][y] == 'W') continue;

            visibleBoard[x][y] = board[x][y];
            blockedTiles.push_back({x, y});
            break;
        }
    }

    vector<vector<char>> renderBuffer;
    for(int i = 0; i < RENDER_BUFFER_SIZE; ++i) {
        vector<char> tmp;
        for(int j = 0; j < RENDER_BUFFER_SIZE; ++j)
            tmp.push_back(' ');
        renderBuffer.push_back(tmp);
    }

    int xCursor = 2;
    int yCursor = 2;

    ClearConsole();
    renderBuffer = RenderBoard(renderBuffer, visibleBoard, board, size);

    renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 1, "Arrows - Move");
    renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 2, "Q - quit game");
    renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 3, "C - Check board");
    renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 4, "M - Mark tile");
    renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 5, "A - Answer");

    renderBuffer[xCursor][yCursor] = 239;
    RenderRenderingBuffer(renderBuffer);

    int wait = true;
    while(wait)
        for(int i = 8; i <= 256; i++)
            if(!GetAsyncKeyState(65)) {
                wait = false;
                break;
            }

    bool firstCycle = true;
    while (!GetAsyncKeyState('q')) {
        wait = true;

        if(firstCycle) {
            Sleep(500);
            firstCycle = false;
            continue;
        }

        while(wait)
            for(int i = 8; i <= 256; i++)
                if(GetAsyncKeyState(i) & 0x7FFF) {
                    wait = false;
                    break;
                }

        if(GetAsyncKeyState(37))       //37 - Left
            if(yCursor - 2 >= 0) yCursor -= 2;
        
        if(GetAsyncKeyState(38))         //38 - Up
            if(xCursor - 1 >= 0) --xCursor;
        
        if(GetAsyncKeyState(39))      //39 - Right
            if(yCursor + 2 < RENDER_BUFFER_SIZE) yCursor += 2;
        
        if(GetAsyncKeyState(40))       //40 - Down
            if(xCursor + 1 < RENDER_BUFFER_SIZE) ++xCursor;

        if(GetAsyncKeyState(81))       //81 - Exit
            return false;

        bool renderBlockedTileWarning = false;
        if(GetAsyncKeyState(77)) {     //77 - M - Mark
            int boardX = xCursor - 2;
            int boardY = (yCursor / 2) - 1;

            //Check for blocked tile
            int blocked = false;
            for(auto tile : blockedTiles) {
                if(tile.first == boardX && tile.second == boardY)
                    blocked = true;
            }

            if(!blocked) {
                if(boardX < 0 || boardX >= size) continue;
                if(boardY < 0 || boardY >= size) continue;

                char chosenTile = visibleBoard[boardX][boardY];

                if(chosenTile == ' ')
                    visibleBoard[boardX][boardY] = 'W';
                else if(chosenTile == 'W')
                    visibleBoard[boardX][boardY] = 'S';
                else if(chosenTile == 'S')
                    visibleBoard[boardX][boardY] = ' ';   
            } else
                renderBlockedTileWarning = true;
        }

        bool renderMistakeWarning = false;

        if(GetAsyncKeyState(67)) {     //67 - C - Check if board correct
            bool res = CheckBoard(visibleBoard, board, size);

            if(res == true) {
                return true;
            } else {
                renderMistakeWarning = true;
            }
        }

        bool renderAnswerNote = false;

        if(GetAsyncKeyState(65)) {     //65 - A - Answer
            for(int x = 0; x < size; ++x) {
                for(int y = 0; y < size; ++y) {
                    visibleBoard[x][y] = board[x][y];
                }
            }

            renderAnswerNote = true;
        }

        ClearConsole();
        renderBuffer = RenderBoard(renderBuffer, visibleBoard, board, size);

        if(renderBlockedTileWarning)
            renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2, 3 + size, "This tile was given to you at the start and cannot be changed");

        if(renderMistakeWarning)
            renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2, 3 + size, "Mistakes Found");

        if(renderAnswerNote)
            renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2, 3 + size, "Answer revealed");
        
        renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 1, "Arrows - Move");
        renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 2, "Q - quit game");
        renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 3, "C - Check board");
        renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 4, "M - Mark tile");
        renderBuffer = RenderTextOnRenderingBuffer(renderBuffer, 2 + 2 * size, 5, "A - Answer");

        renderBuffer[xCursor][yCursor] = 239;
        RenderRenderingBuffer(renderBuffer);

        if(renderAnswerNote)
            return false;
    }    

    return false;
}

int main() {
    srand(time(NULL));

    while(true) {
        string welcomeScreenBuffer =
            "\n"
            "       Daily Battleships     \n"
            "1. Begin Puzzle              \n"
            "2. How to play               \n"
            "3. Controls                  \n"
            "4. Exit                      \n";

        cout << welcomeScreenBuffer;

        string tmp;
        cout << ">> ";
        cin >> tmp;

        if(tmp == "1") {
            bool rez = Puzzle();

            if(rez) {
                cout << "Congratulations, you completed the game! :)";
            }
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
