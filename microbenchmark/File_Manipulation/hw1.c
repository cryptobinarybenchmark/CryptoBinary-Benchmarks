/* Name, hw1.c, CS 24000, Fall 2018
 * Last updated August 30, 2018 
 */

/* Add any includes here */

#include "hw1.h"
#include <stdio.h>

/* This function computes the average of the final_score
 * which belongs to the students who are in the same 
 * section as the passed int section_num
 */

float get_section_average(char *filename, int section_num){
  char student_name[30];
  int student_id;
  int final_score;
  int section_no;
  float sum = 0;
  float total = 0;
  float average = 0;
  int return_value = 0;
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    return FILE_READ_ERR;
  }
  else if ((section_num <= 0) || 
          (section_num >= 10)) {
    fclose(fp);
    return BAD_SECTION;
  }
  while(1){
    return_value = fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                          &student_id, &final_score, &section_no);
    if (return_value == -1){
      break;
    }       
    if (student_name[0] == '\0') {
	    fclose(fp);
	    return NO_STUDENTS;
    }
    if (return_value == 4) {
	    if (section_no == section_num) {
        total++;
        sum = sum + final_score;
      }
    }
    else { 
	    fclose(fp);
      return BAD_RECORD;
    }
  }
  if (total == 0) {
    fclose(fp);
    return NO_STUDENTS;
  }
  average =  sum/total;
  fclose(fp);
  return average;
}/* get_section_average() */

/*  This function returns the highest final_score
 *  among all students in the file filename 
 */

int get_top_score(char *filename){
  char student_name[30];
  int student_id;
  int final_score;
  int section_no;
  int top_score = 0;
  int return_value = 0;
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    return FILE_READ_ERR;
  }
  fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                          &student_id, &final_score, &section_no);
  while(feof(fp) == 0){
		    if (student_name[0] == '\0') {
      fclose(fp);
      return NO_STUDENTS;
    }
    if (return_value == 4) {
      if(final_score > top_score){
                top_score = final_score;
            }
    }
    fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                          &student_id, &final_score, &section_no);
  }

  while(1) {
    return_value = fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                          &student_id, &final_score, &section_no);
    if (return_value == -1){
    break;
    }
    if (student_name[0] == '\0') {
      fclose(fp);
      return NO_STUDENTS;
    }
    if (return_value == 4) {
      if(final_score > top_score){
  		top_score = final_score;
	    }
    } 
    else {
      fclose(fp);
      return BAD_RECORD;
    }
  }
  fclose(fp);
  return top_score;
}/* get_top_score() */

/* This function returns the number of students
 * whose final_score is lower than passed int cutoff
 * and writes student name, corresponded final score and 
 * section number into file out_file
 */

int create_fail_list(char *in_file, char *out_file,
                     int cutoff){
  char student_name[30];
  int student_id;
  int final_score;
  int section_no;
  int total=0;
  int return_value = 0;
  FILE *fp;
  FILE *fpw;
  fp = fopen(in_file, "r");
  if (fp == NULL) {
    return FILE_READ_ERR;
  }
  fpw = fopen(out_file, "w");
  if (fpw == NULL) {
    fclose(fp);
	  return FILE_WRITE_ERR;
  }
  if ((cutoff <= 0) || 
      (cutoff > 100)) {
    fclose(fp);
    fclose(fpw);
    return BAD_CUTOFF;
  }
  while(1) {
    return_value = fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                           &student_id, &final_score, &section_no);
    if (return_value == -1) {
    break;
    }
    if (student_name[0] == '\0') {
      fclose(fp);
	    fclose(fpw);
      return NO_STUDENTS;
    }
    if (return_value == 4) {
      if (final_score < cutoff) {
		    total++;
	      fprintf(fpw, "%d - %d - %s\n", section_no, 
                  student_id, student_name);
      }
    }
    else {
	    fclose(fpw);
      fclose(fp);
      return BAD_RECORD;
    }
  }
  if( total == 0) {
    fclose(fpw);
    fclose(fp);
    return NO_STUDENTS;
  }
  fclose(fpw);
  fclose(fp);
  return total;                     
} /* reate_fail_list() */

/* This function returns the number of students
 * in the same section as passed int section_num
 * It also determines students' letter grades 
 * depends on different final score cutoff
 * and writes student id, letter grade into file out_file
 */

int create_grade_report(char *in_file, char *out_file,
                        int section_num){
  char student_name[30];
  int student_id;
  int final_score;
  int section_no;
  int total=0;
  int return_value = 0;
  FILE *fp;
  FILE *fpw;
  fp = fopen(in_file, "r");
  if (fp == NULL) {
    return FILE_READ_ERR;
  }
  fpw = fopen(out_file, "w");
  if (fpw == NULL) {
    fclose(fp);
    return FILE_WRITE_ERR;
  }
  if ((section_num <= 0) || 
      (section_num >= 10)) {
    fclose(fpw);
    fclose(fp);
    return BAD_SECTION;
  }
  while(1) {
    return_value = fscanf(fp, "%[^;];%d;%d%%;%d\n",student_name,
                          &student_id, &final_score, &section_no);
    if (return_value == -1) {
      break;
    }
    if (student_name[0] == '\0') {
      fclose(fp);
      fclose(fpw);
      return NO_STUDENTS;
    }
    if (return_value == 4) {
	    if (section_num == section_no) {
		    total++;
        if (final_score >= 90) {
          fprintf(fpw, "%d: %c\n", student_id,'A');
        }
	      else if (final_score >= 80) {
          fprintf(fpw, "%d: %c\n", student_id,'B');
        }
	      else if (final_score >= 70) {
          fprintf(fpw, "%d: %c\n", student_id,'C');
        }
	      else if (final_score >= 60) {
          fprintf(fpw, "%d: %c\n", student_id,'D');
        }  
	      else {
          fprintf(fpw, "%d: %c\n", student_id,'F');          } 
	    }
    }
    else {
      fclose(fpw);
      fclose(fp);
      return BAD_RECORD;
    }
  }
  if (total == 0) {
    fclose(fpw);
    fclose(fp);
    return NO_STUDENTS;
  }
  fclose(fpw);
  fclose(fp);
  return total;
} /* create_grade_report() */

/* Remember, you don't need a main function!
 * it is provided by hw1_main.c or hw1_test.o
 */
