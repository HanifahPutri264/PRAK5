#include "TIMER.h"

void TIMER::Reset() {
    startTime = std::chrono::high_resolution_clock::now();
    pauseTime = 0.0;
    isPaused = false;
}

double TIMER::GetTime() {
    if (isPaused)
        return pauseTime;

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    return elapsed.count();
}

void TIMER::Pause() {
    if (!isPaused) {
        pauseTime = GetTime();
        isPaused = true;
    }
}

void TIMER::Unpause() {
    if (isPaused) {
        startTime = std::chrono::high_resolution_clock::now() -
            std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                std::chrono::duration<double>(pauseTime)
            );
        isPaused = false;
    }
}
