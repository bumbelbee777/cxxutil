#pragma once

#include <Exceptions.h>
#include <Utility.h>

namespace Cxxutil {
template <typename T>
class Result {
public:
    Result(const T& Value) : Value_(Value), HasValue_(true) {}
    Result(T&& Value) : Value_(Move(Value)), HasValue_(true) {}
    Result(const Exception &Error) : Error_(std::make_exception_ptr(Error)), HasValue_(false) {}
    Result(ExceptionPointer Error) : Error_(Error), HasValue_(false) {}

    bool HasValue() const { return HasValue_; }

    T& Value() & {
        if (!HasValue_) std::rethrow_exception(Error_);
        return Value_;
    }

    const T& Value() const& {
        if (!HasValue_) std::rethrow_exception(Error_);
        return Value_;
    }

    T&& Value() && {
        if (!HasValue_) std::rethrow_exception(Error_);
        return Move(Value_);
    }

    const T&& Value() const&& {
        if (!HasValue_) std::rethrow_exception(Error_);
        return Move(Value_);
    }

    ExceptionPointer Error() const {
        return Error_;
    }

private:
    bool HasValue_;
    T Value_;
    ExceptionPointer Error_;
};
}