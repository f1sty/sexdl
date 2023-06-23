#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <erl_nif.h>

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

static ERL_NIF_TERM sdl_init_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  int flags;

  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  if (SDL_Init(flags) != 0) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return atom_ok;
}

static ERL_NIF_TERM sdl_create_window_nif(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  char title[50];
  int x, y, w, h, flags;
  unsigned long int retval;

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

  retval = SDL_CreateWindow(title, x, y, w, h, flags);

  if (retval == NULL) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return enif_make_tuple2(env, atom_ok, enif_make_uint64(env, retval));
}

static ERL_NIF_TERM sdl_get_window_surface_nif(ErlNifEnv *env, int argc,
                                               const ERL_NIF_TERM argv[]) {
  unsigned long int window, retval;

  if (!enif_get_uint64(env, argv[0], &window)) {
    return enif_make_badarg(env);
  }

  retval = SDL_GetWindowSurface((SDL_Window *)window);
  if (retval == NULL) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return enif_make_tuple2(env, atom_ok, enif_make_uint64(env, retval));
}

static ERL_NIF_TERM sdl_update_window_surface_nif(ErlNifEnv *env, int argc,
                                                  const ERL_NIF_TERM argv[]) {
  unsigned long int window;
  int retval;

  if (!enif_get_uint64(env, argv[0], &window)) {
    return enif_make_badarg(env);
  }

  if (SDL_UpdateWindowSurface((SDL_Window *)window) != 0) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return atom_ok;
}

// Diversion from params in API, here we get SDL_Surface * as 2nd param, not
// SDL_PixelFormat *, and no flags are passed as 3rd parameter, because:
// "the flags are unused and should be set to 0; this is a leftover from
// SDL 1.2's API".
static ERL_NIF_TERM sdl_convert_surface_nif(ErlNifEnv *env, int argc,
                                            const ERL_NIF_TERM argv[]) {
  unsigned long int window_surface_src, window_surface_dst, retval;

  if (!enif_get_uint64(env, argv[0], &window_surface_src)) {
    return enif_make_badarg(env);
  }

  if (!enif_get_uint64(env, argv[1], &window_surface_dst)) {
    return enif_make_badarg(env);
  }

  retval = SDL_ConvertSurface((SDL_Surface *)window_surface_src,
                              ((SDL_Surface *)window_surface_dst)->format, 0);
  if (retval == NULL) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return enif_make_tuple2(env, atom_ok, enif_make_uint64(env, retval));
}

static ERL_NIF_TERM sdl_blit_surface_nif(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  unsigned long int surface_src, surface_dst, src_rect, dst_rect;
  int retval;

  if (!enif_get_uint64(env, argv[0], &surface_src)) {
    return enif_make_badarg(env);
  }

  if (argv[1] == atom_nil) {
    src_rect = NULL;
  } else if (!enif_get_uint64(env, argv[1], &src_rect)) {
    return enif_make_badarg(env);
  }

  if (!enif_get_uint64(env, argv[2], &surface_dst)) {
    return enif_make_badarg(env);
  }

  if (argv[3] == atom_nil) {
    dst_rect = NULL;
  } else if (!enif_get_uint64(env, argv[3], &dst_rect)) {
    return enif_make_badarg(env);
  }

  if (SDL_BlitSurface((SDL_Surface *)surface_src, (SDL_Rect *)src_rect,
                      (SDL_Surface *)surface_dst, (SDL_Rect *)dst_rect) < 0) {
    return enif_make_tuple2(
        env, atom_error, enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8));
  }

  return atom_ok;
}

static ERL_NIF_TERM sdl_free_surface_nif(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  unsigned long int window_surface;

  if (!enif_get_uint64(env, argv[0], &window_surface)) {
    return enif_make_badarg(env);
  }

  SDL_FreeSurface((SDL_Surface *)window_surface);

  return atom_ok;
}

static ERL_NIF_TERM sdl_destroy_window_nif(ErlNifEnv *env, int argc,
                                           const ERL_NIF_TERM argv[]) {
  unsigned long int window;

  if (!enif_get_uint64(env, argv[0], &window)) {
    return enif_make_badarg(env);
  }

  SDL_DestroyWindow((SDL_Window *)window);

  return atom_ok;
}

static ERL_NIF_TERM sdl_quit_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  SDL_Quit();

  return atom_ok;
}

static ErlNifFunc nif_funcs[] = {
    {"sdl_init", 1, sdl_init_nif},
    {"sdl_create_window", 6, sdl_create_window_nif},
    {"sdl_get_window_surface", 1, sdl_get_window_surface_nif},
    {"sdl_update_window_surface", 1, sdl_update_window_surface_nif},
    {"sdl_convert_surface", 2, sdl_convert_surface_nif},
    {"sdl_blit_surface", 4, sdl_blit_surface_nif},
    {"sdl_free_surface", 1, sdl_free_surface_nif},
    {"sdl_destroy_window", 1, sdl_destroy_window_nif},
    {"sdl_quit", 0, sdl_quit_nif},
};

ERL_NIF_INIT(Elixir.Sexdl, nif_funcs, load, NULL, NULL, NULL)
