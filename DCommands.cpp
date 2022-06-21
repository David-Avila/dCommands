#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

//dCommand type declaration
typedef void (*dCommand) (string cmd);

//Function Declarations
void NewLine();
void cmdNewLine(string cmd);
void cmdExit(string cmd);
void cmdEnter(string cmd);
void cmdBack(string cmd);
void cmdFile(string cmd);
void cmdFolder(string cmd);

string GetFunc(string cmd);
string GetArg1(string cmd);
string GetArg2(string cmd);
void UnExistingCmd(string cmd);
void procCmd(string cmd);

//****************Command*Names************************
static string cmdNames[] = {
    "exit",
    "log",
    "enter",
    "back",
    "file",
    "folder"
};

static int cmdAmount = sizeof(cmdNames) / sizeof(string);

//****************Comand**Functions************************
static dCommand cmdFunctions[] = {
    cmdExit,
    cmdNewLine,
    cmdEnter,
    cmdFile,
};

//SUPER IMPORTANT HERE
//
// The name of the command in cmdNames MOST be at the same index of the function
// you want to attache to it in the cmdFunctions array.
//
// I call the function 'NewLine' at the end of every command so the console doesn't close
// until we write the command 'exit'.
//

int main()
{
    NewLine();
    return 0;
}

void NewLine() 
{
    //This is self-explanatory
    cout << "DCommand:";

    //Super straightforward stuff
    string dCmd;
    getline(cin, dCmd);//I use getline() in order to cath the funtions along with up to 2 arguments

    //Call the function that procces the user-entered command
    procCmd(dCmd);
}

void procCmd(string cmd)
{

    string func = GetFunc(cmd);

    //Looping trough the commands to check if the user entered a defined command
    for (int i = 0; i < cmdAmount; i++)
    {
        if (cmdNames[i] == func)
        {            
            //Executing the function that match with the command the user entered
            cmdFunctions[i](cmd);
            break;
        }

        //If reached the last array index the command does not match any of
        //the pre-defined commands, tell the user there command does not exists.
        if (i == cmdAmount - 1)
        {
            UnExistingCmd(func);
        }
    }
}

string GetFunc(string cmd)
{
    //Separate function from arguments (if any).
    int spacePos = cmd.find(" ");

    if (spacePos != -1)
    {
        return cmd.substr(0, spacePos);
    }
    else
    {
        return cmd;
    }
}

string GetArg1(string cmd) 
{
    //Erasing function name from command
    int spacePos = cmd.find(" ");
    cmd.erase(0, spacePos + 1);

    //testing if there is more than 1 argument by checking for another 'space'
    spacePos = cmd.find(" ");

    if (spacePos != -1) //cmd.find() returns -1 if no spaces are found
    {
        return cmd.substr(0, spacePos);
    }
    else
    {
        return cmd;
    }
}

string GetArg2(string cmd)
{
    //Erasing function name from command
    int spacePos = cmd.find(" ");
    cmd.erase(0, spacePos + 1);

    //Erasing argument1 from command
    spacePos = cmd.find(" ");
    cmd.erase(0, spacePos + 1);

    //returning argument 2
    return cmd;
}

//************dCommands****************

//Without this function the program would close if the entered command
//is not in the defined commands
void UnExistingCmd(string cmd)
{
    string enteredCmd = "'" + GetFunc(cmd) + "'";//putting the command betwen quotes ''

    cout << enteredCmd << " command not found.\n";

    NewLine();
}


//Exit application
void cmdExit(string cmd)
{
    exit(0);

    NewLine();
};

//This is useless
void cmdNewLine(string cmd)
{
    cout << cmd << endl;
    NewLine();
}


//Create new file
void cmdFile(string cmd)
{
    //Getting the arguments
    string arg1 = GetArg1(cmd);//name of the file
    string arg2 = GetArg2(cmd);//content fo the file

    ofstream newFile;
    newFile.open(arg1);
    newFile << arg2 << endl;
    newFile.close();

    cout << "New file created with the name " << arg1 << endl;
    NewLine();
}