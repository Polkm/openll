-- A unquie instance of a mesh.

local newShader = require("Content/lua/shader")
local newMesh = require("Content/lua/mesh")

return function(shaderFile, meshFile)
	local public = {}

	local pos = {0, 0, 0}
	local scale = {1, 1, 1}
	local rotate = {0, 0, 0}
	local shader = newShader(shaderFile)
	local mesh = newMesh(meshFile)

	function public.setPos(p)
		pos = p
	end

	function public.setScale(s)
		scale = s
	end

	function public.setRotate(r)
		rotate = r
	end

	function public.getMatrix()
		local mat = glm.mat4()
		mat = glm.translate(mat, pos)
		mat = glm.rotate(mat, rotate[1], {1, 0, 0})
		mat = glm.rotate(mat, rotate[2], {0, 1, 0})
		mat = glm.rotate(mat, rotate[3], {0, 0, 1})
		mat = glm.scale(mat, scale)
		return mat
	end

	function public.render()
		if shader and mesh then
			shader.bind()
			shader.uniformMaxtrix("u_model", public.getMatrix())
			mesh.render()
			shader.unbind()
		end
	end

	function public.delete()
		shader.delete()
		mesh.delete()
	end

	return public
end