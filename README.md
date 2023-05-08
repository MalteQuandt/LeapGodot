## Leap Godot

How to Build on Windows with MSVC:
```sh
cmake -B build -G"Visual Studio 17 2022"  -DCMAKE_BUILD_TYPE=Release -DConfigFilePath=".cmakeconfig"
cmake --build build --config Release
cmake --install build
```