#include <iostream>
#include <array>
#include <limits>
#include <climits>
#include <algorithm>
#include <utility>
using namespace std;

const int SIZE = 3;
using Board = array<array<char, SIZE>, SIZE>;

// ---- Prototipos ----
void initBoard(Board &board);
void printBoard(const Board &board);
bool isValidMove(const Board &board, int row, int col);
bool makeMove(Board &board, int row, int col, char player);
bool isBoardFull(const Board &board);
char checkWinner(const Board &board);

int evaluate(const Board &board);
int minimax(Board &board, int depth, bool isMax);
pair<int,int> findBestMove(Board &board, char aiPlayer, char humanPlayer);

void playPvP();
void playPvC();
int getIntInRange(int minv, int maxv);

// ---- Implementación ----
void initBoard(Board &board) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';
}

void printBoard(const Board &board) {
    cout << "\n   1   2   3\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "  ---+---+---\n";
    }
    cout << "\n";
}

bool isValidMove(const Board &board, int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

bool makeMove(Board &board, int row, int col, char player) {
    if (!isValidMove(board, row, col)) return false;
    board[row][col] = player;
    return true;
}

bool isBoardFull(const Board &board) {
    for (auto &r : board)
        for (auto c : r)
            if (c == ' ') return false;
    return true;
}

char checkWinner(const Board &b) {
    for (int i = 0; i < SIZE; ++i)
        if (b[i][0] != ' ' && b[i][0] == b[i][1] && b[i][1] == b[i][2]) return b[i][0];
    for (int j = 0; j < SIZE; ++j)
        if (b[0][j] != ' ' && b[0][j] == b[1][j] && b[1][j] == b[2][j]) return b[0][j];
    if (b[0][0] != ' ' && b[0][0] == b[1][1] && b[1][1] == b[2][2]) return b[0][0];
    if (b[0][2] != ' ' && b[0][2] == b[1][1] && b[1][1] == b[2][0]) return b[0][2];
    return isBoardFull(b) ? 'D' : ' ';
}

// ---- IA (Minimax) ----
int evaluate(const Board &board) {
    char w = checkWinner(board);
    if (w == 'X') return +10;
    if (w == 'O') return -10;
    return 0;
}

int minimax(Board &board, int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10 || score == -10) return score;
    if (isBoardFull(board)) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = ' ';
                }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = ' ';
                }
        return best;
    }
}

pair<int,int> findBestMove(Board &board, char aiPlayer, char humanPlayer) {
    int bestVal = (aiPlayer == 'X') ? INT_MIN : INT_MAX;
    pair<int,int> bestMove = {-1,-1};

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = aiPlayer;
                int moveVal = minimax(board, 0, aiPlayer == 'O' ? false : true);
                board[i][j] = ' ';

                if (aiPlayer == 'X' && moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                } else if (aiPlayer == 'O' && moveVal < bestVal) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

// ---- Entrada segura ----
int getIntInRange(int minv, int maxv) {
    int x;
    while (true) {
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Intenta de nuevo: ";
            continue;
        }
        if (x < minv || x > maxv) {
            cout << "Fuera de rango (" << minv << "-" << maxv << "): ";
            continue;
        }
        break;
    }
    return x;
}

// ---- Juego PvP ----
void playPvP() {
    Board board; initBoard(board);
    char turn = 'X';
    while (true) {
        printBoard(board);
        cout << "Turno de " << turn << " (fila y columna): ";
        int r = getIntInRange(1,3) - 1;
        int c = getIntInRange(1,3) - 1;
        if (!makeMove(board, r, c, turn)) {
            cout << "Movimiento inválido, intenta de nuevo.\n";
            continue;
        }
        char w = checkWinner(board);
        if (w == 'X' || w == 'O') { printBoard(board); cout << "¡Gana " << w << "!\n"; break; }
        if (w == 'D') { printBoard(board); cout << "Empate.\n"; break; }
        turn = (turn == 'X') ? 'O' : 'X';
    }
}

// ---- Juego PvC ----
void playPvC() {
    Board board; initBoard(board);
    cout << "Elige tu ficha: 1) X  2) O: ";
    int ch = getIntInRange(1,2);
    char human = (ch == 1) ? 'X' : 'O';
    char ai = (human == 'X') ? 'O' : 'X';
    char turn = 'X';

    while (true) {
        printBoard(board);
        if (turn == human) {
            cout << "Tu turno (" << human << "). Fila (1-3): ";
            int r = getIntInRange(1,3) - 1;
            cout << "Columna (1-3): ";
            int c = getIntInRange(1,3) - 1;
            if (!makeMove(board, r, c, human)) {
                cout << "Movimiento inválido, intenta de nuevo.\n";
                continue;
            }
        } else {
            cout << "Turno CPU (" << ai << ")...\n";
            pair<int,int> mv = findBestMove(board, ai, human);
            if (mv.first == -1) {
                bool done = false;
                for (int i = 0; i < SIZE && !done; ++i)
                    for (int j = 0; j < SIZE && !done; ++j)
                        if (board[i][j] == ' ') { board[i][j] = ai; done = true; }
            } else board[mv.first][mv.second] = ai;
        }

        char w = checkWinner(board);
        if (w == 'X' || w == 'O') {
            printBoard(board);
            if (w == human) cout << "¡Ganaste!\n"; else cout << "La CPU ganó.\n";
            break;
        } else if (w == 'D') {
            printBoard(board);
            cout << "Empate.\n"; break;
        }
        turn = (turn == 'X') ? 'O' : 'X';
    }
}

// ---- Menú principal ----
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "===== TIC TAC TOE (GATO) =====\n";
        cout << "1) Jugador vs Jugador\n";
        cout << "2) Jugador vs CPU\n";
        cout << "3) Salir\n";
        cout << "Opción: ";
        int op = getIntInRange(1,3);

        if (op == 1) playPvP();
        else if (op == 2) playPvC();
        else break;

        cout << "¿Volver al menú? (s/n): ";
        char again; cin >> again;
        if (again == 'n' || again == 'N') break;
    }

    cout << "Gracias por jugar.\n";
    return 0;
}
