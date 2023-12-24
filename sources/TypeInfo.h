#pragma once

#include <String.h>
#include <CTypes.h>

namespace Cxxutil {

struct TypeInfoBase {
	TypeInfo() = default;
	TypeInfo(const TypeInfo& Other) = default;
	virtual ~TypeInfo() = default;

	virtual const char* Name() const = 0;
	virtual bool Before(const TypeInfo& Other) const = 0;
	virtual bool operator==(const TypeInfo& Other) const = 0;
	virtual bool operator!=(const TypeInfo& Other) const = 0;
};

template<typename T>
struct TypeInfo : TypeInfoBase {
	virtual const char *Name() const override { return typeid(T).name(); }

	virtual bool Before(const TypeInfo &Other) const override {
		return typeid(T).before(typeid(Other));
	}

	virtual bool operator==(const TypeInfo &Other) const override {
		return typeid(T) == typeid(Other);
	}

	virtual bool operator!=(const TypeInfo &Other) const override {
		return typeid(T) != typeid(Other);
	}
};

constexpr nullptr_t nullptr_val{};

template<class T, class U> struct IsSame {
    static constexpr bool Value = false;
    using type = IsSame;
};

template<class T> struct IsSame<T, T> {
    static constexpr bool Value = true;
    using type = IsSame;
};

struct TrueType {
    static constexpr bool Value = true;
    using type = TrueType;
};

struct FalseType {
    static constexpr bool Value = false;
    using type = FalseType;
};

struct nullopt_t {
    explicit nullopt_t() = default;
};

constexpr nullopt_t nullopt {};

template<class T> struct IsClass {
    template <class U> static constexpr bool Test(int U::*p) { return true; }
    template <class U> static constexpr bool Test(...) { return false; }
    static constexpr bool Value = Test<T>(nullptr);
    using type = IsClass;
};

template<class T> struct IsPointer {
    static constexpr bool Value = false;
    using type = IsPointer;
};

template<class T> struct IsPointer<T*> {
    static constexpr bool Value = true;
    using type = IsPointer;
};

template<class T> struct IsIntegral {
    static constexpr bool Value =
        (IsSame<T, bool>::Value || IsSame<T, char>::Value || IsSame<T, signed char>::Value ||
         IsSame<T, unsigned char>::Value || IsSame<T, wchar_t>::Value ||
         IsSame<T, char16_t>::Value || IsSame<T, char32_t>::Value || IsSame<T, short>::Value ||
         IsSame<T, unsigned short>::Value || IsSame<T, int>::Value || IsSame<T, unsigned int>::Value ||
         IsSame<T, long>::Value || IsSame<T, unsigned long>::Value || IsSame<T, long long>::Value ||
         IsSame<T, unsigned long long>::Value);
    using type = IsIntegral;
};

template<class T> struct IsFloatingPoint : FalseType {};

template<> struct IsFloatingPoint<float> : TrueType {};

template<> struct IsFloatingPoint<double> : TrueType {};

template<> struct IsFloatingPoint<long double> : TrueType {};

template<class T> struct IsInteger {
    static constexpr bool Value = IsIntegral<T>::Value;
    using type = IsInteger;
};

template<class T> struct IsArithmetic {
    static constexpr bool Value = IsInteger<T>::Value || IsFloatingPoint<T>::Value;
    using type = IsArithmetic;
};

template<class T> struct IsString : FalseType {};

template<> struct IsString<const char*> : TrueType {};

template<> struct IsString<char*> : TrueType {};

template<> struct IsString<String> : TrueType {};

template<class T> struct IsLValueReference : FalseType {};

template<class T> struct IsLValueReference<T&> : TrueType {};

template<class Base, class Derived> class IsBaseOf {
    static void Check(const Base&);
    static FalseType Test(const volatile void*);
    static TrueType Test(const volatile Base*);

public:
    static constexpr bool Value = decltype(Test(static_cast<Derived*>(nullptr)))::Value;
    using type = IsBaseOf;
};

template<class T> struct IsArray : FalseType {};

template<class T, size_t N> struct IsArray<T[N]> : TrueType {};

template<class T> struct IsArray<T[]> : TrueType {};

template<class T> struct IsFunction : FalseType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args...)> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args...) const> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args...) volatile> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args...) const volatile> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args......)> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args......) const> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args......) volatile> : TrueType {};

template<class Ret, class... Args> struct IsFunction<Ret(Args......) const volatile> : TrueType {};

template<class T> struct RemoveCV {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveCV<const T> {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveCV<volatile T> {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveCV<const volatile T> {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveReference {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveReference<T&> {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveReference<T&&> {
    using Value = T;
    using type = T;
};

template<class T> struct RemoveCVReference {
    using Value = typename RemoveCV<typename RemoveReference<T>::Value>::Value;
    using type = Value;
};

template<class T> struct RemovePointer {
    using Value = T;
    using type = T;
};

template<class T> struct RemovePointer<T*> {
    using Value = T;
    using type = T;
};

template<class T> struct RemovePointer<T**> {
    using Value = T;
    using type = T;
};

template<bool Condition, class T> struct EnableIf {};

template<class T> struct EnableIf<true, T> {
    using Value = T;
    using type = Value;
};

template<bool Condition, class Expression, class Else> struct Conditional {
    using Value = Expression;
    using type = Value;
};

template<class Expression, class Else> struct Conditional<false, Expression, Else> {
    using Value = Else;
    using type = Value;
};

template<class T> struct UnderlyingType {
    using Value = typename RemoveCV<typename RemoveReference<T>::Value>::Value;
    using type = Value;
};

template<> struct UnderlyingType<bool> {
    using Value = bool;
    using type = Value;
};

template<> struct UnderlyingType<char> {
    using Value = signed char;
    using type = Value;
};

template<> struct UnderlyingType<signed char> {
    using Value = signed char;
    using type = Value;
};

template<> struct UnderlyingType<unsigned char> {
    using Value = unsigned char;
    using type = Value;
};

template<> struct UnderlyingType<wchar_t> {
    using Value = wchar_t;
    using type = Value;
};

template<> struct UnderlyingType<char16_t> {
    using Value = char16_t;
    using type = Value;
};

template<> struct UnderlyingType<char32_t> {
    using Value = char32_t;
    using type = Value;
};

template<> struct UnderlyingType<short> {
    using Value = short;
    using type = Value;
};

template<> struct UnderlyingType<unsigned short> {
    using Value = unsigned short;
    using type = Value;
};

template<> struct UnderlyingType<int> {
    using Value = int;
    using type = Value;
};

template<> struct UnderlyingType<unsigned int> {
    using Value = unsigned int;
    using type = Value;
};

template<> struct UnderlyingType<long> {
    using Value = long;
    using type = Value;
};

template<> struct UnderlyingType<unsigned long> {
    using Value = unsigned long;
    using type = Value;
};

template<> struct UnderlyingType<long long> {
    using Value = long long;
    using type = Value;
};

template<> struct UnderlyingType<unsigned long long> {
    using Value = unsigned long long;
    using type = Value;
};

template<> struct UnderlyingType<float> {
    using Value = float;
    using type = Value;
};

template<> struct UnderlyingType<double> {
    using Value = double;
    using type = Value;
};

template<> struct UnderlyingType<long double> {
    using Value = long double;
    using type = Value;
};

template<class T> struct AddRValueReference {
    using Value = T&&;
    using type = Value;
};
}