#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <variant>

class Entity;
class Value {
public:
	using Null = std::monostate;
	constexpr static Null null = {};
	using Boolean = bool;
	using Integer = std::int64_t;
	using String = std::string;
	using Array = std::vector<Value>;
	using Dict = std::unordered_map<std::string, Value>;
	using EntityPtr = std::weak_ptr<Entity>;
	//using Reference;

	Value() = default;
	Value(Null);
	Value(Boolean v);
	Value(Integer v);
	Value(String v);
	Value(Array v);
	Value(Dict v);
	Value(EntityPtr v);


	enum class Type {
		null,
		boolean,
		integer,
		string,
		array,
		dict,
		reference,
		entity,
	};

	Type type() const;
	bool is_null() const;
	bool is_boolean() const;
	bool is_integer() const;
	bool is_string() const;
	bool is_array() const;
	bool is_dict() const;
	bool is_entity() const;

	Boolean boolean() const;
	const String& string() const;
	const Integer& integer() const;
	const Array& array() const;
	const Dict& dict() const;

	const Value& member(std::size_t index) const;
	const Value& member(const std::string& index) const;

	void set_member(std::size_t index, Value v);
	void set_member(const std::string& index, Value v);

	friend Value operator+(const Value& lhs, const Value& rhs);
	friend Value operator-(const Value& lhs, const Value& rhs);
	friend Value operator*(const Value& lhs, const Value& rhs);
	friend Value operator/(const Value& lhs, const Value& rhs);
	friend Value operator%(const Value& lhs, const Value& rhs);

	Value operator+() const;
	Value operator-() const;
	Value operator!() const;
private:
 	std::variant<
		Null,
		Boolean,
		Integer,
		String,
		Array,
		Dict,
		EntityPtr
		//, Reference
		//, Function
		//, ...
	> v_;
};
