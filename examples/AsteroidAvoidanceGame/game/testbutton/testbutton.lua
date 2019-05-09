
function testButtonPressed()
	print("Test button was pressed")
end

function start()
	EventManager.subscribe("TEST_BUTTON", testButtonPressed)
end

function update()

end