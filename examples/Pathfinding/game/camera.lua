local renderSystem
local manager

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	renderSystem:setBackgroundColor(0.0, 0.0, 0.0, 1.0)
end

function update(dt)

end