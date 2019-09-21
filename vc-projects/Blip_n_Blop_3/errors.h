#pragma once

#include <stdexcept>

template <class T>
T* SDL_ErrWrap(T* ptr) {
    if (ptr) {
        return ptr;
    }
    throw std::runtime_error(SDL_GetError());
}
