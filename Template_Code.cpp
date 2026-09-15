#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
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
    Board(int size = 3) {
        this->size = size;
        grid.resize(size, vector<char>(size, ' '));
    }

    void display() const {
        cout << "\n    ";
        for (int j = 0; j < size; ++j) {
            cout << j << "   ";
        }
        cout << "\n  ";
        for (int j = 0; j < size; ++j) {
            cout << "----";
        }
        cout << "-\n";

        for (int i = 0; i < size; ++i) {
            cout << i << " |";
            for (int j = 0; j < size; ++j) {
                cout << " " << (grid[i][j] == ' ' ? '.' : grid[i][j]) << " |";
            }
            cout << "\n  ";
            for (int j = 0; j < size; ++j) {
                cout << "----";
            }
            cout << "-\n";
        }
        cout << "\n";
    }

    bool makeMove(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    bool isValidMove(int row, int col) const {
        return (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ');
    }

    bool check_diagonal(char symbol) const {
        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; ++i) {
            if (grid[i][i] != symbol) diag1 = false;
            if (grid[i][size - 1 - i] != symbol) diag2 = false;
        }
        return diag1 || diag2;
    }

    bool check_row(char symbol) const {
        for (int i = 0; i < size; ++i) {
            bool rowWin = true;
            for (int j = 0; j < size; ++j) {
                if (grid[i][j] != symbol) {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) return true;
        }
        return false;
    }

    bool check_columns(char symbol) const {
        for (int j = 0; j < size; ++j) {
            bool colWin = true;
            for (int i = 0; i < size; ++i) {
                if (grid[i][j] != symbol) {
                    colWin = false;
                    break;
                }
            }
            if (colWin) return true;
        }
        return false;
    }

    bool checkWin(char symbol) const {
        return check_row(symbol) || check_columns(symbol) || check_diagonal(symbol);
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
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                grid[i][j] = ' ';
            }
        }
    }

    int getSize() const {
        return size;
    }
};

// 2. Player Class (Abstract)
class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    virtual void getMove(int& row, int& col) = 0;

    string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    void setName(const string& name) {
        this->name = name;
    }
    
    virtual ~Player() {}
};

// 3. AIPlayer Class (Derived from Player)
class AIPlayer : public Player {
private:
    Difficulty difficulty;

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty) : Player(name, symbol) {
        this->difficulty = difficulty;
    }
    void getMove(int& row, int& col) override {
    }

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    Difficulty getDifficulty() const {
        return difficulty;
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        int size = board.getSize();
        do {
            row = rand() % size;
            col = rand() % size;
        } while (!board.isValidMove(row, col));
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

// 4. HumanPlayer Class
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getMove(int& row, int& col) override {
        cout << "Enter row and column (0 to 2) separated by a space: ";
        cin >> row >> col;
    }
};

// 5. Game Class
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

    ~Game() {
        delete player1;
        delete player2;
    }

    void start() {
        board.display();
        while (true) {
            AIPlayer* ai = dynamic_cast<AIPlayer*>(currentPlayer);
            if (ai != nullptr) {
                handleAIMove(ai);
            } else {
                handleHumanMove(currentPlayer);
            }

            board.display();

            if (checkGameEnd()) {
                displayResult();
                break;
            }

            switchPlayer();
        }
    }

    void showMenu() {
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

    void setupPvP() {
        string name1, name2;
        cout << "Enter name for Player 1 (X): ";
        cin >> name1;
        cout << "Enter name for Player 2 (O): ";
        cin >> name2;

        player1 = new HumanPlayer(name1, 'X');
        player2 = new HumanPlayer(name2, 'O');
    }

    void setupPvC(Difficulty difficulty) {
        string name1;
        cout << "Enter your name: ";
        cin >> name1;

        player1 = new HumanPlayer(name1, 'X');
        player2 = new AIPlayer("Computer", 'O', difficulty);
    }

    void switchPlayer() {
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    void handleHumanMove(Player* player) {
        int row, col;
        cout << player->getName() << "'s turn (" << player->getSymbol() << ")\n";
        player->getMove(row, col);
        while (!board.isValidMove(row, col)) {
            cout << "Invalid move! Try again: ";
            player->getMove(row, col);
        }
        board.makeMove(row, col, player->getSymbol());
    }

    void handleAIMove(AIPlayer* aiPlayer) {
        int row, col;
        cout << aiPlayer->getName() << " (AI) is thinking...\n";
        
        if (aiPlayer->getDifficulty() == Difficulty::EASY) {
            aiPlayer->getRandomMove(board, row, col);
        } else {
            aiPlayer->getBestMove(board, row, col);
        }

        board.makeMove(row, col, aiPlayer->getSymbol());
        cout << "AI played at: " << row << ", " << col << "\n";
    }

    bool checkGameEnd() {
        if (board.checkWin(player1->getSymbol()) || board.checkWin(player2->getSymbol())) {
            return true;
        }
        if (board.isFull()) {
            return true;
        }
        return false;
    }

    void displayResult() const {
        if (board.checkWin(player1->getSymbol())) {
            cout << "Congratulations! " << player1->getName() << " wins!\n";
        } else if (board.checkWin(player2->getSymbol())) {
            cout << "Congratulations! " << player2->getName() << " wins!\n";
        } else {
            cout << "It's a draw!\n";
        }
    }

    void reset() {
        board.reset();
        currentPlayer = player1;
    }
};

// ==========================================
// Main Function
// ==========================================
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Game myGame;
    myGame.start();

    return 0;
}