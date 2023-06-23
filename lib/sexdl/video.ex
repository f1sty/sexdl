defmodule Sexdl.Video do
  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_video_nif", 0)

  # @spec new() :: reference
  # def new(), do: nif_not_loaded!()

  @spec create_window(charlist, integer, integer, integer, integer, integer) ::
          {:ok, reference} | {:error, charlist}
  def create_window(_title, _x, _y, _w, _h, _flags), do: nif_not_loaded!()

  @spec destroy_window(reference) :: :ok
  def destroy_window(_window), do: nif_not_loaded!()

  @spec get_window_surface(non_neg_integer) :: {:ok, integer} | {:error, charlist}
  def get_window_surface(_window), do: nif_not_loaded!()

  @spec update_window_surface(non_neg_integer) :: :ok | {:error, charlist}
  def update_window_surface(_window), do: nif_not_loaded!()
end
