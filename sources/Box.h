#pragma once

namespace Cxxutil {

template<class T> class Box {
    T* Data;

public:
    Box() : Data(nullptr) {}
    explicit Box(T *Data) : Data(Data) {}
    Box(const Box &Other) : Data(Other.Data ? new T(*Other.Data) : nullptr) {}
    Box &operator=(const Box &Other) {
        if(this != &Other) {
            delete Data;
            Data = Other.Data ? new T(*Other.Data) : nullptr;
        }
        return *this;
    }
    Box(Box &&Other) : Data(Other.Data) { Other.Data = nullptr; }
    Box &operator=(Box &&Other) {
        if(this != &Other) {
            delete Data;
            Data = Other.Data;
            Other.Data = nullptr;
        }
        return *this;
    }
    ~Box() { delete Data; }

    T *operator->() const { return Data; }
    T &operator*() const { return *Data; }

    bool Null() const { return !Data; }

    operator T*() const { return Data; }
};

template<typename T>
Box<T> MakeBox(const T &Value) {
    return Box<T>(new T(Value));
}
} // namespace Cxxutil
