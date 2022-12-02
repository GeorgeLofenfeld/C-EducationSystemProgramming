#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <malloc.h>

long int list_file(const char* dirname) {
	    DIR* dir;
        struct dirent *item;
        struct stat file;
        long int file_size[5] = { 0 };
        int key = 0;
        if ( (dir = opendir(dirname)) != NULL) {
		printf("Reading files in: %s\n", dirname);
		item = readdir(dir);
		if (item == NULL) {
			perror("Error in readdir");
			return 1;
		   }
        while (item != NULL) {
		    char path_to_current_file[256] = {0};
		    strcat(path_to_current_file, dirname);
			strcat(path_to_current_file, "/");
			strcat(path_to_current_file, item->d_name);
			if (stat(path_to_current_file, &file) == -1) { 
                perror("Error during stat");
                return 1;
                }
            if (item->d_type == DT_REG) {
			    printf("Found file: %s\n", item->d_name);
                file_size[key] += file.st_size;
            };     
		    if ( (item->d_type == DT_DIR && strcmp(item->d_name, ".") != 0) && (strcmp(item->d_name, "..") != 0)) {
                printf("Size of this dir: %ld\n", file_size[key]);
                key++;
				printf("Open directory: %s\n\n", item->d_name);
				char path[256] = {0};
				strcat(path, dirname);
				strcat(path, "/");
				strcat(path, item->d_name);
				list_file(path);
				} 
		    item = readdir(dir);
		    errno = 0; 
		    if ( (item == NULL) && (errno != 0)) {
			    perror("Error after readdir");
				return 1;
		     	};
		      };
            };
            closedir(dir);
            long int min_size = file_size[0];
            for (int i = 0; i < 5; i++)
                if (file_size[i] < min_size)
                    min_size = file_size[i];
            return min_size;
};


int main() {
	printf("\n\nMinimum size of dir: %ld\n", list_file("."));
	return 0;
}
