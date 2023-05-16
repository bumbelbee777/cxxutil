#pragma once

#include <CTypes.h>
#include <Compare.h>

namespace Cxxutil {
class StringView {
  const char *Data_ = nullptr;
  size_t Size_ = 0;
public:
  	StringView(const char *String) : Data_(String), Size_(strlen(String)) {}
  	StringView(const char *String, size_t _Size) : Data_(String), Size_(_Size) {}

  	const char *Data() const { return Data_; }
  	size_t Size() const { return Size_; }
	size_t Length() const { return Size_; }

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

	bool StartsWith(const char Prefix) const {
		return Size_ > 0 && Data_[0] == Prefix;
	}
	bool EndsWith(const char Suffix) const {
		return Size_ > 0 && Data_[Size_ - 1] == Suffix;
	}

	bool Contains(const char *String) {
		return (strstr(Data_, String) != nullptr);
	}
	bool Contains(String &String) {
		return (strstr(Data_, String.CString()) != nullptr);
	}

	size_t Find(const char *String, size_t Start = 0) const {
		const char *Found = strstr(Data_ + Start, String);
		return Found ? Found - Data_ : npos;
	}

  	StrongOrdering operator<=>(const StringView *Other) const {
		int Result = strcmp(Data_, Other->Data_);
		if(Result < 0) return StrongOrdering::Less;
		if(Result > 0) return StrongOrdering::Greater;
		if(Result == 0) return StrongOrdering::Equal;
  	}	

  	bool operator<(const StringView *Other) const {
		return (this <=> Other) == StrongOrdering::Less;
  	}
  	bool operator>(const StringView *Other) const {
		return (this <=> Other) == StrongOrdering::Greater;
  	}
  	bool operator==(const StringView *Other) const {
		return (this <=> Other) == StrongOrdering::Equal;
  	}
  	bool operator<=(const StringView *Other) const {
		return (this <=> Other) == StrongOrdering::Greater;
 	}
  	bool operator>=(const StringView *Other) const {
		return (this <=> Other) == StrongOrdering::Equal;
  	}
};
}
