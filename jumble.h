#pragma once
#ifndef JUMBLE_H
#define JUMBLE_H

#include <string>
#include <exception>

// Type definition for a pointer to an array of chars
typedef char* charArrayPtr;

class BadJumbleException : public std::exception {
public:
    BadJumbleException(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};

class JumblePuzzle {
public:
    // Constructor
    JumblePuzzle(const std::string& toHide, const std::string& difficulty);

    JumblePuzzle(const JumblePuzzle& jp);

    // Assignment Operator Overload
    JumblePuzzle& operator=(const JumblePuzzle& jp);

    // Destructor
    ~JumblePuzzle();

    // Accessors
    charArrayPtr* getJumble() const;
    int getSize() const;
    int getRowPos() const;
    int getColPos() const;
    char getDirection() const;

private:
    charArrayPtr* jumble;
    int size;             
    int rowPos;           
    int colPos;            
    char direction; // ('n', 'e', 's', 'w')

    // Helper function to check if a string is all lowercase letters
    bool isLowerCase(const std::string& str) const;

    // Helper function to generate the puzzle
    void generatePuzzle(const std::string& toHide);
};

#endif // JUMBLE_H
