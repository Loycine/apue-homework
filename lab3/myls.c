#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void print_type(struct stat buf)
{
    char* ptr;
    if (S_ISREG(buf.st_mode))
        ptr = "-";
    else if (S_ISDIR(buf.st_mode))
        ptr = "d";
    else if (S_ISCHR(buf.st_mode))
        ptr = "c";
    else if (S_ISBLK(buf.st_mode))
        ptr = "b";
    else if (S_ISFIFO(buf.st_mode))
        ptr = "p";
    else if (S_ISLNK(buf.st_mode))
        ptr = "l";
    else if (S_ISSOCK(buf.st_mode))
        ptr = "s";
    else
        ptr = "** unknown mode **";
    printf("%s", ptr);
}

void print_perm(struct stat* buf)
{
    printf((S_IRUSR & buf->st_mode)?"r" : "-");
    printf((S_IWUSR & buf->st_mode)?"w" : "-");
    printf((S_IXUSR & buf->st_mode)?"x" : "-");
    printf((S_IRGRP & buf->st_mode)?"r" : "-");
    printf((S_IWGRP & buf->st_mode)?"w" : "-");
    printf((S_IXGRP & buf->st_mode)?"x" : "-");
    printf((S_IROTH & buf->st_mode)?"r" : "-");
    printf((S_IWOTH & buf->st_mode)?"w" : "-");
    printf((S_IXOTH & buf->st_mode)?"x" : "-");
}

void print_link(struct stat* buf)
{
    printf(" ");
    printf("%ld", buf->st_nlink);
}

void print_usrname(struct stat* buf)
{
    struct passwd* psd = getpwuid(buf->st_uid);
    printf(" ");
    printf("%s", psd->pw_name);
}

void print_grname(struct stat* buf)
{
    struct group* grp = getgrgid(buf->st_gid);
    printf(" ");
    printf("%s", grp->gr_name);
}

void print_time(struct stat* buf)
{
    printf(" ");
    struct tm* mtime = localtime(&buf->st_mtime);
    printf("%d-%d-%d %d:%d", mtime->tm_year+1900, mtime->tm_mon+1, mtime->tm_mday, mtime->tm_hour, mtime->tm_min);

}

void print_filename(struct dirent* entry)
{
    printf(" ");
    printf("%s", entry->d_name);
}

int main(int argc, char* argv[])
{
    char* cur_path = NULL;
    if((cur_path = getcwd(cur_path, 0)) == NULL)
    {
        perror("getcwd");
        return -1;
    }

    DIR* cur_dir;
    if((cur_dir = opendir(cur_path)) == NULL)
    {
        perror("opendir");
        return -1;
    }

    struct dirent* entry;
    struct stat sb;
    while((entry=readdir(cur_dir))!=NULL)
    {
        if(lstat(entry->d_name, &sb) < 0) {
            perror("lstat");
            continue;
        }

        print_type(sb);
        print_perm(&sb);
        print_link(&sb);
        print_usrname(&sb);
        print_grname(&sb);
        print_time(&sb);
        print_filename(entry);
        printf("\n");
    }

    closedir(cur_dir);
    free(cur_path);
}



