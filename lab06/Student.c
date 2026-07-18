#include "Student.h"

Student* StudentCreate(const char* name, const char* id) {

   Student* student = (Student*) malloc(sizeof(Student));
   if (student == NULL) {
      fprintf(stderr, "Student memory allocation failed.\n");
      exit(1);
   }
   
   student -> name = (char*) malloc(sizeof(char) * NAME_LENGTH);
   if (student -> name == NULL) {
      fprintf(stderr, "Name memory allocation failed.\n");
      exit(1);
   }
   
   student -> id = (char*) malloc(sizeof(char) * ID_LENGTH);
   if (student -> id == NULL) {
      fprintf(stderr, "ID memory allocation failed.\n");
      exit(1);
   }

   student -> grades = (Grade*) malloc(sizeof(Grade) * MAX_COURSES);
   if (student -> grades == NULL) {
      fprintf(stderr, "Grades memory allocation failed.\n");
      exit(1);
   }

   strcpy(student -> name, name);
   strcpy(student -> id, id);
   for(int i = 0; i < MAX_COURSES; i++) {
      (student -> grades)[i] = NO_GRADE;
   }

   return student;
}


void StudentDestroy(Student* student) {

   free(student -> name);
   free(student -> id);
   free(student -> grades);

   free(student);
}


void StudentSetGrade(Student* student, Course course, Grade grade) {

   if(course >= MAX_COURSES || grade < -1 || grade > 100) {
      fprintf(stderr, "Error in %s at line %d.\n", __FILE__, __LINE__);
      exit(1);
   }
   
   (student -> grades)[course] = grade;
}

Grade StudentGetGrade(Student* student, Course course) {
   
   if(course >= MAX_COURSES || (student -> grades)[course] < -1 || (student -> grades)[course] > 100) {
      fprintf(stderr, "Error in %s at line %d.\n", __FILE__, __LINE__);
      exit(1);
   }

   return (student -> grades)[course];
}