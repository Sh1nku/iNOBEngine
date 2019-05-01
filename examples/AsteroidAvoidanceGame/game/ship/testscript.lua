local input

function start()
	input = localObject:getInputComponent()
end

function update()
	if input:isKeyPressed("W") then
		print("W is pressed")
	end
end