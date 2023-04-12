#pragma once

template<class T, class Tag>
class Strong {
	T Value;
public:
    explicit Strong(T const& Value) : Value(Value) {}
    T& Get() { return Value; }
    T const& Get() const { return Value; }
};
