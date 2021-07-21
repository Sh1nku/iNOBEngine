local timeAlive
local timeDie = 5
local manager
local BULLET_SPEED = 20
local collision
local renderSystem

function start()
	timeAlive = 0
	manager = Manager:getInstance()
	collision = localObject:getCollisionComponent()
	collision:setLinearVelocity(Vec2(0, BULLET_SPEED))
	collision:setCollisionFunc(collisionFunc)
	renderSystem = manager:getRenderSystem()
end

function update(dt)
	timeAlive = timeAlive + dt
	if timeAlive > timeDie then
		manager:destroy(localObject)
	end
end

function collisionFunc(otherCollision)
	points = otherCollision:getParent():getPointsComponent():getPoints()
	_G.points = _G.points + points
	renderSystem:executeJavascript('document.getElementById("points").innerHTML = "' .. _G.points .. '";')
	manager:destroy(localObject)
end