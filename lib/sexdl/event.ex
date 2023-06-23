defmodule Sexdl.Event do
  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_event_nif", 0)

  @spec new() :: reference
  def new(), do: nif_not_loaded!()

  @spec poll_event(reference) :: non_neg_integer
  def poll_event(_event), do: nif_not_loaded!()
end
