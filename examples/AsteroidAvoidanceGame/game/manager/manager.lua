local manager
local renderSystem

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	renderSystem:setBackgroundColor(0,0,0,1)
end

function update()

end