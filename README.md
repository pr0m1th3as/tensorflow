# tensorflow
TensorFlow interface for GNU Octave

**Content:**

1. About
2. Install
3. Contribute

## 1. About
This is an Octave Package for interfacing GNU Octave to the TensorFlow library (`v2.18.0`) through its C API. It runs inference with trained models saved in the SavedModel format:

```matlab
model = TFModel ("path/to/saved_model");
y = model.predict (x);
```

Underneath, `TF_Session`, `TF_Graph` and `TF_Tensor` wrap the corresponding TensorFlow objects, each releasing what it owns when it goes out of scope, and the `tensorflow` function is the intermediate **`OCT`** interface handling the calls to the C API directly. 111 of the 208 exported C API functions are wrapped, covering graph construction and execution; training is not supported, since the layer that makes it usable lives in TensorFlow's Python API and has no counterpart in the C API.

This package has been inspired by @asteinh's work on [tensorflow.m](https://github.com/asteinh/tensorflow.m).


Documentation for the `tensorflow` Octave Package can be found [here](https://pr0m1th3as.github.io/tensorflow/).

## 2. Install
The `tensorflow` **`OCT`** interface links against the TensorFlow C library (`libtensorflow v2.18.0`) on Linux systems only. Before installing the `tensorflow` Octave Package, you must download and install the required library.

Issuing the following commands from the Linux terminal will download, extract into /usr/local/lib, and make the library visible to the linker.
```
wget https://storage.googleapis.com/tensorflow/versions/2.18.0/libtensorflow-cpu-linux-x86_64.tar.gz
sudo tar -C /usr/local -xzf libtensorflow-cpu-linux-x86_64.tar.gz
sudo ldconfig
```
`/usr/local/lib` is already on the loader's search path on most distributions, so plain `ldconfig` is what refreshes the cache; passing it a directory does not necessarily do so, and the symptom is a package that links but fails to load with `libtensorflow.so.2: cannot open shared object file`.

Replace `cpu` with `gpu` in both the URL and the file name for the GPU build, which additionally requires CUDA 12.5 and cuDNN 9.3. Only the CPU build is tested.

**Note on versions.** `v2.18.0` is the last release of `libtensorflow` for Linux x86, so it is the version this package targets and will keep targeting; newer TensorFlow releases ship no C library. A SavedModel exported by a newer TensorFlow normally loads and runs under `v2.18.0`, since the op set used by ordinary models has been stable for years, but a model using ops introduced after `v2.18.0` will be rejected at load time with the offending op named in the returned status.

From within the Octave command, you can install the latest `tensorflow` package as usual with
```
pkg install -forge tensorflow
```
or install the latest developments (`main`) with
```
pkg install "https://github.com/pr0m1th3as/tensorflow/archive/refs/heads/main.zip"
```

## 3. Contribute
As said, this is an experimental version under development. Few things have been tested so far, most things are likely to have bugs. Feel free to contribute with a [PR](https://github.com/pr0m1th3as/tensorflow/pulls) or open an [issue](https://github.com/pr0m1th3as/tensorflow/issues) or both!
