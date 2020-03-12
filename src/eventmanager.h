#pragma once
#include <unordered_map>
#include <functional>

class EventManager {
public:
	EventManager();
	int Subscribe(std::string ev, std::function<void(void*)> func);
	void FireEvent(std::string ev, void* data);
	void Unsubscribe(int ev);
private:
	std::unordered_map<std::string, std::unordered_map<int, std::function<void(void*)>>> events;
	long counter;
	std::vector<int> unused;
	std::unordered_map<int, std::string> references;
};