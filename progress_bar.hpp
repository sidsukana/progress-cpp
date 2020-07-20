#ifndef PROGRESS_BAR_PROGRESS_BAR_HPP
#define PROGRESS_BAR_PROGRESS_BAR_HPP

#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

class ProgressBar {
public:
    ProgressBar(int total, int width, char complete, char incomplete)
            : total_ticks {total},
              bar_width {width},
              complete_char {complete},
              incomplete_char {incomplete}
    {}

    ProgressBar(int total, int width)
            : total_ticks {total},
              bar_width {width}
    {}

    int operator++() {
        ++ticks;
        display();
        stream << "\r";
        return ticks;
    }

    int update(int amount) {
        ticks += amount;
        display();
        stream << "\r";
        return ticks;
    }

    int get() {
        return ticks;
    }

    float progress() {
        return (float) ticks / total_ticks;
    }

    std::chrono::milliseconds time_elapsed() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
    }

    std::chrono::milliseconds eta() {
        return time_elapsed() * (total_ticks - ticks) / ticks;
    }
    
    void finish(const std::string& finish)
    {
        display(true);
        if (!finish.empty()) {
            stream << finish;
        }
        stream << std::endl;
    }
    
    void reset(int total)
    {
        ticks = 0;
        total_ticks = total;
        start_time = std::chrono::steady_clock::now();
        last_display_time = std::chrono::steady_clock::now();
    }

    void display(bool force_redraw=false)
    {
        if (force_redraw || time_since_last_draw() >= time_between_draws)
            last_display_time = std::chrono::steady_clock::now();
        else
            return;

        int pos = (int) (bar_width * progress());

        stream << "["
               << std::string(pos, complete_char) << (pos == bar_width ? "" : ">") << std::string(std::max(bar_width - pos - 1, 0), incomplete_char)
               << "] "
               << int(progress() * 100.f) << "% "
               << std::flush;
    }

private:
    std::chrono::milliseconds time_since_last_draw() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_display_time);
    }

    std::string formatted_duration(std::chrono::milliseconds millis) {
        auto hours = std::chrono::duration_cast<std::chrono::hours>(millis).count();
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(millis).count() - hours * 60;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(millis).count() - minutes * 60;

        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(2) << hours << ":"
            << std::setw(2) << minutes << ":"
            << std::setw(2) << seconds;
        return oss.str();
    }

private:
    int ticks = 0;
    int total_ticks;
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point last_display_time = std::chrono::steady_clock::now();
    
    const int bar_width;
    const char complete_char = '=';
    const char incomplete_char = ' ';
    const std::chrono::milliseconds time_between_draws{500};
    
    std::ostream& stream = std::cout;
};

#endif //PROGRESS_BAR_PROGRESS_BAR_HPP
