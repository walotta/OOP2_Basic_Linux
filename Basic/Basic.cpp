/*
 * File: Basic.cpp
 * ---------------
 * Name: [walotta]
 * Section: B
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 *
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

//state 用于变量储存
//program 用于储存程序
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();//要求去除空格
   scanner.scanNumbers();//要求寻找数字
   scanner.setInput(line);//制定输入流
   Expression *exp;
   // cout<<exp->getType()<<endl;
   //int value;// = exp->eval(state);
   //cout << value << endl;

    //exp = readE(scanner);
    //cout<<exp->getType()<<endl;
    //value;// = exp->eval(state);
    //cout << value << endl;
    exp=readE(scanner);
    cout<<exp->toString()<<' '<<exp->getType()<<endl;
    if(exp->getType()==0)
    {
        if(scanner.hasMoreTokens())
        {
            //todo
            // add a new line
        }else
        {
            //todo
            // delete a line
        }
    }else if(exp->getType()==1)
    {
        if(exp->toString()=="LET")
        {

        }else if(exp->toString()=="IF")
        {

        }else if(exp->toString()=="PRINT")
        {

        }else if(exp->toString()=="GOTO")
        {

        }else if(exp->toString()=="REM")
        {

        }else if(exp->toString()=="END")
        {

        }else if(exp->toString()=="RUN")
        {

        }else if(exp->toString()=="INPUT")
        {

        }else if(exp->toString()=="LIST")
        {

        }else if(exp->toString()=="CLEAR")
        {

        }else if(exp->toString()=="QUIT")
        {
            exit(0);
        }else if(exp->toString()=="HELP")
        {

        }
    }else if(exp->getType()==2)
    {
        int value=exp->eval(state);
        cout<<value<<endl;
    }
   delete exp;
}
