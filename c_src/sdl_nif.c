#include <SDL2/SDL.h>
// #include <SDL2/SDL_error.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_surface.h>
// #include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <erl_nif.h>

extern int sdl_init(int flags);
extern unsigned long int sdl_create_window(char *title, int x, int y, int w,
                                           int h, int flags);
extern unsigned long int sdl_get_window_surface(unsigned long int window);

// static ErlNifResourceType *SDL_WINDOW_RES;
// static size_t res_size = 1024;

// SDL_Window *window = NULL;
// SDL_Window *window = enif_alloc_resource(SDL_WINDOW_RES, res_size);
// SDL_Surface *window_surface = NULL;
// SDL_Surface *image_surface = NULL;
// SDL_Surface *optimazed_surface = NULL;

static ERL_NIF_TERM sdl_init_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  int flags, retval;
  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  retval = SDL_Init(flags);

  return enif_make_int(env, retval);
}

static ERL_NIF_TERM sdl_create_window_nif(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  char title[1024];
  int x, y, w, h, flags;
  unsigned long int retval;

  if (enif_get_string(env, argv[0], title, 1024, ERL_NIF_UTF8) <= 0) {
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

  // retval = enif_make_resource(env, SDL_CreateWindow(title, x, y, w, h,
  // flags));

  retval = SDL_CreateWindow(title, x, y, w, h, flags);

  return enif_make_uint64(env, retval);
}

static ERL_NIF_TERM sdl_get_window_surface_nif(ErlNifEnv *env, int argc,
                                               const ERL_NIF_TERM argv[]) {
  unsigned long int window_handle, retval;

  if (!enif_get_uint64(env, argv[0], window_handle)) {
    return enif_make_badarg(env);
  }

  retval = SDL_GetWindowSurface((SDL_Window *)window_handle);

  return enif_make_uint64(env, retval);
}

static ErlNifFunc nif_funcs[] = {
    {"sdl_init", 1, sdl_init_nif},
    {"sdl_create_window", 6, sdl_create_window_nif},
    {"sdl_get_window_surface", 1, sdl_get_window_surface_nif},
};

ERL_NIF_INIT(Elixir.Sexdl, nif_funcs, NULL, NULL, NULL, NULL)
