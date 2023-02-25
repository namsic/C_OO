#include "test-util.h"

#include <stdio.h>

unsigned int indent = 0;
static void printIndent()
{
  for (int i=0; i<indent; i++) printf("  ");
}

void pushTestGroup(char *group_name)
{
  printIndent(); printf("%s\n", group_name);
  indent += 1;
}

void popTestGroup()
{
  indent -= 1;
}

bool logTestResult(bool result, char *cond_str, char *file_path, unsigned int line)
{
  printIndent(); printf("(%s) ...%s\n", cond_str, result ? "OK" : "FAIL");
  if (!result) {
    printIndent(); printf("  %s:%d\n", file_path, line);
  }
  return result;
};