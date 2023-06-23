defmodule Sexdl.Surface do
  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_surface_nif", 0)

  @spec new() :: reference
  def new(), do: nif_not_loaded!()

  @spec convert_surface(reference, reference, non_neg_integer) :: {:ok, reference} | {:error, charlist}
  def convert_surface(_surface, _pixel_format, _flags), do: nif_not_loaded!()

  @spec blit_surface(reference, reference, reference, reference) ::
          :ok | {:error, charlist}
  def blit_surface(_surface_src, _src_rect, _surface_dst, _dst_rect), do: nif_not_loaded!()

  @spec free_surface(reference) :: :ok
  def free_surface(_surface), do: nif_not_loaded!()
end
