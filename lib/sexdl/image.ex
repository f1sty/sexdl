defmodule Sexdl.Image do
  @moduledoc """
  Exports `SDL2/SDL_image.h` functions.
  """
  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  @on_load :init
  def init, do: :erlang.load_nif(~c"c_src/sdl_image_nif", 0)

  @spec init(non_neg_integer) :: :ok | {:error, charlist}
  def init(_flags), do: nif_not_loaded!()

  @spec load(charlist) :: {:ok, reference} | {:error, charlist}
  def load(_path), do: nif_not_loaded!()

  @spec quit() :: :ok
  def quit(), do: nif_not_loaded!()

  def img_init_jpg, do: 0x00000001
  def img_init_png, do: 0x00000002
  def img_init_tif, do: 0x00000004
  def img_init_webp, do: 0x00000008
  def img_init_jxl, do: 0x00000010
  def img_init_avif, do: 0x00000020
end
