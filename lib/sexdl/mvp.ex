defmodule Sexdl.Mvp do
  alias Sexdl, as: S
  alias Sexdl.Video, as: V
  alias Sexdl.Image, as: I
  alias Sexdl.Surface, as: Sf
  alias Sexdl.Event

  def run(title, bg_image_path \\ nil, width \\ 600, height \\ 600) do
    with :ok <- S.init(S.sdl_init_video()),
         {:ok, window} <-
           V.create_window(
             title,
             S.sdl_windowpos_centered(),
             S.sdl_windowpos_centered(),
             width,
             height,
             S.sdl_window_shown()
           ),
         {:ok, window_surface} <- V.get_window_surface(window) do
      if not is_nil(bg_image_path) do
        I.img_init_png() |> I.init()
        {:ok, window_surface_img} = I.load(bg_image_path)
        Sf.blit_surface(window_surface_img, nil, window_surface, nil)
        Sf.free_surface(window_surface_img)
      end

      V.update_window_surface(window)
      Event.new() |> loop(window_surface, window)
    end
  end

  def loop(event, window_surface, window) do
    case Event.poll_event(event) do
      %Event{type: :SDL_QUIT} ->
        Sf.free_surface(window_surface)
        I.quit()
        V.destroy_window(window)
        S.quit()

      %Event{type: :SDL_MOUSEMOTION} = event ->
        IO.inspect(event)
        loop(event, window_surface, window)

      %Event{type: :SDL_WINDOWEVENT} = event ->
        IO.inspect(event)
        loop(event, window_surface, window)

      %Event{type: :SDL_KEYDOWN} = event ->
        IO.puts("key pressed")
        loop(event, window_surface, window)

      %Event{type: :SDL_TEXTINPUT} = event ->
        IO.puts("input registered")
        loop(event, window_surface, window)

      %Event{type: :SDL_KEYUP} = event ->
        loop(event, window_surface, window)

      %Event{type: :SDL_POLLSENTINEL} = event ->
        loop(event, window_surface, window)
    end
  end
end
