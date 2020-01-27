Progress-CPP
===

A flexible ASCII progress bar for your console based C++ projects.

### Usage
Progress is a header-only library and can be used by simply including the `progress_bar.hpp` header file.

The bar takes the following options at initialization
- Limit: the total number of ticks that need to be completed
- Width: width of the bar
- Complete Char: the character to indicate completion (defaults to `=`)
- Incomplete Char: the character to indicate pending. (defaults to ' ')

```c++
#include "ProgressBar.hpp"

int main() {

    const int limit = 10000;

    {
        // Initialize the bar
        ProgressBar<> progressBar(total, 70);
        for (int i = 0; i < total; i++) {
            // Simulate work
            usleep(200); 
            
            // Update the progress bar
            ++progressBar;
        }
    } // Bar finishes here
}
```
The above code results in the following output

```
[=======================>                                               ] 33% [00:00:01<00:00:01]
```

### Example
Refer to [main.cpp](main.cpp) file for an example usage. To run it,

```
$ mkdir build && cd build
$ cmake ..
$ make
$ ./progress_bar
```

Or without `cmake`
```
$ g++ -O3 -I. main.cpp -Wall -std=c++11 -o progress_bar
$ ./progress_bar
```

### License
MIT
