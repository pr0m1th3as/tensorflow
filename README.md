# tensorflow
TensorFlow interface for GNU Octave

**Content:**

1. About
2. Install
3. Contribute

## 1. About
This is an experimental Octave Package for interfacing GNU Octave to the TensorFlow library (`v2.15.0`) through its C API. At the moment, there is only a single dynamically linked octave library (the `tensorflow` function), which is handling the interface between Octave and TensorFlow's C API. This package is at a very early stage of development and the calls to the intermediate **`OCT`** interface might (most likely) change in the near future. Once the **`OCT`** interface supports most of TensorFlow's C API, Octave classdefs will be added as wrappers to facilitate the use of the TensorFlow library through GNU Octave. This package has been inspired by @asteinh's work with [tensorflow.m](https://github.com/asteinh/tensorflow.m).

## 2. Install
The `tensorflow` **`OCT`** interface links against the TensorFlow library (`v2.15.0`) for CPU and GPU on Linux systems only. Other versions have not been tested. Before installing the `tensorflow` Octave Package, you must downloaded and install the required library.

Issuing the following commands from the Linux terminal will download, extract into /urs/local/lib, and make the library visible to the linker.
```
wget https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-linux-x86_64-2.15.0.tar.gz
sudo tar -C /usr/local -xzf libtensorflow-cpu-linux-x86_64-2.15.0.tar.gz
sudo ldconfig /usr/local/lib
```
From within the Octave command, you can install the `tensorflow` package as usual with
```
pkg install tensorflow
```
or install the latest developments (`main`) with
```
pkg install "https://github.com/pr0m1th3as/tensorflow/archive/refs/heads/main.zip"
```

## 3. Contribute
As said, this is an experimental version under development. Few things have been tested so far, most things are likely to have bugs. Feel free to contribute with a [PR](https://github.com/gnu-octave/statistics/pulls) or open an [issue](https://github.com/gnu-octave/statistics/issues) or both!
