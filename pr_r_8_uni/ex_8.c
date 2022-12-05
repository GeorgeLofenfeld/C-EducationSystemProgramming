/*
Найти каталог (выведите его имя на экран) в текущем каталоге и его подкаталогах любой степени
вложенности, имеющий суммарный наименьший размер файлов. Если таких каталогов несколько, то
выведите любой из них.
Реализовать используя pipe();
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

struct Res {
    long int size;
    char name[256];
};

int list_file(const char* dirname, struct Res* res) {
	DIR* dir;
    struct dirent *item;
    struct stat file;
    long int cur_dir_size = 0;
    long int prev_dir_size = 0;
    if ( (dir = opendir(dirname)) != NULL) {
    	printf("\nReading files in: %s\n", dirname);
	    item = readdir(dir);
		if (item == NULL) {
			perror("Error in readdir");
			exit(0);
		    }
        while (item != NULL) {
			char path_to_current_file[256] = {0};
			strcat(path_to_current_file, dirname);
			strcat(path_to_current_file, "/");
			strcat(path_to_current_file, item->d_name);
			if (stat(path_to_current_file, &file) == -1) { 
                perror("Error during stat");
                exit(0);
                }
            if (item->d_type == DT_REG) {
	            printf("Find file: %s, size: %ld bytes\n", item->d_name, file.st_size);
                cur_dir_size += file.st_size;
                }
		    if ((item->d_type == DT_DIR && strcmp(item->d_name, ".") != 0) && (strcmp(item->d_name, "..") != 0)) {
                int fd[2] = { 0 };
                if (pipe(fd) < 0 ) {
                    perror("ERROR: Can't create pipe()");
                    return 1;
                };
                int pid = fork();
                if (pid == 0) {
                    printf("Creating child proccess %d\n", getpid());
                    printf("My parent: %d\n", getppid());
                    printf("Find dir: %s\n", item->d_name);
                    printf("Open directory: %s\n", item->d_name);
			        char path[256] = {0};
			        strcat(path, dirname);
			        strcat(path, "/");
		    	    strcat(path, item->d_name);
                    list_file(path, res);
                    open(fd[1]);
                    write(fd[1], res, sizeof(res));
                    exit(&pid);
                } else if (pid < 0) {
                    perror("ERROR: Cant creating proccess\n");
                    return 1;
                };
                if (pid > 0) {
                    close(fd[1]);
                    read(fd[0], res, sizeof(res));
                    printf("This is a parent proccess %d\n", getpid());
                    printf("Waiting my child %d\n", pid);
                    wait(&pid); 
                }
            };
		    item = readdir(dir);
		    errno = 0; 
		    if ( (item == NULL) && (errno != 0)) {
			    perror("Error after readdir");
				exit(0);
			    };
            };
        } else {
            perror("");
            exit(0);
            }; 
    closedir(dir);
    if (res->size == 0 || res->size > cur_dir_size ) {
        res->size = cur_dir_size;
        strcpy(res->name, dirname); 
    };

    

    return 0;
};


int main() {
   struct Res res = { 0 };
   list_file(".", &res);
   printf("\n\nThe directory with the smallest sum of file sizes: %s, %ld bytes\n\n", res.name, res.size);
   return 0;
}
