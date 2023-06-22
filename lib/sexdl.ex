defmodule Sexdl do
  @moduledoc """
  Exports `SDL2/SDL.h` funcions.
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

  @spec sdl_free_surface(non_neg_integer) :: :ok
  def sdl_free_surface(_window_surface), do: nif_not_loaded!()

  @spec sdl_destroy_window(non_neg_integer) :: :ok
  def sdl_destroy_window(_window), do: nif_not_loaded!()

  @spec sdl_quit() :: :ok
  def sdl_quit(), do: nif_not_loaded!()

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
  def sdl_window_shown, do: 0x00000004
end
