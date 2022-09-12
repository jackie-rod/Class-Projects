//program description & implementation details, *****SEE ADDED IMPLEMENTATION SECTION*****
/**
  -----------------------------------------SPECIALCOUNTMULTHREADS FUNCTION
  The function counts the frequency of each special word (he, she, they, him and me  (case insensitive)) in all the .txt files under
  directory of the given path and writes the results to a file named as "filetowrite". Implemented the program using mutithreading and semaphores.

  -----------------------------------------INPUT:
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      specialfreq - a pointer to a long array storing the frequency of each special word "he","she","they","him", "me", which should be already up-to-date;
	      specialfreq[0] - > # of "he" counted
	      specialfreq[1] - > # of "she" counted
		  specialfreq[2] - > # of "they" counted
		  specialfreq[3] - > # of "him" counted
		  specialfreq[4] - > # of "me" counted
      num_threads - number of the threads running in parallel to process the files

  -----------------------------------------OUTPUT:
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in

  -----------------------------------------REQUIREMENTS:
    1)	Multiple threads are expected to run in parallel to share the workload, i.e. suppose 3 threads to process 30 files, then each thread should process 10 files;
    2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
    Thread id = 274237184 starts processing files with index from 0 to 10!
    3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
    Thread id = 265844480 is processing file input_11.txt
    4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
          Thread id = 274237184 is done !
    5)	The array: long specialfreq[ ] should always be up-to-date, i.e. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]

 -----------------------------------------IMPLEMENTATION:
   1)   EXECTHREAD FUNCTION
                *   The program contains a thread function "execthread" that successfully splits the amount of files inside the given directory by the number of threads.
                Execthreads keeps track of the current thread it is working with and processes the filenames[][] array according to the calculated range of target files.
                The function also uses semaphores to lock the data and prevent unwanted results and conflicts.

                *   Once the range of target files is determined the function announces it is starting, processes each file, and increments the respective global special
                frequency array as well as the file count. The semaphore is unlocked and the file stream is closed. This process is looped until the thread reaches the end target file.

                *   Thread announces its exit.

   2)   SPECIALCOUNTMULTHREADS FUNCTION
                *   The first task for this function is to add each file in the given path directory in the global filenames array. This is utilized through the dirent.h library.
                The function determines what type of file extension and concatenates the full path to the filenames array if it proves to be a txt type.
                The directory is closed as soon as all the files in the directory is added to the array.

                *   The function then focuses on the threads. It creates a thread id array based on the num_threads input arg and initializes the semaphore. The global thread_count is set to equal num_threads
                for global thread access. Function checks if arg is less than 3. The program creates threads using a for loop and checks for error using check int variable.
                The function then collects the thread processes using pthread.join.

                *   The global special freq array "sf[]" copies its elements to the input arg specialfreq[]. The semaphore is then destroyed.

                *   The last area of focus is the result file output. Using the filetowrite arg the program opens the target result file and writes the special freq of each special word.
                The target stream is closed and the file announces it is complete.

 RESULTS SHOULD LOOK LIKE THE FOLLOWING:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  � �

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 he -> 250932
 she -> 181764
 ... ...
 �  �
*/

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "count.h"      //program header
#include <dirent.h>     //file directory library
#include <string.h>     //string manipulation library, strcmp, strcat
#include <pthread.h>    //thread library
#include <semaphore.h>  //semaphore library

//GLOBALS
int threads_count;      //global thread count
int file_count = 0;     //global file count
char filenames[30][100];//global file list array

typedef struct{
    long sf[SPECIALSIZE];   //global specialfreq array
}args;

//SEMAPHORE VAR
pthread_mutex_t a_mutex = PTHREAD_MUTEX_INITIALIZER;

