#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#ifdef _WIN32
#include <direct.h>
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

// #pragma comment( lib, "psapi.lib" )
// #if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

#include <fstream>
#include <sys/types.h>
// #include <bits/stdc++.h>
#include <unistd.h>
#include <fstream>
#include <map>
#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <ios>
// #include <proc/readproc.h>
#include <process.h>
#include <ctime>
#include <iomanip>
using namespace std;

typedef int (*action)(string);
map<string /*command name*/, action /*action*/> commands;

// **************************  Present Working Directory  *************************
int pwd_action(string args)
{
    char pwd[PATH_MAX];
    if (_getcwd(pwd, sizeof(pwd)) != NULL)
    {
        cout << "Current working directory : " << pwd << "\n";
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
    cout << setw(36) << "NAME";
    cout << "                 Creation date                  Modification Date\n";
    cout << setw(40) << "-------------";
    cout << "           -----------------             ----------------------\n";
    if (dr)
    {
        struct stat file;
        while ((en = readdir(dr)) and (readdir(dr) != NULL))
        {
            stat(en->d_name, &file);
            string fileinfo = ctime(&file.st_ctime);
            fileinfo.erase(fileinfo.find('\n', 0), 1);
            // cout << "\n";
            cout << setw(40) << en->d_name << "        " << fileinfo << "        " << ctime(&file.st_mtime);
        }
        cout << "\n";
        closedir(dr);
    }
}

// **************************  To print the List of Files, Directories and Links  *****************************
int ls_type_action(string args)
{
    string dr_type;
    cin >> dr_type;
    int type;
    if (dr_type == "folder")
        type = 16;
    else if (dr_type == "file")
        type = 24;
    else if (dr_type == "link")
        type = 0;
    else
        perror("No Such Type");

    DIR *dr;
    struct dirent *en;
    dr = opendir(".");
    if (dr)
    {
        cout << "\n";
        while ((en = readdir(dr)))
        {
            if (en->d_type == type)
            {
                cout << en->d_name;
                cout << "\n";
            }
        }
        cout << "\n";
        closedir(dr);
    }
}

// **************************  Change Directory  *****************************
int cd_action(string args)
{
    char changed_dir[PATH_MAX];
    string newdir;
    cin >> newdir;
    _chdir(newdir.c_str());
    if (_getcwd(changed_dir, sizeof(changed_dir)) == NULL)
    {
        perror("ERROR MESSAGE ");
        return 1;
    }
    cout << "Current Working Directory Changed to ---> " << changed_dir << "\n";
}

// **************************  ECHO    *********************
int echo_action(string args)
{
    string text;
    cin >> text;
    cout << text << "\n";
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
        perror("ERROR MESSAGE ");
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
    if (rename(old_name.c_str(), new_name.c_str()))
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

int move_action(string args)
{
    string oldname;
    cout << "Old Name \n";
    cin >> oldname;
    string newname;
    cout << "New Name \n";
    cin >> newname;
    ifstream src(oldname.c_str(), ios::binary);
    ofstream dest(newname.c_str(), ios::binary);

    dest << src.rdbuf();
    cout << "File copied successfully";
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
        cout << word << " ";
}

// ***********************  Check for a files existence ********************
int exists_action(string args)
{
    string path;
    cin >> path;
    int check = access(path.c_str(), F_OK);
    if (!check)
        cout << "File/Folder Exists on your FileSystem\n";
    else
        cout << "NO SUCH File/Folder on your FileSystem\n";
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
int clear_action(string args)
{
    system("CLS");
}

// **************************  Commands List/ HELP  ***********************
int help_action(string args)
{
    cout << "J_pwd    => The Current Working Directory \n";
    cout << "J_ls     => List of Sub Directories in the Current directory \n";
    cout << "J_lstype => To print the list of based on Folder, Files or Links\n";
    cout << "J_cd     => To Change the Current Working Directory \n";
    cout << "J_echo   => To print text to the terminal window \n";
    cout << "J_mkdir  => To Make a new Directory \n";
    cout << "J_rmdir  => To Remove a particular Directory \n";
    cout << "J_rename => To Rename a directory \n";
    cout << "J_mkfile => To Make a New File (txt, cpp, py, xls, pptx, pdf etcccc.)\n";
    cout << "J_rmfile => To Delete a File \n";
    cout << "J_mv     => To move a directory from one location to another \n";
    cout << "J_read   => To Read each and every word from a file\n";
    cout << "J_exist  => To check if a particular file or folder Exits \n";
    // cout << "J_memory => To check the Current Memory and the Peak Memory \n";
    cout << "J_time   => To Display current Day, Date and Time \n";
    cout << "J_clear => To Clear the Terminal \n";
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
    commands["J_lstype"] = ls_type_action;
    commands["J_cd"] = cd_action;
    commands["J_echo"] = echo_action;
    commands["J_mkdir"] = mkdir_action;
    commands["J_rmdir"] = rmdir_action;
    commands["J_rename"] = rename_action;
    commands["J_mkfile"] = createfile_action;
    commands["J_rmfile"] = removefile_action;
    commands["J_mv"] = move_action;
    commands["J_read"] = read_action;
    commands["J_exist"] = exists_action;
    // commands["J_memory"] = memory_action;
    commands["J_time"] = time_action;
    commands["J_clear"] = clear_action;
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
                commands[cmd]("");
            else
                cout << "No Such Command in the J_Shell, Many more commands to come soon\n";
        }
    }
    return 0;
}
