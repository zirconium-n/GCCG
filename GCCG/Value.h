#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <variant>

class Value {
public:
	using Null = std::monostate;
	constexpr static Null null = {};
	using Boolean = bool;
	using Integer = std::int64_t;
	using String = std::string;
	using Array = std::vector<Value>;
	using Dict = std::unordered_map<std::string, Value>;
	//using Reference;

	Value() = default;
	Value(Null);
	Value(Boolean v);
	Value(Integer v);
	Value(String v);
	Value(Array v);
	Value(Dict v);

	enum class Type {
		null,
		boolean,
		integer,
		string,
		array,
		dict,
		reference,
	};

	Type type() const;
	bool is_null() const;
	bool is_boolean() const;
	bool is_integer() const;
	bool is_string() const;
	bool is_array() const;
	bool is_dict() const;


	Boolean boolean() const;
	const String& string() const;
	const Integer& integer() const;
	const Array& array() const;
	const Dict& dict() const;

	const Value& member(std::size_t index) const;
	const Value& member(const std::string& index) const;

	void set_member(std::size_t index, Value v);
	void set_member(const std::string& index, Value v);
private:
	std::variant<Null, Boolean, Integer, String, Array, Dict/*, Reference*/> v_;
};
