/*  File:     interact_utils.c
    Author:   Robin Boswell
    Purpose:  Filename expansion etc.

    Change Log:

      2/16/96 - Rick Kufrin, NCSA/UIUC <rkufrin@ncsa.uiuc.edu>
        Changed to use termios terminal interface. Old version
        bracketed by _TTYOLD preprocessor directives.
          Affected routines: get_filename()
                             tidy_before_quitting()
                             select_char()

        Added static globals: cc_t user_eof, user_eol

        Removed #include <sys/timeb.h> (not needed)      

      3/16/96 - Rick Kufrin
        Added reset of signal handling after continuing from
        stop.
          Affected routine: reset_on_continuing()

        Replaced use of ioctl() request TIOCSTI with test for
        interrupted read() system calls.
        Change bracketed by _USE_TIOCSTI preprocessor directives.
          Affected routines: get_filename()
                             reset_on_continuing()
                             select_char()

        Redeclared char variables as int when used with getchar().
          Affected routines: scrap_till_newline()
                             scrap_till_next_command()
                             select_char()

*/ 

static char *SccsId = "@(#)interact_utils.c 5.1 9/25/91 MLT Robin Boswell Copyright The Turing Institute 1989";

#include "mdep.h"
#include "cn_externs.h"

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef OS
#define OS (4)
#endif

#if OS == 3
#include <sys/dir.h>
typedef struct direct DIRENT;
#else
#include <dirent.h>
typedef struct dirent DIRENT; 
#endif

#define DEFAULT_PAGER "/usr/ucb/more"

#include <ctype.h>    
#include <sys/file.h>
#include <sys/stat.h>
#include <string.h>
#ifdef _TTYOLD
#include <sys/ioctl.h>
#else
#include <termios.h>
#endif
#ifndef _USE_TIOCSTI
#include <errno.h>
extern int errno;
#endif

#include <stdio.h>
#include <sys/types.h>
/*#include <sys/timeb.h>*/
#include <time.h>



#define BS     8
#define EXPAND 9 /* Tab */
#define DEL  127
#define SP    32
#define BEL    7
#define ESC   27

void (*default_stop_func)();
BOOL pager_flag;
BOOL can_execute();
extern char *getenv();

#ifndef _TTYOLD
static cc_t user_eof = 0, user_eol = 0; /* See select_char() */
#endif

/* Simple line-editor, with (so far) two EMACS commands:
      TAB invokes filename-completion
      ESC-h = backward-kill-word

   In addition, if the user types the name of a non-existent directory,
   it rejects all subsequent input except delete-commands until the
   offending '/' has been removed.
                                                                    */
