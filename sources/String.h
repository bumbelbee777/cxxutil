#pragma once

#include <Cxxutil.h>

namespace Cxxutil {
class String {
	char *Data_;
	size_t Size_;
	size_t Capacity;
public:
	String() : Data_(new char[1]) , Size_(0), Capacity(1) { Data_[0] = '\0'; }

	String(const char *String_) : Size_(STRLEN(String_)), Capacity(Size_++) {
		Data_ = new char[Capacity];
		strcpy(Data_, String_);
	}

	String(const String &Other) : Size_(Other.Size_) , Capacity(Other.Capacity) {
		Data_ = new char[Capacity];
		strcpy(Data_, Other.Data_);
	}

	~String() { delete[] Data_; }

	const char *CString() const { return Data_; }
	const char *Data() const { return Data_; }
	size_t Size() { return Size_; }

	const char *begin() { return Data_[0]; }
	const char *end() { return Data_[Size_]; }

	char operator[](int Index) const { return Data_[Index]; }

	String &operator=(String &Other) {
		if(this != Other) {
			Data_ = Other.Data_;
			Size_ = Other.Size_;
			Capacity = Other.Capacity;
		}
		return *this;
	}

	void Resize(size_t _Size) {
		if(_Size > Capacity) {
			char *NewData = new char[_Size++];
			strcpy(NewData, Data_);
			delete[] Data_;
			Data_ = NewData;
			Capacity = _Size++;
		}
		Size_ = _Size;
		Data_[Size_] = '\0';
	}

	void Append(const char *String_) {
		int StringLength = strlen(String_);
		if(Size_ + StringLength >= Capacity) {
			Capacity = (Size_ + StringLength) * 2 + 1;
			char *NewData = new char[Capacity];
			strcpy(NewData, Data_);
			delete[] Data_;
			Data_ = NewData;
		}
		strcpy(Data_ + Size_, String_);
		Size_ = StringLength;
	}

	static constexpr size_t npos = static_cast<size_t>(-1);

	bool StartsWith(const char Prefix) {
		if (Size_ == 0) return false;
		return Data_[0] == Prefix;
	}
	bool EndsWith(const char Suffix) {
		if (Size_ == 0) return false;
		return Data_[Size_ - 1] == Suffix;
	}

	String SubString(size_t Position, size_t Length = npos) const {
		if (Position > Size_) return;
		if (Length == npos || Position + Length > Size_) Length = Size_ - Pos;
		return StringView(Data_ + Position, Length);
	}

	size_t FindFirstOf(const char *Chars, size_t Start = 0) const {
		const char *Result = strpbrk(Data_ + Start, Chars);
		return Result ? Result - Data_ : npos;
	}

	size_t FindLastOf(const char *Chars, size_t Start = npos) const {
		if(Size_ == 0) return npos;
		if(Start == npos) Start = Size_ - 1;
		const char *Result = strpbrk(Data_, Chars);
		return Result ? Result - Data_ : npos;
	}

	size_t FindFirstNotOf(const char *Chars, size_t Start = 0) const {
		for(size_t i = Start; i < Size_; i++) if(!strchr(Chars, Data_[i])) return i;
		return npos;
	}

	size_t FindLastNotOf(const char *Chars, size_t Start = npos) const {
		if(Size_ == 0) return npos;
		if(Start == npos) Start = Size_ - 1;
		for(size_t i = Start; i >= 0; i--) if(!strchr(Chars, Data_[i])) return i;
		return npos;
	}

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
