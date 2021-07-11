local input
_G.paused = false
local collision
local renderSystem
local speed = 4
local TIME_BETWEEN_SHOTS = 0.3
local BULLET_POS = Vec2(0.35, -0.2);
local lastShot
local manager
local transform
local animation

function start()
	manager = Manager:getInstance()
	input = localObject:getInputComponent()
	collision = localObject:getCollisionComponent()
	transform = localObject:getTransformComponent()
	animation = localObject:getAnimationComponent()
	renderSystem = manager:getRenderSystem()
	_G.paused = false
	drawCollisionData = false
	lastShot = 0
	collision:setCollisionFunc(collisionFunc)
end

function update(dt)
	if not _G.paused then
		local velocity = Vec2(0,0)
		if input:isKeyPressed("W") then
			velocity.y = velocity.y + 1
		end
		if input:isKeyPressed("S") then
			velocity.y = velocity.y - 1
		end
		local moved = false
		if input:isKeyPressed("A") then
			velocity.x  = velocity.x - 1
			animation:setClip("ship_left", false)
			moved = true
		end
		if input:isKeyPressed("D") then
			velocity.x  = velocity.x + 1
			animation:setClip("ship_right", false)
			moved = true
		end
		if not moved then
			animation:setClip("ship_idle", false)
		end
		
		local length = velocity:length()
		if(length ~= 0) then
			velocity:set((velocity.x / length)*speed, (velocity.y / length)*speed)
			if input:isKeyPressed("Left Shift") then
			velocity:set(velocity.x*2, velocity.y*2)
			end
		end
		collision:setLinearVelocity(velocity);
		
		lastShot = lastShot + dt
		if input:isKeyPressed("Space") and lastShot >= TIME_BETWEEN_SHOTS then
			local position = transform:getWorldPosition()
			lastShot = 0
			manager:instantiate(getPrefab("bullet"), "", Vec3(position.x - BULLET_POS.x,position.y + BULLET_POS.y, 0))
			manager:instantiate(getPrefab("bullet"), "", Vec3(position.x + BULLET_POS.x,position.y + BULLET_POS.y, 0))
		end

	end

	if input:getKeyDown("Escape") then
		_G.paused = not _G.paused
		manager:fireEvent(nil,"PAUSED", boolToVoid(paused))
	end
	if input:getKeyDown("F1") then
		drawCollisionData = not drawCollisionData
		renderSystem:setShowCollisions(drawCollisionData)
	end
	if input:getKeyDown("F2") then
		manager:loadScene("game.scene")
	end
	if input:getKeyDown("F3") then
		renderSystem:setShowFPS(not renderSystem:getShowFPS())
	end
	if input:getKeyDown("F4") then
		renderSystem:setShowProfiling(not renderSystem:getShowProfiling())
	end
end

function collisionFunc(otherCollision)
	manager:destroy(localObject)
	manager:destroy(manager:getGameObjectByName("Backgrounds"))
	manager:destroy(manager:getGameObjectByName("Camera"))
	manager:loadScene("menu.scene")
end