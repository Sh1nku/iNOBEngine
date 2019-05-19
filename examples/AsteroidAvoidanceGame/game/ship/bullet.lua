local timeAlive
local timeDie = 5
local manager
local BULLET_SPEED = 20
local collision

function start()
	timeAlive = 0
	manager = Manager:getInstance()
	collision = localObject:getCollisionComponent()
	collision:setLinearVelocity(Vec2(0, BULLET_SPEED))
	collision:setCollisionFunc(collisionFunc)
end

function update(dt)
	timeAlive = timeAlive + dt
	if timeAlive > timeDie then
		manager:destroy(localObject)
	end
end

function collisionFunc(otherCollision)
	manager:destroy(otherCollision:getParent())
	manager:destroy(localObject)
end