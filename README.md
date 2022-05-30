# HeadGamer
Tool for gaming with mouse for people with disabilities

# Clone repo
```sh
git clone https://github.com/Da4HuK/HeadGamer.git
git submodule update --init --recursive --remote
```

# How to build project
```sh
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=<path_to_qt_libs>    (e.g. /home/ayaremchuk/Qt5.12.10/5.12.10/gcc_64)
cmake --build . --parallel
```
