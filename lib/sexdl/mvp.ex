defmodule Sexdl.Mvp do
  alias Sexdl.{Video, Event, Surface, Image}
  import Sexdl
  # import Bitwise

  @fps 60
  @width 600
  @height 600

  def run(title, bg_image_path \\ nil, width \\ @width, height \\ @height) do
    with :ok <- init(sdl_init_video()),
         {:ok, window} <-
           Video.create_window(
             title,
             sdl_windowpos_centered(),
             sdl_windowpos_centered(),
             width,
             height,
             sdl_window_shown()
           ),
         {:ok, window_surface} <- Video.get_window_surface(window) do
      if not is_nil(bg_image_path) do
        Image.init(Image.img_init_png())

        {:ok, window_surface_img} = Image.load(bg_image_path)

        Surface.blit_surface(window_surface_img, nil, window_surface, nil)
        Surface.free_surface(window_surface_img)
      end

      loop(Event.new(), window_surface, window, fps_to_tick(@fps))
    end
  end

  def loop(event, window_surface, window, tick) do
    Video.update_window_surface(window)
    Process.sleep(tick)

    case Event.poll_event(event) do
      %Event{type: :SDL_QUIT} ->
        Surface.free_surface(window_surface)
        Image.quit()
        Video.destroy_window(window)
        quit()

      %Event{type: :SDL_MOUSEMOTION} = event ->
        loop(event, window_surface, window, tick)

      %Event{type: :SDL_WINDOWEVENT} = event ->
        loop(event, window_surface, window, tick)

      %Event{type: :SDL_KEYDOWN} = event ->
        loop(event, window_surface, window, tick)

      %Event{type: :SDL_TEXTINPUT} = event ->
        loop(event, window_surface, window, tick)

      %Event{type: :SDL_KEYUP} = event ->
        loop(event, window_surface, window, tick)

      %Event{type: :SDL_POLLSENTINEL} = event ->
        loop(event, window_surface, window, tick)

      event ->
        IO.inspect(event)
        loop(event, window_surface, window, tick)
    end
  end

  defp fps_to_tick(fps), do: round((1 / fps) * 1000)
end
