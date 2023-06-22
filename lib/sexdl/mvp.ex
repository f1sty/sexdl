defmodule Sexdl.Mvp do
  import Sexdl
  import Sexdl.Image

  def run(title, width \\ 600, height \\ 600, _bg_image_path \\ nil) do
    with :ok <- sdl_init(sdl_init_video()),
         {:ok, window} <-
           sdl_create_window(
             title,
             sdl_windowpos_centered(),
             sdl_windowpos_centered(),
             width,
             height,
             sdl_window_shown()
           ),
         {:ok, window_surface} <- sdl_get_window_surface(window),
         :ok <- sdl_update_window_surface(window),
         :ok <- img_init(img_init_png()) do
      Process.sleep(3000)
      sdl_free_surface(window_surface)
      img_quit()
      sdl_destroy_window(window)
      sdl_quit()
    end
  end
end
