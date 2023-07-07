#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <erl_nif.h>

#define SDL_ERROR_TUPLE                                                        \
  enif_make_tuple2(env, atom_error,                                            \
                   enif_make_string(env, SDL_GetError(), ERL_NIF_UTF8))

ERL_NIF_TERM atom_error;
ERL_NIF_TERM atom_ok;
ERL_NIF_TERM atom_nil;
ERL_NIF_TERM atom_type;
ERL_NIF_TERM atom_ref;
ERL_NIF_TERM atom_struct;
ERL_NIF_TERM atom_event;
ErlNifResourceType *event_t;

static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  atom_nil = enif_make_atom(env, "nil");
  atom_type = enif_make_atom(env, "type");
  atom_ref = enif_make_atom(env, "ref");
  atom_struct = enif_make_atom(env, "__struct__");
  atom_event = enif_make_atom(env, "Elixir.Event");
  event_t = enif_open_resource_type(env, "SDL", "Event", NULL,
                                    ERL_NIF_RT_CREATE, NULL);

  return 0;
}

static ERL_NIF_TERM new_nif(ErlNifEnv *env, int argc,
                            const ERL_NIF_TERM argv[]) {
  SDL_Event *res = enif_alloc_resource(event_t, sizeof(SDL_Event));
  ERL_NIF_TERM ref = enif_make_resource(env, res);
  ERL_NIF_TERM keys[] = {atom_struct, atom_type, atom_ref};
  ERL_NIF_TERM vals[] = {atom_event, atom_nil, ref};
  ERL_NIF_TERM map;

  if (enif_make_map_from_arrays(env, keys, vals, 3, &map)) {
    return map;
  } else {
    return atom_nil;
  }
}

static ERL_NIF_TERM poll_event_nif(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  SDL_Event *res;
  int retval;

  if (!enif_get_resource(env, argv[0], event_t, (void **)&res)) {
    return enif_make_badarg(env);
  }

  retval = SDL_PollEvent(res);

  ERL_NIF_TERM type = enif_make_int(env, res->type);
  ERL_NIF_TERM keys[] = {atom_struct, atom_type, atom_ref};
  ERL_NIF_TERM vals[] = {atom_event, type, argv[0]};
  ERL_NIF_TERM map;

  if (enif_make_map_from_arrays(env, keys, vals, 3, &map) && retval) {
    return map;
  } else {
    return atom_nil;
  }
}

static ErlNifFunc funcs[] = {
    {"new", 0, new_nif},
    {"poll_event", 1, poll_event_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Event, funcs, load, NULL, NULL, NULL)
