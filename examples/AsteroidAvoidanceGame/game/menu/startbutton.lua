function startButtonPressed(data)
	Manager:getInstance():loadScene("game.scene")
end

function start()
	EventManager.subscribe("START_BUTTON", startButtonPressed)
end

function update()

end