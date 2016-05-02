/* A FAIRE : complétez le début de ce programme. */
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N(x) (sizeof(x)/sizeof(*x))

typedef char* (*function) (const char*);

void iterate_over_functions(const char* inputs[], size_t size, function f[], size_t num_f);
char* copy(const char* s);
char* to_upper_case_all_a(const char* s);
char* split_at_third_space(const char* s);
char* append_hello(const char* s);

int main() {
    const char* inputs[] = {
      "Hallo Anno! Cammant ca va ? Ahlala...",
      "aaaaa",
      " a a a a a ",
      "Une phrose sons oucun o"
    };

    /* A FAIRE : définissez ici my_functions. */
        function my_functions[4] = {
          copy, 
          to_upper_case_all_a, 
          split_at_third_space,
          append_hello
        };
    
    iterate_over_functions(inputs      , N(inputs),
                           my_functions, N(my_functions));

    return 0;
}

void iterate_over_functions(const char* inputs[], size_t size, 
  function f[], size_t num_f) {

  char* out = NULL;
  for(int i = 0; i < num_f; ++i) {
    printf("Applying transformation %d :\n", i+1);
    
    for(int j = 0 ; j < size; ++j) {
      out = f[i](inputs[j]);
      printf("\t->%s\n", out);
      free(out);
    }
  }

}

char* copy(const char* s) {
  size_t len = strlen(s);
  char* new = malloc(len+1);
  strncpy(new, s, len);
  new[len] = '\0';
  return new;
}

char* to_upper_case_all_a(const char* s) {
  size_t len = strlen(s);
  char* st = copy(s);
  for(int i = 0; i < len; ++i) {
    if(st[i] == 'a') {
      st[i] = 'A';
    }
  }
  return st;
}

char* split_at_third_space(const char* s) {
  size_t len = strlen(s);
  char* st = malloc(len+1);
  size_t pos = 0;
  int count = 0;
   while(count < 3 && s[pos]!= '\0') {
    if (s[pos] == ' ') {
      count += 1;
    }
    st[pos] = s[pos];
    pos += 1;
  }
  st[pos-1] = '\0';
  return st;
}

char* append_hello(const char* s) {
  size_t len = strlen(s);
  const char* hello = "hello";
  char* st = calloc(len+10, sizeof(char));
  strncpy(st, s, len);
  strcat((char*) st, (char*) hello);
  return st;
}
