/*
Удалить обычные файлы (regular file), имя которых содержит символ ~ в случае, если длина их равна 0
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR* dir;
	struct dirent *item;
	struct stat file;
	if ( (dir = opendir(".")) != NULL) {
		while ((item = readdir(dir)) != NULL) {
	 	     if (stat(item->d_name, &file) == -1) {
				perror(" ");
				return 1;
			}
			if ( (item->d_type == DT_REG) && (file.st_size == 0))
				for (int i = 0; i < strlen(item->d_name); i++) 
					if (item->d_name[i] == '~') {
						if (remove(item->d_name) == 0) {
							break;
						} else { 
							perror(" ");
							return 1; 
						}
						
					} 					  
		}
	} else perror(" ");
	closedir(dir);
	return 0;
}
