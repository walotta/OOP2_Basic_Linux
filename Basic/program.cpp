/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   //empty
}

Program::~Program() {
   //empty
}

void Program::clear() {
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
   return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
   return 0;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
   return 0;     // Replace this stub with your own code
}

Program::data::data(TokenScanner in_code)
{
    string CMD;
    CMD=in_code.nextToken();
    if(CMD=="REM")
    {

    }else if(CMD=="PRINT")
    {

    }else if(CMD=="INPUT")
    {

    }else if(CMD=="END")
    {

    }else if(CMD=="GOTO")
    {

    }else if(CMD=="IF")
    {

    }else if(CMD=="LET")
    {

    }else
    {
        error("not fit cmd");
    }
}

Program::data::~data()
{

}
