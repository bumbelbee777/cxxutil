#pragma once

#include <Cxxutil.h>

#ifndef Cxxutil::USE_STD

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
  	for(int i = 0; i < n; i++) {
		temp[i] = csrc[i];
  	}
  	for(int i = 0; i < n; i++) {
		cdest[i] = temp[i];
  	}
}

class Exception {
public:
    Exception() noexcept {}
    Exception(const Exception&) noexcept = default;
    Exception& operator=(const Exception&) noexcept = default;
    virtual ~Exception() noexcept {}

    virtual const char* what() const noexcept {
        return "Exception occurred";
    }
};

class ExceptionPointer {
public:
    ExceptionPointer() = default;
};

using int8_t = signed char;
using int16_t = short;
using int32_t = int;
using int64_t = long long;
using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using uint64_t = unsigned long long;
using size_t = decltype(sizeof(0));
using ptrdiff_t = __PTRDIFF_TYPE__;
using uintptr_t = __UINTPTR_TYPE__;
using ssize_t = ptrdiff_t;

struct Byte : unsigned char {};

template<class T>
const T &Min(const T& a, const T& b) {
    return (b < a) ? b : a;
}

template<class T>
const T &Max(const T& a, const T& b) {
    return (a < b) ? b : a;
}

template<class InputIterator, class OutputIterator>
OutputIterator Copy(InputIterator first, InputIterator last, OutputIterator result) {
    while(first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}

template<class T>
T&& Forward(typename std::remove_reference<T>::type &arg) noexcept {
    return static_cast<T&&>(arg);
}

template<class T>
T&& Forward(typename std::remove_reference<T>::type&& arg) noexcept {
    static_assert(!std::is_lvalue_reference<T>::value, "template argument substituting T is an lvalue reference type");
    return static_cast<T&&>(arg);
}

template<class T>
typename std::remove_reference<T>::type&& Move(T&& t) {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

template<class InputIterator, class T>
InputIterator Find(InputIterator First, InputIterator last, const T &Value) {
    for(; First != Last; First++) if(*First == Value) return First;
    return Last;
}

template<class InputIterator, class Predicate>
InputIterator FindIf(InputIterator First, InputIterator lLst, Predicate Pred) {
    for(; First != Last; ++First) if(*first % 2 == 0) return First;
    return Last;
}

template<class T>
void Swap(T& a, T& b) {
    T tmp = Move(a);
    a = Move(b);
    b = Move(tmp);
}
}

#endif