BOOL get_filename(prompt, startup, filename)
char prompt[];
char startup[];
char filename[];
{
     
     int c, l;
     int i=0;
     BOOL selected = FALSE;
     BOOL D_ERROR = FALSE;
     BOOL ESC_FLAG = FALSE;     
     
     int fd;
#ifdef _TTYOLD
     struct sgttyb cb_state, old_state;
#else
     struct termios tbuf, old_tbuf;
#endif
     
     fd = 0;
#ifdef _TTYOLD
     if (isatty(fd) &&
	 ioctl(fd, TIOCGETP, &old_state) == 0 &&
	 ioctl(fd, TIOCGETP, &cb_state) == 0) {
	  tty_ok = TRUE;
	  cb_state.sg_flags |= CBREAK;
	  cb_state.sg_flags &= ~ECHO;
	  ioctl(fd, TIOCSETP, &cb_state);
     }
#else
     if (isatty(fd) && tcgetattr(fd, &tbuf) != -1) { 
         tty_ok = TRUE;
         old_tbuf = tbuf;
         tbuf.c_lflag &= ~(ICANON | ECHO);
         tbuf.c_lflag |= ISIG;
         tbuf.c_cc[VMIN] = 1;
         tbuf.c_cc[VTIME] = 0;
         tcsetattr(fd, TCSANOW, &tbuf);
     }
#endif
     else {
	  tty_ok = FALSE;
	  strcpy(startup, "");       
   }
      
     
     strcpy(filename, startup);
     i = strlen(startup);
     fprintf(stdout, "%s%s", prompt, startup);
     fflush(stdout);
     while (! selected) {
	  if (ESC_FLAG) {
	       switch (c = getchar()){
	       case 'h':
	       case 'H':
		    if (i > 0) {
			 putchar(BS);
			 putchar(SP);
			 putchar(BS);
			 filename[--i] = (char)0;
		    }
		    while ((i > 0) && isalnum(filename[i-1])){
			 putchar(BS);
			 putchar(SP);
			 putchar(BS);
			 filename[--i] = (char)0;
		    }
		    D_ERROR = FALSE;		    
		    break;
#ifndef _USE_TIOCSTI
               case -1:
                    if (errno == EINTR) c = '\n';
                    break;
#endif
	       default:
		    putchar(BEL);
	       }
	       ESC_FLAG = FALSE;
	  }
	  else if (! D_ERROR) {
	       switch (c = getchar()){
	       case '\n':
	       case '\r':
		    filename[i] = (char)0;
		    selected = TRUE;
		    putchar(c);
		    if (!tty_ok) {
			 ungetc(c, stdin);
			 scrap_till_next_command();			 
		    }
		    break;
	       case EXPAND:
		    filename[i] = (char)0;
		    if (extend_file_name(filename)) {
			 if ((l = strlen(filename)) == i) {
			      fprintf(stdout, "\n");
			      print_possible_files(filename);
			      fprintf(stdout, "%s%s", prompt, filename);
			      fflush(stdout);
			 }
			 else
			   i = l;
		    }
		    break;
	       case '/':
		    filename[i] = (char)0;		    
		    if ( !  ((i == 0)
  			  ||  directory_p(filename)))
		      D_ERROR = TRUE;
		    else
		      strcpy(data_dir, filename);
		    putchar(c);
		    filename[i++] = c;
		    break;
	       case BS:
	       case DEL:
		    if (i > 0){
			 putchar(BS);
			 putchar(SP);
			 putchar(BS);
			 filename[--i] = (char)0;
		    }
		    break;
	       case ESC:
		    ESC_FLAG = TRUE;
		    break;
	       case COMMENT_CHAR:
		    if (!tty_ok){
			 scrap_till_newline();
			 break;
		    }
#ifndef _USE_TIOCSTI
               case -1:
                    if (errno == EINTR) {
                         selected = TRUE;
                         filename[i] = (char)0;
                         c = '\n';
                         putchar(c);
                    }
                    break;
#endif
		    /* Else drop down to default case */
	       default:
		    if (isprint(c)){
			 putchar(c);
			 filename[i++] = c;
		    }
	       }
	  }
	  else {
	       if (! tty_ok){
		    fprintf(stdout, "\n   No such directory - aborting\n");
		    exit(-1);
	       }
	       switch (c = getchar()){
	       case BS:
	       case DEL:
		    if (i > 0){
			 putchar(BS);
			 putchar(SP);
			 putchar(BS);
			 filename[--i] = (char)0;
			 D_ERROR = FALSE;
		    }
		    break;
	       case ESC:
		    ESC_FLAG = TRUE;
		    break;
#ifndef _USE_TIOCSTI
               case -1:
                    if (errno == EINTR) {
                         selected = TRUE;
                         filename[i] = (char)0;
                         c = '\n';
                         putchar(c);
                    }
                    break;
#endif
	       default:
		    putchar(BEL);
		    fflush(stdout);
	       }
	  }
     }
     if (tty_ok)
#ifdef _TTYOLD
       ioctl(fd, TIOCSETP, &old_state);
#else
       tcsetattr(fd, TCSANOW, &old_tbuf);
#endif
     
     if (strcmp(filename, "") == 0)
       return(0);
     else {
	  if (! strchr(filename, '/'))
	    strcpy(data_dir, "");
	  return(1);
     }
}     


int FileBaseName(name, path, file, index)
char name[], path[], file[];
int *index;
{
     int l = strlen(name);
     int found = FALSE;
     int i;
     
     for (i=(l-1); i>=0; --i){
	  if (name[i] == '/'){
	       found = TRUE;
	       break;
	  }
     }
     if (! found){
	  strcpy(file, name);
	  strcpy(path, ".");
	  *index = 0;
     }
     else {
	  strcpy(file, name+(i+1));
	  name[i] = (char)0;
	  strcpy(path, name);
	  if (strcmp(path, "") == 0)
	    strcpy(path, "/");	    
	  name[i] = '/';	  
	  *index = i+1;
     }
     return(1);
}

extend_file_name(name)
char name[];
{
     int i, l1, l2, status;
     
     l1 = strlen(name);
     status = expand(name);
     if ((l2 = strlen(name)) > l1){
	  for (i=l1; i < l2; ++i)
	    putchar(name[i]);
	  fflush(stdout);
     }
     return(status);
}

     
     


