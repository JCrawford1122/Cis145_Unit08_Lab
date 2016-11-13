#define _CRT_SECURE_NO_WARNINGS
#define MAX_COUNT 30
#define FILE_ERROR "There was an error opening the file"
#define NUMBER_OF_LABS 8
#define NUMBER_OF_EXAMS 3
#define LABS_WEIGHT .4f
#define EXAMS_WEIGHT .4f
#define FINAL_WEIGHT .2f
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void calcPercent(float *);
void calcLabs(float *);
void calcExams(float *);
void calcFinal(float *);
void calcLetterGrade(float, char *);

int main()
{
  int studentCount = 0;
  char studentName[30];
  char *ptr_studentName = studentName;
  char letterGrade;
  float percentGrade;
  // Open the file
  FILE * rpt;
  rpt = fopen("grades.txt", "w");
  if (rpt == NULL)
  {
    printf(FILE_ERROR);
    fflush(stdin); getchar();
    exit(0);
  }
  // Write file headings
  fprintf(rpt, "%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  // Get the student name
  // Couldn't get the program to not blow up if the string for the name
  // was to long. Added instructions for user to limit characters
  printf("Enter student name (First, Last)(limit 30 characters) or (0) to exit: ");
  fflush(stdin);
  scanf(" %29[^\n]s", studentName);
  while (studentName[0] != '0' && studentCount <= MAX_COUNT)
  {
    percentGrade = 0;
    calcPercent(&percentGrade);
    calcLetterGrade(percentGrade, &letterGrade);
    fprintf(rpt, "\n%-30s%6.2f%10c", studentName, percentGrade, letterGrade);
    studentCount++;
    printf("\nEnter student name (First, Last) or (0) to exit: ");
    fflush(stdin);
    scanf(" %29[^\n]s", studentName);
  }
  fprintf(rpt, "\n\n%d %s", studentCount, " Total Students");
  // Close the file
  fclose(rpt);
  // End Program
  return(0);
}

void calcPercent(float *ptr_percentGrade)
{
  float labs = 0;
  float exams = 0;
  float final = 0;
  float total = 0;
  calcLabs(&labs);
  calcExams(&exams);
  calcFinal(&final);
  total = labs + exams + final;
  *ptr_percentGrade = total;
}

void calcLabs(float *ptr_labs)
{
  int i;
  float score;
  for (i = 0; i < NUMBER_OF_LABS; i++)
  {

    printf("%s %d %s", "Enter lab", i + 1, "score: ");
    fflush(stdin);
    scanf(" %f", &score);
    *ptr_labs += score;
  }
  *ptr_labs /= NUMBER_OF_LABS;
  *ptr_labs *= (float)LABS_WEIGHT;
}

void calcExams(float *ptr_exams)
{
  int i;
  float score;
  for (i = 0; i < NUMBER_OF_EXAMS; i++)
  {
    printf("%s %d %s", "Enter exam", i + 1, "score: ");
    fflush(stdin);
    scanf(" %f", &score);
    *ptr_exams += score;
  }

  *ptr_exams /= NUMBER_OF_EXAMS;
  *ptr_exams *= EXAMS_WEIGHT;
}

void calcFinal(float *ptr_final)
{
  float score;
  printf("Enter final exam score :");
  fflush(stdin);
  scanf(" %f", &score);

  *ptr_final = score;
  *ptr_final *= (float)FINAL_WEIGHT;
}

void calcLetterGrade(float percentGrade, char *ptr_letterGrade)
{
  if (percentGrade >= 94)
    *ptr_letterGrade = 'A';
  else if (percentGrade >= 85)
    *ptr_letterGrade = 'B';
  else if (percentGrade >= 75)
    *ptr_letterGrade = 'C';
  else if (percentGrade >= 65)
    *ptr_letterGrade = 'D';
  else
    *ptr_letterGrade = 'F';
}