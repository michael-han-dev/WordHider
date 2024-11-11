#include "jumble.h"
#include <cstdlib> 
#include <ctime>   
#include <iostream> 
#include <cctype>

using namespace std;

// BadJumbleException implementation

BadJumbleException::BadJumbleException(const string& message) : message(message) {}

const char* BadJumbleException::what() const noexcept {
    return message.c_str();
}

// JumblePuzzle implementation

// Helper function to check if a string is all lowercase letters
bool JumblePuzzle::isLowerCase(const std::string& str) const {
    for (char c : str) {
        if (!islower(c)) {
            return false;
        }
    }
    return true;
}

// Constructor
JumblePuzzle::JumblePuzzle(const std::string& toHide, const std::string& difficulty) {
    // Check word length
    if (toHide.length() < 3 || toHide.length() > 10) {
        throw BadJumbleException("Word length must be between 3 and 10 characters.");
    }
    // Check that the word is all lower case letters
    if (!isLowerCase(toHide)) {
        throw BadJumbleException("Word must be all lower case letters.");
    }
    // Set size based on difficulty
    int multiplier;
    if (difficulty == "easy") {
        multiplier = 2;
    } else if (difficulty == "medium") {
        multiplier = 3;
    } else if (difficulty == "hard") {
        multiplier = 4;
    } else {
        throw BadJumbleException("Invalid difficulty. Choose from \"easy\", \"medium\", or \"hard\".");
    }
    size = toHide.length() * multiplier;
    // Initialize the 2D array
    jumble = new charArrayPtr[size];
    for (int i = 0; i < size; ++i) {
        jumble[i] = new char[size];
    }
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    // Generate the puzzle
    generatePuzzle(toHide);
}

// Helper function to generate the puzzle
void JumblePuzzle::generatePuzzle(const std::string& toHide) {
    // Fill the array with random lower case letters
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            jumble[i][j] = 'a' + rand() % 26;
        }
    }
    // Now, hide the word in the puzzle
    bool placed = false;
    int wordLen = toHide.length();
    string directions = "nesw";
    while (!placed) {
        // Generate random starting position
        rowPos = rand() % size;
        colPos = rand() % size;
        // Choose random direction
        direction = directions[rand() % 4];
        // Check if the word fits in the chosen direction
        if (direction == 'n') {
            if (rowPos - wordLen + 1 >= 0) {
                // Place the word going north
                for (int i = 0; i < wordLen; ++i) {
                    jumble[rowPos - i][colPos] = toHide[i];
                }
                placed = true;
            }
        } else if (direction == 'e') {
            if (colPos + wordLen <= size) {
                // Place the word going east
                for (int i = 0; i < wordLen; ++i) {
                    jumble[rowPos][colPos + i] = toHide[i];
                }
                placed = true;
            }
        } else if (direction == 's') {
            if (rowPos + wordLen <= size) {
                // Place the word going south
                for (int i = 0; i < wordLen; ++i) {
                    jumble[rowPos + i][colPos] = toHide[i];
                }
                placed = true;
            }
        } else if (direction == 'w') {
            if (colPos - wordLen + 1 >= 0) {
                // Place the word going west
                for (int i = 0; i < wordLen; ++i) {
                    jumble[rowPos][colPos - i] = toHide[i];
                }
                placed = true;
            }
        }
        // If not placed, the loop continues
    }
}

// Copy Constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
    size = jp.size;
    rowPos = jp.rowPos;
    colPos = jp.colPos;
    direction = jp.direction;
    // Allocate new 2D array
    jumble = new charArrayPtr[size];
    for (int i = 0; i < size; ++i) {
        jumble[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            jumble[i][j] = jp.jumble[i][j];
        }
    }
}

// Assignment Operator Overload
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp) {
    if (this != &jp) {
        // Deallocate existing memory
        for (int i = 0; i < size; ++i) {
            delete[] jumble[i];
        }
        delete[] jumble;
        // Copy data members
        size = jp.size;
        rowPos = jp.rowPos;
        colPos = jp.colPos;
        direction = jp.direction;
        // Allocate new memory
        jumble = new charArrayPtr[size];
        for (int i = 0; i < size; ++i) {
            jumble[i] = new char[size];
            for (int j = 0; j < size; ++j) {
                jumble[i][j] = jp.jumble[i][j];
            }
        }
    }
    return *this;
}

// Destructor
JumblePuzzle::~JumblePuzzle() {
    for (int i = 0; i < size; ++i) {
        delete[] jumble[i];
    }
    delete[] jumble;
}

// Accessors

// Returns a deep copy of the jumble puzzle
charArrayPtr* JumblePuzzle::getJumble() const {
    charArrayPtr* copyJumble = new charArrayPtr[size];
    for (int i = 0; i < size; ++i) {
        copyJumble[i] = new char[size];
        for (int j = 0; j < size; ++j) {
            copyJumble[i][j] = jumble[i][j];
        }
    }
    return copyJumble;
}

int JumblePuzzle::getSize() const {
    return size;
}

int JumblePuzzle::getRowPos() const {
    return rowPos;
}

int JumblePuzzle::getColPos() const {
    return colPos;
}

char JumblePuzzle::getDirection() const {
    return direction;
}
