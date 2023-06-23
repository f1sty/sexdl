defmodule Sexdl.Mvp do
  import Sexdl
  import Sexdl.Image

  def run(title, bg_image_path \\ nil, width \\ 600, height \\ 600) do
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
         {:ok, window_surface} <- sdl_get_window_surface(window) do
      if not is_nil(bg_image_path) do
        img_init(img_init_png())
        {:ok, window_surface_img} = img_load(bg_image_path)
        sdl_blit_surface(window_surface_img, nil, window_surface, nil)
        sdl_free_surface(window_surface_img)
      end

      sdl_update_window_surface(window)
      Process.sleep(3000)
      sdl_free_surface(window_surface)
      img_quit()
      sdl_destroy_window(window)
      sdl_quit()
    end
  end
end
