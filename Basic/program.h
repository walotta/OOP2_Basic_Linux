/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include <map>
#include "statement.h"
using namespace std;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

   void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */

   void addSourceLine(int lineNumber, std::string line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

   void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */

   std::string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 */

   void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */

   Statement *getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

   int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

   int getNextLineNumber(int lineNumber);

   void printAllLine();

   int getEndLineNumber();

private:

// Fill this in with whatever types and instance variables you need
class data
{
public:
    data(string in_code)
    {
        command=in_code;
        wzj::DeleteWhite(in_code);
        while(in_code[0]>='0'&&in_code[0]<='9')
        {
            in_code.erase(0,1);
        }
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
    data()
    {
        cmd_state=nullptr;
        command="";
    }
    void operator=(data &&o)
    {
        //cout<<"sghazuiydcghasyiudghaiuh"<<endl;
        if(cmd_state!=nullptr)delete cmd_state;
        cmd_state=o.cmd_state;
        o.cmd_state=nullptr;
        command=o.command;
    }
    ~data()
    {
        if(cmd_state!=nullptr)delete cmd_state;
    }
    Statement* cmd_state=nullptr;
    string command;
};

map<int , data> program_store;
};

#endif
