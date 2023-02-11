#ifdef _WIN32
#include <unistd.h> // For Windows
#define GetCurrentDir _getcwd
#else
#include <unistd.h> // For Linux
#define GetCurrentDir getcwd
#endif

#ifdef _WIN32
#include <direct.h>
#define cwd _getcwd
#define cd chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

#include <fstream>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fstream>
#include <map>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <ios>
#include <process.h>
#include <ctime>
using namespace std;

typedef int (*action)(string);
map<string /** command name */, action /* action */> commands;

// **************************  Present Working Directory  *************************
int pwd_action(string args)
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        cout << "Current working directory : " << buffer << "\n";
    }
    else
        perror("ERROR MESSAGE ");
    return 0;
}

// **************************  List  *****************************
int ls_action(string args)
{
    DIR *dr;
    struct dirent *en;
    dr = opendir("."); // single dot to open the current directory.
    if (dr)
    {
        while ((en = readdir(dr)) != NULL)
        {
            cout << " \n"
                 << en->d_name;
        }
        cout << "\n";
        closedir(dr);
    }
}

// **************************  Change Directory  *****************************
int cd_action(string args)
{
    char buff[PATH_MAX];
    string newdir;
    cin >> newdir;
    chdir(newdir.c_str());
    if (getcwd(buff, sizeof(buff)) == NULL)
    {
        perror("ERROR MESSAGE ");
        return 1;
    }
    cout << "Current Working Directory Changed to ---> " << buff << "\n";
}

// **************************  Make New Directory  *********************
int mkdir_action(string args)
{
    string dir_name;
    cin >> dir_name;

    int check;
    check = mkdir(dir_name.c_str());
    if (check)
        perror("ERROR MESSAGE ");
}

// **************************  Delete A Directory ********************
int rmdir_action(string args)
{
    string dir_name;
    cin >> dir_name;

    int check = rmdir(dir_name.c_str());
    if (check)
    {
        perror("ERROR MESSAGE ");
    }
    // else
    //     cout << "Directory Removed Successfully \n";
}

// **************************  Rename a Directory ***********************
int rename_action(string args)
{
    string old_name;
    cout << "Old Name :\n";
    cin >> old_name;
    string new_name;
    cout << "New Name :\n";
    cin >> new_name;
    int check = rename(old_name.c_str(), new_name.c_str());

    if (check)
        perror("ERROR MESSAGE ");
}

//  **************************  Make New File ***********************
int createfile_action(string args)
{
    ofstream file;
    string name;
    cin >> name;
    file.open(name.c_str());
}

//  **************************  Delete a File  *******************
int removefile_action(string args)
{
    string file_name;
    cin >> file_name;

    int check = remove(file_name.c_str());
    if (check)
        perror("ERROR MESSAGE ");
}

// **************************  Move a File from one Location to Another *******************
int move_action(string args)
{
    string oldname;
    cout << "Enter the name of the file or the folder you want to change\n";
    cin >> oldname;

    string newname;
    cout << "Enter the Destination\n";
    cin >> newname;

    if (rename(oldname.c_str(), newname.c_str()) != 0)
        perror("ERROR MESSAGE ");
    else
        cout << "SUCCESS !!\n";
}

int read_action(string args)
{
    fstream file;
    string word;
    cout << "Enter the file name thru which u wanna read the contents \n";
    string filename;
    cin >> filename;
    // fstream filename;
    file.open(filename.c_str());
    while (file >> word)
    {
        cout << word << " ";
    }
}

int exists_action(string args)
{
    // Check for file existence
    string path;
    cin >> path;
    int check = access(path.c_str(), F_OK);
    if (!check)
        cout << "File/Folder Exists on your FileSystem\n";
    else
        cout << "NO SUCH File/Folder on your FileSystem\n";
}

int echo_action(string args)
{
    cout << cin.rdbuf();
}

// **************************  Day, Date, Time **************************
int time_action(string args)
{
    time_t tt;     // tt passed as an argument in funciton time()
    struct tm *ti; // declaring variable for localtime()
    time(&tt);     // passing argument to time()
    ti = localtime(&tt);
    cout << "Day Date   Time     Year\n";
    cout << "--------   ----     ----\n"
         << asctime(ti);
}

// **************************  Clear Terminal ***********************
int clrscr_action(string args)
{
    system("CLS");
}

// **************************  Commands List/ HELP  ***********************
int help_action(string args)
{
    cout << "1)  J_pwd          The Current Working Directory \n";
    cout << "2)  J_ls           List of Sub Directories in the Current directory \n";
    cout << "3)  J_cd           To Change the Current Working Directory \n";
    cout << "4)  J_mkdir        To Make a new Directory \n";
    cout << "5)  J_rmdir        To Remove a particular Directory \n";
    cout << "6)  J_rename       To Rename a directory \n";
    cout << "7)  J_mkfile       To Make a New File (txt, cpp, py, xls, pptx, pdf etcccc.)\n";
    cout << "8)  J_rmfile       To Delete a File \n";
    cout << "9)  J_move         To Move a file from one location to another\n";
    cout << "10) J_read         To Read each and every word from a file\n";
    cout << "11) J_echo         To print the Text on the terminal as it is\n";
    cout << "12) J_exist        To check if a particular file or folder Exits \n";
    cout << "13) J_time         To Display current Day, Date and Time \n";
    cout << "14) J_clrscr       To Clear the Terminal \n";
}

int main()
{
    cout << endl;
    cout << "------------------        ---------\n";
    cout << "         |                |       |\n";
    cout << "         |                |\n";
    cout << "         |                |\n";
    cout << "         |                `--------\n";
    cout << "|        |                        |\n";
    cout << "|        |                        |\n";
    cout << "|        |                |       |\n";
    cout << "`--------`   ----------   `-------`\n\n";

    cout << "_______________________________________\n";
    cout << ".......WELCOME TO JATIN's SHELL....... \nYou can use the Command J_help to start \n";
    cout << "---------------------------------------\n";
    commands["J_pwd"] = pwd_action;
    commands["J_ls"] = ls_action;
    commands["J_cd"] = cd_action;
    commands["J_mkdir"] = mkdir_action;
    commands["J_rmdir"] = rmdir_action;
    commands["J_rename"] = rename_action;
    commands["J_mkfile"] = createfile_action;
    commands["J_rmfile"] = removefile_action;
    commands["J_move"] = move_action;
    commands["J_read"] = read_action;
    commands["J_exist"] = exists_action;
    commands["J_echo"] = echo_action;
    commands["J_time"] = time_action;
    commands["J_clrscr"] = clrscr_action;
    commands["J_help"] = help_action;
    while (true)
    {
        string cmd;
        cout << "> ";
        cin >> cmd;
        if (cmd == "exit")
            break;
        else
        {
            if (commands.find(cmd) != commands.end())
            {
                commands[cmd]("");
            }
            else
            {
                cout << "No Such Command in the J_Shell, Many more commands to come soon\n";
            }
        }
    }
    return 0;
}
