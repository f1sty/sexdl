#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <erl_nif.h>

#define SDL_ERROR_TUPLE                                                        \
  enif_make_tuple2(env, atom_error,                                            \
                   enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8))

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;
ERL_NIF_TERM atom_nil;

// NOTE: init atoms and resource types in here.
static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  atom_nil = enif_make_atom(env, "nil");

  return 0;
}

static ERL_NIF_TERM init_nif(ErlNifEnv *env, int argc,
                             const ERL_NIF_TERM argv[]) {
  int flags;

  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  if (SDL_Init(flags) != 0)
    return SDL_ERROR_TUPLE;
  return atom_ok;
}

static ERL_NIF_TERM quit_nif(ErlNifEnv *env, int argc,
                             const ERL_NIF_TERM argv[]) {
  SDL_Quit();

  return atom_ok;
}

static ErlNifFunc funcs[] = {
    {"init", 1, init_nif},
    {"quit", 0, quit_nif},
};

ERL_NIF_INIT(Elixir.Sexdl, funcs, load, NULL, NULL, NULL)
