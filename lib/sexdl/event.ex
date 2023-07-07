defmodule Sexdl.Event do
  import Sexdl.Utils, only: [nif_not_loaded!: 0]
  defstruct [:type, :ref]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_event_nif", 0)

  @spec new() :: reference
  def new(), do: nif_not_loaded!()

  @spec poll_event(reference) :: non_neg_integer
  def poll_event(_event), do: nif_not_loaded!()

  # TODO: implement all event types
  def sdl_firstevent, do: 0
  def sdl_quit, do: 0x100
  def sdl_app_terminating, do: nil
  def sdl_app_lowmemory, do: nil
  def sdl_app_willenterbackground, do: nil
  def sdl_app_didenterbackground, do: nil
  def sdl_app_willenterforeground, do: nil
  def sdl_app_didenterforeground, do: nil
  def sdl_localechanged, do: nil
  def sdl_displayevent, do: 0x150
  def sdl_windowevent, do: 0x200
  def sdl_syswmevent, do: nil
  def sdl_keydown, do: 0x300
  def sdl_keyup, do: nil
  def sdl_textediting, do: nil
  def sdl_textinput, do: nil
  def sdl_keymapchanged, do: nil
  def sdl_textediting_ext, do: nil
  def sdl_mousemotion, do: 0x400
  def sdl_mousebuttondown, do: nil
  def sdl_mousebuttonup, do: nil
  def sdl_mousewheel, do: nil
  def sdl_joyaxismotion, do: 0x600
  def sdl_joyballmotion, do: nil
  def sdl_joyhatmotion, do: nil
  def sdl_joybuttondown, do: nil
  def sdl_joybuttonup, do: nil
  def sdl_joydeviceadded, do: nil
  def sdl_joydeviceremoved, do: nil
  def sdl_joybatteryupdated, do: nil
  def sdl_controlleraxismotion, do: 0x650
  def sdl_controllerbuttondown, do: nil
  def sdl_controllerbuttonup, do: nil
  def sdl_controllerdeviceadded, do: nil
  def sdl_controllerdeviceremoved, do: nil
  def sdl_controllerdeviceremapped, do: nil
  def sdl_controllertouchpaddown, do: nil
  def sdl_controllertouchpadmotion, do: nil
  def sdl_controllertouchpadup, do: nil
  def sdl_controllersensorupdate, do: nil
  def sdl_fingerdown, do: 0x700
  def sdl_fingerup, do: nil
  def sdl_fingermotion, do: nil
  def sdl_dollargesture, do: 0x800
  def sdl_dollarrecord, do: nil
  def sdl_multigesture, do: nil
  def sdl_clipboardupdate, do: 0x900
  def sdl_dropfile, do: 0x1000
  def sdl_droptext, do: nil
  def sdl_dropbegin, do: nil
  def sdl_dropcomplete, do: nil
  def sdl_audiodeviceadded, do: 0x1100
  def sdl_audiodeviceremoved, do: nil
  def sdl_sensorupdate, do: 0x1200
  def sdl_render_targets_reset, do: 0x2000
  def sdl_render_device_reset, do: nil
  def sdl_pollsentinel, do: 0x7F00
  def sdl_userevent, do: 0x8000
  def sdl_lastevent, do: 0xFFFF
end
