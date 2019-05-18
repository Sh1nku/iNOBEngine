local input
local paused
local collision
local renderSystem
local speed = 4

function start()
	input = localObject:getInputComponent()
	collision = localObject:getCollisionComponent()
	renderSystem = Manager.getInstance():getRenderSystem()
	paused = false
	drawCollisionData = false
end

function update(dt)
	local velocity = Vec2(0,0)
	if input:isKeyPressed("W") then
		velocity.y = velocity.y + 1
	end
	if input:isKeyPressed("S") then
		velocity.y = velocity.y - 1
	end
	if input:isKeyPressed("A") then
		velocity.x  = velocity.x - 1
	end
	if input:isKeyPressed("D") then
		velocity.x  = velocity.x + 1
	end
	
	local length = velocity:length()
	if(length ~= 0) then
		velocity:set((velocity.x / length)*speed, (velocity.y / length)*speed)
		if input:isKeyPressed("Left Shift") then
		velocity:set(velocity.x*2, velocity.y*2)
		end
	end
	collision:setLinearVelocity(velocity);
	
	if input:getControllerButtonDown("a") then
		print("a was pressed on controller")
	end
	if input:getControllerButtonUp("a") then
		print("a was released on controller")
	end
	if input:isControllerButtonPressed("X") then
		print("x was continually pressed")
	end
	
	if input:getKeyDown("Escape") then
		paused = not paused
		EventManager.fireEvent("PAUSED", boolToVoid(paused))
	end
	if input:getKeyDown("F1") then
		drawCollisionData = not drawCollisionData
		renderSystem:setShowCollisions(drawCollisionData)
	end
end