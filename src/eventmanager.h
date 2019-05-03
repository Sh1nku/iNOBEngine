#pragma once
#include <unordered_map>
#include <functional>

class EventManager {
public:
	static void Subscribe(std::string ev, std::function<void(void*)> func);
	static void FireEvent(std::string ev, void* data);
private:
	static std::unordered_map<std::string, std::vector<std::function<void(void*)>>> events;
};