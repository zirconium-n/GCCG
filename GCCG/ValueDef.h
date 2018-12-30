#pragma once
#include "Value.h"

class NullValue : public Value {
public:
	Type type() const override{
		return Type::null;
	}

	Ptr clone() const override {
		return std::make_shared<NullValue>();
	}
};

class BooleanValue : public Value {
public:
	explicit BooleanValue(bool b)
		: v_{ b }
	{
	}
	Type type() const override {
		return Type::boolean;
	}
	Ptr clone() const override {
		return std::make_shared<BooleanValue>(v_);
	}
private:
	bool v_;
};