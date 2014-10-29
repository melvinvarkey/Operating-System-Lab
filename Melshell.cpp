//**********************************
//  Shell code
//**********************************

#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>

using namespace std;

//char pathname[MAXPATHLEN];

int main()
{
  string command;
  int ls();
  int ps();
  cout << "\n**MelShell**\n";
  while( command != "exit")
  {
    if( command == "help" )
      cout << "This is a small shell used to perform ls and ps commands";
    else if ( command == "ls" )
      ls();
    else if ( command == "ps" )
      ps();
    else if ( command != "\0" )
      cout << "Error: Unknown Command";

    cout << "\n%_ ";
    cin >> command;
  }
  return 0;
}
int ls()
{
  int i;
  struct dirent **files;
  //if(!getcwd(pathname, sizeof(pathname)))                                      
  //  cout <<  "Error getting pathname\n";
  //cout << "Current Working Directory = " << pathname;
  //count = scandir( pathname, &files, file_selecto, alphasort );
  //if(count <= 0)
