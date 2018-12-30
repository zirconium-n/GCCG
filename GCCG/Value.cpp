#include "Value.h"
#include <exception>
#include <stdexcept>

Value::Value(Null)
{
}

Value::Value(Boolean v)
	: v_{ std::move(v) }
{
}

Value::Value(Integer v)
	: v_{ std::move(v) }
{
}

Value::Value(String v)
	: v_{ std::move(v) }
{
}

Value::Value(Array v)
	: v_{ std::move(v) }
{
}

Value::Value(Dict v)
	: v_{ std::move(v) }
{
}

Value::Type Value::type() const
{
	return static_cast<Value::Type>(v_.index());
}

bool Value::is_null() const {
	return type() == Type::null;
}

bool Value::is_boolean() const {
	return type() == Type::boolean;
}

bool Value::is_integer() const {
	return type() == Type::integer;
}

bool Value::is_string() const {
	return type() == Type::string;
}

bool Value::is_array() const {
	return type() == Type::array;
}

bool Value::is_dict() const {
	return type() == Type::dict;
}

Value::Boolean Value::boolean() const {
	return std::get<Boolean>(v_);
}

const Value::String& Value::string() const {
	return std::get<String>(v_);
}

const Value::Integer& Value::integer() const {
	return std::get<Integer>(v_);
}

const Value::Array& Value::array() const {
	return std::get<Array>(v_);
}

const Value::Dict& Value::dict() const {
	return std::get<Dict>(v_);
}

const Value & Value::member(std::size_t index) const
{
	return array().at(index);
}

const Value & Value::member(const std::string & index) const
{
	return dict().at(index);
}

void Value::set_member(std::size_t index, Value v)
{
	auto& arr = std::get<Array>(v_);
	if (index >= arr.size()) {
		arr.resize(index + 1);
	}
	arr[index] = std::move(v);
}

void Value::set_member(const std::string & index, Value v)
{
	auto& dict = std::get<Dict>(v_);
	dict.try_emplace(index, std::move(v));
}
