#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
template<class T> struct Hash {
	size_t operator()(const T &Value) const {
		uint64_t Hash = 14695981039346656037ull;
		const uint8_t *Data = reinterpret_cast<const uint8_t*>(&Value);
		const uint8_t *End = Data + sizeof(T);
		while(Data != End) {
			Hash ^= static_cast<uint64_t>(*Data++);
			Hash *= 1099511628211ull;
		}
		return static_cast<size_t>(Hash);
	}
};

template<> struct Hash<STRING> {
	size_t operator()(const STRING &String) const {
		size_t Hash = 5381;
		for(char Character : String) {
			Hash = ((Hash << 5) + Hash) + Character;
		}
		return Hash;
	}
};
}
