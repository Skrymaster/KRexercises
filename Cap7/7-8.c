#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LINES_PER_PAGE 10
#define TRUE           1
#define FALSE          0

void print_file(char *file_name) {
  FILE *f;
  int page_number = 1;
  int line_count;    
  int c;        
  int new_page = TRUE;
 
  assert(file_name != NULL);

  if ((f = fopen(file_name, "r")) != NULL) {
    while ((c = fgetc(f)) != EOF) {
      if (new_page) {  
        printf("[%s] page %d starts\n", file_name, page_number);
        new_page = FALSE;
        line_count = 1;
      }                
      putchar(c);
      if (c == '\n' && ++line_count > LINES_PER_PAGE) {
        printf("[%s] page %d ends\n", file_name, page_number);
        putchar('\n');
        new_page = TRUE;
        page_number++;
      }              
    } 
    if (!new_page) {
      printf("[%s] page %d ends\n", file_name, page_number);
    }
    putchar('\n');    
    fclose(f);
  } 
}

int main(int argc, char *argv[]) {
  int i;

  if (argc < 2) {
    fputs("no files specified\n", stderr);
    return EXIT_FAILURE;
  }
  for (i = 1; i < argc; i++) {
    print_file(argv[i]);
  }
  return EXIT_SUCCESS;
}