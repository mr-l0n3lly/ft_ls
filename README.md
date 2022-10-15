# Ft_ls

---

### Objectives

The project ft_ls opens the path to the Unix branch of the sphere system. For the first time, you will have to face the one libc functions that will allow you to do other things than just read or write on a file descriptor (this is to simplify of course). You will discover a sub-system of functions of operating system’s API, the associated data structures, as well as the management of memory allocation and the associated data.

ft_ls is also a great opportunity to think about the structure of your code before you even start writing your code. ft_ls’ bad reputation is due to students discovering too late in the game that their (lack of) initial design is preventing them from finishing their project without refactorizing a great part of their code. I admit that it can be frustrating...

To conclude, ft_ls is another opportunity to add to your libft new practical func- tions. Browsing a file and identifying directories is quite common in programming. Re- member that you you will have to do it on many future occasions. Improving your libft today will save you time tomorrow

---
### Allowed functions
- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit
- libft functions


##### write - write output
---
```C
#include <unistd.h>

ssize_t write(int filedes, const void *buf, size_t nbytes);
```

<b>Description:</b>

write() attempts to write nbyte of data to the object referenced by the descriptor fildes from the buffer pointed to by buf.  writev() performs the same action, but gathers the output data from the iovcnt buffers specified by the members of the iov array: iov[0], iov[1], ..., iov.

pwrite() and pwritev() perform the same functions, but write to the specified position in the file without modifying the file pointer.

---

##### opendir, readdir, closedir - directory operations
---
```C
#include <dirent.h>

DIR           *opendir(const char *filename);
struct dirent *readdir(DIR *dirp);
int           closedir(DIR *dirp);

/**********************************/

dirp = opendir(".");

if (dirp == NULL)
	return (ERROR);
	
len = strlen(name);

while ((dp = readdir(dirp)) != NULL) {
	if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
		(void)closedir(dirp);
		return (FOUND);
	}
}

(void)closedir(dirp);

return (NOT_FOUND);
```

<b>Description:</b>

The <b>opendir()</b> function opens the directory named by filename, associates a directory stream with it and returns a pointer to be used to identify the directory stream in subsequent operations.  The pointer NULL is returned if filename cannot be accessed, or if it cannot malloc(3) enough memory to hold the whole thing.

The <b>readdir()</b> function returns a pointer to the next directory entry.  The directory entry remains valid until the next call to readdir() or closedir() on the same directory stream.  The function returns NULL upon reaching the end of the directory or on error.  In the event of an error, errno may be set to any of the values documented for the getdirentries(2) system call.  Note that the order of the directory entries vended by readdir() is not specified.  Some filesystems may return entries in lexicographic sort order and others may not.  Also note that not all filesystems will provide a value for d_type and may instead set the field to DT_UNKNOWN.

The <b>closedir()</b> function closes the named directory stream and frees the structure associated with the dirp pointer, returning 0 on success.  On failure, -1 is returned and the global variable errno is set to indicate the error.

---

##### stat, lstat - display file status
---
```C
#include <sys/stat.h>

int stat(const char *restrict_path, struct stat *restrict_buf);
int lstat(const char *restrict_path, struct strat *restrict_buf);
```

<b>Description:</b>

The <b>stat()</b> function obtains information about the file pointed to by path.  Read, write or execute permission of the named file is not required, but all directories listed in the path name leading to the file must be searchable.

The <b>lstat()</b> function is like stat() except in the case where the named file is a symbolic link;
lstat() returns information about the link, while stat() returns information about the file the link references.  For symbolic links, the st_mode member contains meaningful information when used with the file type macros, and the st_size member contains the length of the pathname contained in the symbolic link.  File mode bits and the contents of the remaining members of the stat structure are unspecified.  The value returned in the st_size member is the length of the contents of the symbolic link, and does not count any trailing null.

---

