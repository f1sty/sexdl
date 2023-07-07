#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <erl_nif.h>
#include <stdint.h>
#include <stdio.h>

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

static ERL_NIF_TERM create_window_nif(ErlNifEnv *env, int argc,
                                      const ERL_NIF_TERM argv[]) {
  char title[50];
  int x, y, w, h, flags;
  SDL_Window *window;

  if (!enif_get_string(env, argv[0], title, 50, ERL_NIF_UTF8)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[1], &x)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[2], &y)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[3], &w)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[4], &h)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[5], &flags)) {
    return enif_make_badarg(env);
  }

  window = SDL_CreateWindow(title, x, y, w, h, flags);
  if (window == NULL)
    return SDL_ERROR_TUPLE;
  return enif_make_tuple2(env, atom_ok,
                          enif_make_uint64(env, (uint64_t)window));
}

static ERL_NIF_TERM destroy_window_nif(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  SDL_Window *window;

  if (!enif_get_uint64(env, argv[0], (uint64_t *)&window)) {
    return enif_make_badarg(env);
  }

  SDL_DestroyWindow(window);
  return atom_ok;
}

static ERL_NIF_TERM get_window_surface_nif(ErlNifEnv *env, int argc,
                                           const ERL_NIF_TERM argv[]) {
  SDL_Window *window;
  SDL_Surface *surface;

  if (!enif_get_uint64(env, argv[0], (uint64_t *)&window)) {
    return enif_make_badarg(env);
  }

  surface = SDL_GetWindowSurface(window);
  if (surface == NULL)
    return SDL_ERROR_TUPLE;
  return enif_make_tuple2(env, atom_ok,
                          enif_make_uint64(env, (uint64_t)surface));
}

static ERL_NIF_TERM update_window_surface_nif(ErlNifEnv *env, int argc,
                                              const ERL_NIF_TERM argv[]) {
  SDL_Window *window;

  if (!enif_get_uint64(env, argv[0], (uint64_t *)&window)) {
    return enif_make_badarg(env);
  }

  if (SDL_UpdateWindowSurface(window) != 0)
    return SDL_ERROR_TUPLE;
  return atom_ok;
}

static ErlNifFunc funcs[] = {
    {"create_window", 6, create_window_nif},
    {"destroy_window", 1, destroy_window_nif},
    {"get_window_surface", 1, get_window_surface_nif},
    {"update_window_surface", 1, update_window_surface_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Video, funcs, load, NULL, NULL, NULL)
