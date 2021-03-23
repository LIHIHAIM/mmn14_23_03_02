/* [mmn 14 : ]:
in this file: 

author: Uri K.H,   Lihi Haim       Date: 21.3.2021 
ID: 215105321,     313544165       Tutor: Danny Calfon */

#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "util.h"
#include "privateDataFuncs.h"
#include "privateInstFuncs.h"
#include "privateSymTabFuncs.h"

#define RAM_SIZE 4096

/* openf(): Open a given file in a given status and returns the pointer to the file. */
FILE *openf(char *file, char *status){
     FILE *fd = fopen(file, status);
     if(!fd){
          printf("error : could not open file: \"%s\"\n",file);
          return NULL;
     }
     return fd;
}

/* readLine(): Reads a line (length 80 characters) from a given file pointer - fd, 
 to a dinamic array and returns the array. */
char *readLine(FILE *fd, int len){
     char *line = calloc(len, sizeof(char));
     fgets(line,len,fd);
     return line;
}

void buildOutputFiles(char *fileName){
     FILE *fd;
     char *tempFileName = malloc(strlen(fileName) + MAX_SUFIX_LEN + 1);
     if(getIC() + getDC() >= RAM_SIZE){
          printf("error: file is too long\n");
          free(tempFileName);
          return;
     }
     fd = openf(addSufix(tempFileName, ".ob", fileName), "w");
     fprintf(fd, "\t%d %d\n", getIC()-OS_MEM, getDC());
     pushInstsToFile(fd);
     pushDataToFile(fd);
     fclose(fd);
     
     if(entryExist()){
          fd = openf((addSufix(tempFileName, ".ent", fileName)), "w");
          pushEntryToFile(fd);
          fclose(fd);
     }
     if(externalExist()){
          fd = openf((addSufix(tempFileName, ".ext", fileName)), "w");

          fclose(fd);
     }
     return;
}

char *addSufix(char *dest, char *suffix, char *name){
     strcpy(dest, name);
     strcat(dest, suffix);
     return dest;
}