##### getpwuid - password database operations
---
```C
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

struct passwd *getpwuid(uid_t uid);

struct passwd {
	char    *pw_name;       /* user name */
	char    *pw_passwd;     /* encrypted password */
	uid_t   pw_uid;         /* user uid */
	gid_t   pw_gid;         /* user gid */
	time_t  pw_change;      /* password change time */
	char    *pw_class;      /* user access class */
	char    *pw_gecos;      /* Honeywell login info */
	char    *pw_dir;        /* home directory */
	char    *pw_shell;      /* default shell */
	time_t  pw_expire;      /* account expiration */
	int     pw_fields;      /* internal: fields filled in */
};
```

<b>Description</b>

The functions getpwuid() search the password database for the given user uid, always returning the first one encountered.

---

##### getgrgid - group database operations
---
```C
#include <grp.h>
#include <uuid/uuid.h>

struct group *getgrgid(gid_t gid);

struct group {
	char    *gr_name;       /* group name */
	char    *gr_passwd;     /* group password */
	gid_t   gr_gid;         /* group id */
	char    **gr_mem;       /* group members */
};
```

<b>Description:</b>

The functions getgrgid(), and getgruuid() search the group database for the group id given by gid, returning the first one encountered.  Identical group gids may result in undefined behavior.

---

##### listxattr - list extended attribute name
---
```C
#include <sys/xattr.h>

ssize_t listxattr(const char *path, char *namebuf, size_t size, int options);
```

<b>Description:</b>

Extended attributes extend the basic attributes associated with files and directories in the file system.  They are stored as name:data pairs associated with file system objects (files, directories, symlinks, etc).

listxattr() retrieves a list of names of extended attributes associated with the given path in the file system.

namebuf is a data buffer of size bytes for the names of the extended attributes associated with path.  The extended attribute names are simple NULL-terminated UTF-8 strings and are returned in arbitrary order.  No extra padding is provided between names in the buffer.  The list will only include names of extended attributes to which the calling process has access.  The function returns the size of the list of names.

options controls how the attribute list is generated:

XATTR_NOFOLLOW  do not follow symbolic links.  listxattr() normally lists attributes of the target of path if it is a symbolic link.  With this option, listxattr() will list attributes of the link itself.

XATTR_SHOWCOMPRESSION listxattr() and flistxattr() will list HFS Plus Compression extended attribute(s) (if present) for the file referred to by path or fd.

If namebuf is set to NULL, the function returns the size of the list of extended attribute names.  This facility can be used to determine the size of a buffer sufficiently large to hold the names of the attributes currently associated with path.

---

##### getxattr - get an extended attribute value
---
```C
#include <sys/xattr.h>

size_t getxattr(
	const char *path,
	const char *name,
	void *value,
	size_t size,
	u_int32_t position,
	int options
);
```

<b>Description:</b>

Extended attributes extend the basic attributes of files and directories in the file system.  They are stored as name:data pairs associated with file system objects (files, directories, symlinks, etc).

The getxattr() function retrieves up to size bytes of data from the extended attribute identified by name associated with path into the pre-allocated buffer pointed to by value.  The function returns the number of bytes of data retrieved.

An extended attribute's name is a simple NULL-terminated UTF-8 string.  position specifies an offset within the extended attribute.  In the current implementation, this argument is only used with the resource fork attribute. For all other extended attributes, this parameter is reserved and should be zero.

On success, value contains the data associated with name.  When value is set to NULL, getxattr() returns current size of the named attribute.  This facility can be used to determine the size of a buffer sufficiently large to hold the data currently associated with the attribute.

options specify options for retrieving extended attributes:

XATTR_NOFOLLOW  do not follow symbolic links.  getxattr() normally returns information from the target of path if it is a symbolic link.  With this option, getxattr() will return extended attribute data from the symbolic link instead.

XATTR_SHOWCOMPRESSION getxattr() and fgetxattr() will return HFS Plus Compression extended attribute name (if present) for the file referred to by path or fd.

---

##### time - get time of day
---
```C
#include <type.h>

time_t time(time_t *tloc);
```

<b>Description:</b>

