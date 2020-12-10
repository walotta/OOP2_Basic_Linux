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
    //program_store.insert(make_pair(lineNumber,data{line}));
    program_store[lineNumber]=data(line);
}

void Program::removeSourceLine(int lineNumber) {
    program_store.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
   if(program_store.count(lineNumber)==0)
   {
       return "not_find";
   }else
   {
       return (program_store.find(lineNumber)->second).command;
   }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   //do nothing
}

Statement *Program::getParsedStatement(int lineNumber) {
    if(program_store.count(lineNumber)==0)
    {
        return nullptr;
    }else
    {
        return program_store[lineNumber].cmd_state;
    }
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

void Program::printAllLine()
{
    if(program_store.empty())
    {
        return;
    }else
    {
        //遍历出错？
        for(auto &it:program_store)
        {
            cout<<(it.second).command<<endl;
        }
    }
    return;
}

int Program::getEndLineNumber()
{
    auto it=program_store.end();
    it--;
    return it->first;
}

