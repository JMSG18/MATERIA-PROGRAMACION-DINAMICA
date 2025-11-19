#include <iostream>
#include <vector>
#include <limits>
#include <windows.h> // Para colores y beep
using namespace std;

const int BOARD_SIZE = 3;

// Cambiar color de texto
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Mostrar tabla de colores
void showColorTable() {
    cout << "Colores de consola disponibles (número):\n";
    for(int i=0;i<=15;i++){
        setColor(i);
        cout << i << " ";
        if(i%8==7) cout << "\n";
    }
    setColor(7);
    cout << "\n";
}

// Inicializar tablero
void initBoard(vector<vector<char>>& board) {
    board.assign(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
}

// Imprimir tablero
void printBoard(const vector<vector<char>>& board, char p1Char, char p2Char, int p1Color, int p2Color) {
    system("cls");
    cout << "\n    1   2   3\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << " " << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == p1Char) setColor(p1Color);
            else if (board[i][j] == p2Char) setColor(p2Color);
            else setColor(7); // color normal
            cout << " " << board[i][j] << " ";
            setColor(7);
            if(j<BOARD_SIZE-1) cout << "|";
        }
        cout << "\n";
        if(i<BOARD_SIZE-1) cout << "   ---+---+---\n";
    }
    cout << "\n";
}

// Validar movimiento
bool isValidMove(const vector<vector<char>>& board, int row, int col) {
    return row >=0 && row < BOARD_SIZE && col >=0 && col < BOARD_SIZE && board[row][col]==' ';
}

// Colocar ficha
bool makeMove(vector<vector<char>>& board, int row, int col, char symbol) {
    if(!isValidMove(board,row,col)) return false;
    board[row][col] = symbol;
    Beep(750,100);
    return true;
}

// Comprobar tablero lleno
bool isBoardFull(const vector<vector<char>>& board){
    for(auto &r:board)
        for(auto c:r)
            if(c==' ') return false;
    return true;
}

// Comprobar ganador
char checkWinner(const vector<vector<char>>& board){
    for(int i=0;i<BOARD_SIZE;i++){
        if(board[i][0]!=' ' && board[i][0]==board[i][1] && board[i][1]==board[i][2]) return board[i][0];
        if(board[0][i]!=' ' && board[0][i]==board[1][i] && board[1][i]==board[2][i]) return board[0][i];
    }
    if(board[0][0]!=' ' && board[0][0]==board[1][1] && board[1][1]==board[2][2]) return board[0][0];
    if(board[0][2]!=' ' && board[0][2]==board[1][1] && board[1][1]==board[2][0]) return board[0][2];
    if(isBoardFull(board)) return 'D';
    return ' ';
}

// Entrada segura
int getIntInRange(int minv, int maxv){
    int x;
    while(true){
        if(!(cin>>x)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Entrada inválida, intenta de nuevo: ";
            continue;
        }
        if(x<minv || x>maxv){
            cout << "Fuera de rango ("<<minv<<"-"<<maxv<<"): ";
            continue;
        }
        break;
    }
    return x;
}

// Juego PvP
void playPvP(){
    vector<vector<char>> board;
    initBoard(board);

    cout << "=== Jugador vs Jugador ===\n";
    showColorTable();
    
    char p1Char, p2Char;
    int p1Color, p2Color;

    // Elegir ficha
    cout << "Jugador 1, elige tu ficha: ";
    cin >> p1Char; p1Char = toupper(p1Char);
    cout << "Jugador 2, elige tu ficha diferente: ";
    while(true){
        cin >> p2Char; p2Char = toupper(p2Char);
        if(p2Char!=p1Char) break;
        cout << "Debe ser diferente a Jugador 1: ";
    }

    // Elegir color
    cout << "Jugador 1, elige color: "; p1Color = getIntInRange(1,15);
    cout << "Jugador 2, elige color: "; 
    while(true){
        p2Color = getIntInRange(1,15);
        if(p2Color!=p1Color) break;
        cout << "Debe ser diferente a Jugador 1: ";
    }

    char turn = p1Char;
    while(true){
        printBoard(board,p1Char,p2Char,p1Color,p2Color);
        cout << "Turno de " << turn << " (fila columna): ";
        int r=getIntInRange(1,3)-1, c=getIntInRange(1,3)-1;
        if(!makeMove(board,r,c,turn)){ cout<<"Movimiento inválido.\n"; continue; }
        char w = checkWinner(board);
        if(w==p1Char||w==p2Char){ printBoard(board,p1Char,p2Char,p1Color,p2Color); cout<<"¡Gana "<<w<<"!\n"; break; }
        if(w=='D'){ printBoard(board,p1Char,p2Char,p1Color,p2Color); cout<<"Empate.\n"; break; }
        turn = (turn==p1Char)?p2Char:p1Char;
    }
}

// IA sencilla
pair<int,int> aiMove(const vector<vector<char>>& board){
    for(int i=0;i<BOARD_SIZE;i++)
        for(int j=0;j<BOARD_SIZE;j++)
            if(board[i][j]==' ') return {i,j};
    return {-1,-1};
}

// Juego PvC
void playPvC(){
    vector<vector<char>> board;
    initBoard(board);

    cout << "=== Jugador vs CPU ===\n";
    showColorTable();

    char human, ai; int humanColor, aiColor;
    cout << "Elige tu ficha: "; cin >> human; human = toupper(human);
    ai = (human=='X')?'O':'X';
    cout << "Elige tu color: "; humanColor = getIntInRange(1,15);
    aiColor = (humanColor==15)?14:15;

    char turn = 'X';
    while(true){
        printBoard(board,human,ai,humanColor,aiColor);
        if(turn==human){
            cout << "Tu turno (fila columna): ";
            int r=getIntInRange(1,3)-1, c=getIntInRange(1,3)-1;
            if(!makeMove(board,r,c,human)){ cout<<"Movimiento inválido.\n"; continue; }
        } else {
            cout << "Turno CPU...\n";
            pair<int,int> m = aiMove(board);
            if(m.first!=-1) makeMove(board,m.first,m.second,ai);
        }
        char w = checkWinner(board);
        if(w==human){ printBoard(board,human,ai,humanColor,aiColor); cout<<"¡Ganaste!\n"; break; }
        if(w==ai){ printBoard(board,human,ai,humanColor,aiColor); cout<<"La CPU ganó.\n"; break; }
        if(w=='D'){ printBoard(board,human,ai,humanColor,aiColor); cout<<"Empate.\n"; break; }
        turn = (turn=='X')?'O':'X';
    }
}

int main(){
    while(true){
        cout << "===== TIC TAC TOE =====\n";
        cout << "1) Jugador vs Jugador\n";
        cout << "2) Jugador vs CPU\n";
        cout << "3) Salir\n";
        cout << "Opción: ";
        int op = getIntInRange(1,3);
        if(op==1) playPvP();
        else if(op==2) playPvC();
        else break;
        cout << "¿Volver al menú? (s/n): ";
        char again; cin >> again;
        if(again=='n'||again=='N') break;
    }
    cout << "Gracias por jugar.\n";
    return 0;
}
