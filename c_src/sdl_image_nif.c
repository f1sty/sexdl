#include <SDL2/SDL.h>
// #include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_surface.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_video.h>
#include <erl_nif.h>

extern int img_init(int flags);
extern int img_laod(char *path);
// extern long unsigned int sdl_create_window(char *title, int x, int y, int w,
//                                            int h, int flags);

// static ErlNifResourceType *SDL_WINDOW_RES;
// static size_t res_size = 1024;

// SDL_Window *window = NULL;
// SDL_Window *window = enif_alloc_resource(SDL_WINDOW_RES, res_size);
// SDL_Surface *window_surface = NULL;
// SDL_Surface *image_surface = NULL;
// SDL_Surface *optimazed_surface = NULL;

static ERL_NIF_TERM img_init_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  int flags, retval;
  if (!enif_get_int(env, argv[0], &flags)) {
    return enif_make_badarg(env);
  }

  retval = IMG_Init(flags);

  return enif_make_int(env, retval);
}

static ERL_NIF_TERM img_load_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  char path[1024];
  unsigned long int retval;
  if (!enif_get_string(env, argv[0], path, 1024, ERL_NIF_UTF8) <= 0) {
    return enif_make_badarg(env);
  }

  retval = IMG_Load(path);

  return enif_make_uint64(env, retval);
}

static ErlNifFunc nif_funcs[] = {
    {"img_init", 1, img_init_nif},
    {"img_load", 1, img_load_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Image, nif_funcs, NULL, NULL, NULL, NULL)