The time() function returns the value of time in seconds since 0 hours, 0 minutes, 0 seconds, January 1, 1970, Coordinated Universal Time, without including leap seconds.  If an error occurs, time() returns the value (time_t)-1.

---

##### ctime - transforms binary date and time values
---
```C
#include <time.h>

char *ctime(const time_t *clock);
```

<b>Description:</b>

The functions ctime(), gmtime(), and localtime() all take as an argument a time value representing the time in seconds since the Epoch (00:00:00 UTC, January 1, 1970; see time(3)).  When encountering an error, these functions return NULL and set errno to an appropriate value.

---

#####  readlink - read value of symbolic link
---
```C
#include <unistd.h>

ssize_t readlink(const char *restrict_path, char *restrict_buf, size_t bufsize);
```

<b>Description:</b>

readlink() places the contents of the symbolic link path in the buffer buf, which has size bufsize.  Readlink does not append a NUL character to buf.

---

##### perror, strerror - system error message
---
```C
#include <stdio.h>

void perror(const char *s);
char *strerror(int errnum);
```

<b>Description:</b>

The strerror(), strerror_r(), and perror() functions look up the error message string corresponding to an error number.

The strerror() function accepts an error number argument errnum and returns a pointer to the corresponding message string.

The perror() function finds the error message corresponding to the current value of the global variable errno (intro(2)) and writes it, followed by a newline, to the standard error file descriptor.  If the argument s is non-NULL and does not point to the null character, this string is prepended to the message string and separated from it by a colon and space (“: ”); otherwise, only the error message string is printed.

---

##### exit - perform normal program termination
---
```C
#include <stdlib.h>

void exit(int status);
```

<b>Description:</b>

The exit() and _Exit() functions terminate a process.

Before termination, exit() performs the following functions in the order listed:

1.   Call the functions registered with the atexit(3) function, in the reverse order of their registration.

2.   Flush all open output streams.

3.   Close all open streams.

4.   Unlink all files created with the tmpfile(3) function.

The _Exit() function terminates without calling the functions registered with the atexit(3) function, and may or may not perform the other actions listed.  Both functions make the low-order eight bits of the status argument  available to a parent process which has called a wait(2)-family function.

The C Standard (ISO/IEC 9899:1999 (“ISO C99”)) defines the values 0, EXIT_SUCCESS, and EXIT_FAILURE as possible values of status.  Cooperating processes may use other values; in a program which might be called by a mail transfer agent, the values described in sysexits(3) may be used to provide more information to the parent process.

Note that exit() does nothing to prevent bottomless recursion should a function registered using atexit(3) itself call exit().  Such functions must call _Exit() instead (although this has other effects as well which may not be desired).

---

### Mandatory part
---
- You must recode the system’s command ls.
- Its behavior must be identical to the original ls command with the following variations:

- Amongst the numerous options available, we are asking you to create the following:

```
-l, -R, -a, -r and -t.
```

- We strongly recommend that you account for the implications of the option -R from the very beginning of your code...

- You do not have to deal with the multiple column format for the exit when the option -l isn’t in the arguments.

- You are not required to deal with ACL and extended attributes.

- The overall display, depending on each option, must stay as identical as pos- sible to the system command. We will be cordial when grading either the padding or the pagination, but no information can be missing.

---

### Bonus part

We will look at your bonuses if and only if your mandatory part is EXCELLENT. This means that your must complete the mandatory part, beginning to end, and your error management must be flawless, even in cases of twisted or bad usage. If that’s not the case, your bonuses will be totally IGNORED.

Find below a few ideas of interesting bonuses you could create. Some could even be useful. You can, of course, invent your own, which will then be evaluated by your evaluators according to their own taste.

- Management of ACL and extended attributes.
- Management of the columns without the option -l. (man 4 tty)
- Management of options:

```
-u, -f, -g, -d, ...
```

- Management of views in colors (Similar to option -G)
- Optimization of your code (What is the response time of your ls on a BIG ls -lR for example?)

---