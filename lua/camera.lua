camera = {}

local projection = glm.mat4()
local fov = 45.0
local near, far = 0.1, 100.0

local view = glm.mat4()
local camX, camY, camZ = -2.0, 0.0, 0.0
local rotX, rotY = 0, 0

local speed = 0.005

function camera.setProjection(width, height, newFOV, newNear, newFar)
	fov = newFOV or fov
	near, far = newNear or near, newFar or far

	projection = glm.perspective(fov, width / height, near, far)

	gl.viewport(0, 0, width, height)
end

local function sphere(radius, azimuth, inclination)
	local x = radius * math.sin(inclination) * math.cos(azimuth)
	local y = radius * math.cos(inclination)
	local z = radius * math.sin(inclination) * math.sin(azimuth)
	return x, y, z
end

function camera.updateShader(shader)
	local deltX, deltY = glfwx.getMouseDeltaPos(window.get())
	window.centerMouse()

	rotX = rotX + (deltX * 0.005)
	rotY = math.clamp(rotY + (deltY * 0.005), 0.001, math.pi * .999)

	local dirX, dirY, dirZ = sphere(1, rotX, rotY)

	if glfw.getKey(window.get(), GLFW_KEY_W) == GLFW_PRESS then
		camX, camY, camZ = camX + dirX * speed, camY + dirY * speed, camZ + dirZ * speed
	elseif glfw.getKey(window.get(), GLFW_KEY_S) == GLFW_PRESS then
		camX, camY, camZ = camX - dirX * speed, camY - dirY * speed, camZ - dirZ * speed
	end

	view = glm.lookAt({camX, camY, camZ}, {camX + dirX, camY + dirY, camZ + dirZ}, {0.0, 1.0, 0.0})

	shader.uniformMaxtrix("u_view", view)
	shader.uniformMaxtrix("u_projection", projection)
end