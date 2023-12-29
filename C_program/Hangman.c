/*This is a hangman game, the objective is to guess the word
using only the space provided. If the user answer incorrectly
the image changes to a hanged stick figure as it progresses.*/

// Copyright 2023 Wilmer Soriano
// This file is part of the Hangman and is licensed
// under the terms of the Gnu General Public License version 3 or
// any later version, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 1
#define MAX_WRONG 6

void pressEnter();
void Guide();
void displayHangman(int guess);
char* getWord(int level); 
int Checking(char *used, char *reveal,const char *word, int *guess, int* attempt);

int main(void)
{
   int again = 1;
   char *word = (char*)malloc(sizeof(char) * 25); //MA
   char *used = (char*)malloc(sizeof(char) * 30);
   char *reveal = (char*)malloc(sizeof(char) * 25);

   printf("\t\t|================================|\n");
   printf("\t\t  |===== WELCOME TO HANGMAN =====|\n");
   printf("\t\t|================================|\n");
   printf("\n\n\t\t╰(*°▽°*)╯Let's begin!!!\n\n\t\t\t");

   pressEnter();
   Guide();
   pressEnter();

   for(int a=0;a<20;a++)//prints a set of blank space to make interface more appealing.
   printf("\n");

   while (again != 0)  //===The start of the game ===
   {
      int guess = 0, level = 0, attempt = 0;  // These variables must reset everytime user want's to play again

      printf("\nChoose your difficulty (1)Easy, (2)Medium, (3)Hard:");
      scanf("%d",&level);
      word = getWord(level);

      while((guess != MAX_WRONG) && (strcmp(word, reveal)))//Purpose is to maintain the player guessing the hidden word until condtion is met.
      {
         displayHangman(guess);
         guess = guess + Checking(used, reveal, word, &guess, &attempt);

         for(int a=0;a<20;a++)
         printf("\n");
      }

      printf("Do you want to play again?\nEnter your choice (1) for \"yes\", (0) for \"no\" : ");
      scanf("%d", &again);

      free(word);
      free(used);
      free(reveal);
      word = NULL; //free memory and null to prevent future issue and clear the words used before.
      used = NULL;
      reveal = NULL;

      if (again != 0) //If the player decide to play again, I ensure to allocate the necessary memory for these characters.
      {
         word = (char*)malloc(sizeof(char) * 25);
         used = (char*)malloc(sizeof(char) * 30);
         reveal = (char*)malloc(sizeof(char) * 25);
      }
   }//===The end of the game

   printf("\n\nThank you for playing! please play again soon!\n");
   printf("[Exiting Game...]");
   return 0;
}

char* getWord(int level)
{
   srand(time(NULL));
   FILE* file = NULL;
   int max_words, rand_num;
   char* filename;
   char* word = (char*)malloc(sizeof(char) * 25);

   switch(level) //Using the intenger select the level
   {
      case 1:
         printf("You have chosen Easy!\n");
         filename = "easy.txt";          //Save the string name of the file
         max_words = 500;               //including the maximum word inside the file
         break;
      case 2:
         printf("You have chosen Medium!\n");
         filename = "medium.txt";
         max_words = 2500;
         break;
      case 3:
         printf("You have chosen Hard!\n");
         filename = "hard.txt";
         max_words = 2026;
         break;
      default:
      printf("\n\nWait hold on...Sorry, your input doesn't match any of my data\n"); //If the intenger is not withint scale, display error message
      printf("please try again");
      printf("\n[Exisitng Game...]");
      exit(DEBUG);
   }

   file = fopen(filename, "r");   //else proceed to openfile 
   if(file == NULL)
   {
      printf("File failed to open\n");
      printf("[Exiting game...]");
      fclose(file);
      exit(DEBUG);
   }
   else
   {
      int a;
      rand_num = 1 + rand() % max_words; //Grab a random value 
      for(a = 0; a < rand_num; a++)
      {
         fscanf(file, "%s", word);     //access that line based on random value
      }
      fclose(file);
   }
   return word;
}

