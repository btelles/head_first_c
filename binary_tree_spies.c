#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct question_or_suspect {
  char *text;
  struct question_or_suspect *no;
  struct question_or_suspect *yes;
} question_or_suspect;

int yes_no(char *question)
{
  char answer[3];
  printf("%s? (y/n): ", question);
  fgets(answer, 3, stdin);
  return answer[0] == 'y';
}

question_or_suspect* create_question_or_suspect(char *question_text)
{
  question_or_suspect *new_question = malloc(sizeof(question_or_suspect));
  new_question->text = strdup(question_text);
  new_question->no = NULL;
  new_question->yes = NULL;
}

void release(question_or_suspect *question)
{
  if (question)
  {
    if (question->no)
      release(question->no);
    if (question->yes)
      release(question->yes);
    if (question->text)
      free(question->text);
  }
}
int main(int argc, char **argv)
{
  char question_text[80];
  char suspect[20];

  question_or_suspect *start_question = create_question_or_suspect("Has mustache");
  start_question->no = create_question_or_suspect("Loretta");
  start_question->yes = create_question_or_suspect("Vinny");

  question_or_suspect *current = NULL;

  do {
    current = start_question;

    while(1) {
      if (yes_no(current->text)) {
        if (current->yes) {
          current = current->yes;
        } else {
          printf("SUSPECT IDENTIFIED!\n");
          break;
        }
      } else if (current->no) {
        current = current->no
      } else {

      }
    }
  } while (yes_no("Run again"));
}
