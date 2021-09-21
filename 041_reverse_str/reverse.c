#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  const char * ptr = str;
  size_t len = 0;

  // Get the len of string
  while (*ptr != '\0') {
    len++;
    ptr++;
  }

  // Copy the string
  char copy[len];
  strcpy(copy, str);

  ptr = copy + len - 1;

  // Write the output
  for (size_t i = 0; i < len; i++) {
    str[i] = *ptr;
    ptr -= 1;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
