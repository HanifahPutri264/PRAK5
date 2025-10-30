#ifndef TIMER_H
#define TIMER_H

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>  // Tetap pakai ini di macOS
#include <chrono>       // Gantikan mmsystem.h

class TIMER {
public:
    TIMER() : isPaused(false) {
        Reset();
    }

    ~TIMER() {}

    void Reset();
    double GetTime();
    void Pause();
    void Unpause();

protected:
    bool isPaused;
    double pauseTime;
    std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMER_H
