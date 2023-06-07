## Leap Godot

## How to Run

How to Build on Windows with MSVC:
```sh
cmake -B build -G"Visual Studio 17 2022"  -DCMAKE_BUILD_TYPE=Release -DConfigFilePath=".cmakeconfig"
cmake --build build --config Release
cmake --install build
```

## Requirements
This project only supports Windows 10 currently.
It might be possible to get it to run on other versions, and other operating systems with a bit of work, it was not tested.
Additionally, the only supported compiler is visual studio, because of the leap motion controller

## Installation

Clone this Module with the recurse command:
> git clone --recurse <URL_OF_REMOTE>

## Depends On

| Library                                                                                          | Purpose                                                                     |
|--------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------|
| [LeapMotionSDK/V2.3.1](https://developer-archive.leapmotion.com/documentation/v2/cpp/index.html) | Establish connection to the Leap Motion Device and collect the data from it |
| [Godot Template](https://github.com/nathanfranke/gdextension)                                    | Template for building Godot Extension Projects using C++                    |
