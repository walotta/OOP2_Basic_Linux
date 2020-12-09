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
void wrongHandle(const string &message);

/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         wrongHandle(ex.getMessage());
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
inline void avoidAssign(Expression* exp);
inline void evalExp(Expression* exp,EvalState & state);
inline void AssignVar(Expression* exp,EvalState & state);

void processLine(string line, Program & program, EvalState & state) {
       TokenScanner scanner;
       scanner.ignoreWhitespace();//要求去除空格
       scanner.scanNumbers();//要求寻找数字
       scanner.setInput(line);//制定输入流
       Expression *exp;

       //exp = readE(scanner);
       //cout<<exp->getType()<<endl;
       //value;// = exp->eval(state);
       //cout << value << endl;
       exp=readE(scanner);
       cout<<"[write]"<<exp->toString()<<' '<<exp->getType()<<endl;
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
               exp=readE(scanner);
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   AssignVar(exp,state);
               }
           }else if(exp->toString()=="PRINT")
           {
               //todo
               // avoid mul exp
               exp=readE(scanner);
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens or have =");
               }else
               {
                   evalExp(exp,state);
               }
           }else if(exp->toString()=="RUN")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   //todo
                   // run the program
               }
           }else if(exp->toString()=="INPUT")
           {
               exp=readT(scanner);
               string name=exp->toString();
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else if(exp->getType()!=1)
               {
                   error("assign:not a var");
               }else if(!state.isDefined(name))
               {
                   error("var not defined");
               }else
               {
                   // require a var
                   // wait to check
                   TokenScanner NumberVar;
                   NumberVar.ignoreWhitespace();
                   NumberVar.scanNumbers();
                   NumberVar.setInput(name+"="+getLine(" ? "));
                   exp=readE(NumberVar);
                   if(NumberVar.hasMoreTokens()||exp->getType()!=0)
                   {
                       error("assign number invalid");
                   }
                   //cout<<"[debug]exp :"<<exp->toString()<<endl;
                   exp->eval(state);
               }
           }else if(exp->toString()=="LIST")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   //todo
                   // list all line
               }
           }else if(exp->toString()=="CLEAR")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   //todo
                   // delete a line
               }
           }else if(exp->toString()=="QUIT")
           {if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   exit(0);
               }
           }else if(exp->toString()=="HELP")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   cout<<"Yet another basic interpreter"<<endl;
               }
           }else
           {
               error("no match exp");
           }
       }else if(exp->getType()==2)
       {
           error("can't be a exp");
       }
       if(scanner.hasMoreTokens())
       {
           error("have token left or receive invalid token");
       }
       delete exp;
}

inline void avoidAssign(Expression* exp)
{
    string check;
    check=exp->toString();
    int len=check.length();
    for(int i=0;i<len;i++)
    {
        if(check[i]=='=')error("invalid expression:you assign wrong");
    }
}

inline void evalExp(Expression* exp,EvalState & state)
{
    // avoid var=int(assign)
    //avoidAssign(exp);
    if(((CompoundExp*)(exp))->getOp()=="=")
    {
        error("you assign wrong when eval");
    }
    int value=exp->eval(state);
    cout<<value<<endl;
}

void wrongHandle(const string &message)
{
    //todo
    // wrong handle
    cout<<"[demo]your wrong with: "<<message<<endl;
}

inline void AssignVar(Expression* exp,EvalState & state)
{
    if(((CompoundExp*)(exp))->getOp()!="=")
    {
        error("find no = in assign");
    }else
    {
        exp->eval(state);
    }
}