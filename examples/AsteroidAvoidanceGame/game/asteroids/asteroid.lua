local transform
local manager
local DELETE = -8.0
local timeAlive
local timeDeath = 20

function start()
	transform = localObject:getTransformComponent()
	manager = Manager:getInstance()
	timeAlive = 0
end

function update(dt)
	if not _G.paused then
		timeAlive = timeAlive + dt
		if transform:getWorldPosition().y < DELETE or timeAlive > timeDeath then
			manager:destroy(localObject)
		end
	end
end