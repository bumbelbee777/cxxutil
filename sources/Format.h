#pragma once

#include <TypeInfo.h>
#include <HeapAllocator.h>
#include <Utility.h>
#include <String.h>

namespace Cxxutil {
int FormatBuffer(char *str, size_t size, const char *Format, ...) {
	va_list args;
	va_start(args, Format);
    
	int Written = 0;
	size_t Remaining = size;
	const char*Source = Format;
	char *Destination = str;
	
	while(*Source && Remaining) {
		if(*Source == '%') {
			Source++;
			if(*Source == '\0') break;
			if (*Source == '%') {
				*Destination++ = '%';
				Written++;
				Remaining--;
				Source++;
				continue;
			}
			int Width = 0;
			while (*Source >= '0' && *Source <= '9') {
				Width = Width * 10 + (*Source - '0');
				Source++;
			}
			int Precision = -1;
			if (*Source == '.') {
				Source++;
				Precision = 0;
				while (*Source >= '0' && *Source <= '9') {
					Precision = Precision * 10 + (*Source - '0');
					Source++;
				}
			}
			if (*Source == 's') {
				const char* s = va_arg(args, const char*);
				int len = strlen(s);
				if (Precision >= 0 && Precision < len) {
					len = Precision;
				}
				while (Width > len && Remaining > 1) {
					*Destination++ = ' ';
					Width--;
					Remaining--;
					Written++;
				}
				while (*s && len && Remaining > 1) {
					*Destination++ = *s++;
					len--;
					Remaining--;
					Written++;
				}
				while (Width > 0 && Remaining > 1) {
					*Destination++ = ' ';
					Width--;
					Remaining--;
					Written++;
				}
			} else if (*Source == 'd') {
				int num = va_arg(args, int);
				int len = 0;
				if (num < 0) {
					*Destination++ = '-';
					num = -num;
					len++;
					Remaining--;
					Written++;
				}
				int tmp = num;
				do {
					tmp /= 10;
					len++;
				} while (tmp);
				while (Width > len && Remaining > 1) {
					*Destination++ = ' ';
					Width--;
					Remaining--;
					Written++;
				}
				char* p = Destination + len - 1;
				do {
					*p-- = '0' + (num % 10);
					num /= 10;
				} while (num);
				Destination += len;
				Remaining -= len;
				Written += len;
				while (Width > 0 && Remaining > 1) {
					*Destination++ = ' ';
					Width--;
					Remaining--;
					Written++;
				}
			} else {
				*Destination++ = '%';
				while (*Source && *Source != '%') {
					*Destination++ = *Source++;
					Written++;
					Remaining--;
				}
				continue;
			}
			Source++;
		} else {
			*Destination++ = *Source++;
			Written++;
			Remaining--;
		}
	}
	if (Remaining > 0) {
		*Destination = '\0';
	} else if (size > 0) {
		str[size - 1] = '\0';
	}
	va_end(args);
	return Written;
}

template<size_t Index, class T, class... Args> typename EnableIf<Index == 0, T>::Value
GetArgument(const T &Argument, const Args&...) {
	return Argument;
}

template<size_t Index, class T, class... Args> typename EnableIf<Index != 0, T>::Value
GetArgument(const T&, const Args&... Arguments) {
	return GetArgument<Index - 1>(Arguments...);
}

template<class... Args> String Format(const char *Format, Args&&... Arguments) const {
	String Result;
	char *Buffer;
	char *Iterator = Format;
	while(*Iterator) {
		if(Iterator == '{' && *Iterator++ == '}') {
			if constexpr(IsInteger<Forward<Args>(Arguments)...>) {
				Buffer = reinterpret_cast<char*>(Heap.Allocate(sizeof(int*)));
				Result.Append(Buffer);
			}
		}
	}
	return Result;
}
}