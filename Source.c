#define _CRT_SECURE_NO_WARNINGS
#define MAX_COUNT 3
#define FILE_ERROR "There was an error opening the file"
#define NUMBER_OF_LABS 1
#define NUMBER_OF_EXAMS 1
#define LABS_WEIGHT .4f
#define EXAMS_WEIGHT .4f
#define FINAL_WEIGHT .2f
#define GPA_FILE "StudentsByGpa.txt"
#define NAMES_FILE "StudentsByName.txt"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct students{
  char firstName[15];
  char lastName[20];
  float percentGrade;
  char letterGrade;
};
typedef struct students STUDENTS;

void calcPercent(float *);
void calcLabs(float *);
void calcExams(float *);
void calcFinal(float *);
void calcLetterGrade(float, char *);
void enterStudents(STUDENTS[], int *);
void sortByName(STUDENTS[], int);
void sortByGpa(STUDENTS[], int);
void displayStudents(STUDENTS[], int);
void writeStudents(STUDENTS[], int, char[]);

int main()
{
  int selection = 0;
  STUDENTS students[30];
  int studentCount = 0;
  
  do {
    printf("\nSelect an Option (0-5)\n");
    printf("\n1. Enter Students");
    printf("\n2. GPA to Screen");
    printf("\n3. GPA to File");
    printf("\n4. Names to Screen");
    printf("\n5. Names to File");
    printf("\n0. Exit\n");
    printf("\nEnter your Selection: ");
    scanf("%d", &selection);

    switch (selection)
    {
    case 0:
      break;
    case 1: enterStudents(students, &studentCount);
      break;
    case 2: sortByGpa(students, studentCount);
      displayStudents(students, studentCount);
      break;
    case 3: sortByGpa(students, studentCount);
      writeStudents(students, studentCount, GPA_FILE);
      break;
    case 4: sortByName(students, studentCount);
      displayStudents(students, studentCount);
      break;
    case 5: sortByName(students, studentCount);
      writeStudents(students, studentCount, NAMES_FILE);
      break;
    default: printf("Enter 0-5");
      break;

    }
  } while (selection);

  system("pause");
  return(0);
}

void enterStudents(STUDENTS students[], int * ptr_studentCount)
{
  char firstName[15];
  char lastName[20];
  char letterGrade;
  float percentGrade = 0.0f;
  printf("Enter student's first name: ");
  fflush(stdin);
  scanf(" %14[^\n]s", firstName);
  while (firstName[0] != '0' && *ptr_studentCount < MAX_COUNT)
  {

    printf("enter student's last name: ");
    fflush(stdin);
    scanf(" %19[^\n]s", lastName);

    calcPercent(&percentGrade);
    calcLetterGrade(percentGrade, &letterGrade);
    strcpy(students[*ptr_studentCount].firstName, firstName);
    strcpy(students[*ptr_studentCount].lastName, lastName);
    students[*ptr_studentCount].percentGrade = percentGrade;
    students[*ptr_studentCount].letterGrade = letterGrade;
    (*ptr_studentCount)++;

    
    if (*ptr_studentCount == MAX_COUNT - 1)
    {
      printf("\nClass is full after one more student.");
    }
    else if (*ptr_studentCount == MAX_COUNT)
      printf("The class is full. Enter (0) to return to the menu");
    printf("\nEnter student's first name or (0) to Exit: ");
    fflush(stdin);
    scanf(" %14[^\n]s", firstName);
  }

}

void sortByName(STUDENTS students[], int studentCount)
{
  STUDENTS temp;
  int i;
  int x;

  
  for (x = 0; x<studentCount; x++)
  {
    for (i = 0; i<studentCount - 1 - x; i++)
    {
      /* Sort students by last name or by first name if the last names
       are the same.*/
      if (strcmp(students[i].lastName, students[i + 1].lastName) > 0 ||
        strcmp(students[i].lastName, students[i + 1].lastName) == 0 &&
        strcmp(students[i].firstName, students[i + 1].firstName) > 0)
      {
        temp = students[i];
        students[i] = students[i + 1];
        students[i + 1] = temp;
      }
    }
  }
}

void sortByGpa(STUDENTS students[], int studentCount)
{
  STUDENTS temp;
  int i;
  int x;

  for (x = 0; x < studentCount; x++)
  {
    for (i = 0; i < studentCount - 1 - x; i++) 
    {
      if (students[i].percentGrade < students[i + 1].percentGrade)
      {
        temp = students[i];
        students[i] = students[i + 1];
        students[i + 1] = temp;
      }
    }
  }
}

void displayStudents(STUDENTS students[], int studentCount)
{
  int i;
  printf("%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  for (i = 0; i < studentCount; i++)
  {
    printf("\n%-10s%-20s%6.2f % 10c", students[i].firstName, students[i].lastName, students[i].percentGrade, students[i].letterGrade);
  }
  printf("\n\nTotal Students - %d", studentCount);
}

void writeStudents(STUDENTS students[], int studentCount, char fileType[])
{
  // Open the file
  FILE * rpt;
  rpt = fopen(fileType, "w");
  int i;
  if (rpt == NULL)
  {
    printf(FILE_ERROR);
    fflush(stdin); getchar();
    exit(0);
  }
  // Write file headings
  fprintf(rpt, "%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  for (i = 0; i < studentCount; i++)
  {
    fprintf(rpt, "\n%-10s%-20s%6.2f % 10c", students[i].firstName, students[i].lastName, students[i].percentGrade, students[i].letterGrade);
  }
  fprintf(rpt, "\n\nTotal Students - %d", studentCount);
  fclose(rpt);
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