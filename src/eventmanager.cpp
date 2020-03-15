#include "eventmanager.h"
#include "manager.h"

EventManager::EventManager() {

}

EventManager::~EventManager() {
	Manager* manager = Manager::GetInstance();
	for (auto& ev : ref) {
		for (auto& string : ev.second) {
			manager->Unsubscribe(ev.first, string, this);
		}
	}
	manager->RemoveFromEvent(this);
}

void EventManager::Subscribe(EventManager* to, std::string ev, std::function<void(void*)> func) {
	Manager::GetInstance()->Subscribe(to, ev, this, func);
	if (ref.find(to) == ref.end()) {
		ref.emplace(to, std::vector<std::string>());
	}
	ref.find(to)->second.push_back(ev);
}

void EventManager::Unsubscribe(EventManager* to, std::string ev) {
	if (ref.find(to) != ref.end()) {
		auto& i = ref.at(to);
		auto it = std::find(i.begin(), i.end(), ev);
		if (it != i.end()) {
			i.erase(it);
			Manager::GetInstance()->Unsubscribe(to, ev, this);
		}
	}
}

void EventManager::FireEvent(std::string ev, void* data) {
	Manager::GetInstance()->FireEvent(this, ev, data);
}
