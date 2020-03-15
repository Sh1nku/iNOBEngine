#pragma once
#include <unordered_map>
#include <functional>
#include <string>

class EventManager {
public:
	EventManager();
	virtual ~EventManager();
	void Subscribe(EventManager* to, std::string ev, std::function<void(void*)> func);
	void Unsubscribe(EventManager* to, std::string ev);
	void FireEvent(std::string ev, void* data);
private:
	std::unordered_map < EventManager*, std::vector<std::string>> ref;
};