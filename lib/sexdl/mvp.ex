defmodule Sexdl.Mvp do
  alias Sexdl, as: S
  alias Sexdl.Image

  def run(title, width \\ 600, height \\ 600, bg_image_path \\ nil) do
    with 0 = S.sdl_init(S.sdl_init_video()),
         window when window != 0 <-
           S.sdl_create_window(
             title,
             S.sdl_windowpos_centered(),
             S.sdl_windowpos_centered(),
             width,
             height,
             S.sdl_window_shown()
           ),
         img_type <- Image.img_init_png(),
         ^img_type = Image.img_init(img_type),
         window_surface <- S.sdl_get_window_surface(window) do
      S.sdl_update_window_surface(window)
      Process.sleep(3000)
      S.sdl_free_surface(window_surface)
      Image.img_quit()
      S.sdl_destroy_window(window)
      S.sdl_quit()
    end
  end
end

#         optimazed_surface =
#             SDL_ConvertSurface(image_surface, window_surface->format, 0);
#         if (optimazed_surface == NULL) {
#           printf("Error converting surface: %s\n", IMG_GetError());
#         }
#         SDL_FreeSurface(image_surface);
#       }
#     }
#
#     SDL_BlitSurface(optimazed_surface, NULL, window_surface, NULL);
#     SDL_UpdateWindowSurface(window);
#     SDL_Delay(3000);
#   }
# }
#
# IMG_Quit();
# SDL_DestroyWindow(window);
# SDL_Quit();
