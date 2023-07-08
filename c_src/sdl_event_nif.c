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
ERL_NIF_TERM event_types[65536];
ErlNifResourceType *event_t;

static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
  atom_error = enif_make_atom(env, "error");
  atom_ok = enif_make_atom(env, "ok");
  atom_nil = enif_make_atom(env, "nil");
  atom_type = enif_make_atom(env, "type");
  atom_ref = enif_make_atom(env, "ref");
  atom_struct = enif_make_atom(env, "__struct__");
  atom_event = enif_make_atom(env, "Elixir.Sexdl.Event");
  event_types[SDL_FIRSTEVENT] = enif_make_atom(env, "SDL_FIRSTEVENT");
  event_types[SDL_QUIT] = enif_make_atom(env, "SDL_QUIT");
  event_types[SDL_APP_TERMINATING] = enif_make_atom(env, "SDL_APP_TERMINATING");
  event_types[SDL_APP_LOWMEMORY] = enif_make_atom(env, "SDL_APP_LOWMEMORY");
  event_types[SDL_APP_WILLENTERBACKGROUND] =
      enif_make_atom(env, "SDL_APP_WILLENTERBACKGROUND");
  event_types[SDL_APP_DIDENTERBACKGROUND] =
      enif_make_atom(env, "SDL_APP_DIDENTERBACKGROUND");
  event_types[SDL_APP_WILLENTERFOREGROUND] =
      enif_make_atom(env, "SDL_APP_WILLENTERFOREGROUND");
  event_types[SDL_APP_DIDENTERFOREGROUND] =
      enif_make_atom(env, "SDL_APP_DIDENTERFOREGROUND");
  event_types[SDL_LOCALECHANGED] = enif_make_atom(env, "SDL_LOCALECHANGED");
  event_types[SDL_DISPLAYEVENT] = enif_make_atom(env, "SDL_DISPLAYEVENT");
  event_types[SDL_WINDOWEVENT] = enif_make_atom(env, "SDL_WINDOWEVENT");
  event_types[SDL_SYSWMEVENT] = enif_make_atom(env, "SDL_SYSWMEVENT");
  event_types[SDL_KEYDOWN] = enif_make_atom(env, "SDL_KEYDOWN");
  event_types[SDL_KEYUP] = enif_make_atom(env, "SDL_KEYUP");
  event_types[SDL_TEXTEDITING] = enif_make_atom(env, "SDL_TEXTEDITING");
  event_types[SDL_TEXTINPUT] = enif_make_atom(env, "SDL_TEXTINPUT");
  event_types[SDL_KEYMAPCHANGED] = enif_make_atom(env, "SDL_KEYMAPCHANGED");
  event_types[SDL_TEXTEDITING_EXT] = enif_make_atom(env, "SDL_TEXTEDITING_EXT");
  event_types[SDL_MOUSEMOTION] = enif_make_atom(env, "SDL_MOUSEMOTION");
  event_types[SDL_MOUSEBUTTONDOWN] = enif_make_atom(env, "SDL_MOUSEBUTTONDOWN");
  event_types[SDL_MOUSEBUTTONUP] = enif_make_atom(env, "SDL_MOUSEBUTTONUP");
  event_types[SDL_MOUSEWHEEL] = enif_make_atom(env, "SDL_MOUSEWHEEL");
  event_types[SDL_JOYAXISMOTION] = enif_make_atom(env, "SDL_JOYAXISMOTION");
  event_types[SDL_JOYBALLMOTION] = enif_make_atom(env, "SDL_JOYBALLMOTION");
  event_types[SDL_JOYHATMOTION] = enif_make_atom(env, "SDL_JOYHATMOTION");
  event_types[SDL_JOYBUTTONDOWN] = enif_make_atom(env, "SDL_JOYBUTTONDOWN");
  event_types[SDL_JOYBUTTONUP] = enif_make_atom(env, "SDL_JOYBUTTONUP");
  event_types[SDL_JOYDEVICEADDED] = enif_make_atom(env, "SDL_JOYDEVICEADDED");
  event_types[SDL_JOYDEVICEREMOVED] =
      enif_make_atom(env, "SDL_JOYDEVICEREMOVED");
  event_types[SDL_JOYBATTERYUPDATED] =
      enif_make_atom(env, "SDL_JOYBATTERYUPDATED");
  event_types[SDL_CONTROLLERAXISMOTION] =
      enif_make_atom(env, "SDL_CONTROLLERAXISMOTION");
  event_types[SDL_CONTROLLERBUTTONDOWN] =
      enif_make_atom(env, "SDL_CONTROLLERBUTTONDOWN");
  event_types[SDL_CONTROLLERBUTTONUP] =
      enif_make_atom(env, "SDL_CONTROLLERBUTTONUP");
  event_types[SDL_CONTROLLERDEVICEADDED] =
      enif_make_atom(env, "SDL_CONTROLLERDEVICEADDED");
  event_types[SDL_CONTROLLERDEVICEREMOVED] =
      enif_make_atom(env, "SDL_CONTROLLERDEVICEREMOVED");
  event_types[SDL_CONTROLLERDEVICEREMAPPED] =
      enif_make_atom(env, "SDL_CONTROLLERDEVICEREMAPPED");
  event_types[SDL_CONTROLLERTOUCHPADDOWN] =
      enif_make_atom(env, "SDL_CONTROLLERTOUCHPADDOWN");
  event_types[SDL_CONTROLLERTOUCHPADMOTION] =
      enif_make_atom(env, "SDL_CONTROLLERTOUCHPADMOTION");
  event_types[SDL_CONTROLLERTOUCHPADUP] =
      enif_make_atom(env, "SDL_CONTROLLERTOUCHPADUP");
  event_types[SDL_CONTROLLERSENSORUPDATE] =
      enif_make_atom(env, "SDL_CONTROLLERSENSORUPDATE");
  event_types[SDL_FINGERDOWN] = enif_make_atom(env, "SDL_FINGERDOWN");
  event_types[SDL_FINGERUP] = enif_make_atom(env, "SDL_FINGERUP");
  event_types[SDL_FINGERMOTION] = enif_make_atom(env, "SDL_FINGERMOTION");
  event_types[SDL_DOLLARGESTURE] = enif_make_atom(env, "SDL_DOLLARGESTURE");
  event_types[SDL_DOLLARRECORD] = enif_make_atom(env, "SDL_DOLLARRECORD");
  event_types[SDL_MULTIGESTURE] = enif_make_atom(env, "SDL_MULTIGESTURE");
  event_types[SDL_CLIPBOARDUPDATE] = enif_make_atom(env, "SDL_CLIPBOARDUPDATE");
  event_types[SDL_DROPFILE] = enif_make_atom(env, "SDL_DROPFILE");
  event_types[SDL_DROPTEXT] = enif_make_atom(env, "SDL_DROPTEXT");
  event_types[SDL_DROPBEGIN] = enif_make_atom(env, "SDL_DROPBEGIN");
  event_types[SDL_DROPCOMPLETE] = enif_make_atom(env, "SDL_DROPCOMPLETE");
  event_types[SDL_AUDIODEVICEADDED] =
      enif_make_atom(env, "SDL_AUDIODEVICEADDED");
  event_types[SDL_AUDIODEVICEREMOVED] =
      enif_make_atom(env, "SDL_AUDIODEVICEREMOVED");
  event_types[SDL_SENSORUPDATE] = enif_make_atom(env, "SDL_SENSORUPDATE");
  event_types[SDL_RENDER_TARGETS_RESET] =
      enif_make_atom(env, "SDL_RENDER_TARGETS_RESET");
  event_types[SDL_RENDER_DEVICE_RESET] =
      enif_make_atom(env, "SDL_RENDER_DEVICE_RESET");
  event_types[SDL_POLLSENTINEL] = enif_make_atom(env, "SDL_POLLSENTINEL");
  event_types[SDL_USEREVENT] = enif_make_atom(env, "SDL_USEREVENT");
  event_types[SDL_LASTEVENT] = enif_make_atom(env, "SDL_LASTEVENT");

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
  ERL_NIF_TERM ref;
  ERL_NIF_TERM type;
  SDL_Event *event;
  int retval;

  if (enif_get_map_value(env, argv[0], atom_ref, &ref) &&
      enif_get_map_value(env, argv[0], atom_type, &type) &&
      enif_get_resource(env, ref, event_t, (void **)&event)) {

    retval = SDL_PollEvent(event);

    ERL_NIF_TERM map;
    ERL_NIF_TERM keys[] = {atom_struct, atom_type, atom_ref};
    ERL_NIF_TERM vals[] = {atom_event, event_types[event->type], ref};

    if (!enif_make_map_from_arrays(env, keys, vals, 3, &map)) {
      return enif_make_badarg(env);
    }

    return map;
  } else {
    return enif_make_badarg(env);
  }
}

static ErlNifFunc funcs[] = {
    {"new", 0, new_nif},
    {"poll_event", 1, poll_event_nif},
};

ERL_NIF_INIT(Elixir.Sexdl.Event, funcs, load, NULL, NULL, NULL)
