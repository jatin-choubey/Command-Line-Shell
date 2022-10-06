#ifdef WINDOWS
#include <direct.h> // For Windows
#define GetCurrentDir _getcwd
#else
#include <unistd.h> // For Linux
#define GetCurrentDir getcwd
#endif

#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif
#include <map>

// #include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <process.h>
using namespace std;

typedef int (*action)(string);
map<string /*command name*/, action /*action*/> commands;

// **************************  Present Working Directory  *************************
int pwd_action(string args)
{
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        printf("Current working directory : %s\n", buffer);
    }
}
// *********************  List  *****************************
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

// *****************************  Change Directory  *****************************
int cd_action(string args)
{
    char buff[PATH_MAX];
    cout << "Enter the directory you want to Enter \n";
    string newdir;
    cin >> newdir;
    _chdir(newdir.c_str());
    if (getcwd(buff, sizeof(buff)) == NULL)
    {
        perror("");
        return 1;
    }
    cout << "Current Working Directory Changed to ---> " << buff << endl;
}

// ****************  Make New Directory  *********************
int mkdir_action(string args)
{
    string dir_name;
    cout << "Enter the name of the new directory \n";
    cin >> dir_name;

    int check;
    check = mkdir(dir_name.c_str());
    if (!check)
        cout << "Directory has been succesfully created \n";
    else
        cout << "Directory Creation Failed \n";
}

// ************************** Delete A Directory ********************
int rmdir_action(string args)
{
    string dir_name;
    cout << "Enter the Location of the directory to be Deleted \n";
    cin >> dir_name;

    int check = rmdir(dir_name.c_str());
    if (check == 0)
    {
        cout << "The Target Directory has been succesfully removed \n";
        return 1;
    }
    else
        perror("");
}

// ******************  Clear Terminal ***********************
int clrscr_action(string args)
{
    system("CLS");
}

int help_action(string args)
{
    cout << "J_pwd = The Current Working Directory \n";
    cout << "J_ls = List of Sub Directories in the Current in the current directory \n";
    cout << "J_cd = To Change the Current Working Directory \n";
    cout << "J_mkdir = To Make a new Directory \n";
    cout << "J_rmdir = To Remove a particular Directory \n";
    cout << "J_clrscr = To Clear the Terminal \n";
}

int main()
{
    cout << "......WELCOME TO JATIN's SHELL...... \nYou can use the Command J_help to start" << endl;
    commands["J_pwd"] = pwd_action;
    commands["J_ls"] = ls_action;
    commands["J_cd"] = cd_action;
    commands["J_mkdir"] = mkdir_action;
    commands["J_rmdir"] = rmdir_action;
    commands["J_clrscr"] = clrscr_action;
    commands["J_help"] = help_action;
    while (true)
    {
        string cmd;
        cout << "> ";
        cin >> cmd;
        if (cmd == "exit")
            return 0;
        else
        {
            if (commands.find(cmd) != commands.end())
            {
                commands[cmd]("");
            }
            else
            {
                cout << "command not found" << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}