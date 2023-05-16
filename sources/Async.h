#pragma once

#include <Function.h>

namespace Cxxutil {
template<class T> class Future;

template<class T> class Async {
	T Result_;
	bool IsReady_ = false;
	Function<T()> Function_;
public:
	Async(Function<T()> Function) : Function_(Function) {}

	Future<T> GetFuture() { return Future<T>(this); }

	void Execute() {
		Result_ = function_();
		IsReady_ = true;
	}

	bool Ready() const { return IsReady_; }

	T Result() const { return Result_; }
};

template<class T> class Future {
	Async<T> *async_;
	bool IsReady_ = false;

public:
	Future() : async_(nullptr) {}
	Future(Async<T> *async) : async_(async) {}

	bool Ready() const { return IsReady_; }

	T Result() const {
		static_assert(async_, "Future<T> not associated with any asynchronous operation.");
		return async_->Result();
	}
};

template<class T> Future<T> AsyncExecute(Function<T()> Function_) {
	Async<T> Async(Function_);
	Async.Execute();
	return Async.Future();
}
}
