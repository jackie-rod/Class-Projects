/*
 * specialcount.c - this file implements the specialcount function.
 */


#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <string.h>

void specialcount(char *path, char *filetowrite, long charfreq[])
{
    DIR *directory;
    char *filename;
    char *fi;
    struct dirent *dir;

    //TARGETED SPECIAL WORDS
    char he[] = " he ";
    char she[] = " she ";
    char they[] = " they ";
    char him[] = " him ";
    char me[] = " me "
    char checker[6];

    directory = opendir(path);
    if(d != NULL) {
        while((dir = readdir(d)) != NULL) {
            fi = dir->d_name;
            char p[256];
            strcpy(p, path);
            strcat(p, "/");
            strcat(p, fi);
            FILE *f = fopen(p, "r");
            if(f == NULL)
                return;
            int c = fgetc(f);
            while(!feof(f)) {
                if(c == '\0' && checker[0] !='\0') {
                    if(checker == he)
                        charfreq[0] = (long) charfreq[0] + 1;
                    else if(checker == she)
                        charfreq[1] = (long) charfreq[1] + 1;
                    else if(checker == they)
                        charfreq[2] = (long) charfreq[2] + 1;
                    else if(checker == him)
                        charfreq[3] = (long) charfreq[3] + 1;
                    else if(checker == me)
                        charfreq[4] = (long) charfreq[4] + 1;
                    checker[] = {};
                    c = fgetc(f);
                }
                if(checker.size() > 6)
                    checker={};
                for(int i = 0; i< checker.size(); i++)
                    if(checker[i] == NULL)
                        checker[i] = c;
            }

            fclose(f); //close
            FILE *g = fopen(filetowrite, "w"); //opens result.txt for writing
            fprintf(f, "he -> %ld\n", charfreq[0]);
            fprintf(f, "she -> %ld\n", charfreq[1]);
            fprintf(f, "they -> %ld\n", charfreq[2]);
            fprintf(f, "him -> %ld\n", charfreq[3]);
            fprintf(f, "me -> %ld\n", charfreq[4]);
            fclose(g);
        }}}
closedir(directory); //close dir
}
/**
  The specialcharcount function counts the frequency of the following 5 special words:
  "he"   "she"   "they"    "him"    "me"
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      charfreq - a pointer to a long array storing the frequency of the above 5 special words
      
      charfreq[0]: the frequency of "he"
      charfreq[1]: the frequency of "she"
      charfreq[2]: the frequency of "they"
      charfreq[3]: the frequency of "him"
      charfreq[4]: the frequency of "me"

  
  Output: a new file named as filetowrite with the frequency of the above 5 special words written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each of the above special words. The array 
  long charfreq[] always has the up-to-date frequencies of special words counted so far. If the word is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     he -> 20
     she -> 11
     they -> 20
     him -> 11
     me -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/

