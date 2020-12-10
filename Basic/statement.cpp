/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include <cstring>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
#include <sstream>
using namespace std;

/* Implementation of the Statement class */


Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

PrintState::PrintState(TokenScanner &scanner)
{
    Exp=readE(scanner);
    if(scanner.hasMoreTokens())
    {
        error("too many tokens or have =");
    }else if(((CompoundExp*)(Exp))->getOp()=="=")
    {
        error("you assign wrong when eval");
    }
}

PrintState::~PrintState()
{
    delete Exp;
}

void PrintState::execute(EvalState &state)
{
    wzj::evalExp(Exp,state);
}

InputState::InputState(TokenScanner &scanner)
{
    Exp=readT(scanner);
    name=Exp->toString();
    if(scanner.hasMoreTokens())
    {
        error("input wrong");
    }else if(Exp->getType()!=1)
    {
        error("input wrong");
    }
}

InputState::~InputState()
{
    delete Exp;
}

void InputState::execute(EvalState &state)
{
    TokenScanner NumberVar;
    NumberVar.ignoreWhitespace();
    NumberVar.scanNumbers();

    bool flag=true;
    while(flag)
    {
        try{
            flag= false;
            string NUMBER;
            NUMBER=getLine(" ? ");
            NumberVar.setInput(NUMBER);
            while (NumberVar.hasMoreTokens())
            {
                Exp=readT(NumberVar);
                if(Exp->getType()==1)
                    error("input wrong");
            }
            NumberVar.setInput(name+"="+NUMBER);
            Exp=readE(NumberVar);
            //cout<<"[debug]exp: "<<exp->toString()<<endl;
            if(NumberVar.hasMoreTokens()||Exp->getType()!=2)
            {
                error("input wrong");
            }
            //cout<<"[debug]exp :"<<exp->toString()<<endl;
            Exp->eval(state);
        }catch(...)
        {
            //error("assign number invalid");
            cout<<"INVALID NUMBER"<<endl;
            flag=true;
        }
    }
}

EndState::EndState()
{
    //empty
}

EndState::~EndState()
{
    //empty
}

void EndState::execute(EvalState &state)
{
    error("to_line -1");
}


GotoState::GotoState(TokenScanner &scanner)
{
    Expression* tem_exp;
    tem_exp=readE(scanner);
    if(scanner.hasMoreTokens())
    {
        error("line_number input error");
    }
    if(tem_exp->getType()!=0)
    {
        error("line_number input error");
    }
    line_number=tem_exp->getType();
    delete tem_exp;
}

GotoState::~GotoState()
{
    //empty
}

void GotoState::execute(EvalState &state)
{
    error("to_line "+line_number);
}

IfState::IfState(string x)
{
    int x_len=x.length();
    int op_position;
    bool op_flag=false;
    for(int i=0;i<x_len;i++)
    {
        if(x[i]=='='||x[i]=='<'||x[i]=='>')
        {
            if(op_flag)
            {
                error("invalid if exp");
            }
            op_position=i;
            op_flag=true;
        }

    }
    Operator=x[op_position];
    string left_string;
    string right_string;
    left_string=x.substr(0,op_position);
    right_string=x.substr(op_position+1,x_len);
    TokenScanner tem;
    tem.ignoreWhitespace();
    tem.scanNumbers();
    tem.setInput(left_string);
    left=readE(tem);
    tem.setInput(right_string);
    right=readE(tem);
    if(tem.nextToken()!="THEN")
    {
        error("find no THEN");
    }
    Expression* tem_exp;
    tem_exp=readT(tem);
    if(tem.hasMoreTokens())
    {
        error("if invalid");
    }
    if(tem_exp->getType()!=0)
    {
        error("after then not a number");
    }
    line_number=tem_exp->toString();
    delete tem_exp;
}

IfState::~IfState()
{
    delete left;
    delete right;
}

void IfState::execute(EvalState &state)
{
    const int left_val=left->eval(state);
    const int right_val=right->eval(state);
    if(Operator=='<')
    {
        if(left_val<right_val)error("to_line "+line_number);
    }else if(Operator=='=')
    {
        if(left_val==right_val)error("to_line "+line_number);
    }else if(Operator=='>')
    {
        if(left_val>right_val)error("to_line "+line_number);
    }
}

RemState::RemState(string x)
{
    store=x;
}

void RemState::execute(EvalState &state)
{
    //do nothing
    //cout<<store<<endl;
}

RemState::~RemState()
{
    //empty
}

LetState::LetState(TokenScanner &scanner)
{
    Exp=readE(scanner);
    if(Exp->getType()!=2)
    {
        error("not a assign command");
    }else if(scanner.hasMoreTokens())
    {
        error("too many tokens");
    }
    name=(((CompoundExp*)Exp)->getLHS())->toString();
    if(((CompoundExp*)(Exp))->getOp()!="=")
    {
        error("find no = in assign");
    }
    if(wzj::VarNameCheck(name))
    {
        error("var name invalid");
    }
}

LetState::~LetState()
{
    delete Exp;
}

void LetState::execute(EvalState &state)
{
    wzj::AssignVar(Exp,name,state);
}

void wzj::wrongHandle(const string &message)
{
    //cout<<"[demo]your wrong with: "<<message<<endl;
    if(message=="divide with 0")
    {
        cout<<"DIVIDE BY ZERO"<<endl;
    }else if(message=="input wrong")
    {
        cout<<"INVALID NUMBER"<<endl;
    }else if(message=="var is undefined")
    {
        cout<<"VARIABLE NOT DEFINED"<<endl;
    }else if(message=="wrong line number")
    {
        cout<<"LINE NUMBER ERROR"<<endl;
    }else
    {
        cout<<"SYNTAX ERROR"<<endl;
    }
}

void wzj::evalExp(Expression* exp,EvalState & state)
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

void wzj::AssignVar(Expression* exp,const string &name,EvalState & state)
{
    if(((CompoundExp*)(exp))->getOp()!="=")
    {
        error("find no = in assign");
    }else
    {
        //cout<<"[debug]name: "<<name<<endl;
        if(VarNameCheck(name))
        {
            error("var name invalid");
        }
        exp->eval(state);
    }
}

bool wzj::VarNameCheck(const string &name)
{
    for(int i=0;i<13;i++)
    {
        if(name==key_word[i])return true;
    }
    return false;
}

void wzj::DeleteWhite(string &x)
{
    while(x.length()!=0)
    {
        if(x[0]==' ')
        {
            x.erase(0,1);
        }else
        {
            return;
        }
    }
}
