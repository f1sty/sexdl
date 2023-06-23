#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <erl_nif.h>

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;

// NOTE: init atoms and resource types in here.
static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");

  return 0;
}

static ERL_NIF_TERM img_init_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  int flags, retval;
  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  if (IMG_Init(flags) != flags) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return atom_ok;
}

static ERL_NIF_TERM img_load_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  char path[50];
  unsigned long int retval;
  if (!enif_get_string(env, argv[0], path, 50, ERL_NIF_UTF8)) {
    return enif_make_badarg(env);
  }

  retval = IMG_Load(path);

  if (retval == NULL) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return enif_make_tuple2(env, atom_ok, enif_make_uint64(env, retval));
}

static ERL_NIF_TERM img_quit_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  IMG_Quit();

  return atom_ok;
}

static ErlNifFunc nif_funcs[] = {
    {"img_init", 1, img_init_nif},
    {"img_load", 1, img_load_nif},
    {"img_quit", 0, img_quit_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Image, nif_funcs, load, NULL, NULL, NULL)
