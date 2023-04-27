#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T> class Optional {
public:
    Optional() : HasValue_(false) {}
    Optional(const T& Value) : Value_(Value), HasValue_(true) {}
    Optional(const Optional& Other) : HasValue_(Other.HasValue_) {
        if(HasValue_) new(&Value_) T(Other.Value_);
    }
    Optional(Optional &&Other) : HasValue_(Other.HasValue_) {
        if(HasValue_) new(&Value_) T(MOVE(Other.Value_));
        Other.Reset();
    }
    ~Optional() { Reset(); }
    Optional &operator=(const T &Value) {
        if(HasValue_) Value_ = Value;
        else {
            new(&Value_) T(Value);
            HasValue_ = true;
        }
        return *this;
    }
    Optional &operator=(T &&Value) {
        if(HasValue_) Value_ = MOVE(Value);
        else {
            new(&Value_) T(MOVE(Value));
            HasValue_ = true;
        }
        return *this;
    }
    Optional &operator=(const Optional& Other) {
        if(HasValue_ && Other.HasValue_) Value_ = Other.Value_;
        else if(Other.HasValue_) {
            new(&Value_) T(Other.Value_);
            HasValue_ = true;
        } else Reset();
        return *this;
    }
    Optional &operator=(Optional &&Other) {
        if(this != &Other) {
            Reset();
            HasValue_ = Other.HasValue_;
            if(HasValue_) new(&Value_) T(MOVE(Other.Value_));
            Other.Reset();
        }
        return *this;
    }
    bool HasValue() const { return HasValue_; }
    T &Value() { return Value_; }
    const T &Value() const { return Value_; }
    T& operator*() { return Value_; }
    const T& operator*() const { return Value_; }
    T* operator->() { return &Value_; }
    const T* operator->() const { return &Value_; }
    void Reset() {
        if(HasValue_) {
            Value_.~T();
            HasValue_ = false;
        }
    }
private:
    alignas(T) char Storage_[sizeof(T)];
    bool HasValue_;
    T &Value() { return *reinterpret_cast<T*>(Storage_); }
    const T &Value() const { return *reinterpret_cast<const T*>(Storage_); }
};

} // namespace Cxxutil
