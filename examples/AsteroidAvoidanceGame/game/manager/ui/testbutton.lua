function testButtonPressed(data)
	print(voidToString(data))
end

function start()
	localObject:subscribe(localObject,"TEST_BUTTON", testButtonPressed)
end

function update()

end