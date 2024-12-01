# liblk

![License](https://img.shields.io/github/license/R0rt1z2/liblk-cpp)
![GitHub Issues](https://img.shields.io/github/issues-raw/R0rt1z2/liblk-cpp?color=red)

`liblk-cpp` is a faster and more efficient C++ implementation of my old Python based [liblk](https://github.com/R0rt1z2/liblk) library.

## Installation

Clone the repository and follow these steps:

```bash
git clone https://github.com/R0rt1z2/liblk-cpp.git
cd liblk-cpp
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

This will install the library and headers to the default system paths (e.g., `/usr/local`).

## Usage

To use `liblk` in your C++ project, include the main header and link against the library:

### Example Code
Here’s how to list all partitions in an LK image:

```c++
#include <iostream>
#include <liblk/liblk.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <lkimage>" << std::endl;
        return 1;
    }

    liblk::LkImage image(argv[1]);

    for (const auto& partition : image.get_partition_list()) {
        std::cout << partition << std::endl;
    }

    return 0;
}
```

Compile and run the example:
```bash
g++ example.cpp -o example $(pkg-config --cflags --libs liblk)
./example <path_to_lk_image>
```

## License
This project is licensed under the GPL-3.0 License - see the [LICENSE](https://github.com/R0rt1z2/liblk-cpp/tree/master/LICENSE) file for details.