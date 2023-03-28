#pragma once

template <typename T> class Optional {
public:
    Optional() : HasValue_(false) {}
    Optional(const T& Value) : Value_(Value), HasValue_(true) {}
    bool HasValue() const { return HasValue_; }
    T& Value() { return Value_; }
    const T& Value() const { return Value_; }
    void Reset() { HasValue_ = false; }
private:
    T Value_;
    bool HasValue_;
};
