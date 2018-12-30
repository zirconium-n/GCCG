#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

class Value : public std::enable_shared_from_this<Value>{
public:
	Value() = default;
	Value(const Value&) = delete;
	Value(Value&&) = delete;
	Value& operator=(const Value&) = delete;
	Value& operator=(Value&&) = delete;

	using Ptr = std::shared_ptr<Value>;
	using Const_ptr = std::shared_ptr<const Value>;

	enum class Type {
		null,
		boolean,
		integer,
		string,
		array,
		dict,
	};

	virtual Type type() const = 0;
	bool is_null() const;
	bool is_boolean() const;
	bool is_integer() const;
	bool is_string() const;
	bool is_array() const;
	bool is_dict() const;

	
	virtual bool get_bool() const;
	virtual std::string get_string() const;
	virtual std::int64_t get_integer() const;
	
	virtual std::vector<Ptr> get_array() const;
	virtual std::unordered_map<std::string, Ptr> get_dict() const;

	virtual Ptr operator[](std::size_t index) const;
	virtual Ptr operator[](const std::string& index) const;



	virtual Ptr clone() const = 0;

	virtual ~Value() = default;
};



