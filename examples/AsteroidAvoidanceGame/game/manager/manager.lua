local manager
local renderSystem
local collisionSystem
local animationSystem
local scriptSystem;
local timeSinceLastUpdate = 0.0
local timePerSpawn = 0.1
local PLAYAREA_X = 6.0
local PLAYAREA_Y_TOP = 8.0
local PLAYAREA_Y_BOT = -8.0
local ROTATION_MAX = 3.0
local SPEED_MAX = 4.0
local SPEED_MIN = 2.5
local SCALE_MIN = 1
local SCALE_MAX = 1.5

function randomFloat(low, high)
    return low + math.random()  * (high - low);
end

function spawnAsteroid()
	local asteroid
	local asteroidString
	if math.random(0, 1) == 0 then
		asteroidString = "small_asteroid"
	else
		asteroidString = "big_asteroid"
	end
	local startPos = Vec2(randomFloat(-PLAYAREA_X, PLAYAREA_X), PLAYAREA_Y_TOP)
	local endPos = Vec2(randomFloat(-PLAYAREA_X, PLAYAREA_X), PLAYAREA_Y_BOT)
	local normalizedBetween = getVector2f(startPos, endPos);
	normalizedBetween:normalize();
	asteroid = manager:instantiate(getPrefab(asteroidString), "", Vec3(startPos.x, startPos.y, 0))
	local transform = asteroid:getTransformComponent()
	transform:setScale(randomFloat(SCALE_MIN, SCALE_MAX))
	local collision = asteroid:getCollisionComponent()
	local speed = randomFloat(SPEED_MIN, SPEED_MAX)
	collision:setLinearVelocity(Vec2(normalizedBetween.x * speed, normalizedBetween.y * speed))
	collision:setAngularVelocity(randomFloat(-ROTATION_MAX, ROTATION_MAX))
	
end

function start()
	manager = Manager:getInstance()
	renderSystem = manager:getRenderSystem()
	animationSystem = manager:getAnimationSystem()
	collisionSystem = manager:getCollisionSystem()
	scriptSystem = manager:getScriptSystem()
	renderSystem:setBackgroundColor(0,0,0,1)
	renderSystem:setShowFPS(true)
	renderSystem:setShowProfiling(true)
	localObject:subscribe(nil,"PAUSED", paused)
end

function update(dt)
	if not _G.paused then
		timeSinceLastUpdate = timeSinceLastUpdate + dt
		if timeSinceLastUpdate >= timePerSpawn then
		spawnAsteroid()
		timeSinceLastUpdate = timeSinceLastUpdate - timePerSpawn
		end
	end
end

function paused(pausedBool)
		renderSystem:executeJavascript('document.getElementById("paused").style.display = "' .. (voidToBool(pausedBool) and "flex" or "none") .. '";')
		animationSystem.active = not voidToBool(pausedBool)
		collisionSystem.active = not voidToBool(pausedBool)
end