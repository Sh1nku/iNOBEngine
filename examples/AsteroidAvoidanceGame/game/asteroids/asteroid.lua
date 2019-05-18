local transform
local manager
local DELETE = -8.0

function start()
	transform = localObject:getTransformComponent()
	manager = Manager:getInstance()
end

function update(dt)
	if transform:getWorldPosition().y < DELETE then
		manager:destroy(localObject)
	end
end