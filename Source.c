#define _CRT_SECURE_NO_WARNINGS
#define MAX_COUNT 3
#define FILE_ERROR "There was an error opening the file"
#define NUMBER_OF_LABS 1
#define NUMBER_OF_EXAMS 1
#define LABS_WEIGHT .4f
#define EXAMS_WEIGHT .4f
#define FINAL_WEIGHT .2f
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
void sortByGpa(void);
void displayStudents(STUDENTS[], int);
void writeStudents(void);

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
    case 2: sortByGpa();
      displayStudents(students, studentCount);
      break;
    case 3: sortByGpa();
      writeStudents();
      break;
    case 4: sortByName(students, studentCount);
      displayStudents(students, studentCount);
      break;
    case 5: sortByName(students, studentCount);
      writeStudents();
      break;
    default: printf("Enter 0-5");
      break;

    }
  } while (selection);

  system("pause");
  return(0);
  /*  
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
  // End Program */
 
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
    printf("\nEnter student's first name: ");
    fflush(stdin);
    scanf(" %14[^\n]s", firstName);
  }

}
void sortByName(STUDENTS students[], int studentCount)
{
  STUDENTS temp;
  int i;
  int x;

  //do i need to swap
  for (x = 0; x<studentCount; x++)
  {
    for (i = 0; i<studentCount - 1 - x; i++)
    {
      //if the name is larger
      //if the last name is larger OR
      //   the last name is the same AND
      //   the first name is larger

      //concat
      if (strcmp(students[i].lastName, students[i + 1].lastName) > 0)
      {
        temp = students[i];
        students[i] = students[i + 1];
        students[i + 1] = temp;
      }
    }
  }
}

void sortByGpa(void)
{
  printf("sorting students by gpa");
}
void displayStudents(STUDENTS students[], int studentCount)
{
  int i;
  printf("%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  for (i = 0; i < studentCount; i++)
  {
    printf("\n%-15s%-20s%6.2f%10c", students[i].firstName, students[i].lastName, students[i].percentGrade, students[i].letterGrade);
  }
}
void writeStudents(void)
{
  printf("writing students");
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