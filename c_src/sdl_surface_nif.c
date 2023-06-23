#include <SDL2/SDL_error.h>
#include <SDL2/SDL_surface.h>
#include <erl_nif.h>

#define SDL_ERROR_TUPLE                                                        \
  enif_make_tuple2(env, atom_error,                                            \
                   enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8))

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;
ERL_NIF_TERM atom_nil;
ErlNifResourceType *surface_t;
ErlNifResourceType *rect_t;
ErlNifResourceType *pixel_format_t;

// NOTE: init atoms and resource types in here.
static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  atom_nil = enif_make_atom(env, "nil");
  surface_t = enif_open_resource_type(env, "SDL", "Surface", NULL,
                                      ERL_NIF_RT_CREATE, NULL);
  rect_t = enif_open_resource_type(env, "SDL", "Rect", NULL, ERL_NIF_RT_CREATE,
                                   NULL);
  pixel_format_t = enif_open_resource_type(env, "SDL", "PixelFormat", NULL,
                                           ERL_NIF_RT_CREATE, NULL);

  return 0;
}

static ERL_NIF_TERM new_nif(ErlNifEnv *env, int argc,
                            const ERL_NIF_TERM argv[]) {
  SDL_Surface *surface = enif_alloc_resource(surface_t, sizeof(SDL_Surface));
  return enif_make_resource(env, surface);
}

static ERL_NIF_TERM convert_surface_nif(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  SDL_Surface *surface;
  SDL_PixelFormat *pixel_format;
  int flags;

  if (!enif_get_resource(env, argv[0], surface_t, (void **)&surface)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_resource(env, argv[1], pixel_format_t,
                         (void **)&pixel_format)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[2], &flags)) {
    return enif_make_badarg(env);
  }

  surface = SDL_ConvertSurface(surface, pixel_format, flags);
  if (surface == NULL)
    return SDL_ERROR_TUPLE;
  return enif_make_tuple2(env, atom_ok, enif_make_resource(env, surface));
}

static ERL_NIF_TERM blit_surface_nif(ErlNifEnv *env, int argc,
                                     const ERL_NIF_TERM argv[]) {
  SDL_Surface *src;
  SDL_Surface *dst;
  SDL_Rect *src_rect;
  SDL_Rect *dst_rect;
  int retval;

  if (!enif_get_resource(env, argv[0], surface_t, (void **)&src)) {
    return enif_make_badarg(env);
  }
  if (argv[1] == atom_nil) {
    src_rect = NULL;
  } else if (!enif_get_resource(env, argv[1], rect_t, (void **)&src_rect)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_resource(env, argv[2], surface_t, (void **)&dst)) {
    return enif_make_badarg(env);
  }
  if (argv[3] == atom_nil) {
    dst_rect = NULL;
  } else if (!enif_get_resource(env, argv[3], rect_t, (void **)&dst_rect)) {
    return enif_make_badarg(env);
  }

  if (SDL_BlitSurface(src, src_rect, dst, dst_rect) != 0)
    return SDL_ERROR_TUPLE;
  return atom_ok;
}

static ERL_NIF_TERM free_surface_nif(ErlNifEnv *env, int argc,
                                     const ERL_NIF_TERM argv[]) {
  SDL_Surface *surface;

  if (!enif_get_resource(env, argv[0], surface_t, (void **)&surface)) {
    return enif_make_badarg(env);
  }

  SDL_FreeSurface(surface);

  return atom_ok;
}

static ErlNifFunc funcs[] = {
    {"new", 0, new_nif},
    {"convert_surface", 3, convert_surface_nif},
    {"blit_surface", 4, blit_surface_nif},
    {"free_surface", 1, free_surface_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Surface, funcs, load, NULL, NULL, NULL)