expand(name)
char name[];
{
      DIR *dirp;
      static DIRENT *dp;      
      char path[256], file[256], max_com_sub[256];
      char *current;
      int length, matched, index;
      
      if (!FileBaseName(name, path, file, &index))
	    return(0);
      if (!(dirp = opendir(path))) 
	    return(0);

      length = strlen(file);
      matched = FALSE;
      max_com_sub[0] = (char)0;
      while (dp = readdir(dirp)){
	   current = dp->d_name;
	   if (strncmp(file, current, length) == 0){
		if (! matched) {
		     strcpy(max_com_sub, current);
		     matched = TRUE;
		}
		else
		  max_com(max_com_sub, current);
	   }
      }
      closedir(dirp);            
      if (matched) {
	   int l;
	   strcpy(name+index, max_com_sub);
	   if (directory_p(name) && (l = strlen(name)) > 0 &&
	       name[l-1] != '/') {
		strcat(name, "/");
		strcpy(data_dir, name);
	   }
	   return(1);
      }
      else {
	   putchar(7);
	   fflush(stdout);
	   return(0);
      }

}

max_com(max, new)
char max[], new[];
{
     int i=0;
     
     while (max[i] == new[i])
       ++i;
     max[i] = (char)0;
}

	  
print_possible_files(start)
char start[];
{
      DIR *dirp;
      DIRENT *dp;      
      char path[256], file[256];
      int index, length;
      
      if (!FileBaseName(start, path, file, &index))
	    return(0);
      if (!(dirp = opendir(path))) 
	    return(0);

      length = strlen(file);
      while (dp = readdir(dirp)){
	   if (strncmp(file, dp->d_name, length) == 0)
	     if (strncmp(".", dp->d_name, 1) &&
		  strncmp("..", dp->d_name, 2))
		  fprintf(stdout, "\t%s\n", dp->d_name);
      }
      return(1);
 }


      
directory_p(name)
char *name;
{
      struct stat inode;

      if (stat(name, &inode) == -1)
	    return(0);
      if (inode.st_mode & S_IFDIR) 
	    return(1);
      else
	    return(0);
}



void set_signal_handling()
{
     signal(SIGINT, tidy_before_quitting);
     signal(SIGTSTP, tidy_before_quitting);
}


void reset_on_continuing()
{
#ifdef _USE_TIOCSTI
     char c = '\n';
#endif
     fprintf(stdout, "Welcome back!\n");
     signal(SIGTSTP, tidy_before_quitting);  /* Reinstall signal handler */
#ifdef _USE_TIOCSTI
     //ioctl(0, TIOCSTI, &c);
#endif
}

void tidy_before_quitting(sig, code, scp, addr)
int sig, code;
struct sigcontext *scp;
char *addr;
{
     int fd = 0;
#ifdef _TTYOLD
     struct sgttyb state;
#else
     struct termios tbuf;
#endif

     code = code; /* To keep saber_tool quiet */
     scp = scp;
     addr = addr;

#ifdef _TTYOLD
     if (isatty(fd) &&
	 ioctl(fd, TIOCGETP, &state) == 0){
	  state.sg_flags &= ~CBREAK;
	  state.sg_flags |= ECHO;
	  ioctl(fd, TIOCSETP, &state);
     }
#else
     if (isatty(fd) && tcgetattr(fd, &tbuf) != -1) {
          tbuf.c_lflag |= ICANON;
          tbuf.c_lflag |= ECHO;
          tbuf.c_cc[VEOF] = user_eof;
          tbuf.c_cc[VEOL] = user_eol;
          tcsetattr(fd, TCSANOW, &tbuf);
     }
#endif

     switch (sig){
     case SIGINT:
	  fprintf(stdout, "   Bye-bye!\n");
	  exit(1);
	  break;
     case SIGTSTP:
	  fprintf(stdout, "\n   Au revoir\n");
	  signal(SIGCONT, reset_on_continuing);
	  kill(getpid(), SIGSTOP);
	  break;
     }
}


void scrap_till_newline()
{
     /*char*/ int c;

     while ((c = getchar()) != EOF){
	  if (c == '\n')
	    return;
     }
     return;
}


void scrap_till_next_command()
{
     /*char*/ int c;
     BOOL command_ended = FALSE;
     
     while ((c = getchar()) != EOF){
	  if (isspace(c))
	    command_ended = TRUE;
	  else if (command_ended) {
	       ungetc(c, stdin);
	       return;
	  }
     }
     return;
}


