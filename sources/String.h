#pragma once

#include <CTypes.h>
#include <Compare.h>

namespace Cxxutil {

class String {
	char *Data_;
	size_t Size_;
	size_t Capacity_;
public:
	String() : Data_(new char[1]), Size_(0), Capacity_(1) {
		Data_[0] = '\0';
	}

	String(const char *String_) : Size_(strlen(String_)), Capacity_(Size_ + 1) {
		Data_ = new char[Capacity_];
		strcpy(Data_, String_);
	}

	String(const String &Other) : Size_(Other.Size_), Capacity_(Other.Capacity_) {
		Data_ = new char[Capacity_];
		strcpy(Data_, Other.Data_);
	}

	String(const char *String, size_t Length) : Data_(String), Size_(Length), Capacity_(Size_ + 1) {
		Data_ = new char[Capacity_];
		strcpy(Data_, String_);
	}

	~String() { delete[] Data_; }

	const char *CString() const { return Data_; }

	const char *Data() const { return Data_; }
	size_t Size() const { return Size_; }
	size_t Length() const { return Size_; }

	const char *begin() const { return *Data_; }
	const char *end() const { return *Data_ + Size_; }

	char operator[](size_t Index) const { return Data_[Index]; }

	String &operator=(const String &Other) {
		if (this != &Other) {
			char *NewData = new char[Other.Capacity_];
			strcpy(NewData, Other.Data_);
			delete[] Data_;
			Data_ = NewData;
			Size_ = Other.Size_;
			Capacity_ = Other.Capacity_;
		}
		return *this;
	}

	void Resize(size_t Size) {
		if (Size > Capacity_) {
			char *NewData = new char[Size + 1];
			strcpy(NewData, Data_);
			delete[] Data_;
			Data_ = NewData;
			Capacity_ = Size + 1;
		}
		Size_ = Size;
		Data_[Size_] = '\0';
	}

	void Append(const char *String) {
		size_t StringLength = strlen(String);
		if (Size_ + StringLength >= Capacity_) {
			Capacity_ = (Size_ + StringLength) * 2 + 1;
			char *NewData = new char[Capacity_];
			strcpy(NewData, Data_);
			delete[] Data_;
			Data_ = NewData;
		}
		strcpy(Data_ + Size_, String);
		Size_ += StringLength;
		Data_[Size_] = '\0';
	}

	static constexpr size_t npos = static_cast<size_t>(-1);

	bool StartsWith(const char Prefix) const {
		return Size_ > 0 && Data_[0] == Prefix;
	}

	bool EndsWith(const char Suffix) const {
		return Size_ > 0 && Data_[Size_ - 1] == Suffix;
	}

	String SubString(size_t Position, size_t Length = npos) const {
		if (Position > Size_) {
			return String();
		}
		if (Length == npos || Position + Length > Size_) {
			Length = Size_ - Position;
		}
		return String(Data_ + Position, Length);
	}

	size_t FindFirstOf(const char *Chars, size_t Start = 0) const {
		const char *Result = strpbrk(Data_ + Start, Chars);
		return Result ? Result - Data_ : npos;
	}

	size_t FindLastOf(const char *Chars, size_t Start = npos) const {
		if(Size_ == 0) return npos;
		if(Start == npos) Start = Size_ - 1;
		const char *Result = nullptr;
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

	char *ToUTF8() const {
		char *Result = new char[Size_ * 3 + 1];
		size_t i = 0;
		for (size_t j = 0; j < Size_; ++j) {
			if ((Data_[j] & 0x80) == 0) {
				Result[i++] = Data_[j];
			} else if ((Data_[j] & 0xE0) == 0xC0) {
				Result[i++] = ((Data_[j] & 0x1F) << 6) | (Data_[j + 1] & 0x3F);
				++j;
			} else if((Data_[j] & 0xF0) == 0xE0) {
				Result[i++] = ((Data_[j] & 0x0F) << 12) | ((Data_[j + 1] & 0x3F) << 6) | (Data_[j + 2] & 0x3F);
				j += 2;
			} else {
				delete[] Result;
				return nullptr;
			}
		}
		Result[i] = '\0';
		return String(Result);
	}

	wchar_t *ToUnicode() {
		wchar_t *Result = new wchar_t[length + 1];
		size_t n = mbstowcs(Result, Data_, Size_);
		if(n == static_cast<size_t>(-1)) {
			delete[] Result;
			return nullptr;
		}
		Result[n] = L'\0';
		return Result;
	}
	char *ToANSI() {
		char *Result = new char[length + 1];
		size_t n = wcstombs(Result, reinterpret_cast<const wchar_t*>(Data_), Size_);
		if(n == static_cast<size_t>(-1)) {
			delete[] Result;
			return nullptr;
		}
		Result[n] = '\0';
		return Result;
	}

	StrongOrdering operator<=>(const String *Other) const {
		int Result = strcmp(Data_, Other->Data_);
		if(Result < 0) return StrongOrdering::Less;
		if(Result > 0) return StrongOrdering::Greater;
		if(Result == 0) return StrongOrdering::Equal;
	}

	bool operator<(const String *Other) const {
		return (this <=> Other) == StrongOrdering::Less;
	}
	bool operator>(const String *Other) const {
		return (this <=> Other) == StrongOrdering::Greater;
	}
	bool operator==(const String *Other) const {
		return (this <=> Other) == StrongOrdering::Equal;
	}
	bool operator<=(const String *Other) const {
		return (this <=> Other) == StrongOrdering::Greater;
	}
	bool operator>=(const String *Other) const {
		return (this <=> Other) == StrongOrdering::Less;
	}
};
}
