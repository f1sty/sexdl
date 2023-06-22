#include <SDL2/SDL.h>
// #include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_surface.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_video.h>
#include <erl_nif.h>

extern int img_init(int flags);
extern int img_load(char *path);
extern int img_quit(void);
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
  char path[50];
  unsigned long int retval;
  if (!enif_get_string(env, argv[0], path, 50, ERL_NIF_UTF8) <= 0) {
    return enif_make_badarg(env);
  }

  retval = IMG_Load(path);

  return enif_make_uint64(env, retval);
}

static ERL_NIF_TERM img_quit_nif(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  IMG_Quit();

  return enif_make_int(env, 0);
}

static ErlNifFunc nif_funcs[] = {
    {"img_init", 1, img_init_nif},
    {"img_load", 1, img_load_nif},
    {"img_quit", 0, img_quit_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Image, nif_funcs, NULL, NULL, NULL, NULL)
