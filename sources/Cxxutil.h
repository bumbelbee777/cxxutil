#pragma once

#include <All.h>
#include <string>
#include <pair>
#include <vector>
#include <string_view>
#include <functional>
#include <cstring>
#include <algorithm>
#include <unordered_map>

namespace Cxxutil {

//#define USE_STD

#ifdef USE_STD
    #define STRING std::string
#else
    #define STRING String
#endif

#ifdef USE_STD
	#define STRING_(x) std::string(x)
#else
	#define STRING_(x) String(x)
#endif

#ifdef USE_STD
    #define STRINGVIEW std::string_view
#else
    #define STRINGVIEW StringView
#endif

#ifdef USE_STD
    #define STRINGVIEW_(x) std::string_view(x)
#else
    #define STRINGVIEW_(x) StringView(x)
#endif

#ifdef USE_STD
    #define PAIR(x, y) std::pair<x, y>
#else
    #define PAIR(x, y) Pair<x, y>
#endif

#ifdef USE_STD
    #define FUNCTION(x) std::function<x>
#else
    #define FUNCTION(x) Function<x>
#endif

#ifdef USE_STD
    #define VECTOR(x) std::vector<x>
#else
    #define VECTOR(x) Vector<x>
#endif

#ifdef USE_STD
    #define ITERATOR(x) std::iterator<x>
#else
    #define ITERATOR(x) Iterator(x)
#endif

#ifdef USE_STD
    #define MEMSET(dest, src, n) std::memset(dest, src, n)
#else
    #define MEMSET(dest, src, n) memset(dest, src, n)
#endif

#ifdef USE_STD
    #define COPY(first, last, dest) std::copy(dest, src, n)
#else
    #define COPY(first, last, dest) Copy(dest, src, n)
#endif

#ifdef USE_STD
    #define SWAP(rhs, lhs) std::swap(rhs, lhs)
#else
    #define SWAP(rhs, lhs) Swap(rhs, lhs)
#endif

#ifdef USE_STD
    #define MOVE(rhs, lhs) std::move(rhs, lhs)
#else
    #define MOVE(rhs, lhs) Move(rhs, lhs)
#endif

#ifdef USE_STD
    #define MIN(rhs, lhs) std::min(rhs, lhs)
#else
    #define MIN(rhs, lhs) Min(rhs, lhs)
#endif

#ifdef USE_STD
    #define MAX(rhs, lhs) std::max(rhs, lhs)
#else
    #define MAX(rhs, lhs) Max(rhs, lhs)
#endif

#ifdef USE_STD
	#define HASHMAP(x, y) std::unordered_map<x, y>
#else
	#define HASHMAP(x, y) Hashmap<x, y>
#endif
}
