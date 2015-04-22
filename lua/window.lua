window = {}

glfw.init()
local w, h = 900, 800
local window1 = glfw.createWindow(w, h, "OpenLL")
glfw.makeContextCurrent(window1)

local function resize(window, width, height)
	gl.viewport(width, height)
	camera.setProjection(width, height, 45.0, 0.1, 1000.0)
end
glfw.setFramebufferSizeCallback(window1, resize)
resize(window1, w, h)

gl.enable(GL_DEPTH_TEST)
gl.clearColor(0, 0.2, 0.2, 1)

function window.shouldClose()
	return glfw.windowShouldClose(window1) or glfw.getKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS
end

function window.swap()
	glfw.swapBuffers(window1)
	glfw.pollEvents()

	gl.clear(GL_DEPTH_BUFFER_BIT)
	gl.clear(GL_COLOR_BUFFER_BIT)
end

function window.delete()
	glfw.destroyWindow(window1)
	glfw.terminate()
end

function window.get()
	return window1
end

function window.centerMouse()
	glfw.setCursorPos(window1, w / 2, h / 2)
	glfwx.getMouseDeltaPos(window.get())
end