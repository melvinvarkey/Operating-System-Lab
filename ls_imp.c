//--------------------------------------------------------------
// Implementation of ls command in C
//--------------------------------------------------------------

#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <fcntl.h>
#define FALSE 0
#define TRUE !FALSE
extern int alphasort();
static char perms_buff[30];
char pathname[MAXPATHLEN];
void die(char *msg)
{
  perror(msg);
  exit(0);
}
int file_selecto(struct direct *entry)
{
  char *ptr;
  char *rindex(const char *s, int c );
  if ((strcmp(entry->d_name, ".")== 0) ||(strcmp(entry->d_name, "..") == 0)) return (FALSE);
    ptr = rindex(entry->d_name, '.');
  if ((ptr != NULL) && ((strcmp(ptr, ".c") == 0) ||(strcmp(ptr, ".h") == 0) ||(strcmp(ptr, ".o") == 0) ))
    return (TRUE);
  else
    return(FALSE);
}
const char *get_perms(mode_t mode)
{
  char ftype = '?';
  if (S_ISREG(mode)) ftype = '-';
  if (S_ISLNK(mode)) ftype = 'l';
  if (S_ISDIR(mode)) ftype = 'd';
  if (S_ISBLK(mode)) ftype = 'b';
  if (S_ISCHR(mode)) ftype = 'c';
  if (S_ISFIFO(mode)) ftype = '|';
  sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c %c%c%c", ftype,
   mode & S_IRUSR ? 'r' : '-',
   mode & S_IWUSR ? 'w' : '-',
   mode & S_IXUSR ? 'x' : '-',
   mode & S_IRGRP ? 'r' : '-', 
   mode & S_IWGRP ? 'w' : '-',
   mode & S_IXGRP ? 'x' : '-',
   mode & S_IROTH ? 'r' : '-',
   mode & S_IWOTH ? 'w' : '-', 
   mode & S_IXOTH ? 'x' : '-',
   mode & S_ISUID ? 'U' : '-',
   mode & S_ISGID ? 'G' : '-',
   mode & S_ISVTX ? 'S' : '-');
  return (const char *)perms_buff;
}

int file_select(struct direct *entry)
{
  if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
    return (FALSE);
  else
    return (TRUE);
}
int excecute_a()
{
  int count,i;
  struct direct **files;
  if(!getcwd(pathname, sizeof(pathname)))
    die("Error getting pathname\n");
  printf("Current Working Directory = %s\n",pathname);
  count = scandir(pathname, &files, file_select, alphasort);
  if(count <= 0)
    die("No files in this directory\n");
  printf("Number of files = %d\n",count); 
  for (i=1; i<count+1; ++i)
    printf("%s\n ",files[i-1]->d_name);
  printf("\n");
  exit(0);
}
int excecute_l()
{
  int count,i;
  struct direct **files;
  struct stat statbuf;
  char datestring[256];
  struct passwd pwent;
  struct passwd *pwentp;
  struct group grp;
  struct group *grpt;
  struct tm time;
  char buf[1024];
  count = scandir(pathname, &files, file_selecto, alphasort);
  if(count > 0) 
  {
     printf("total %d\n",count);
     printf("pathname name is = %s\n" , pathname);
   for (i=0; i<count; ++i)
   {  
     if (!getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
       printf(" %s", pwent.pw_name);
     else
       printf(" %d", statbuf.st_uid);
     if (!getgrgid_r (statbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
       printf(" %s", grp.gr_name);
     else
       printf(" %d", statbuf.st_gid);
       printf(" %5d", (int)statbuf.st_size);
     localtime_r(&statbuf.st_mtime, &time);
     strftime(datestring, sizeof(datestring), "%F %T", &time);
     printf(" %s %s\n", datestring, files[i]->d_name);
     free (files[i]);
    }
  free(files);
  }
exit(0);
}
int excecute_lp()
{ 
  int count,i;
  struct direct **files;
  struct stat statbuf;
  char datestring[256];
  struct passwd pwent;
  struct passwd *pwentp;
  struct group grp;
  struct group *grpt;
  struct tm time;
  char buf[1024];
  if(!getcwd(pathname, sizeof(pathname)))
    die("Error getting pathnamen");
  count = scandir(pathname, &files, file_selecto, alphasort);
  if(count > 0)
  {
    printf("total %d\n",count);
    for (i=0; i<count; ++i)
    {
      if (stat(files[i]->d_name, &statbuf) == 0)
      {
        printf("%10.10s", get_perms(statbuf.st_mode));
        printf(" %d", statbuf.st_nlink);
        if (!getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
          printf(" %s", pwent.pw_name);
        else
          printf(" %d", statbuf.st_uid);
       if (!getgrgid_r (statbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
          printf(" %s", grp.gr_name);
       else
          printf(" %d", statbuf.st_gid);
          printf(" %5d", (int)statbuf.st_size);
       localtime_r(&statbuf.st_mtime, &time);
       strftime(datestring, sizeof(datestring), "%F %T", &time);
       printf(" %s %s\n", datestring, files[i]->d_name);
      }
    free (files[i]);
    }
  free(files);
}
exit(0);
}
int execute_ls()
{
  int count,i;
  struct direct **files;
  if(!getcwd(pathname, sizeof(pathname))) 
  die("Error getting pathname\n");
  printf("Current Working Directory = %s\n",pathname);
    count = scandir(pathname, &files,file_selecto, alphasort);
  if(count <= 0)
    die("No files in this directory\n");
    printf("Number of files = %d\n",count);
  for (i=1; i<count+1; ++i)
    printf("%s\n ",files[i-1]->d_name);
    return 0;
}
int main(int argc, char* argv[])
{
  if (argc ==2)
  {
    if (!strcmp(argv[1], "-a"))
    {
      excecute_a();
    }
    if (!strcmp(argv[1], "-l"))
    {
      excecute_lp();
    } 
  }
  if (argc == 3)
  {
    strcpy(pathname, argv[2]);
    excecute_l();
  }
  if (argc == 1)
    execute_ls();
}
