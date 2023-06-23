# Sexdl

SDL wrapper library for Elixir


## TODO

- [x] refresh on NIFs
- [x] research on SDL library
- [x] MVP with window showed
- [x] unify error handling in nifs
- [ ] fix `sdl_convert_surface_nif` to accept same params as API function
- [ ] look into `enif_alloc_resource` more and decide how to handle pointers
- [ ] separate `SDL2/SDL_video.h` functions into `Sexdl.Video` module (maybe?)
- [ ] add helper functions into `Sexdl.Video` for `SDL_WindowFlags` enum values

## Run MVP

To compile nifs and launch sanity test program, run:

```bash
$ cd c_src/ && ./build.sh && .. && iex -S mix run
```

followed by:

```elixir
iex> Sexdl.Mvp.run(~c"title")
```

Black window should appear for about 3 seconds.

You also can run:

```elixir
iex> Sexdl.Mvp.run(~c"title", ~c"test.png")
```

And you should see an owl on black background for the same timespan:).
