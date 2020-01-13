local SPEED = 2.0
local SCROLL_START = 8.0
local SCROLL_END = 0.0
local transform

function start()
	transform = localObject:getTransformComponent()
end

function update(dt)
	if not _G.paused then
		local position = transform:getWorldPosition()
		if position.y < SCROLL_END then
			transform:setPosition(Vec3(position.x, SCROLL_START, position.z))
		else
		transform:setPosition(Vec3(position.x, position.y - (SPEED * dt), position.z))
		end
	end
end