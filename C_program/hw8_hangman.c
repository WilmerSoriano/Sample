/*This is a hangman game, the objective is to guess the word
using only the space provided. If the user answer incorrectly
the image changes to a hanged stick figure.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 1
#define MAX_WRONG 6
#define MAX_WORDS 2600

    void Level();

int main(){
    int cont;
    char enter;
    if (DEBUG == 1) {
        srand(1);
    }
    else {
        srand(time(NULL));
    }

    printf("Do you want to play? Enter your choice (1-yes, 0-no): ");
    scanf("%d", &cont );
    while (cont!=0){
        Level();
		printf("Do you want to play again? Enter your choice (1-yes, 0-no): ");
        scanf("%d", &cont);
    }
    printf("\nThank you for playing our game! Goodbye!");
}
void Level(){
    // ===============Calls and sets up Files based on level=====================
    int level;
    int ran_num=0;
    char ran_word[50];
    FILE *f1=NULL;
    FILE *f2=NULL;
    FILE *f3=NULL;
    printf("Choose your difficulty (1-easy, 2-medium, 3-hard):");
    scanf("%d",&level);
    switch (level){
        case 1:
            printf("you have chosen easy\n");
            f1=fopen("easy.txt","r");
                ran_num=1+rand()%500;
                if(f1==NULL){
                printf("File can not be open");
                exit(0);
                }
                for(int k=0; k<=ran_num;k++){
                    fscanf(f1,"%s",ran_word);
                }
                break;
        case 2:
            printf("you have chosen medi\n");
            f2=fopen("medium.txt","r");
                ran_num=1+rand()%2500;
                if(f2==NULL){
                printf("File can not be open");
                exit(0);
                }
                for(int k=0; k<=ran_num;k++){
                    fscanf(f2,"%s",ran_word);
                }
                break;
        case 3:
            printf("you have chosen hard\n");
            f3=fopen("hard.txt","r");
                ran_num=1+rand()%2026;
                if(f3==NULL){
                printf("File can not be open");
                exit(0);
                }
                for(int k=0; k<=ran_num;k++){
                    fscanf(f3,"%s",ran_word);
                }
                break;
}
//========================end of Files, begin to reveal answer and index======================
    printf("rand index=%d\n",ran_num+1);
    printf("-----hidden word:|%s|\n",ran_word);
    for(int s=0;s<20;s++){ //creates a large space
        printf("\n");
    }
//=======================end of reveal, begin to stay in do/ while loop, begin to form hangman=======================
int guess=0,attempt=0,correct=0,input=0, current=0, previous_correct=0, wrong=0;
int num=-1;
int check,Total;
char hidden[25]={'-'};
char letter[25]={};
char revealed[26];
        Total=strlen(ran_word);// This is the number of words you need to get correct!
do{
    if((previous_correct==correct)&&(attempt>=1)||((wrong>correct)&&(attempt>=1))){//after the 1st attempt
            guess++;                                                              //it checks if you had any wrong answer repeated or not
    }
        if(guess==0){
        printf("------|\n");
        printf("|     |\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("|\n");
        printf("-------------\n");
        }
    else{
        switch(guess){
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
//======================end of hangman, STILL inside a loop, begin to reveal used letter, Num of guess==============================
    printf("Used letter:%s\n",letter);
    printf("Number of bad guesses:%d (out of 6)\n\n",guess);
    current=0;//reset
    for(check=0;check<strlen(ran_word);check++){// update:complete
        if(revealed[check]==ran_word[check]){
            printf("%c",ran_word[check]);
            current++;   //adds to how many you currently have right!!
        }
        else{
            printf("%s",hidden);
        }
    }
//==========================end of reveal/num of guess, STILL inside a loop, begin to ask and check answer========================

    if ((!(guess==MAX_WRONG))&&(!(current==Total))){// determines if u passed or not.
            previous_correct=correct;//before reset save your previous correct here.
            correct=0;//RESET
            wrong=0;
    printf("\n\nEnter a letter:");
    num++;
    scanf("%s",&letter[num]);
    attempt=attempt+1;//This is for computer to determine.
    for(check=0;check<attempt;check++){
        if(revealed[check]==letter[num]){//before, check if user has used this word before for correct answer
            wrong=50;//Even if the user had 3 correct words 1 'wrong' is still bigger.
        }
        else{
            continue;
        }
    }
    input=0; //RESET, this would update by it self to check every user letter and attempt
    do{
        for(check=0;check<strlen(ran_word);check++){//This would only check and confirm the correct answer
            if(letter[input]==ran_word[check]){
                revealed[check]=ran_word[check];
                correct++; //1 correct letter per try
            }
            else {
                continue;
            }
        }
        input++;
    }while(input<attempt);// it checks from 0 to all the way from number of'attempt'
    for(int a=0;a<20;a++){
    printf("\n");
    }
}
    else {
        break;//if somehow it made it here then break and check the condition for final'while'
    }
    if(current==Total){       //This is only for ALL correct answer, it prevents it from going to final condition and complete it.
        current=current-1;   //why? so we can print one last hangman, then we can leave loop.
    }
//===========================end of checking, determine if computer should stay within loop or leave============================

}while((!(guess==MAX_WRONG))&&(!(current==Total)));//final condition. checks the total of wrong OR total of correct. with true statement(which is false).
    if(guess==MAX_WRONG){                         //if any of them is false it would leave(which is true)
        printf("\nSorry. You lost. Better luck next time\n");
        printf("The word was: %s\n\n",ran_word);
    }
    else{
        printf("\n\nYou won!\n\n");
    }
}