local transform
local manager
local collision
local animation
local DELETE = -8.0
local timeAlive
local timeDeath = 20
local impacted = false

function impact()
	if not impacted then
		collision:setEnabled(false)
		animation:setClip('small_asteroid_explosion', false)
		animation:subscribe(animation,'small_asteroid_explosion', death_done)
	end

	impacted = true
end

function death_done(data)
	manager:destroy(localObject)
end

function start()
	transform = localObject:getTransformComponent()
	collision = localObject:getCollisionComponent()
	animation = localObject:getAnimationComponent()
	collision:setCollisionFunc(impact)
	manager = Manager:getInstance()
	timeAlive = 0
end

function update(dt)
	if not _G.paused then
		timeAlive = timeAlive + dt
		if transform:getWorldPosition().y < DELETE or timeAlive > timeDeath then
			manager:destroy(localObject)
		end
	end
end