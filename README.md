# Sexdl

SDL wrapper library for Elixir


## TODO

- [x] refresh on NIFs
- [x] research on SDL library
- [x] MVP with window showed
- [ ] look into `enif_alloc_resource` more and decide how to handle pointers
- [ ] separate `SDL2/SDL_video.h` functions into `Sexdl.Video` module (maybe?)
- [ ] add helper functions into `Sexdl.Video` for `SDL_WindowFlags` enum values

## Run MVP

To compile nifs and run minimal program:

```bash
$ cd c_src/ && ./build.sh && .. && iex -S mix run
```

followed by:

```elixir
iex> Sexdl.Mvp.run(~c"title")
```

You should see black window appear for abou 3 seconds.
