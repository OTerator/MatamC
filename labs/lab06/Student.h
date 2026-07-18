#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef STUDENT
#define STUDENT



#define MAX_COURSES  100
#define NO_GRADE    -1
#define NAME_LENGTH  64
#define ID_LENGTH  16
typedef unsigned int Course;
typedef int Grade;


typedef struct Student
{
   char* name;
   char* id;
   Grade* grades;
} Student;

Student* StudentCreate(const char* name, const char* id);
void StudentDestroy(Student* student);
void StudentSetGrade(Student* student, Course course, Grade grade);
Grade StudentGetGrade(Student* student, Course course);


#endif //STUDENT