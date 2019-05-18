function testButtonPressed(data)
	print(voidToString(data))
end

function start()
	EventManager.subscribe("TEST_BUTTON", testButtonPressed)
end

function update()

end