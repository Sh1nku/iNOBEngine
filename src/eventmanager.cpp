#include "eventmanager.h"

EventManager::EventManager() {
	counter = 0;

}

int EventManager::Subscribe(std::string ev, std::function<void(void*)> func) {
	int ref;
	if (unused.empty()) {
		ref = counter++;
	}
	else {
		ref = unused.back();
		unused.pop_back();
	}
	auto& iterator = events.find(ev);
	if (iterator != events.end()) {
		iterator->second.emplace(ref, func);
	}
	else {
		events.emplace(ev, std::unordered_map<int, std::function<void(void*)>> {std::pair<int, std::function<void(void*)>>(ref, func)});
	}
	references.emplace(ref, ev);
	return ref;
}

void EventManager::FireEvent(std::string ev, void* data) {
	auto& iterator = events.find(ev);
	if (iterator != events.end()) {
		for (auto& func : iterator->second) {
			std::bind(func.second, data)();
		}
	}
}

void EventManager::Unsubscribe(int ev) {
	auto& iterator = references.find(ev);
	if (iterator != references.end()) {
		auto &it2 = events.find(iterator->second);
		if (it2 != events.end()) {
			it2->second.erase(ev);
		}
		references.erase(iterator);
		unused.push_back(ev);
	}
}