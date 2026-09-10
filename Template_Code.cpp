#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Enum for AI Difficulty levels
enum class Difficulty {
    EASY,
    HARD
};

// 1. Board Class
class Board {
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int s){
        // TO DO: Implement This Function
    }    
    
    void display() const{ 
        // TO DO: Implement This Function
    }

    bool makeMove(int row, int col, char symbol){ 
        // TO DO: Implement This Function
    }

    bool isValidMove(int row, int col) const{
        // TO DO: Implement This Function
    }

    bool checkWin(char symbol) const{
        // TO DO: Implement This Function
    }

    bool isFull() const{
        // TO DO: Implement This Function
    }

    char getCell(int row, int col) const{ 
        // TO DO: Implement This Function
    }

    void reset(){ 
        // TO DO: Implement This Function
    }

    int getSize() const{ 
        // TO DO: Implement This Function
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
    if (difficulty == Difficulty::HARD) {
        
    } else {
        
    }
}
void setDifficulty(Difficulty newDifficulty) {
    difficulty = newDifficulty;
    }
}
    void getRandomMove(const Board& board, int& row, int& col) const {
        // TO DO: Implement This Function
    }
    int minimax(Board& board, int depth, bool isMax, char aiSymbol, char humanSymbol) const {
        if (board.checkWin(aiSymbol)) return 10 - depth;
        if (board.checkWin(humanSymbol)) return depth - 10;
        if (board.isFull()) return 0;

        int size = board.getSize();

        if (isMax) {
            int best = -1000;
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    if (board.isValidMove(r, c)) {
                        board.makeMove(r, c, aiSymbol);
                        best = std::max(best, minimax(board, depth + 1, false, aiSymbol, humanSymbol));
                        board.makeMove(r, c, ' ');
                    }
                }
            }
            return best;
        } else {
            int best = 1000;
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    if (board.isValidMove(r, c)) {
                        board.makeMove(r, c, humanSymbol);
                        best = std::min(best, minimax(board, depth + 1, true, aiSymbol, humanSymbol));
                        board.makeMove(r, c, ' ');
                    }
                }
            }
            return best;
        }
    }
    void getBestMove(Board& board, int& row, int& col) const {
        // TO DO: Implement This Function
        int bestVal = -1000;
    row = -1;
    col = -1;
    char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
    int size = board.getSize();

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board.isValidMove(r, c)) {
                board.makeMove(r, c, symbol);
                int moveVal = minimax(board, 0, false, symbol, opponentSymbol);
                board.makeMove(r, c, ' '); 

                if (moveVal > bestVal) {
                    row = r;
                    col = c;
                    bestVal = moveVal;
                }
            }
        }
    }

    int evaluateBoard(const Board& board) const {
        // TO DO: Implement This Function
        char opponentSymbol = (symbol == 'X') ? 'O' : 'X';

    if (board.checkWin(symbol)) {
        return +10; 
    } else if (board.checkWin(opponentSymbol)) {
        return -10; 
    }
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
        // TO DO: Implement This Function
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
        // TO DO: Implement This Function
    }

    void handleHumanMove(Player* player){
        // TO DO: Implement This Function
    }

    void handleAIMove(AIPlayer* aiPlayer){
        // TO DO: Implement This Function
    }

    bool checkGameEnd(){
        // TO DO: Implement This Function
    }

    void displayResult() const{
        // TO DO: Implement This Function
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