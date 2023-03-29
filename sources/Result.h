#pragma once

#include <stdexcept>

namespace Cxxutil {
template <typename T>
class Result {
public:
    Result(const T& Value) : Value_(Value), HasValue_(true) {}
    Result(T&& Value) : Value_(std::move(Value)), HasValue_(true) {}
    Result(const std::exception& Error) : Error_(std::make_exception_ptr(Error)), HasValue_(false) {}
    Result(std::exception_ptr Error) : Error_(Error), HasValue_(false) {}

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
        return std::move(Value_);
    }

    const T&& Value() const&& {
        if (!HasValue_) std::rethrow_exception(Error_);
        return std::move(Value_);
    }

    std::exception_ptr Error() const {
        return Error_;
    }

private:
    bool HasValue_;
    T Value_;
    std::exception_ptr Error_;
};
}