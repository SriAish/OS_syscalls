#include<stdio.h>
// #include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char *argv[]){
	int fd,fw;
	/*
	 * OS exposes files to programs through file descriptors
	 * These file descriptors are small non-negative integers which refer to files opened by the OS.
	 * 0, 1 and 2 file descriptors are reserved for stdin, stdout and stderr respectively
	 */
	if(argc != 4){
		printf("Usage: ./a.out [filename]\n");
		return 0;
	}
	/*
	 *   Look up the 'open' man page for more information about what values each argument can take
	 *   Opens the file specified through argument in read-only mode
	 */
	fd = open(argv[1], O_RDONLY);
	fw = open(argv[2], O_WRONLY | O_APPEND | O_CREAT, 0666);
	if(fd < 0){
		// open returns -1 if the file failed to open
		fprintf(stderr, "Failed to open file \"%s\"\n", argv[1]);
		exit(1);
	}
	/* Now we read the first 100 characters of the file and print them */
	char s[101];
	size_t size_read;

	/* NOTE : DONOT use fread command for your assignment. */
	size_read = read(fd, s, 100);
	if(size_read < 0){
		/* read returns -1 if there was an error reading the file */

		fprintf(stderr, "Failed to read file \"%s\"\n", argv[1]);
		exit(1);
	}
	printf("Read %d bytes\n", (int)size_read);
	printf("%s\n", s);
	write(fw,s,100);
	printf("%s\n",argv[3]);
	write(fw,argv[3],sizeof(argv[3]));
	return 0;
}
