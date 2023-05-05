#pragma once

#include <Strong.h>

namespace Cxxutil {
size_t strlen(const char *String) {
	size_t Length = 0;
	while(String[Length]) Length++;
	return Length;
}

char *strcpy(char *Destination, const char *Source) {
	if(Destination == nullptr) return nullptr;
	char *Pointer = Destination;
	while(*Source != '\0') {
		*Destination = *Source;
		Destination++;
		Source++;
	}
	*Destination = '\0';
	return Pointer;
}

char *strcat(char *Destination, const char *Source) {
	char *ptr = Destination + strlen(Destination);
	while(*Source != '\0') {
		*ptr++ = *Source++;
	}
	*ptr = '\0';
	return Destination;
}

int strcmp(const char *a, const char *b) {
	while(*a && *a == *b) {
		++a;
		++b;
	}
	return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

char *strstr(const char *str, const char *substring) {
	const char *a = str, *b = substring;
	for(;;) {
		if(!*b) return (char *)str;
		if(!*a) return nullptr;
		if(*a++ != *b++) {
			a = ++str;
			b = substring;
		}
	}
}

char *strchr(const char str[], char ch) {
	while(*str && *str != ch) str++;
	return (char *)(ch == *str ? str : nullptr);
}

char *strpbrk(const char *str1, const char *str2) {
	for(const char *p = str1; *p; ++p) if(strchr(str2, *p)) return const_cast<char *>(p);
	return nullptr;
}

void memcpy(void *dest, void *src, size_t n) {
	int i;
	char *src_char = (char *)src;
	char *dest_char = (char *)dest;
	for(i = 0; i < n; i++) {
		dest_char[i] = src_char[i];
	}
}

void memset(void *str, char ch, size_t n) {
	char *s = (char *)str;
	for(size_t i = 0; i < n; i++) s[i] = ch;
}

void memmove(void *dest, void *src, size_t n) {
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	char temp[n];
	for(int i = 0; i < n; i++) temp[i] = csrc[i];
	for(int i = 0; i < n; i++) cdest[i] = temp[i];
}

using int8_t = signed char;
using int16_t = short;
using int32_t = int;
using int64_t = long long;
using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using uint64_t = unsigned long long;
using size_t = uint64_t;
using ptrdiff_t = __PTRDIFF_TYPE__;
using uintptr_t = __UINTPTR_TYPE__;
using ssize_t = ptrdiff_t;

class Byte {
	uint8_t Value;
public:
	Byte() = default;
	Byte(uint8_t Value) : Value(Value) {}

	Byte operator+(const Byte &Other) const { return Byte(Value + Other.Value); }
	Byte operator-(const Byte &Other) const { return Byte(Value - Other.Value); }
	Byte operator*(const Byte &Other) const { return Byte(Value * Other.Value); }
	Byte operator/(const Byte &Other) const { return Byte(Value / Other.Value); }
	Byte operator%(const Byte &Other) const { return Byte(Value % Other.Value); }
	Byte operator|(const Byte &Other) const { return Byte(Value | Other.Value); }
	Byte operator^(const Byte &Other) const { return Byte(Value ^ Other.Value); }
	Byte operator~(const Byte &Other) const { return Byte(~Value); }
	
	Byte operator<<(const Byte &Other) const { return Byte(Value << Other.Value); }
	Byte operator>>(const Byte &Other) const { return Byte(Value >> Other.Value); }

	Byte operator++() const { return Byte(Value + 1); }
	Byte operator--() const { return Byte(Value - 1); }

	Byte operator+=(const unsigned char Value_) const { return Byte(Value_ + Value); }
	Byte operator-=(const unsigned char Value_) const { return Byte(Value_ - Value); }
	Byte operator*=(const unsigned char Value_) const { return Byte(Value_ * Value); }
	Byte operator/=(const unsigned char Value_) const { return Byte(Value_ / Value); }
	Byte operator%=(const unsigned char Value_) const { return Byte(Value_ % Value); }
	Byte operator|=(const unsigned char Value_) const { return Byte(Value_ | Value); }
	Byte operator^=(const unsigned char Value_) const { return Byte(Value_ ^ Value); }
	Byte operator~=(const unsigned char Value_) const { return Byte(~Value); }
	Byte operator<<=(const unsigned char Value_) const { return Byte(Value_ << Value); }
	Byte operator>>=(const unsigned char Value_) const { return Byte(Value_ >> Value); }

	bool operator==(const Byte &Other) const { return Value == Other.Value; }
	bool operator!=(const Byte &Other) const { return !(*this == Other); }
	bool operator<(const Byte &Other) const { return Value < Other.Value; }
	bool operator>(const Byte &Other) const { return Other < *this; }
	bool operator<=(const Byte &Other) const { return !(Other < *this); }
	bool operator>=(const Byte &Other) const { return !(*this < Other); }
};
}