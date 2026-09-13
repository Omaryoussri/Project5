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
    vector<std::vector<char>> grid;
    int size;

public:
    Board(int s)
    {
        // TO DO: Implement This Function
    }
    void display() const {
        // TO DO: Implement This Function
    }

    bool makeMove(int row, int col, char symbol){
        // TO DO: Implement This Function
    }

    bool isValidMove(int row, int col) const{
        // TO DO: Implement This Function
    }

    bool check_diagonal(char symbol)
    {
        // TO DO: Implement This Function
    }

    bool check_row(char symbol)
    {
        // TO DO: Implement This Function
    }

    bool check_columns(char symbol)
    {
        // TO DO: Implement This Function
    }

    bool checkWin(char symbol) const {
        for (int i = 0; i < size; ++i) {
            bool rowWin = true, colWin = true;
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] != symbol) rowWin = false;
                if (grid[j][i] != symbol) colWin = false;
            }
            if (rowWin || colWin) return true;
        }

        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; ++i) {
            if (grid[i][i] != symbol) diag1 = false;
            if (grid[i][size - 1 - i] != symbol) diag2 = false;
        }
        return diag1 || diag2;
    }

    bool isFull() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] == ' ') return false;
            }
        }
        return true;
    }

    char getCell(int row, int col) const {
        return grid[row][col];
    }

    void reset() {
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
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getMove(int& row, int& col) override {
        cout << "Enter row and column (0 to 2) separated by a space: ";
        cin >> row >> col;
    }
};
class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;

public:
    Game() : board(3), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {
        showMenu();
        currentPlayer = player1;
    }
    
    ~Game(){ 
        delete player1;
        delete player2;
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
        int choice = 0;
        cout << "===== Tic Tac Toe =====\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer (Easy)\n";
        cout << "3. Player vs Computer (Hard)\n";
        cout << "Enter your choice: ";
        cin >> choice;

    switch (choice) {
        case 1:
            setupPvP();
            break;
        case 2:
            setupPvC(Difficulty::EASY);
            break;
        case 3:
            setupPvC(Difficulty::HARD);
            break;
        default:
            cout << "Invalid choice, defaulting to Player vs Player.\n";
            setupPvP();
            break;
    }
    }

    void setupPvP(){ 
         string name1, name2;
         cout << "Enter name for Player 1 (X): ";
         cin >> name1;
         cout << "Enter name for Player 2 (O): ";
         cin >> name2;

         player1 = new HumanPlayer(name1, 'X');
         player2 = new HumanPlayer(name2, 'O');
    }

    void setupPvC(Difficulty difficulty){ 
        string name1;
        cout << "Enter your name: ";
        cin >> name1;

        player1 = new HumanPlayer(name1, 'X');
        player2 = new AIPlayer("Computer", 'O', difficulty);
    }

    void switchPlayer(){ 
        if(currentPlayer == player1){
            currentPlayer = player2;
        }
        else{
            currentPlayer = player1;
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
