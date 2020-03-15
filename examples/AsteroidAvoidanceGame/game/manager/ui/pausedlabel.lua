local manager
local pausedLabel

function start()
	manager = Manager:getInstance()
	localObject:subscribe(nil,"PAUSED", changed)
	pausedLabel = manager:getGameObjectByName("PausedLabel")
end

function update(dt)

end

function changed(paused)
	pausedLabel.active = voidToBool(paused)
end