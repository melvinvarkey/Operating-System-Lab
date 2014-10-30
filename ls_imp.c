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
extern int asort();
static char pbuff[30];
char pname[MAXLEN];

int ex_a()
{
  int count,i;
  struct dirent **fl;
  if(!getcwd(pname, sizeof(pname)))
    die("ERROR\n");
  printf("Directory name: %s\n",pname);
  count = scandir(pname, &fl, f_sel, asort);
  if(count <= 0)
    die("No file in this directory\n");
  printf("Number of fl = %d\n",count); 
  for (i=1; i<count+1; ++i)
    printf("%s\n ",fl[i-1]->d_name);
  printf("\n");
  exit(0);
}

int ex_l()
{
  int count,i;
  struct dirent **fl;
  struct stat sb;
  char datestring[256];
  struct passwd pwent;
  struct passwd *pwentp;
  struct group grp;
  struct group *grpt;
  struct tm time;
  char buf[1024];
  count = scandir(pname, &fl, f_selo, asort);
  if(count > 0) 
  {
     printf("total %d\n",count);
     printf("pname name is = %s\n" , pname);
   for (i=0; i<count; ++i)
   {  
     if (!getpwuid_r(sb.st_uid, &pwent, buf, sizeof(buf), &pwentp))
       printf(" %s", pwent.pw_name);
     else
       printf(" %d", sb.st_uid);
     if (!getgrgid_r (sb.st_gid, &grp, buf, sizeof(buf), &grpt))
       printf(" %s", grp.gr_name);
     else
       printf(" %d", sb.st_gid);
       printf(" %5d", (int)sb.st_size);
     localtime_r(&sb.st_mtime, &time);
     strftime(datestring, sizeof(datestring), "%F %T", &time);
     printf(" %s %s\n", datestring, fl[i]->d_name);
     free (fl[i]);
    }
  free(fl);
  }
exit(0);
}

int ex_lp()
{ 
  int count,i;
  struct dirent **fl;
  struct stat sb;
  char datestring[256];
  struct passwd pwent;
  struct passwd *pwentp;
  struct group grp;
  struct group *grpt;
  struct tm time;
  char buf[1024];
  if(!getcwd(pname, sizeof(pname)))
    die("ERROR");
  count = scandir(pname, &fl, f_selo, asort);
  if(count > 0)
  {
    printf("total %d\n",count);
    for (i=0; i<count; ++i)
    {
      if (stat(fl[i]->d_name, &sb) == 0)
      {
        printf("%10.10s", get_perms(sb.st_mode));
        printf(" %d", sb.st_nlink);
        if (!getpwuid_r(sb.st_uid, &pwent, buf, sizeof(buf), &pwentp))
          printf(" %s", pwent.pw_name);
        else
          printf(" %d", sb.st_uid);
       if (!getgrgid_r (sb.st_gid, &grp, buf, sizeof(buf), &grpt))
          printf(" %s", grp.gr_name);
       else
          printf(" %d", sb.st_gid);
          printf(" %5d", (int)sb.st_size);
       localtime_r(&sb.st_mtime, &time);
       strftime(datestring, sizeof(datestring), "%F %T", &time);
       printf(" %s %s\n", datestring, fl[i]->d_name);
      }
    free (fl[i]);
    }
  free(fl);
}
exit(0);
}

int ex_ls()
{
  int count,i;
  struct dirent **fl;
  if(!getcwd(pname, sizeof(pname))) 
  die("ERROR\n");
  printf("Current Working Directory = %s\n",pname);
    count = scandir(pname, &fl,f_selo, asort);
  if(count <= 0)
    die("No fl in this directory\n");
    printf("Number of fl = %d\n",count);
  for (i=1; i<count+1; ++i)
    printf("%s\n ",fl[i-1]->d_name);
    return 0;
}

void die(char *msg)
{
  perror(msg);
  exit(0);
}

int f_selo(struct dirent *entry)
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
  sprintf(pbuff, "%c%c%c%c%c%c%c%c%c", ftype,
   mode & S_IRUSR ? 'r' : '-',mode & S_IWUSR ? 'w' : '-',
   mode & S_IXUSR ? 'x' : '-',mode & S_IRGRP ? 'r' : '-', 
   mode & S_IWGRP ? 'w' : '-',mode & S_IXGRP ? 'x' : '-',
   mode & S_IROTH ? 'r' : '-',mode & S_IWOTH ? 'w' : '-', 
   mode & S_IXOTH ? 'x' : '-',mode & S_ISUID ? 'U' : '-',
   mode & S_ISGID ? 'G' : '-',mode & S_ISVTX ? 'S' : '-');
  return (const char *)pbuff;
}

int f_sel(struct dirent *entry)
{
  if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
    return (FALSE);
  else
    return (TRUE);
}


int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    if (!strcmp(argv[1], "-a"))
      ex_a();
    if (!strcmp(argv[1], "-l"))
      ex_lp();
  }
  if (argc == 3)
  {
    strcpy(pname, argv[2]);
    ex_l();
  }
  if (argc == 1)
    ex_ls();
}
