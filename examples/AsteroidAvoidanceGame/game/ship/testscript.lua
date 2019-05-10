local input

function start()
	input = localObject:getInputComponent()
end

function update(dt)
	if input:isKeyPressed("W") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x, currentPos.y + 0.01 * dt))
	end
	if input:isKeyPressed("S") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x, currentPos.y - 0.01 * dt))
	end
	if input:isKeyPressed("A") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x - 0.01 * dt, currentPos.y))
	end
	if input:isKeyPressed("D") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x + 0.01 * dt, currentPos.y))
	end
	
	if input:getControllerButtonDown("a") then
		print("a was pressed on controller")
	end
	if input:getControllerButtonUp("a") then
		print("a was released on controller")
	end
	if input:isControllerButtonPressed("X") then
		print("x was continually pressed")
	end
end