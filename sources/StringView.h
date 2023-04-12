#pragma once

#include <Cxxutil.h>
#include <compare>

namespace Cxxutil {
class StringView {
  const char *Data_ = nullptr;
  size_t Size_ = 0;

public:
  	StringView(const char *String) : Data_(String), Size_(strlen(String)) {}
  	StringView(const char *String, size_t _Size) : Data_(String), Size_(_Size) {}

  	const char *Data() const { return Data_; }
  	size_t Size() const { return Size_; }

	const char *begin() const { return Data_[0]; }
	const char *end() const { return Data_[Size_]; }
  	const char *cbegin() const { return Data_; }
  	const char *cend() const { return Data_ + Size_; }

  	char operator[](size_t Position) {
		if(Position >= Size_) return 0;
		return At(Position);
  	}

  	char At(size_t Position) { return Data_[Position]; }

  	static constexpr size_t npos = static_cast<size_t>(-1);

  	bool StartsWith(const char Prefix) {}
  	bool EndsWith(const char Suffix) {}

  	std::strong_ordering operator<=>(const String *Other) const {
		int Result = strcmp(Data_, Other->Data_);
		if(Result < 0) return std::strong_ordering::less;
		if(Result > 0) return std::strong_ordering::greater;
		if(Result == 0) return std::strong_ordering::equal;
  	}	

  	bool operator<(const String *Other) const {
		return (this <=> Other) == std::strong_ordering::less;
  	}
  	bool operator>(const String *Other) const {
		return (this <=> Other) == std::strong_ordering::greater;
  	}
  	bool operator==(const String *Other) const {
		return (this <=> Other) == std::strong_ordering::equal;
  	}
  	bool operator<=(const String *Other) const {
		return (this <=> Other) == std::strong_ordering::greater;
 	}
  	bool operator>=(const String *Other) const {
		return (this <=> Other) == std::strong_ordering::less;
  	}
};
}
