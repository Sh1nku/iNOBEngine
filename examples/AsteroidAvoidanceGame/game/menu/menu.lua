local manager
local renderSystem
local collisionSystem
local animationSystem

function startButtonPressed(data)
	manager:loadScene("game.scene")
end

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	animationSystem = manager:getAnimationSystem()
	collisionSystem = manager:getCollisionSystem()
	scriptSystem = manager:getScriptSystem()
	renderSystem:setBackgroundColor(0,0,0,1)
	renderSystem:loadURL('menu/menu.html');
	localObject:subscribe(nullptr,"START_BUTTON", startButtonPressed)
end

function update(dt)

end