# Peakwork Development Challenge - C++
## Required
    1. Visual Studio (V16) / GCC (V7.X)
    2. CMake (V3.x)
    3. Python (V3.x)
    4. Conan package manager
    
### Conan packages
    1. jsoncpp/1.9.0@theirix/stable
    2. libcurl/7.64.1@bincrafters/stable

## Important note
Make sure the bincrafters repository is added to the conan remote list
```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

## How to build
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release/Debug
cmake --build . --config Release/Debug 
```

## How to run
```
cd build/bin
peakwork_challange <symbol> <iex_secret_token>
```
