#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <erl_nif.h>
#include <stdint.h>

#define SDL_ERROR_TUPLE                                                        \
  enif_make_tuple2(env, atom_error,                                            \
                   enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8))

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;
// ErlNifResourceType *surface_t;

static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  // surface_t = enif_open_resource_type(env, "SDL", "Surface", NULL,
  //                                     ERL_NIF_RT_CREATE, NULL);

  return 0;
}

static ERL_NIF_TERM init_nif(ErlNifEnv *env, int argc,
                             const ERL_NIF_TERM argv[]) {
  int flags;

  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  if (IMG_Init(flags) != flags)
    return SDL_ERROR_TUPLE;
  return atom_ok;
}

static ERL_NIF_TERM load_nif(ErlNifEnv *env, int argc,
                             const ERL_NIF_TERM argv[]) {
  char path[50];
  SDL_Surface *surface;

  if (!enif_get_string(env, argv[0], path, 50, ERL_NIF_UTF8)) {
    return enif_make_badarg(env);
  }

  surface = IMG_Load(path);
  if (surface == NULL)
    return SDL_ERROR_TUPLE;
  return enif_make_tuple2(env, atom_ok,
                          enif_make_uint64(env, (uint64_t)surface));
}

static ERL_NIF_TERM quit_nif(ErlNifEnv *env, int argc,
                             const ERL_NIF_TERM argv[]) {
  IMG_Quit();

  return atom_ok;
}

static ErlNifFunc funcs[] = {
    {"init", 1, init_nif},
    {"load", 1, load_nif},
    {"quit", 0, quit_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Image, funcs, load, NULL, NULL, NULL)
