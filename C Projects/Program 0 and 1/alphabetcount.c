/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <string.h>

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (A-Z a-z, case sensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from A - Z a - z:
      alphabetfreq[0]: the frequency of 'A'
      alphabetfreq[1]: the frequency of 'B'
         ... ...
      alphabetfreq[25]:the frequency of 'Z'
      alphabetfreq[26]:the frequency of 'a'
         ...  ...
      alphabetfreq[51]:the frequency of 'z'
  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (A-Z a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     A -> 200
     B -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
    //SELECTING DIRECTORY PROCESS
    DIR *directory;
    struct dirent *dir; //put a file in specific directory
    directory = opendir(path);  //find path

    char *filename;
    char *f;    //file pointer
    int character;  //char holder for alphabetfreq array
    int position = -1;  //position holder for alphabetfreq array

    //NULL DIRECTORY ERROR
    if(d == NULL){
        printf("ERROR: OPENING DIRECTORY\n");
        return;
    }
    //A DIRECTORY EXISTS -> GO THROUGH FILE ONE BY ONE
    else{
        while((entry = readdir(directory)) != NULL) {
            f = dir->d_name;
            char p[256];
            strcpy(p, path);
            strcat(p, "/");
            strcat(p, fil);
            FILE *f = fopen(p, "r");
            if(f == NULL)
                return;
            int c = fgetc(f);

            //FIND END OF FILE - START ALPHABET FREQUENCY COUNT
            while(!feof(f)) {
                position = -1;
                if(character <= 'Z' && character >= 'A')//    UPPERCASE - ASCII POSITION
                    position = (int)character-65;
                else if(character <= 'z' && character >= 'a') //  LOWERCASE - ASCII POSITION
                    position = (int)character-97+26;
                c = fgetc(f); //re-initializes fgetc for next character in while loop
                if(position != -1)
                    alphabetfreq[position]++;
            }
            fclose(f);

            //WRITE TO FILETOWRITE
            FILE *g = fopen(filetowrite, "w");
            if(g){  //if g file is open
                character=-1;
                for(int i=0;i<51;i++){
                    if(i <= 25 && i >= 0)
                        character=i+65;
                    else if(i <= 51 && i >= 26)
                        character=i-26+97;
                    fprintf(g,"%c -> %ld\n",character,alphabetfreq[i]);
                }
            }
            else
                printf("\nERROR: OUTPUT FILE UNABLE TO OPEN\n");
            fclose(g);
            }
        }
    }
    closedir(directory);
}
