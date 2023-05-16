#pragma once

namespace Cxxutil {
template<typename Function> class Function;

template<typename ReturnValue, typename... Arguments> class Function<ReturnValue(Arguments...)> {
public:
    template<typename func>
    Function(func t) : callable_(new CallableFunction<func>(t)) {}

    ~Function() { this->clear(); }

    void Clear() {
        if(this->callable_ == nullptr) return;
        delete this->callable_;
    }

    template<typename func>
    Function &operator=(func t) {
        if(this->callable_ != nullptr) delete this->callable_;
        this->callable_ = new CallableFunction<func>(t);
        return *this;
    }

    ReturnValue operator()(Arguments... args) const {
        if(this->callable_ == nullptr) return ReturnValue();
        return this->callable_->Invoke(args...);
    }

    bool operator==(bool Set) { return (this->callable_ != nullptr) == Set; }

private:
    class Callable {
    public:
        virtual ~Callable() = default;
        virtual ReturnValue invoke(Arguments...) = 0;
    };

    template<typename func>
    class CallableFunction : public Callable {
    public:
        CallableFunction(func t) : t_(t) {}
        ~CallableFunction() override = default;

        ReturnValue Invoke(Arguments... args) override { return t_(args...); }
    private:
        func t_;
    };
    Callable *callable_;
};
}