require("Content/lua/alx")
require("Content/lua/camera")
require("Content/lua/window")
-- require("Content/lua/model")
-- require("Content/lua/glenums")

local newModel = require("Content/lua/model")

local monkey = newModel("min", "monkey.ply")
local shpere5 = newModel("min", "shpere5.ply")
shpere5.setPos({0, 5, 0})
shpere5.setScale({3, 3, 3})

local counter = 0
while not window.shouldClose() do
	counter = counter + .001
	monkey.setRotate({counter, counter * .7816538, counter * .543252})

	monkey.render()
	shpere5.render()

	window.swap()
end

monkey.delete()
shpere5.delete()
window.delete()



	-- local deltX, deltY = glfwx.getMouseDeltaPos(window1)
	-- print(deltX, deltY)

	-- rotX = rotX + (deltX * 0.005)
	-- rotY = math.clamp(rotY + (-deltY * 0.005), -math.pi * 0.5, math.pi * 0.5)

	-- --local camX, camY, camZ = 1.0, 0.0, 1.0
	-- dirX, dirY, dirZ = math.cos(rotX) + math.cos(rotX) * math.cos(rotY), math.sin(rotY), math.sin(rotX) + math.sin(rotX) * math.cos(rotY)

	-- local speed = 0.005
	-- -- if input.getKey("W") then
	-- -- 	camX, camY, camZ = camX + dirX * speed, camY + dirY * speed, camZ + dirZ * speed
	-- -- elseif input.getKey("S") then
	-- -- 	camX, camY, camZ = camX - dirX * speed, camY - dirY * speed, camZ - dirZ * speed
	-- -- end

	-- matrix.lookAt(viewMatrix, {camX, camY, camZ}, {camX + dirX, camY + dirY, camZ + dirZ}, {0.0, 1.0, 0.0})

	-- gl.uniformMatrix4fv(uniView, 1, GL_FALSE, matrix.get(viewMatrix))

	
	-- gl.clear(GL_COLOR_BUFFER_BIT)
	-- gl.clear(GL_DEPTH_BUFFER_BIT)

	-- testModel.render()
-- local shaderProgram
-- local uniView, viewMatrix
-- local planetMesh, buildingMesh
-- local testModel

-- gl.enable(GL_DEPTH_TEST)
-- gl.clearColor(0, 0.2, 0.2, 1)

-- -- alx.defaultContext()
-- -- alx.listener(0, 0, 0, 0, 0, 0, {0.0, 0.0, -1.0,  0.0, 1.0, 0.0})
-- -- alx.playFile("Content/clickclack.ogg")

-- -- Create and compile the shaders
-- local vertexShader = import.shader("Content/shaders/shader.vert", GL_VERTEX_SHADER)
-- local fragmentShader = import.shader("Content/shaders/shader.frag", GL_FRAGMENT_SHADER)

-- -- Link the vertex and fragment shader into a shader program
-- shaderProgram = glx.createProgram("out_color", vertexShader, fragmentShader)

-- planetMesh = mesh.new()
-- planetMesh.setModel(shaderProgram, "Content/shpere5.ply")

-- -- buildingMesh = mesh.new()
-- -- buildingMesh.setModel(shaderProgram, "Content/satallite.ply")

-- -- Setup matrix
-- viewMatrix = matrix.gen(4, 4)
-- uniView = gl.getUniformLocation(shaderProgram, "view")

-- local camX, camY, camZ = 1.0, 1.0, 1.0
-- matrix.lookAt(viewMatrix, {camX, camY, camZ}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})
-- gl.uniformMatrix4fv(uniView, 1, GL_FALSE, matrix.get(viewMatrix))

-- testModel = model.new(shaderProgram, planetMesh)

-- -- Hide mouse
-- -- input.setMouseVisible(false)

-- local camX, camY, camZ = 0.0, 0.0, 1.0
-- local dirX, dirY, dirZ = 0.0, 0.0, -1.0
-- local rotX, rotY = 0.0, 0.0

-- alx.destroyContext()
-- --gl.deleteTextures(text)

-- planetMesh.delete()
-- buildingMesh.delete()

-- gl.deleteProgram(shaderProgram)

-- while true do end


