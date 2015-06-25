/*
** mruby-r.c
**
*/

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"
#include <string.h>

void mruby_r_eval(char **source, char ***output)
{
  mrb_state *state = mrb_open();

  // load the given file
  FILE      *fp = fopen(source[0], "r");
  mrb_value class = mrb_load_file(state, fp);
  int       outputIndex = 0;

  // instantiate the class provided
  mrb_value inst = mrb_funcall(state, class, "new", 0);

  // start iterating
  mrb_value curr = mrb_funcall(state, inst, "next", 0);

  // stop when it's not a String anymore
  while(mrb_string_p(curr)) {
    output[outputIndex] = strdup(RSTRING_PTR(curr));
    curr = mrb_funcall(state, inst, "next", 0);
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
