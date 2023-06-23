# Sexdl

SDL2 bindings for Elixir (NIFs)

## TODO

- [x] refresh on NIFs
- [x] research on SDL library
- [x] MVP with window showed
- [x] unify error handling in NIFs
- [x] add helper functions into `Sexdl.Video` for `SDL_WindowFlags` enum values
- [x] make NIFs compilation process easier
- [ ] fix `sdl_convert_surface_nif` to accept same params as API function
- [ ] look into `enif_alloc_resource` more and decide how to handle pointers
- [ ] separate `SDL2/SDL_video.h` functions into `Sexdl.Video` module (maybe?)

## Run MVP

To compile NIFs and launch sanity test program, run:

```bash
$ mix do deps.get, compile
$ iex -S mix
```

followed by:

```elixir
iex> Sexdl.Mvp.run(~c"title")
```

Black window should appear for about 3 seconds.

You also can run:

```elixir
iex> Sexdl.Mvp.run(~c"title", ~c"priv/test.png")
```

And you should see an owl on black background for the same time span:).

## Implemented bindings (so far)

- `SDL_Init`
- `SDL_CreateWindow`
- `SDL_GetWindowSurface`
- `SDL_UpdateWindowSurface`
- `SDL_BlitSurface`
- `SDL_FreeSurface`
- `SDL_DestroyWindow`
- `SDL_Quit`
- `IMG_Init`
- `IMG_Load`
- `IMG_Quit`
- `SDL_ConvertSurface` partially (see TODO list)
