#include<stdio.h>
// #include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

    long long int source, dest, n;
    char buf[1048577],wbuf[1048577];
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
    if (stat("/Assignment", &st) == -1) {
        if (mkdir("./Assignment", 0700)<0) {
          char msg[] = "can't make the directory Assignment\n";
          write(STDOUT_FILENO, msg, sizeof(msg)-1);
          return 0;
        }
    }
    if ((dest = open("Assignment/output.txt", O_WRONLY | O_CREAT, 0600)) < 0) {
      //rwx permission for user on dest
      char msg[] = "can't open destination";
      write(STDOUT_FILENO, msg, sizeof(msg)-1);
        exit(-1);
    }

    filesize = lseek(source, 0, SEEK_END); //filesize is lastby +offset
    int flag=0;
    if(filesize<1048576){
      n=lseek(source, 0, SEEK_SET);
      n = read(source, buf, filesize-1);

      if (n != filesize-1) {
        char msg[] = "can't read 1 byte";
        write(STDOUT_FILENO, msg, sizeof(msg)-1);
          exit(-1);
      }
      long long int k=0;
      for(j=filesize-2; j>=0 ; j--){
        if(buf[j]>='a' && buf[j]<='z') buf[j] = buf[j] - 32;
        else if(buf[j]>='A'&& buf[j]<='Z') buf[j] = buf[j] + 32;
        wbuf[k] = buf[j];
        ++k;
      }
      write(dest,wbuf,filesize-1);
    }
    for (i = filesize-1048576; i >= 0; i-=1048576) {
        //read byte by byte from end
        if(i!=0) n=lseek(source, -1048576, SEEK_CUR);
        else n = lseek(source, 0, SEEK_SET);

        if(flag==0) n = read(source, buf, 1048576);
        else n = read(source, buf, flag);

        if(flag==0) flag=1048576;
        else i= -1;

        if (n != flag) {
            char msg[] = "can't read 1 byte";
            write(STDOUT_FILENO, msg, sizeof(msg)-1);
            exit(-1);
        }
        long long int k = 0;
        for(j=flag-1; j>=0 ; j--){
          if(buf[j]>='a' && buf[j]<='z') buf[j] = buf[j] - 32;
          else if(buf[j]>='A'&& buf[j]<='Z') buf[j] = buf[j] + 32;
          wbuf[k] = buf[j];
          ++k;
        }
        write(dest, wbuf, flag);
        flag = 0;
        if(i<1048576 && i!=-1){
          flag = i;
          i=1048576 ;
        }

    }

    close(source);
    close(dest);

    return 0;
}
