#pragma once

#include "Value.h"
#include <vector>
#include <unordered_set>

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
			if (!e.has_attr(attr)) {
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
	// pos + velo -> positioning
	void register_compo(/*, System ???*/);

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

	void add_component(const std::string& name, Value v) {
		components.try_emplace(name, std::move(v));
		manager.validate(*this);
	}

	void remove_component(const std::string& name) {
		components.erase(name);
		manager.validate(*this);
	}

private:
	std::unordered_map<std::string, Value> components;
	CompoManager& manager;
};
