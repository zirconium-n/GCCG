#include "Value.h"
#include <exception>
#include <stdexcept>

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

bool Value::get_bool() const {
	throw std::runtime_error("");
}

std::string Value::get_string() const {
	throw std::runtime_error("");
}

std::int64_t Value::get_integer() const {
	throw std::runtime_error("");
}

std::vector<Value::Ptr> Value::get_array() const {
	throw std::runtime_error("");
}

std::unordered_map<std::string, Value::Ptr> Value::get_dict() const {
	throw std::runtime_error("");
}

Value::Ptr Value::operator[](std::size_t index) const {
	throw std::runtime_error("");
}

Value::Ptr Value::operator[](const std::string & index) const {
	throw std::runtime_error("");
}
