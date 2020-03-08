local manager
local renderSystem
local collisionSystem
local animationSystem

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	animationSystem = manager:getAnimationSystem()
	collisionSystem = manager:getCollisionSystem()
	scriptSystem = manager:getScriptSystem()
	renderSystem:setBackgroundColor(0,0,0,1)
end

function update(dt)

end