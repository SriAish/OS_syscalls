#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

    long long int k = 0;
    long long int source, dest, n;
    char bufs[1048577],bufd[1048577];
    long long int filesize;
    long long int i,j;
    struct stat st;

    if (argc != 2) {
        char msg[] = "usage ./a.out <source>";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
        exit(-1);
    }
    if ((source = open(argv[1], O_RDONLY)) < 0) {
      //read permission for user on source
      char msg[] = "can't open source";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
        exit(-1);
    }
    if ((dest = open("Assignment/output.txt", O_RDWR | O_CREAT, 0600)) < 0) {
      //rwx permission for user on dest
      char msg[] = "can't open destination";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
        exit(-1);
    }

    filesize = lseek(source, 0, SEEK_END); //filesize is lastby +offset

    symlink("./Assignment/output.txt","./output.symlink");

    if (stat("./Assignment", &st) == -1) {
      char msg[] = "Checking whether the directory has been created: No\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }
    else{
      char msg[] = "Checking whether the directory has been created: Yes\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }

    if(stat("./Assignment/output.txt", &st) == -1) {
      char msg[] = "Checking whether the file has been created: No\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }
    else{
      char msg[] = "Checking whether the file has been created: Yes\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }

    if(stat("./output.symlink", &st) == -1) {
      char msg[] = "Checking whether the symlink has been created: No\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }
    else{
      char msg[] = "Checking whether the symlink has been created: Yes\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }

    int flag=0;
    if(filesize<1048576){
      n = lseek(source, 0, SEEK_SET);
      n = read(source, bufs, filesize-1);
      n = read(dest, bufd, filesize-1);
      k=0;
      for(j=filesize-2; j>=0 ; j--){
        if(bufs[j]>='a' && bufs[j]<='z') bufs[j] = bufs[j] - 32;
        else if(bufs[j]>='A' && bufs[j]<='Z') bufs[j] = bufs[j] + 32;
        if(bufd[k]!=bufs[j]){
          char msg[] = "Checking whether file contents have been reversed and case-inverted: No\n\n";
          write(STDOUT_FILENO, msg, sizeof(msg)-1);
          break;
        }
        ++k;
      }
    }
    for (i = filesize-1048576; i >= 0; i-=1048576) {
        //read byte by byte from end
        if(i!=0) n=lseek(source, -1048576, SEEK_CUR);
        else n = lseek(source, 0, SEEK_SET);
        if(flag==0) {
          n = read(source, bufs, 1048576);
          n = read(dest, bufd, 1048576);
        }
        else {
          n = read(source, bufs, flag);
          n = read(dest, bufd, flag);
        }

        if(flag==0) flag=1048576;
        else i= -1;
        k=0;
        for(j=flag-1; j>=0 ; j--){
          if(bufs[j]>='a' && bufs[j]<='z') bufs[j] = bufs[j] - 32;
          else if(bufs[j]>='A' && bufs[j]<='Z') bufs[j] = bufs[j] + 32;
          if(bufd[k]!=bufs[j]){
            char msg[] = "Checking whether file contents have been reversed and case-inverted: No\n\n";
            write(STDOUT_FILENO, msg, sizeof(msg)-1);
            i=-2;
            flag = 1048579;
            break;
          }
          ++k;
        }
        flag = 0;
        if(i<1048576 && i!=-1){
          flag = i;
          i=1048576;
        }

    }

    if(i<=0 && flag!=1048579){
      char msg[] = "Checking whether file contents have been reversed and case-inverted: Yes\n\n";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
    }

    if (stat("./Assignment/output.txt", &st) != -1) {
      if (st.st_mode & S_IRUSR){
        char msg[] = "User has read permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has read permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if (st.st_mode & S_IWUSR){
        char msg[] = "User has write permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has write permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXUSR){
        char msg[] = "User has execute permission on file: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has execute permission on file: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IRGRP){
        char msg[] = "Group has read permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has read permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IWGRP){
        char msg[] = "Group has write permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has write permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXGRP){
        char msg[] = "Group has execute permission on file: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has execute permission on file: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IROTH){
        char msg[] = "Others has read permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has read permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IWOTH){
        char msg[] = "Others has write permission on file: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has write permission on file: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXOTH){
        char msg[] = "Others has execute permission on file: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has execute permission on file: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
    }
    if (stat("./Assignment", &st) != -1) {
      if (st.st_mode & S_IRUSR){
        char msg[] = "User has read permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has read permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if (st.st_mode & S_IWUSR){
        char msg[] = "User has write permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has write permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXUSR){
        char msg[] = "User has execute permission on directory: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "User has execute permission on directory: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IRGRP){
        char msg[] = "Group has read permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has read permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IWGRP){
        char msg[] = "Group has write permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has write permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXGRP){
        char msg[] = "Group has execute permission on directory: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Group has execute permission on directory: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IROTH){
        char msg[] = "Others has read permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has read permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IWOTH){
        char msg[] = "Others has write permission on directory: Yes\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has write permission on directory: No\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      if(st.st_mode & S_IXOTH){
        char msg[] = "Others has execute permission on directory: Yes\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
      else{
        char msg[] = "Others has execute permission on directory: No\n\n";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
      }
    }
    close(source);
    close(dest);

    return 0;
}
