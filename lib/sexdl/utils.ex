defmodule Sexdl.Utils do
  defmodule NifNotLoaded do
    defexception [:message]
  end

  def nif_not_loaded! do
    raise NifNotLoaded, message: "could not load nif"
  end
end
