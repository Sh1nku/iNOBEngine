local input

function start()
	input = localObject:getInputComponent()
end

function update()
	if input:isKeyPressed("W") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x, currentPos.y + 0.01))
	end
	if input:isKeyPressed("S") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x, currentPos.y - 0.01))
	end
	if input:isKeyPressed("A") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x - 0.01, currentPos.y))
	end
	if input:isKeyPressed("D") then
		local currentPos = localObject.transform:getLocalPosition()
		localObject.transform:setPosition(Vec2(currentPos.x + 0.01, currentPos.y))
	end
end