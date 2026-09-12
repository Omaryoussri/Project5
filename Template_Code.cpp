#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define TOP_LEFT_EDGE_ROW 0
#define TOP_LEFT_EDGE_COLUMN 0

#define BOTTOM_LEFT_EDGE_ROW 2
#define BOTTOM_LEFT_EDGE_COLUMN 0

#define BOTTOM_RIGHT_EDGE 2

#define TOP_RIGHT_EDGE_COLUMN 2
#define TOP_RIGHT_EDGE_ROW 0

#define CENTER 1

#define FIRST 0
#define SECOND 1
#define THIRD 2

#define GRID_SIZE 3

// Enum for AI Difficulty levels
enum class Difficulty {
    EASY,
    HARD
};

// 1. Board Class
class Board {
private:
    static std::vector<std::vector<char>> grid;
    int size;

public:
    Board(int s)
    {

    }
    void display() const {

    }

    bool makeMove(int row, int col, char symbol){

    }

    bool isValidMove(int row, int col) const{

    }

    static bool check_diagonal(char symbol)
    {
        return (grid[TOP_LEFT_EDGE_COLUMN][TOP_LEFT_EDGE_ROW]       == grid[CENTER][CENTER] == grid[BOTTOM_RIGHT_EDGE][BOTTOM_RIGHT_EDGE] == symbol)
            || (grid[BOTTOM_LEFT_EDGE_COLUMN][BOTTOM_LEFT_EDGE_ROW] == grid[CENTER][CENTER] == grid[TOP_RIGHT_EDGE_COLUMN][TOP_RIGHT_EDGE_ROW] == symbol);
    }

    static bool check_row(char symbol)
    {
        return (grid[FIRST][FIRST]  == grid[SECOND][FIRST]  == grid[THIRD][FIRST] == symbol)
            || (grid[FIRST][SECOND] == grid[SECOND][SECOND] == grid[THIRD][SECOND] == symbol)
            || (grid[FIRST][THIRD]  == grid[SECOND][THIRD]  == grid[THIRD][THIRD] == symbol);
    }

    static bool check_columns(char symbol)
    {
        return (grid[FIRST][FIRST]  == grid[FIRST][SECOND]   == grid[FIRST][THIRD] == symbol)
            || (grid[SECOND][FIRST] == grid[SECOND][SECOND]  == grid[SECOND][THIRD] == symbol)
            || (grid[THIRD][FIRST]  == grid[THIRD][SECOND]   == grid[THIRD][THIRD] == symbol);
    }

    bool checkWin(char symbol) const{
        return check_columns(symbol)
            || check_row(symbol)
            || check_diagonal(symbol);
    }

    bool isFull() const {
        return (grid[SECOND][FIRST]  != ' ' && grid[SECOND][FIRST + 1]  != ' ' && grid[SECOND][FIRST - 1]  != ' ')
            && (grid[SECOND][SECOND] != ' ' && grid[SECOND][SECOND + 1] != ' ' && grid[SECOND][SECOND - 1] != ' ')
            && (grid[SECOND][THIRD]  != ' ' && grid[SECOND][THIRD + 1]  != ' ' && grid[SECOND][THIRD - 1]  != ' ');
    }

    char getCell(int row, int col) const {
        return grid[col][row];
    }

    static void reset() {
    }

    int getSize() const{

    }
};

// 2. Player Class (Abstract)
class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol){ 
        // TO DO: Implement This Function
    }

    virtual void getMove(int& row, int& col) = 0;

    string getName() const{ 
        // TO DO: Implement This Function
    }    
    
    char getSymbol() const{ 
        // TO DO: Implement This Function
    }    
    
    void setName(const string& name){
        // TO DO: Implement This Function
    }    
};