char select_char(options)
char *options;
{
     /*char*/ int  c;
     BOOL done = FALSE;
     int fd;
#ifdef _TTYOLD
     struct sgttyb cb_state, old_state;
#else
     struct termios tbuf, old_tbuf;     
#endif

     fd = 0;     /* stdin */
#ifdef _TTYOLD
     if (isatty(fd) &&
	 ioctl(fd, TIOCGETP, &old_state) == 0 &&
	 ioctl(fd, TIOCGETP, &cb_state) == 0) {
	  tty_ok = TRUE;
	  cb_state.sg_flags |= CBREAK;
	  cb_state.sg_flags &= ~ECHO;
	  ioctl(fd, TIOCSETP, &cb_state);
     }
#else
     if (isatty(fd) && tcgetattr(fd, &tbuf) != -1) {
	 /* VEOF/VEOL share same termios slots with VMIN/VTIME.
          * Save original values for later restore on SIGINT/SIGTSTP.
          */
	 if (!(user_eof || user_eol)) {
	   user_eof = tbuf.c_cc[VEOF];
	   user_eol = tbuf.c_cc[VEOL];
	 }
         tty_ok = TRUE;
         old_tbuf = tbuf;
         tbuf.c_lflag &= ~(ICANON | ECHO);
         tbuf.c_lflag |= ISIG;
         tbuf.c_cc[VMIN] = 1;
         tbuf.c_cc[VTIME] = 0;
         tcsetattr(fd, TCSANOW, &tbuf);
     }
#endif
     else
       tty_ok = FALSE;
     
     while (TRUE){
	  int i=0;

	  if ((c = getc(stdin)) == EOF){
#ifndef _USE_TIOCSTI
               if (errno == EINTR)
                     c = '\n';
               else {
	             fprintf(stderr, "Unexpected EOF - aborting\n");
	             exit(-1);
               }
#else
             fprintf(stderr, "Unexpected EOF - aborting\n");
             exit(-1);
#endif
	  }

	  if ((!tty_ok) && (c == COMMENT_CHAR)) {
	    scrap_till_newline();
	    continue;
	  }

	  if (isupper(c)) 
	    c=tolower(c);

	  while(options[i] != (char)0){
	       if (c == options[i++]){
		    done = TRUE;
		    break;
	       }
	  }

	  if (!tty_ok) {
	       if (isspace(c))
		 ungetc(c, stdin);
	       scrap_till_next_command();
	  }
	  
	  
	  if (done){
	       if (tty_ok)
#ifdef _TTYOLD
		 ioctl(fd, TIOCSETP, &old_state);
#else
                 tcsetattr(fd, TCSANOW, &old_tbuf);
#endif
	       return(c);
	  }
	  else 
	    if (tty_ok) {
		 putc(7, stdout);
		 fflush(stdout);
	    }
	    else {
	      fprintf(stderr, "Unexpected character `%c' ", c);
	      fprintf(stderr, "in script - aborting\n"); 
	      exit(-1);
	 }
     }
}


assert_filename(filename)
char *filename;
{
     char *s;
     
     if (s = strrchr(filename, '/'))
       strcpy(global_readfile, s+1);
     else
       strcpy(global_readfile, filename);
}

/* Calling function must ensure memory is allocated for string */
clockin(string)
char *string;
{
     long t = time((time_t)0);
     char *s = ctime(&t);
     s[strlen(s)-1] = '\0';
     sprintf(string, "[ %s ]", s);
}




FILE *pager_open()
{
     char *buffer;
     char pager[BUFSIZ];
     FILE *pipe;

     pager_flag = FALSE;
     
     if (buffer = getenv("PAGER"))
       strcpy(pager, buffer);
     else
       strcpy(pager, DEFAULT_PAGER);

     if (can_execute(pager)){
	  if (pipe = popen(pager, "w"))
	    pager_flag = TRUE;
	  else
	    perror(pager);
     }

     if (!pager_flag)
       pipe = stdout;

     return(pipe);
}

pager_close(fp)
FILE *fp;
{
     if (pager_flag)
       pclose(fp);
}


maybe_print(c)
char c;
{
     if (TRACE_DOTS){
	  switch(c) {
	  case 'l':
	       fprintf(stdout, "L ");
	       break;
	  case '.':
	       fprintf(stdout, ".");	       
	       break;
	  }
	  fflush(stdout);
     }
}



BOOL can_execute(string)
char *string;
{
     struct stat status;
     
     if (stat(string, &status) != 0){
	  fprintf(stderr, "%s: Command not found\n", string);       
	  return(FALSE);
     }

     if (status.st_mode & S_IEXEC)
       return(TRUE);
     else {
	  fprintf(stderr, "%s: Permission denied\n", string);
	  return(FALSE);
     }
}


