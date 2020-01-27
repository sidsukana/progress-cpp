#include "progress_bar.hpp"

#include <iostream>
#include <unistd.h>


/* Example usage of ProgressBar */
int main() {
    const int total = 10000;

    /*
     * Define a progress bar that has a total of 100,
     * a width of 70, shows `=` to indicate completion
     * and a blank space for incomplete
     */
    {
        ProgressBar<> bar(total, 70, '#', '-');
        for (int i = 0; i < total; i++) {
            usleep(200);
            ++bar;
        }
    }
    std::cout << "Done!" << std::endl;
    return 0;
}