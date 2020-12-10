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
#include <sstream>
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
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         wzj::wrongHandle(ex.getMessage());
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

       //exp = readE(scanner);
       //cout<<exp->getType()<<endl;
       //value;// = exp->eval(state);
       //cout << value << endl;
       exp=readE(scanner);
       //cout<<"[debug]"<<line<<endl;
       if(exp->getType()==0)
       {
           if(scanner.hasMoreTokens())
           {
               stringstream ss;
               ss<<exp->toString();
               int LineNumber;
               ss>>LineNumber;
               program.addSourceLine(LineNumber,line);
           }else
           {
               stringstream ss;
               ss<<exp->toString();
               int LineNumber;
               ss>>LineNumber;
               program.removeSourceLine(LineNumber);
           }
           delete exp;
           return;
       }else if(exp->getType()==1)
       {
           if(exp->toString()=="LET")
           {
               exp=readE(scanner);
               if(exp->getType()!=2)
               {
                   error("not a assign command");
               }else if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   string name;
                   name=(((CompoundExp*)exp)->getLHS())->toString();
                   wzj::AssignVar(exp,name,state);
               }
           }else if(exp->toString()=="PRINT")
           {
               // avoid mul exp
               exp=readE(scanner);
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens or have =");
               }else
               {
                   wzj::evalExp(exp,state);
               }
           }else if(exp->toString()=="RUN")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   bool run_flag=true;
                   int now_line=program.getFirstLineNumber();
                   if(now_line==-1)run_flag=false;
                   while(run_flag)
                   {
                       try{
                           program.getParsedStatement(now_line)->execute(state);
                       }catch (ErrorException & ex){
                           string wrongMessage=ex.getMessage();
                           stringstream ss_ex;
                           ss_ex<<wrongMessage;
                           string first_word;
                           ss_ex>>first_word;
                           if(first_word=="to_line")
                           {
                               int next_line_number;
                               ss_ex>>next_line_number;
                               if(next_line_number==-1)
                               {
                                   run_flag=false;
                               }else if(program.getParsedStatement(next_line_number)==nullptr)
                               {
                                   error("wrong line number");
                               }else
                               {
                                   now_line=next_line_number;
                                   continue;
                               }
                           }else
                           {
                               error(wrongMessage);
                           }
                       }
                       if(now_line!=program.getEndLineNumber())
                       {
                           now_line=program.getNextLineNumber(now_line);
                       }
                   }
               }
           }else if(exp->toString()=="INPUT")
           {
               exp=readT(scanner);
               string name=exp->toString();
               if(scanner.hasMoreTokens())
               {
                   error("input wrong");
               }else if(exp->getType()!=1)
               {
                   error("input wrong");
               }else
               {
                   // require a var
                   // wait to check
                   bool flag=true;
                   while(flag)
                   {
                       try{
                           flag= false;
                           string NUMBER;
                           NUMBER=getLine(" ? ");
                           int var_number=stringToInteger(NUMBER);
                           state.setValue(name,var_number);
                       }catch(...)
                       {
                           //error("assign number invalid");
                           cout<<"INVALID NUMBER"<<endl;
                           flag=true;
                       }
                   }
               }
           }else if(exp->toString()=="LIST")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   program.printAllLine();
               }
           }else if(exp->toString()=="CLEAR")
           {
               if(scanner.hasMoreTokens())
               {
                   error("too many tokens");
               }else
               {
                   program.clear();
                   state.clear();
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
