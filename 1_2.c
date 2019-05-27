#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
        if(NULL == opendir("newDir")){
                mkdir("newDir",0775);
                DIR *dir = opendir("/home/pi");
                struct dirent *ent = readdir(dir);
                while(ent){
                        printf("   %s   ", ent -> d_name);
                        ent = readdir(dir);
                }
        }
        system("mkdir -p /home/pi/newDir2");
        char command[50];
        strcpy(command, "ls"); // system("ls")
        system(command);
        return 0;
}

