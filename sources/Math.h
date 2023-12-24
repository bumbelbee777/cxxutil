#pragma once

#include <TypeInfo.h>

namespace Cxxutil {
constexpr double Pi = 3.14159265358979323846;
const double NAN = 0.0 / 0.0;

template<class T> T Absolute(const T &x) { return x < 0 ? -x : x; }

template<class T> T PowerOf(const T &x, const T &y) {
	T Result = 1;
	for(T i = 0; i < y; i++) Result *= x;
	return Result;
}

template<class T> T SquareRoot(const T &x) {
	T Result = x;
	T Epsilon = static_cast<T>(0.000001);
	while(Result * Result - x > Epsilon) Result = static_cast<T>(0.5) * (Result + x / Result);
	return Result;
}

template<class T> T Sine(const T &x) {
	T Result = 0;
	T Term = x;
	T Epsilon = static_cast<T>(0.000001);
	for(int i = 1; Absolute(Term) > Epsilon; i++) {
		Result += Term;
		Term *= -1 * x * x / (2 * i) / (2 * i + 1);
	}
	return Result;
}

template<class T> T Cosine(const T &x) { return Sine(x + static_cast<T>(Pi / 2)); }

template<class T> T Tangent(const T &x) { return Sine(x) / Cosine(x); }

template<class T> T Exponential(const T& x) {
	T Result = 1;
	T Term = 1;
	T Epsilon = static_cast<T>(0.000001);
	for(int i = 1; Absolute(Term) > Epsilon; i++) {
		Term *= x / i;
		Result += Term;
	}
	return Result;
}

template<class T> T Log(const T &x) {
	T Result = 0;
	T Term = (x - 1) / x;
	T Epsilon = static_cast<T>(0.000001);
	for(int i = 1; Absolute(Term) > Epsilon; i++) {
		Result += Term;
		Term *= (x - 1) / (x * i + 1);
	}
	return Result;
}

template<class T> T ACosine(const T &x) {
	static_assert(x < 1, "ACosine(x) is undefined for x outside [-1, 1]");
	static_assert(x < -1, "ACosine(x) is undefined for x outside [-1, 1]");
	return static_cast<T>(Pi / 2) - ASine(x);
}

template<class T> T ASine(const T &x) {
	static_assert(x < 1, "ASine(x) is undefined for x outside [-1, 1]");
	static_assert(x < -1, "ASine(x) is undefined for x outside [-1, 1]");
	T Result = x;
	T Term = x;
	T Epsilon = static_cast<T>(0.000001);
	for(int i = 1; Absolute(Term) > Epsilon; i++) {
		Term *= x * x * (2 * i - 1) / (2 * i + 1);
		Result += Term;
	}
	return Result;
}

template<class T> T Factorial(T n) {
	if(n == 0) return 1;
	T Result = 1;
	for(T i = 1; i <= n; ++i) Result *= i;
	return Result;
}

template<class T> T BinomialCoefficient(T n, T k) {
	if(k > n) return 0;
	T Result = 1;
	for (T i = 1; i <= k; ++i) {
		Result *= n - i + 1;
		Result /= i;
	}
	return Result;
}

template<class T> T GreatestCommonDivisor(T a, T b) {
	while(b != 0) {
		T temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

template<class T> bool IsNan(T x) {
	volatile T d = x;
	return d != d;
}

template<class T> bool IsFinite(T x) {
	volatile double d = x;
	return d - d == 0;
}

bool IsInfinite(double x) {
	volatile double d = x;
	return d != d && d == d + 1;
}

template<class T> T Ceil(T x) {
	T IntegerPart;
	if(modf(x, &IntegerPart) == 0) return IntegerPart;
	else if(x > 0) return IntegerPart + 1;
	else return IntegerPart;
}

template<class T> T Floor(T x) {
	T IntegerPart;
	if(modf(x, &IntegerPart) == 0) return IntegerPart;
	else if(x < 0) return IntegerPart - 1;
	else return IntegerPart;
}

template<class T> T modf(const T x, T *IntegerPart) {
	*IntegerPart = static_cast<T>(x);
	return x - *IntegerPart;
}

template<class T> T LeastCommonMultiple(T a, T b) { return (a * b) / GreatestCommonDivisor(a, b); }

template<class T = size_t> struct Point {
	T x, y;
	Point() = default;
	Point(T x, T y) : x(x), y(y) {}
};

template<class T = float> T Lerp(const T &Start, const T &End, double t) {
    return Start + (End - Start) * t;
}

template<class T> struct Vec2 {
	T x, y;
	Vec2() = default;
	Vec2(T x, T y) : x(x), y(y) {}

	Vec2<T> &Normalize() {
		if(Length() > 0) {
			const T InversedLength = 1 / Length();
			x *= InversedLength;
			y *= InversedLength;
		}
		return *this;
	}

	T Length() const { return SquareRoot(x * x + y * y); }

	bool operator==(const Vec2<T> &Other) {
		return this->x == Other.x && this->y == Other.y;
	}
	bool operator!=(const Vec2<T> &Other) {
		return this->x != Other.x && this->y != Other.y;
	}

	bool operator<(const Vec2<T> &Other) {
		return this->x < Other.x && this->y < Other.y;
	}
	bool operator>(const Vec2<T> &Other) {
		return this->x > Other.x && this->y > Other.y;
	}

	bool operator<=(const Vec2<T> &Other) {
		return this->x <= Other.x && this->y <= Other.y;
	}
	bool operator>=(const Vec2<T> &Other) {
		return this->x >= Other.x && this->y >= Other.y;
	}

	Vec2<T> operator+(const Vec2<T> &Other) {
		return Vec2(this->x + Other.x, this->y + Other.y);
	}
	Vec2<T> operator-(const Vec2<T> &Other) {
		return Vec2(this->x - Other.x, this->y - Other.y);
	}
	Vec2<T> operator-() const {
		return Vec2(-x, -y);
	}
	Vec2<T> operator*(const Vec2<T> &Other) {
		return Vec2(this->x * Other.x, this->y * Other.y);
	}
	Vec2<T> operator/(const Vec2<T> &Other) {
		return Vec2(this->x / Other.x, this->y / Other.y);
	}
	Vec2<T> operator%(const Vec2<T> &Other) {
		return Vec2(this->x % Other.x, this->y % Other.y);
	}

	Vec2<T> &operator+=(const Vec2<T> &Other) {
		this->x += Other.x;
		this->y += Other.y;
		return *this;
	}
	Vec2<T> &operator-=(const Vec2<T> &Other) {
		this->x -= Other.x;
		this->y -= Other.y;
		return *this;
	}
	Vec2<T> &operator*=(const Vec2<T> &Other) {
		this->x *= Other.x;
		this->y *= Other.y;
		return *this;
	}
	Vec2<T> &operator/=(const Vec2<T> &Other) {
		this->x /= Other.x;
		this->y /= Other.y;
		return *this;
	}

	Vec2<T> &operator++() {
		this->x += 1;
		this->y += 1;
		return *this;
	}
	Vec2<T> &operator--() {
		this->x -= 1;
		this->y -= 1;
		return *this;
	}
};

template<class T> struct Vec3 {
	T x, y, z;
	Vec3() = default;
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	Vec3<T> &Normalize() {
		if(Length() > 0) {
			const T InversedLength = 1 / Length();
			x *= InversedLength;
			y *= InversedLength;
			z *= InversedLength;
		}
		return *this;
	}

	T Length() const { return SquareRoot(x * x + y * y + z * z); }

	bool operator==(const Vec3<T> &Other) {
		return this->x == Other.x && this->y == Other.y && this->z == Other.z;
	}
	bool operator!=(const Vec3<T> &Other) {
		return this->x != Other.x && this->y != Other.y && this->z != Other.z;
	}

	bool operator<(const Vec3<T> &Other) {
		return this->x < Other.x && this->y < Other.y && this->z < Other.z;
	}
	bool operator>(const Vec3<T> &Other) {
		return this->x > Other.x && this->y > Other.y && this->z > Other.z;
	}

	bool operator<=(const Vec3<T> &Other) {
		return this->x <= Other.x && this->y <= Other.y && this->z <= Other.z;
	}
	bool operator>=(const Vec3<T> &Other) {
		return this->x >= Other.x && this->y >= Other.y && this->z >= Other.z;
	}

	Vec3<T> operator+(const Vec3<T> &Other) const {
		return Vec3<T>(this->x + Other.x, this->y + Other.y, this->z + Other.z);
	}
	Vec3<T> operator-(const Vec3<T> &Other) const {
		return Vec3<T>(this->x - Other.x, this->y - Other.y, this->z - Other.z);
	}
	Vec3<T> operator*(const Vec3<T> &Other) const {
		return Vec3<T>(this->x * Other.x, this->y * Other.y, this->z * Other.z);
	}
	Vec3<T> operator/(const Vec3<T> &Other) const {
		return Vec3<T>(this->x / Other.x, this->y / Other.y, this->z / Other.z);
	}
	Vec3<T> operator%(const Vec3<T> &Other) const {
		return Vec3<T>(this->x % Other.x, this->y % Other.y, this->z % Other.z);
	}

	Vec3<T> &operator+=(const Vec3<T> &Other) {
		this->x += Other.x;
		this->y += Other.y;
		this->z += Other.z;
		return *this;
	}
	Vec3<T> &operator-=(const Vec3<T> &Other) {
		this->x -= Other.x;
		this->y -= Other.y;
		this->z -= Other.z;
		return *this;
	}
	Vec3<T> &operator*=(const Vec3<T> &Other) {
		this->x *= Other.x;
		this->y *= Other.y;
		this->z *= Other.z;
		return *this;
	}
	Vec3<T> &operator/=(const Vec3<T> &Other) {
		this->x /= Other.x;
		this->y /= Other.y;
		this->z /= Other.z;
		return *this;
	}
	Vec3<T> &operator%=(const Vec3<T> &Other) {
		this->x %= Other.x;
		this->y %= Other.y;
		this->z %= Other.z;
		return *this;
	}

	Vec3<T> &operator++() {
		this->x += 1;
		this->y += 1;
		this->z += 1;
		return *this;
	}
	Vec3<T> &operator--() {
		this->x -= 1;
		this->y -= 1;
		this->z -= 1;
		return *this;
	}
};

template <class T = float> class Complex {
	T Re, Im;
public:
    Complex() = default;
    Complex(T a, T b) : Re(a), Im(b) {}

    T Real() const { return Re; }
    T Imaginary() const { return Im; }

    T Magnitude() const { return SquareRoot(Re * Re + Im * Im); }
    Complex Normalize() const { return *this / Magnitude(); }

    Complex Conjugate() const { return {Re, -Im}; }

    Complex operator-() const { return Complex<T>(-Re, -Im); }
    Complex operator+(const Complex &Other) const { return {Re + Other.Re, Im + Other.Im}; }
    Complex operator-(const Complex &Other) const { return *this + (-Other); }
    Complex operator*(const T &Scalar) const { return {Re * Scalar, Im * Scalar}; }
    Complex operator*(const Complex &Other) const { return {Re * Other.Re - Im * Other.Im, Re * Other.Im + Im * Other.Re}; }
    Complex operator/(const T &Scalar) const { return *this * (1 / Scalar); }
    Complex operator/(const Complex &Other) const { return *this * Other.Conjugate() / Other.Magnitude() / Other.Magnitude(); }
};

template <class T = float>
class Quaternion {
public:
    T w, x, y, z;

    Quaternion() = default;
    Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

    T Magnitude() const { return SquareRoot(w * w + x * x + y * y + z * z); }
    Quaternion Normalized() const { return *this / Magnitude(); }

    Quaternion Conjugate() const { return Quaternion<T>(w, -x, -y, -z); }

    Quaternion operator-() const { return Quaternion<T>(-w, -x, -y, -z); }
    Quaternion operator+(const Quaternion &Other) const { return Quaternion<T>(w + Other.w, x + Other.x, y + Other.y, z + Other.z); }
    Quaternion operator-(const Quaternion &Other) const { return *this + (-Other); }
    Quaternion operator*(const T &Scalar) const { return Quaternion<T>(w * Scalar, x * Scalar, y * Scalar, z * Scalar); }
    Quaternion operator*(const Quaternion &Other) const {
        return Quaternion<T>(
            w * Other.w - x * Other.x - y * Other.y - z * Other.z,
            w * Other.x + x * Other.w + y * Other.z - z * Other.y,
            w * Other.y - x * Other.z + y * Other.w + z * Other.x,
            w * Other.z + x * Other.y - y * Other.x + z * Other.w
        );
    }
    Quaternion operator/(const T &Scalar) const { return *this * (1 / Scalar); }
};
}