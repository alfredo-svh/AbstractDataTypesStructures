#include <stdio.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
   FILE *fp;
   char word[31];
   int counter=0;


   if(argc!=2){ //there must be 2 arguments
      printf("Text file is missing");
      return 0;
   }   

   fp=fopen(argv[1], "r"); //open file of second argument for reading
   while (fscanf(fp, "%s", word)==1){ //counter increases on for each word of the file
      counter++;
   }   
   fclose(fp); //closes file
   printf("%d total words\n", counter); //prints counter
   return 0;
}