void pressEnter()
{
   printf("[Press Enter]");
   while (getchar() != '\n'); // Clear input buffer, wait until user presses enter.
}

void Guide()//A Guide to help the user understand the game
{
   printf("\n\t\t\t    RULES:\n•The game is simple, enter the correct letter to solve for a word.\n");
   pressEnter();
   printf("\n•You'll be given 3 sets of diffculty with (1) easy , (2) hard, (3)hard\n");
   printf("The amount of attempt's won't change but the word would be much harder to guess\n");
   pressEnter();
   printf("\nThe game is design to be winable, meaning if you decide to press the same letter again\n");
   printf("which was previously used as a correct answer, no penality will be counted.\n");
   pressEnter();
   printf("\n•If correct! proceed to the next missing letter until\n");
   printf("the word is spelled out, in which case you Win!\n");
   pressEnter();
   printf("\n•If wrong! Stick man Steve is formed, based on the number\n");
   printf("of attempts made per letter. If Stick man Steve is formed, you Lose!\n");
   pressEnter();
   printf("\n\n•If your ready to start: ");
}

void displayHangman(int guess)
{
   switch(guess)
   {
      case(0):
         printf("------|\n");
         printf("|     |\n");
         printf("|\n");
         printf("|\n");
         printf("|\n");
         printf("|\n");
         printf("|\n");
         printf("-------------\n");
         break;
      case(1):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|\n");
         printf("|\n");
         printf("|\n");
         printf("|\n");
         printf("-------------\n");
         break;
      case(2):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|     |\n");
         printf("|     |\n");
         printf("|     |\n");
         printf("|\n");
         printf("-------------\n");
         break;
      case(3):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|     |\n");
         printf("|    /|\n");
         printf("|     |\n");
         printf("|\n");
         printf("-------------\n");
         break;
      case(4):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|     |\n");
         printf("|    /|\\\n");
         printf("|     |\n");
         printf("|\n");
         printf("-------------\n");
         break;
      case(5):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|     |\n");
         printf("|    /|\\\n");
         printf("|     |\n");
         printf("|    /\n");
         printf("-------------\n");
         break;
      case(MAX_WRONG):
         printf("------|\n");
         printf("|     |\n");
         printf("|     0\n");
         printf("|     |\n");
         printf("|    /|\\\n");
         printf("|     |\n");
         printf("|    / \\\n");
         printf("-------------\n");
         break;
   }
}

int Checking(char *used, char *reveal,const char *word, int *guess, int* attempt)
{
   int check;
   printf("Used letter: ");
   for (int i = 0; i < *attempt; i++)
   {
      printf(" %c", used[i]);
   }

   printf("\nNumber of bad guesses:%d (out of 6)\n\n", *guess); //Promps the player attempts left while
   for(check = 0; check <strlen(word); check++)            //revealing which word the player has guessed
   {
      if(reveal[check] == word[check])
      {
         printf("%c", word[check]);
      }
      else
      {
         printf("-");
      }
   }

   printf("\n\nEnter a Letter: ");
   scanf(" %s", &used[*attempt]);
   int correct = 0;

   
   for(check = 0; check < strlen(word); check++) //Check's if the player letter is correct to hidden word
   {
      if (used[*attempt] == word[check])
      {
         reveal[check] = word[check];
         correct++; // Increment the count of correctly guessed characters
      }
   }
   
   (*attempt)++; //Derefrance and increment to next empty character to be used next time

   if(correct >= DEBUG) //If player is able to get 1 or more letter out the word go here...
   {
      if (strcmp(word,reveal) == 0) 
      {
         printf("\n\nYAYA!!! Steve the Stick man is SAVED!!! YOU WIN!\n");
         printf("\t\tYour word was [ %s ]",word);
         return 0;
      }
   }
   else//otherwise, it must be wrong to increment and check if the player has lost the game
   {
      (*guess)++;
      if(*guess == MAX_WRONG)
      {
         printf("\n\n\nOH NO YOU LOST! NOOO!... Steve the stick man is dead :( \n");
         printf("\nThe correct answer is: [ %s ]", word);
         return 0;
      }
   }
   return 0;
}