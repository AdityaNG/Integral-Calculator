/*
 * Helper code that makes working with expr.h easier
*/
struct nop_context {
  void *p;
};
static void user_func_nop_cleanup(struct expr_func *f, void *c) {
  (void)f;
  struct nop_context *nop = (struct nop_context *)c;
  free(nop->p);
}
static float user_func_nop(struct expr_func *f, vec_expr_t *args, void *c) {
  (void)args;
  struct nop_context *nop = (struct nop_context *)c;
  if (f->ctxsz == 0) {
    free(nop->p);
    return 0;
  }
  if (nop->p == NULL) {
    nop->p = malloc(10000);
  }
  return 0;
}

static float user_func_add(struct expr_func *f, vec_expr_t *args, void *c) {
  (void)f, (void)c;
  float a = expr_eval(&vec_nth(args, 0));
  float b = expr_eval(&vec_nth(args, 1));
  return a + b;
}

static float user_func_next(struct expr_func *f, vec_expr_t *args, void *c) {
  (void)f, (void)c;
  float a = expr_eval(&vec_nth(args, 0));
  return a + 1;
}

static float user_func_print(struct expr_func *f, vec_expr_t *args, void *c) {
  (void)f, (void)c;
  int i;
  struct expr e;
  fprintf(stderr, ">> ");
  vec_foreach(args, e, i) { fprintf(stderr, "%f ", expr_eval(&e)); }
  fprintf(stderr, "\n");
  return 0;
}

static struct expr_func user_funcs[] = {
    {"nop", user_func_nop, user_func_nop_cleanup, sizeof(struct nop_context)},
    {"add", user_func_add, NULL, 0},
    {"next", user_func_next, NULL, 0},
    {"print", user_func_print, NULL, 0},
    {NULL, NULL, NULL, 0},
};