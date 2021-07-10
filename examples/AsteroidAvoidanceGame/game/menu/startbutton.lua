local manager
local renderSystem

function startButtonPressed(data)
	manager:loadScene("game.scene")
	renderSystem:loadURL('about:blank');
end

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	localObject:subscribe(nullptr,"START_BUTTON", startButtonPressed)
end

function update()

end