defmodule Sexdl.Image do
  @on_load :init

  import Sexdl.Utils, only: [nif_not_loaded!: 0]

  def init, do: :erlang.load_nif(~c"c_src/sdl_image_nif", 0)

  @spec img_init(non_neg_integer) :: integer | none
  def img_init(_flags) do
    nif_not_loaded!()
  end

  @spec img_load(charlist) :: integer | none
  def img_load(_path) do
    nif_not_loaded!()
  end

  @spec img_quit() :: integer
  def img_quit() do
    nif_not_loaded!()
  end

  def img_init_jpg, do: 0x00000001
  def img_init_png, do: 0x00000002
  def img_init_tif, do: 0x00000004
  def img_init_webp, do: 0x00000008
  def img_init_jxl, do: 0x00000010
  def img_init_avif, do: 0x00000020
end
