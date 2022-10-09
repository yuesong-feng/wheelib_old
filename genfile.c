#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
long long get_size(const char *str){
	int len = strlen(str);
	int mul = -1;
	if(str[len - 1] == 'b') 
		mul = 1;
	else if(str[len - 1] == 'B')
		mul = 8;
	else
		return -1;
	if(str[len - 2] == 'k' || str[len - 2] == 'K'){
		mul *= 1024;
	} else if(str[len - 2] == 'm' || str[len - 2] == 'M') {
		mul *= 1024 * 1024;
	} else if(str[len - 2] == 'g' || str[len - 2] == 'G') {
		mul *= 1024 * 1024 * 1024;
	}
	long long num = atoll(str);
	long long ret = num * mul;
	return ret;
}
int main(int argc, char *argv[]){
	int opt;
	char file_size[32];
	char file_name[32];
	memset(file_size, 0, 32);
	memset(file_name, 0, 32);
	while ((opt = getopt(argc, argv, "s:n:")) != -1){
		switch (opt) {
			case 's':
				strcpy(file_size, optarg);
				break;
			case 'n':
				strcpy(file_name, optarg);
				break;
			default:
				fprintf(stderr, "Usage: genfile -s $file_size -n $file_name\n");
				exit(EXIT_FAILURE);
		}
	}
	if(file_size[0] == 0 || file_name[0] == 0){
		fprintf(stderr, "Usage: genfile -s $file_size -n $file_name\n");
		exit(EXIT_FAILURE);
	}
	printf("Generating %s size of file %s\n", file_size, file_name);
	long long size = get_size(file_size);
	if (size == -1) {
		printf("Size format wrong!\n");
		exit(EXIT_FAILURE);
	}
	printf("size: %llu\n", size);
	int fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd == -1) {
		if(errno == EEXIST) {
			printf("File %s already exist\n", file_name);
			exit(EXIT_FAILURE);
		}
		printf("Failed to open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}
	char buf[1024];
	memset(buf, 'A', 1024);
	long long bytes_left = size;
	while(bytes_left > 0){
		if(bytes_left >= 1024){
			if (write(fd, buf, 1024) != 1024) {
				printf("Error while writing to file %s\n", file_name);
				exit(EXIT_FAILURE);
			}
			bytes_left -= 1024;
		} else {
			if (write(fd, buf, bytes_left) != bytes_left) {
				printf("Error while writing to file %s\n", file_name);
				exit(EXIT_FAILURE);
			}
			bytes_left -= bytes_left;
		}
	}
	close(fd);
	return 0;
}
