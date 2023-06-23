defmodule Sexdl do
  @moduledoc """
  Exports `SDL2/SDL.h` functions.
  """
  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  @on_load :init

  def init, do: :erlang.load_nif(~c"c_src/sdl_nif", 0)

  @spec sdl_init(non_neg_integer) :: :ok | {:error, charlist}
  def sdl_init(_flags), do: nif_not_loaded!()

  @spec sdl_create_window(charlist, integer, integer, integer, integer, integer) ::
          {:ok, integer} | {:error, charlist}
  def sdl_create_window(_title, _x, _y, _w, _h, _flags), do: nif_not_loaded!()

  @spec sdl_get_window_surface(non_neg_integer) :: {:ok, integer} | {:error, charlist}
  def sdl_get_window_surface(_window), do: nif_not_loaded!()

  @spec sdl_update_window_surface(non_neg_integer) :: :ok | {:error, charlist}
  def sdl_update_window_surface(_window), do: nif_not_loaded!()

  @spec sdl_convert_surface(pos_integer, pos_integer) :: {:ok, pos_integer} | {:error, charlist}
  def sdl_convert_surface(_window_surface, _window), do: nif_not_loaded!()

  @spec sdl_blit_surface(pos_integer, non_neg_integer, pos_integer, non_neg_integer) ::
          :ok | {:error, charlist}
  def sdl_blit_surface(_surface_src, _src_rect, _surface_dst, _dst_rect), do: nif_not_loaded!()

  @spec sdl_free_surface(non_neg_integer) :: :ok
  def sdl_free_surface(_window_surface), do: nif_not_loaded!()

  @spec sdl_destroy_window(non_neg_integer) :: :ok
  def sdl_destroy_window(_window), do: nif_not_loaded!()

  @spec sdl_quit() :: :ok
  def sdl_quit(), do: nif_not_loaded!()

  @spec sdl_poll_event(pos_integer) :: non_neg_integer
  def sdl_poll_event(_event), do: nif_not_loaded!()

  def sdl_init_timer, do: 0x00000001
  def sdl_init_audio, do: 0x00000010
  def sdl_init_video, do: 0x00000020
  def sdl_init_joystick, do: 0x00000200
  def sdl_init_haptic, do: 0x00001000
  def sdl_init_gamecontroller, do: 0x00002000
  def sdl_init_events, do: 0x00004000
  def sdl_init_sensor, do: 0x00008000
  def sdl_init_noparachute, do: 0x00100000

  def sdl_init_everything do
    import Bitwise

    sdl_init_timer()
    |> bor(sdl_init_audio())
    |> bor(sdl_init_video())
    |> bor(sdl_init_events())
    |> bor(sdl_init_joystick())
    |> bor(sdl_init_haptic())
    |> bor(sdl_init_gamecontroller())
    |> bor(sdl_init_sensor())
  end

  def sdl_windowpos_centered, do: 0x2FFF0000
  def sdl_windowpos_undefined_mask, do: 0x1FFF0000

  def sdl_window_fullscreen, do: 0x00000001
  def sdl_window_opengl, do: 0x00000002
  def sdl_window_shown, do: 0x00000004
  def sdl_window_hidden, do: 0x00000008
  def sdl_window_borderless, do: 0x00000010
  def sdl_window_resizable, do: 0x00000020
  def sdl_window_minimized, do: 0x00000040
  def sdl_window_maximized, do: 0x00000080
  def sdl_window_mouse_grabbed, do: 0x00000100
  def sdl_window_input_focus, do: 0x00000200
  def sdl_window_mouse_focus, do: 0x00000400
  def sdl_window_fullscreen_desktop, do: Bitwise.bor(sdl_window_fullscreen(), 0x00001000)
  def sdl_window_foreign, do: 0x00000800
  def sdl_window_allow_highdpi, do: 0x00002000
  def sdl_window_mouse_capture, do: 0x00004000
  def sdl_window_always_on_top, do: 0x00008000
  def sdl_window_skip_taskbar, do: 0x00010000
  def sdl_window_utility, do: 0x00020000
  def sdl_window_tooltip, do: 0x00040000
  def sdl_window_popup_menu, do: 0x00080000
  def sdl_window_keyboard_grabbed, do: 0x00100000
  def sdl_window_vulkan, do: 0x10000000
  def sdl_window_metal, do: 0x20000000
  def sdl_window_input_grabbed, do: sdl_window_mouse_grabbed()
end
