#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

bool safe_atoi(const char *str, int *out) {
  assert(out != NULL);
  char *endptr;
  // errno = 0;
  *out = strtol(str, &endptr, 10);
  // if (errno == ERANGE) return false;
  /* if (isspace(*endptr) || (*endptr == '\0' && endptr != str)) {
    return true;
  }*/
  return (*endptr == '\0' && endptr != str);
}

enum DataType
{
    DT_AUTO,
    DT_BOOL,
    DT_INTEGER,
    DT_STRING,
};
char *dt_str[] = {"AUTO", "BOOL", "INT", "STR"};

struct config_item
{
  char* key;
  enum DataType datatype;
  union value_type {
    bool dt_bool;
    int dt_int;
    char* dt_str;
  } value;
};

void parse_value(struct config_item *item, char *value)
{
  assert(item);

  if (item->datatype == DT_AUTO || item->datatype == DT_BOOL) {
    if (!strcmp(value, "true") || !strcmp(value, "TRUE")) {
      item->value.dt_bool = true;
      item->datatype = DT_BOOL;
      return;
    }
    if (!strcmp(value, "false") || !strcmp(value, "FALSE")) {
      item->value.dt_bool = false;
      item->datatype = DT_BOOL;
      return;
    }
    assert(item->datatype == DT_AUTO);
  }

  if (item->datatype == DT_AUTO || item->datatype == DT_INTEGER) {
    if (safe_atoi(value, &item->value.dt_int)) {
      item->datatype = DT_INTEGER;
      return;
    }
    assert(item->datatype == DT_AUTO);
  }

  if (item->datatype == DT_AUTO || item->datatype == DT_STRING) {
    item->value.dt_str = strdup(value);
    assert(item->value.dt_str);
    item->datatype = DT_STRING;
    return;
  }

  assert(0);
}

void save_to_config(struct config_item* config_list, int list_len, char* key, char* value)
{
  for (int i=0; i<list_len; i++) {
    if (strcmp(key, config_list[i].key)) {
      continue;
    }
    parse_value(&config_list[i], value);
    break;
  }
}

int main() {
    struct config_item config[] = {
        {.key = "itisbool", .datatype = DT_BOOL},
        {.key = "itisint"},
        {.key = "itisstr"},
    };

    save_to_config(config, 3, "itisbool", "false");
    save_to_config(config, 3, "itisint", "123");
    save_to_config(config, 3, "itisstr", "helloworld");

    char* boolres = config[0].value.dt_str;
    int intres = config[1].value.dt_int;
    char* strres = config[2].value.dt_str;

    printf("%s: %s\n", dt_str[config[0].datatype], boolres ? "true" : "false");
    printf("%s: %d\n", dt_str[config[1].datatype], intres);
    printf("%s: %s\n", dt_str[config[2].datatype], strres);
    return 0;
}
