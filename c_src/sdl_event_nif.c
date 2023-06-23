#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <erl_nif.h>

#define SDL_ERROR_TUPLE                                                        \
  enif_make_tuple2(env, atom_error,                                            \
                   enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8))

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;
ERL_NIF_TERM atom_nil;
ErlNifResourceType *event_t;

static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  atom_nil = enif_make_atom(env, "nil");
  event_t = enif_open_resource_type(env, "SDL", "Event", NULL,
                                    ERL_NIF_RT_CREATE, NULL);

  return 0;
}

static ERL_NIF_TERM new_nif(ErlNifEnv *env, int argc,
                            const ERL_NIF_TERM argv[]) {
  SDL_Event *res = enif_alloc_resource(event_t, sizeof(SDL_Event));
  return enif_make_resource(env, res);
}

static ERL_NIF_TERM poll_event_nif(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  SDL_Event *res;
  int retval;

  if (!enif_get_resource(env, argv[0], event_t, (void **)&res)) {
    return enif_make_badarg(env);
  }

  retval = SDL_PollEvent(res);

  return enif_make_int(env, retval);
}

static ErlNifFunc funcs[] = {
    {"new", 0, new_nif},
    {"poll_event", 1, poll_event_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Event, funcs, load, NULL, NULL, NULL)
