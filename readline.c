#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>

typedef void cmd_func();
typedef struct {
  char *name;      // cmd name
  cmd_func *func;  // function of this cmd
  char *doc;       // doc for this cmd
} Command;
void cmd_ls();
void cmd_pwd();
void cmd_exit();
Command cmds[] = {{"ls", cmd_ls, "list all files"},
                  {"pwd", cmd_pwd, "show current directory"},
                  {"exit", cmd_exit, "exit the program"},
                  {NULL, NULL, NULL}};

void execute(const char *line);

char **auto_completion(const char *text, int start, int end);
char *command_generator(const char *text, int state);
void initialize_readline();

int main() {
  initialize_readline();
  char *line = NULL;
  while (1) {
    line = readline("prompt> ");
    if (line == NULL) {  // read EOF, usually control + D
      exit(EXIT_SUCCESS);
    }
    if (*line) {  // line not empty
      add_history(line);
      execute(line);
    }
    free(line);
    line = NULL;
  }
  return 0;
}

/* Tell the GNU Readline library how to complete.  We want to try to complete
   on command names if this is the first word in the line, or on filenames
   if not. */
void initialize_readline() {
  /* Allow conditional parsing of the ~/.inputrc file. */
  rl_readline_name = "my_program";

  /* Tell the completer that we want a crack first. */
  rl_attempted_completion_function = auto_completion;
}

void cmd_ls() { printf("ls\n"); }
void cmd_pwd() { printf("pwd\n"); }
void cmd_exit() { exit(EXIT_SUCCESS); }

void execute(const char *line) {
  Command *command = NULL;
  for (int i = 0; cmds[i].name; ++i) {
    if (strcmp(line, cmds[i].name) == 0) command = &cmds[i];
  }
  if (command == NULL) {
    printf("cmd not implemented!\n");
    return;
  }
  (*(command->func))();
}

/* Attempt to complete on the contents of TEXT.  START and END bound the
   region of rl_line_buffer that contains the word to complete.  TEXT is
   the word to complete.  We can use the entire contents of rl_line_buffer
   in case we want to do some simple parsing.  Return the array of matches,
   or NULL if there aren't any. */
char **auto_completion(const char *text, int start, int end) {
  char **matches = NULL;
  if (start == 0) {
    matches = rl_completion_matches(text, command_generator);
  }
  return matches;
}

/* Generator function for command completion.  STATE lets us know whether
   to start from scratch; without any state (i.e. STATE == 0), then we
   start at the top of the list. */
char *command_generator(const char *text, int state) {
  static int list_index, len;
  char *name = NULL;
  if (!state) {
    list_index = 0;
    len = strlen(text);
  }

  while ((name = cmds[list_index].name)) {
    list_index++;

    if (strncmp(name, text, len) == 0) return strdup(name);
  }

  return NULL;
}