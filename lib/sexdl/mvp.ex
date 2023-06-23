defmodule Sexdl.Mvp do
  alias Sexdl, as: S
  alias Sexdl.Video, as: V
  alias Sexdl.Image, as: I
  alias Sexdl.Surface, as: Sf

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

      Process.sleep(3000)

      Sf.free_surface(window_surface)
      I.quit()
      V.destroy_window(window)
      S.quit()
    end
  end
end
