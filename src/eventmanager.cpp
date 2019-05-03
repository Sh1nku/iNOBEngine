#include "eventmanager.h"

std::unordered_map<std::string, std::vector<std::function<void(void*)>>> EventManager::events;

void EventManager::Subscribe(std::string ev, std::function<void(void*)> func) {
	auto& iterator = events.find(ev);
	if (iterator != events.end()) {
		iterator->second.emplace_back(func);
	}
	else {
		events.emplace(ev, std::vector< std::function<void(void*)>> {func});
	}
}

void EventManager::FireEvent(std::string ev, void* data) {
	auto& iterator = events.find(ev);
	if (iterator != events.end()) {
		for (auto& func : iterator->second) {
			std::bind(func, data)();
		}
	}
}