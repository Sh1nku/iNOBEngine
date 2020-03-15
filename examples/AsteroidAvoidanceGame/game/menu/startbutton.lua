function startButtonPressed(data)
	Manager:getInstance():loadScene("game.scene")
end

function start()
	localObject:subscribe(localObject,"START_BUTTON", startButtonPressed)
end

function update()

end