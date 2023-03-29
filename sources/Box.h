#pragma once

namespace Cxxutil {
template<class T> class Box {
    T *Data;
public:
    Box() : Data(nullptr) {}
    Box(T *Data) : Data(Data) {}
    ~Box() { delete Data; }

    T *operator->() const { return Data; }
    T &operator*() const { return *Data; }
};

template<typename T>
Box<T> MakeBox(const T &Value) {
    return Box<T>(Value);
}
}