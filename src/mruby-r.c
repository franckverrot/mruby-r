/*
** mruby-r.c
**
*/

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"

void mruby_r_eval(char **source, char ***output)
{
  mrb_state *state = mrb_open();
  mrb_value out = mrb_load_string_cxt(state, source[0], NULL);
  mrb_value curr;

  curr = mrb_funcall(state, out, "inspect", 0);

  curr = mrb_funcall(state, out, "next", 0);
  int i = 0;

  while(mrb_string_p(curr)) {
    output[i] = RSTRING_PTR(curr);
    curr = mrb_funcall(state, out, "next", 0);
    i++;
  }

  mrb_close(state);
}

void mrb_mruby_r_gem_init(mrb_state* mrb) {
  /* no-op: unused */
}

void mrb_mruby_r_gem_final(mrb_state* mrb) {
  /* no-op: unused */
}
