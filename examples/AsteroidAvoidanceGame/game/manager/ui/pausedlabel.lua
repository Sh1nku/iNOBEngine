local manager
local pausedLabel

function start()
	EventManager.subscribe("PAUSED", changed)
	manager = Manager:getInstance()
	pausedLabel = manager:getGameObjectByName("PausedLabel")
end

function update(dt)

end

function changed(paused)
	pausedLabel.active = voidToBool(paused)
end