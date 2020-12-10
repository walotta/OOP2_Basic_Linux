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
   program_store.erase(program_store.begin(),program_store.end());
}

void Program::addSourceLine(int lineNumber, string line) {
    program_store.erase(lineNumber);
    program_store.insert(make_pair(lineNumber,data(line)));
}

void Program::removeSourceLine(int lineNumber) {
    program_store.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   if(program_store.count(lineNumber))
   {
       return "not_find";
   }else
   {
       return program_store[lineNumber].command;
   }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   //do nothing
}

Statement *Program::getParsedStatement(int lineNumber) {
    //do nothing
   return NULL;
}

int Program::getFirstLineNumber() {
    if(program_store.empty())
    {
        return -1;
    }
    auto it_store=program_store.begin();
    return it_store->first;
}

int Program::getNextLineNumber(int lineNumber) {
   auto it_store=program_store.find(lineNumber);
   it_store++;
   if(it_store==program_store.end())
   {
       return -1;
   }else
   {
       return it_store->first;
   }
}

Program::data::data(string in_code)
{
    command=in_code;
    string CMD;
    TokenScanner in_scanner;
    in_scanner.ignoreWhitespace();
    in_scanner.scanNumbers();
    in_scanner.setInput(in_code);
    CMD=in_scanner.nextToken();
    if(CMD=="REM")
    {
        cmd_state=new RemState(command);
    }else if(CMD=="PRINT")
    {
        cmd_state=new PrintState(in_scanner);
    }else if(CMD=="INPUT")
    {
        cmd_state=new InputState(in_scanner);
    }else if(CMD=="END")
    {
        if(in_scanner.hasMoreTokens())
        {
            error("wrong end cmd");
        }
        cmd_state=new EndState();
    }else if(CMD=="GOTO")
    {
        cmd_state=new GotoState(in_scanner);
    }else if(CMD=="IF")
    {
        string if_in=in_code;
        wzj::DeleteWhite(if_in);
        if_in.erase(0,2);
        cmd_state=new IfState(if_in);
    }else if(CMD=="LET")
    {
        cmd_state=new LetState(in_scanner);
    }else
    {
        error("not fit cmd");
    }
}

Program::data::~data()
{
    delete cmd_state;
}
