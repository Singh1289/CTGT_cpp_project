/*
    Program to calculate the score for a quiz based on the student's answers. 
    The program should prompt the user for answers to a fixed number of questions, 
    compare them with the correct answers, and compute the total score.
*/

#include<stdio.h>
#include<string.h>

#define QUES_COUNT 5

// structure for question and answer
struct Questions{
   char question[QUES_COUNT][200];
   char options[QUES_COUNT][4][50];
   char correct[QUES_COUNT];
};
 
struct Answer{
    char ansIndex[QUES_COUNT];  
}Answer;

void initializeMenu(struct Questions*);
void startQuiz();
void getResult(struct Questions*,struct Answer*);


int main()
{
    // starting quiz
    startQuiz();
    return 0;
}

// hard-coded question
void initializeQuiz(struct Questions *ques)
{
    strcpy(ques->question[0], "Q1. Question for testing quiz? ");
    strcpy(ques->question[1], "Q2. Question for testing quiz? ");
    strcpy(ques->question[2], "Q3. Question for testing quiz? ");
    strcpy(ques->question[3], "Q4. Question for testing quiz? ");
    strcpy(ques->question[4], "Q5. Question for testing quiz? ");

    strcpy(ques->options[0][0], "a. Option A");
    strcpy(ques->options[0][1], "b. Option B");
    strcpy(ques->options[0][2], "c. Option C");
    strcpy(ques->options[0][3], "d. Option D");

    strcpy(ques->options[1][0], "a. Option A");
    strcpy(ques->options[1][1], "b. Option B");
    strcpy(ques->options[1][2], "c. Option C");
    strcpy(ques->options[1][3], "d. Option D");

    strcpy(ques->options[2][0], "a. Option A");
    strcpy(ques->options[2][1], "b. Option B");
    strcpy(ques->options[2][2], "c. Option C");
    strcpy(ques->options[2][3], "d. Option D");

    strcpy(ques->options[3][0], "a. Option A");
    strcpy(ques->options[3][1], "b. Option B");
    strcpy(ques->options[3][2], "c. Option C");
    strcpy(ques->options[3][3], "d. Option D");

    strcpy(ques->options[4][0], "a. Option A");
    strcpy(ques->options[4][1], "b. Option B");
    strcpy(ques->options[4][2], "c. Option C");
    strcpy(ques->options[4][3], "d. Option D");

    ques->correct[0] = 'a';
    ques->correct[1] = 'a';
    ques->correct[2] = 'b';
    ques->correct[3] = 'd';
    ques->correct[4] = 'c';
}


// stat quiz ask user to select from the answer
void startQuiz() {
    struct Questions ques;
    struct Answer ans;
    char temp;
    initializeQuiz(&ques);

    for (int i = 0; i < QUES_COUNT; i++) {
        printf("\n%s", ques.question[i]);
        for (int j = 0; j < 4; j++) 
        {
            printf("\n %s", ques.options[i][j]);
        }

        while(1)
        {
            printf("\nEnter your answer: ");
            scanf("%c", &temp);
            getchar();
            if(temp>96 && temp<101)
            {
                ans.ansIndex[i] = temp;
                break;
            }
            printf("\nChoose valid number!");
        }
    }
    getResult(&ques, &ans);
}


// calculate the result of these question
void getResult(struct Questions *ques, struct Answer *ans) {
    int right = 0, wrong = 0;
    for (int i = 0; i < QUES_COUNT; i++) {
        if (ques->correct[i] == ans->ansIndex[i]) 
            right += 1;
        else
            wrong += 1;
    }

    printf("\nWrong: %d   Right: %d/%d\n", wrong, right, QUES_COUNT);
}