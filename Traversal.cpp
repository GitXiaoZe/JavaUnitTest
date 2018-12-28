#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 10000

using namespace std;

void Recursive_TraversalFile(char* path, int len);

char relative_path[MAX];
char tmp[MAX];
int mylen;

bool EndWith(char *string, char *pattern){
        int i = 0;
        while(string[i] != '\0'){ i++;}
        int j = 0;
        while(pattern[j] != '\0'){ j++;}
        while( i >= 0 && j>=0 && string[i] == pattern[j]){
                i--;j--;
        }
        if(j >= 0) return false;
        return true;
}

//copy src to dest, and return the copied bytes' length
int mystrcpy(char *dest, char *src){
    if(dest==NULL || src == NULL){
        printf("dest is NULL or src is NULL\n");
        return -1;    
    }
    int len=0;
    while((dest[len]=src[len])!='\0'){ len++; }
    return len;
}

void TraversalFile(char *path){
    int len = mystrcpy(relative_path,path);
    mylen  = len;
    if(len <= 0){
        printf("path's length can not be zero!!!!!!!!\n");
        return;
    }
    Recursive_TraversalFile(path,len);
}

void Recursive_TraversalFile(char* path,int len){
    struct stat statbuf;
    if(lstat(path,&statbuf) < 0){
        printf("lstat : %s ERROR\n",path);
        return;    
    }
    if(S_ISREG(statbuf.st_mode)){
		if(EndWith(path,".class")){
			mystrcpy(tmp,path);
       	                int i;
                        //for(i = 0; tmp[i]=='.' || tmp[i]=='/';i++);
                        int begin = i = mylen + 1;
                        for(;tmp[i]!='\0';i++){
                                if(tmp[i]=='/') tmp[i] = '.';
                                else if(tmp[i] == '.') break;
                        }
                        int end = i;
                        for(;tmp[end]!='.' && end>=0;end--){
                                if(tmp[end] == '$') break;
                        }
                        if(end < 0 || tmp[end]=='.') end = i;
                        tmp[i] = '\0';
                        printf("%s\n",tmp+begin);

                }
	
    }else if(S_ISDIR(statbuf.st_mode)){
        DIR* dp = opendir(path);
        if(dp==NULL){
            printf("OpenDir %s ERROR\n",path);
            return;
        }
        struct dirent *entry = NULL;
        while((entry = readdir(dp))!=NULL){
            if(strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,".." ) != 0){
		relative_path[len] = '/';
                int temp = mystrcpy(relative_path+len+1,entry->d_name);
                Recursive_TraversalFile(relative_path,len+1+temp);
                relative_path[len] = '\0';    
            }
        }
        closedir(dp);
    }else{
    }
}


int main(int argc, char* argv[]){
    if(argc < 2){
	printf("Usage : ./main <src>\n");	
    }
    TraversalFile(argv[1]);
    return 0;
}