////--------------------------------------------------THREAD FUNCTION
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void* execthread(void* arg){
    //--------------------------------------------------thread variables
    //--------------------------------------------------thread variables
    args ar = *(args*)arg;
    int *currThread_ptr = (int*) arg;
    int currThread = *currThread_ptr;

    pthread_mutex_lock(&a_mutex);
    int start = (currThread-1) * (file_count / threads_count) + (currThread-1);
    //determine target files range end
    int end = start + (file_count/ threads_count);
    pthread_mutex_unlock(&a_mutex);

    //word buff for character processing in special freq file
    char wordBuff[50];
    printf("%d\n", currThread-1);
    //thread start announcement
    printf("Thread = %lu starts processing files with index from %d to %d!\n", pthread_self(), start, end);


    //--------------------------------------------------thread file processing implementation
    //--------------------------------------------------thread file processing implementation
    //thread starts to process each file in target range
    for (int i = start; i < end; i++) {
        //thread announces start of file processing
        printf("Thread = %lu is processing file %s\n", pthread_self(), filenames[i]);
        //thread opens target file
        FILE *wf = fopen(filenames[i], "r");
        //if target open
        if(wf){
            //uses program zero implementation of wordbuff
            while (fscanf(wf,"%s",wordBuff) ==1) {
                if((strcmp(wordBuff, "he")==0)||(strcmp(wordBuff, "He") == 0))
                    ar.sf[0]++; //increments global special freq
                if((strcmp(wordBuff, "she")==0)||(strcmp(wordBuff, "She") == 0))
                    ar.sf[1]++; //increments global special freq
                if((strcmp(wordBuff, "they")==0)||(strcmp(wordBuff, "They") == 0))
                    ar.sf[2]++; //increments global special freq
                if((strcmp(wordBuff, "him")==0)||(strcmp(wordBuff, "Him") == 0))
                    ar.sf[3]++; //increments global special freq
                if((strcmp(wordBuff, "me")==0)||(strcmp(wordBuff, "Me") == 0))
                    ar.sf[4]++; //increments global special freq
            }
            //thread closes current file stream
            fclose(wf);
        }}

    //thread announces completion
    printf("Thread = %lu is is done!\n", pthread_self());
    //thread exits, return 0 if successful
    pthread_exit(0);
}

////--------------------------------------------------SPECIAL COUNT WITH MULTIPLE THREADS FUNCTION
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void specialcountmulthreads(char *path, char *filetowrite, long specialfreq[], int num_threads)
{
    //--------------------------------------------------filenames array setup variables
    //--------------------------------------------------filenames array setup variables
    int len = 0; //length of current working filename
    int type[5]; //arr for comparison of txt extension, ".txt" + '/0'
    char fullpath[100]; //buffer arr for current full path of current file
    DIR* dir = opendir(path); //directory steam (closed)
    struct dirent* entity;  //creating struct access point for reading into directory
    entity = readdir(dir);// enter directory

    //failure to open directory --> return
    if(dir == NULL)
        return;
    else { //dir is open
        //get each file name until end of file list
        while ((entity = readdir(dir)) != NULL) {
            //pointer to current working filename
            char *filename;
            //pointer to struct access point of directory
            filename = entity->d_name;
            //length of filename
            len = strlen(filename) - 1;
            //get last 4 chars of filename
            type[0] = (entity->d_name)[len - 3];
            type[1] = (entity->d_name)[len - 2];
            type[2] = (entity->d_name)[len - 1];
            type[3] = (entity->d_name)[len];
            type[4] = '\0';
            //if txt extension
            if ((type[1] == 116) && (type[2] == 120) && (type[3] == 116)) {
                //concatenate path given to name of file
                strcpy(fullpath, path);
                strcat(fullpath, "/");
                strcat(fullpath, filename);
                //concatenate the fullpath to global filenames
                strcat(filenames[file_count], fullpath);
                //increment global file count
                file_count++;
            }}}
    //close directory
    closedir(dir);


    //--------------------------------------------------thread implementation
    //--------------------------------------------------thread implementation
    //var used for checking int failure
    int check;
    //array for thread ID's
    pthread_t tids[num_threads];
    // global threads_count equalds given arg num_threads for thread access
    threads_count = num_threads;
    //check if threads_count less than 3
    if (threads_count < 3) {
        printf("Usage: ./a.out num_threads input_1, input_2, ... input_30");
        exit(-1);
    }
    //initialize semaphore for threads
    //create threads using for loop
    for(int i = 0; i < threads_count; i++) {
        check = pthread_create(&tids[i], NULL, execthread, &i);
        if (check != 0) //check if return error
            printf("\nERROR: THREAD FAILURE :[%s]", strerror(check));
    }

    args arg;
    //collect threads after completion
    for(int i = 0; i < threads_count; i++)
        pthread_join(tids[i], NULL);
    //copies elements from global specialfreq to given arg special freq
    for(int i = 0; i < SPECIALSIZE; i++)
        specialfreq[i] = arg.sf[i];
    //destroy semaphore


    //--------------------------------------------------file output implementation
    //--------------------------------------------------file output implementation
    //write to output file , filetowrite arg
    FILE *inOutput = fopen(filetowrite, "w");
    //if output file is open
    if (inOutput) {
        //write frequencies based on local special freq array
        fprintf(inOutput, "he -> %ld\n", specialfreq[0]);
        fprintf(inOutput, "she -> %ld\n", specialfreq[1]);
        fprintf(inOutput, "they -> %ld\n", specialfreq[2]);
        fprintf(inOutput, "him -> %ld\n", specialfreq[3]);
        fprintf(inOutput, "me -> %ld\n", specialfreq[4]);
    } else  //if unable to open file
        printf("\nERROR: OUTPUT FILE UNABLE TO OPEN\n");
    //close output file stream
    fclose(inOutput);
    //completion announcement
    printf(" \nDONE\n");
}
