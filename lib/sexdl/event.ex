defmodule Sexdl.Event do
  import Sexdl.Utils, only: [nif_not_loaded!: 0]
  defstruct [:type, :ref]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_event_nif", 0)

  @spec new() :: reference
  def new(), do: nif_not_loaded!()

  @spec poll_event(reference) :: non_neg_integer
  def poll_event(_event), do: nif_not_loaded!()

  def sdl_firstevent, do: 0
  def sdl_quit, do: 0x100
  def sdl_app_terminating, do: 0x101
  def sdl_app_lowmemory, do: 0x102
  def sdl_app_willenterbackground, do: 0x103
  def sdl_app_didenterbackground, do: 0x104
  def sdl_app_willenterforeground, do: 0x105
  def sdl_app_didenterforeground, do: 0x106
  def sdl_localechanged, do: 0x107
  def sdl_displayevent, do: 0x150
  def sdl_windowevent, do: 0x200
  def sdl_syswmevent, do: 0x201
  def sdl_keydown, do: 0x300
  def sdl_keyup, do: 0x301
  def sdl_textediting, do: 0x302
  def sdl_textinput, do: 0x303
  def sdl_keymapchanged, do: 0x304
  def sdl_textediting_ext, do: 0x305
  def sdl_mousemotion, do: 0x400
  def sdl_mousebuttondown, do: 0x401
  def sdl_mousebuttonup, do: 0x402
  def sdl_mousewheel, do: 0x403
  def sdl_joyaxismotion, do: 0x600
  def sdl_joyballmotion, do: 0x601
  def sdl_joyhatmotion, do: 0x602
  def sdl_joybuttondown, do: 0x603
  def sdl_joybuttonup, do: 0x604
  def sdl_joydeviceadded, do: 0x605
  def sdl_joydeviceremoved, do: 0x606
  def sdl_joybatteryupdated, do: 0x607
  def sdl_controlleraxismotion, do: 0x650
  def sdl_controllerbuttondown, do: 0x651
  def sdl_controllerbuttonup, do: 0x652
  def sdl_controllerdeviceadded, do: 0x653
  def sdl_controllerdeviceremoved, do: 0x654
  def sdl_controllerdeviceremapped, do: 0x655
  def sdl_controllertouchpaddown, do: 0x656
  def sdl_controllertouchpadmotion, do: 0x657
  def sdl_controllertouchpadup, do: 0x658
  def sdl_controllersensorupdate, do: 0x659
  def sdl_fingerdown, do: 0x700
  def sdl_fingerup, do: 0x701
  def sdl_fingermotion, do: 0x702
  def sdl_dollargesture, do: 0x800
  def sdl_dollarrecord, do: 0x801
  def sdl_multigesture, do: 0x802
  def sdl_clipboardupdate, do: 0x900
  def sdl_dropfile, do: 0x1000
  def sdl_droptext, do: 0x1001
  def sdl_dropbegin, do: 0x1002
  def sdl_dropcomplete, do: 0x1003
  def sdl_audiodeviceadded, do: 0x1100
  def sdl_audiodeviceremoved, do: 0x1101
  def sdl_sensorupdate, do: 0x1200
  def sdl_render_targets_reset, do: 0x2000
  def sdl_render_device_reset, do: 0x2001
  def sdl_pollsentinel, do: 0x7F00
  def sdl_userevent, do: 0x8000
  def sdl_lastevent, do: 0xFFFF
end
