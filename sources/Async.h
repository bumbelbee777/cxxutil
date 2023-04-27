#pragma once

#include <Cxxutil.h>
#include <stdexcept>
#include <thread>

namespace Cxxutil {
template<class T> class Future;

template<class T> class Async {
	std::exception_ptr ExceptionPointer;
	T Result;
	bool IsReady = false;
public:
	Async(FUNCTION(T()) Function) : Function(Function) {}

	Future<T> GetFuture() { return Future<T>(this); }

	void Execute() {
		try {
			Result = Function;
			IsReady = true;
		} catch(...) {
			ExceptionPointer = std::current_exception();
		}
	}

	bool Ready() const {
		return IsReady;
	}

	T Get() const {
		if(!IsReady) throw std::runtime_error("Result not ready.");
		if(ExceptionPointer) std::rethrow_exception(ExceptionPointer);
		return Result;
	}

	std::exception_ptr GetExceptionPointer() const { return ExceptionPointer; }
};

template<class T> class Future {
	Async<T> *Async_;
	bool IsReady = false;
public:
	Future() : Async(nullptr) {}
	Future(Async<T> *Async_) Async_(Async_) {}

	bool Ready() const { return IsReady; }

	T Get() const {
		if(!Async_) throw std::runtime_error("Future not associated with any asynchronous operation.");
		return Async_->Get();
	}

	EXCEPTION_PTR GetExceptionPointer() const {
		if(!Async_) throw std::runtime_error("Future not associated with any asynchronous operation.");
		return Async_->GetExceptionPointer();
	}
};

template<typename T>
Future<T> AsyncExecute(FUNCTION(T) Function) {
	Async<T> Async_(Function);
	std::thread Thread(&Async<T>::Execute, &Async_);
	Thread.detach();
	return Async.GetFuture();
}
}
