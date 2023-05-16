#include <SharedPointer.h>

namespace Cxxutil {
struct Exception {
	Exception() noexcept {}
	Exception(const Exception &) noexcept = default;
	Exception &operator=(const Exception &) noexcept = default;
	virtual ~Exception() noexcept {}

	virtual const char *What() const noexcept { return "Exception occurred."; }
	virtual const char *what() const noexcept { return "Exception occurred."; }
};

class ExceptionPointer {
	SharedPointer<Exception const> Pointer;

public:
	ExceptionPointer() noexcept
	    : Pointer(nullptr) {}
	bool operator==(const ExceptionPointer &Other) {
		return this->Pointer == Other.Pointer;
	}
	bool operator!=(const ExceptionPointer &Other) const noexcept {
		return Pointer != Other.Pointer;
	}
	bool HasValue() const noexcept { return Pointer != nullptr; }
};
}
}