// 3. AIPlayer Class (Derived from Player)
class AIPlayer : public Player {
private:
    Difficulty difficulty;

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty) : Player(name, symbol) {
        this->difficulty = difficulty;
        // TO DO: Implement This Function
    }
    void getMove(int& row, int& col) override {

    }

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        // TO DO: Implement This Function
    }


    int minimax(const Board& board, int depth, bool isMax, char aiSymbol, char humanSymbol) const {
    int score = evaluateBoard(board);

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (board.isFull()) return 0;

    int size = board.getSize();

    if (isMax) {
        int best = -1000;
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board.isValidMove(r, c)) {
                    Board tempBoard = board; 
                    tempBoard.makeMove(r, c, aiSymbol);
                    best = std::max(best, minimax(tempBoard, depth + 1, false, aiSymbol, humanSymbol));
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board.isValidMove(r, c)) {
                    Board tempBoard = board; 
                    tempBoard.makeMove(r, c, humanSymbol);
                    best = std::min(best, minimax(tempBoard, depth + 1, true, aiSymbol, humanSymbol));
                }
            }
        }
        return best;
    }
}

    void getBestMove(const Board& board, int& row, int& col) const {
    int bestVal = -1000;
    row = -1;
    col = -1;
    char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    int size = board.getSize();

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board.isValidMove(r, c)) {
                Board tempBoard = board; 
                tempBoard.makeMove(r, c, symbol);
                int moveVal = minimax(tempBoard, 0, false, symbol, opponentSymbol);

                if (moveVal > bestVal) {
                    row = r;
                    col = c;
                    bestVal = moveVal;
                }
            }
        }
    }
}

    int evaluateBoard(const Board& board) const {
        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
        if (board.checkWin(symbol)) return 10;
        if (board.checkWin(opponentSymbol)) return -10;
        return 0;
    }    
};

// 4. Game Class
class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;

public:
    Game() : board(3), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {
    // TO DO: Implement This Function
    }
    
    ~Game(){ 
        // TO DO: Implement This Function
    }

    void start(){
        board.display();
        while(true){
            AIPlayer* ai = dynamic_cast<AIPlayer*>(currentPlayer);
            if(ai != nullptr){
                handleAIMove(ai);
            }
            else{
                handleHumanMove(currentPlayer);
            }

            board.display();

            if(checkGameEnd()){
                displayResult();
                break;
            }
            switchPlayer();
        }
    }

    void showMenu(){ 
        // TO DO: Implement This Function
    }

    void setupPvP(){ 
        // TO DO: Implement This Function
    }

    void setupPvC(Difficulty difficulty){ 
        // TO DO: Implement This Function
    }

    void switchPlayer(){ 
        if(currentPlayer == player1){
            currentPlayer = player2;
        }
        else{
            currentPlayer == player1;
        }
    }

    void handleHumanMove(Player* player){
        int row , col;
        cout << player->getName() << "'s turn (" << player->getSymbol() << ")\n";
        player->getMove(row,col);
        while (!board.isValidMove(row , col))
        {
            cout << "Invalid move! Try again: ";
            player->getMove(row, col);
        }
        board.makeMove(row, col, player->getSymbol());
        
    }

    void handleAIMove(AIPlayer* aiPlayer){
        int row, col;
        cout << aiPlayer->getName() <<" (AI) is thinking...\n";
        aiPlayer->getBestMove(board, row, col);
        board.makeMove(row, col, aiPlayer->getSymbol());
        cout << "AI played at: " << row << ", " << col << "\n";
    }

    bool checkGameEnd(){
        if(board.checkWin(player1->getSymbol()) || board.checkWin(player2->getSymbol())){
            return true;
        }
        if(board.isFull()){
            return true;
        }
        return false;
    }

    void displayResult() const{
        if(board.checkWin(player1->getSymbol())){
            cout << "Congratulations! " << player1->getName() << " wins!\n";
        }
        else if(board.checkWin(player2->getSymbol())){
           cout << "Congratulations! " << player2->getName() << " wins!\n"; 
        }
        else{
            cout << "It's a draw!\n";
        }
    }

    void reset() {
        // TO DO: Implement This Function
    }    
};

// ==========================================
// Main Function
// ==========================================
int main() {
    // Game myGame;
    // myGame.start();
    
    return 0;
}