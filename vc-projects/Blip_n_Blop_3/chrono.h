#pragma once

#include <cassert>
#include <cstdint>

#include <SDL2/SDL.h>

class Chrono {
   private:
    std::uint32_t start_;
    std::uint32_t saved_elapsed_;

   public:
    Chrono() : start_(SDL_GetTicks()), saved_elapsed_(0) {}

    std::uint32_t start() const { return start_; }

    std::uint32_t elapsed() const { return SDL_GetTicks() - start_; }
    std::uint32_t saved_elapsed() const { return saved_elapsed_; }

    void Reset() { start_ = SDL_GetTicks(); }

    void Stop() { saved_elapsed_ = elapsed(); }
};

class Countdown {
   private:
    std::uint32_t end_;

   public:
    Countdown(int duration) : end_(SDL_GetTicks() + duration) {}
    Countdown() : end_(0) {}

    void Reset(int duration) { end_ = SDL_GetTicks() + duration; }

    bool is_zero() const { return int(end_) - int(SDL_GetTicks()) < 0; }
};
