#include <stdbool.h>

#define DO_TEST(e) do{\
  if (logTestResult(e, #e, __FILE__, __LINE__) == false) return false;\
}while(0)

void pushTestGroup(char *group_name);
void popTestGroup();
bool logTestResult(bool result, char *cond_str, char *file_path, unsigned int line);
