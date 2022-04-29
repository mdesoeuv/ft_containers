#pragma once

#include <stddef.h>
#include <iostream>
#include "test.hpp"

template <typename T = char>
class Recorder {

public:
    static size_t constructor_calls;
    static size_t default_constructor_calls;
    static size_t copy_constructor_calls;
    static size_t assignment_operator_calls;
    static size_t destructor_calls;
    static size_t instance_count;

    T inner;

    Recorder() : inner() {
        constructor_calls += 1;
        default_constructor_calls += 1;
        instance_count += 1;
    }

    Recorder(const Recorder& other) : inner(other.inner) {
        constructor_calls += 1;
        copy_constructor_calls += 1;
        instance_count += 1;
    }

    Recorder(const T& inner) : inner(inner) {
        constructor_calls += 1;
        copy_constructor_calls += 1;
        instance_count += 1;
    }

    ~Recorder() {
        destructor_calls += 1;
        instance_count -= 1;
    }

    Recorder& operator=(const Recorder& other) {
        assignment_operator_calls += 1;
        inner = other.inner;
        return (*this);
    }

    operator T&() {
        return inner;
    }

    static void reset() {
        assert(instance_count == 0);
        constructor_calls = 0;
        default_constructor_calls = 0;
        copy_constructor_calls = 0;
        assignment_operator_calls = 0;
        destructor_calls = 0;
        instance_count = 0;
    }

    static void show_stats() {
        std::cout
            << "constructor_calls = " << constructor_calls << std::endl
            << "default_constructor_calls = " << default_constructor_calls << std::endl
            << "copy_constructor_calls = " << copy_constructor_calls << std::endl
            << "assignment_operator_calls = " << assignment_operator_calls << std::endl
            << "destructor_calls = " << destructor_calls << std::endl
            << "instance_count = " << instance_count << std::endl;
    }
};

template <typename T>
bool operator==(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner == b.inner;
}

template <typename T>
bool operator!=(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner != b.inner;
}

template <typename T>
bool operator<(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner < b.inner;
}

template <typename T>
bool operator>(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner > b.inner;
}

template <typename T>
bool operator<=(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner <= b.inner;
}

template <typename T>
bool operator>=(const Recorder<T>& a, const Recorder<T>& b) {
    return a.inner >= b.inner;
}

template <typename T>
size_t Recorder<T>::constructor_calls = 0;
template <typename T>
size_t Recorder<T>::default_constructor_calls = 0;
template <typename T>
size_t Recorder<T>::copy_constructor_calls = 0;
template <typename T>
size_t Recorder<T>::assignment_operator_calls = 0;
template <typename T>
size_t Recorder<T>::destructor_calls = 0;
template <typename T>
size_t Recorder<T>::instance_count = 0;
