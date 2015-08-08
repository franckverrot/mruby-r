/*
** mruby-r.c
**
*/

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include <string.h>

void mruby_r_eval_internal(char **source, char ***output)
{
  mrb_state *state = mrb_open();

  // load the given file
  FILE      *fp = fopen(source[0], "r");
  mrb_value class = mrb_load_file(state, fp);
  int       outputIndex = 0;

  // instantiate the class provided
  mrb_value inst = mrb_funcall(state, class, "new", 0);

  // start iterating
  mrb_value curr;
  char * str;

  // stop when it's not a String anymore
  while(curr = mrb_funcall(state, inst, "next", 0), !mrb_nil_p(curr) && !mrb_exception_p(curr)) {
    if(!mrb_string_p(curr)) {
      curr = mrb_funcall(state, curr, "to_s", 0);
    }
    str = strdup(RSTRING_PTR(curr));
    strcpy(output[outputIndex], str);
    outputIndex++;
  }

  mrb_close(state);
}

void mrb_mruby_r_gem_init(mrb_state* mrb) {
  /* no-op: unused */
}

void mrb_mruby_r_gem_final(mrb_state* mrb) {
  /* no-op: unused */
}
