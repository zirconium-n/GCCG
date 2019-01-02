#pragma once

#include "Value.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

class World;

class Entity;

class System {
public:
	bool validate(Entity& e) {
		if (check(e)) {
			entities.insert(&e);
		}
		else {
			entities.erase(&e);
		}
	}

	bool check(const Entity& e) const { 
		for (const auto& attr : required_attr()) {
			if (!e.has_attribute(attr)) {
				return false;
			}
		}
		return true;
	}

	void update() {
		for (auto pEnetity : entities) {
			update_entity(*pEnetity);
		}
	}

protected:
	virtual const std::vector<std::string>& required_attr() const = 0;
	virtual void update_entity(Entity& e) = 0;

private:
	std::unordered_set<Entity*> entities;
};

class ScriptedSystem : public System {

};


class SystemManager {
public:
	void register_system(std::shared_ptr<System> system) {
		systems.push_back(system);
	}

	void validate(Entity& e) const {
		for (auto& sys : systems) {
			sys->validate(e);
		}
	}

private:
	using Mask = std::vector<std::string>;
	std::vector<std::shared_ptr<System>> systems;
};

class World {
	SystemManager sys_manager;
};

class Entity {
public:
	Entity(SystemManager& manager)
		: manager(manager),
		parent(nullptr)
	{
		manager.validate(*this);
	}

	void add_attributes(const std::string& name, Value v) {
		attributes.try_emplace(name, std::move(v));
		manager.validate(*this);
	}

	void remove_attributes(const std::string& name) {
		attributes.erase(name);
		manager.validate(*this);
	}

	bool has_attribute(const std::string& name) {
		return attributes.count(name);
	}
	
	Value make_child() {
		auto child = std::make_shared<Entity>(manager, this);
		children.insert(child);
		return Value::EntityPtr(child);
	}

private:
	Entity(Entity* parent)
		: manager(parent->manager),
		  parent(parent) 
	{
		manager.validate(*this);
	}

	std::unordered_map<std::string, Value> attributes;
	std::unordered_set<std::shared_ptr<Entity>> children;
	Entity* parent = nullptr;
	SystemManager& manager;
};
