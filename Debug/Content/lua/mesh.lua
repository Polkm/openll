-- Holds the vertex data of a mesh and sets it up for rendering.

return function(meshFile)
	local public = {}

	local vao = gl.genVertexArrays()
	local vboD = 0 -- Data
	local vboE = 0 -- Elements
	local indices = 0
	local indicesType = GL_UNSIGNED_INT
	local drawType = GL_TRIANGLES

	function public.buffer(data, elements, useage)
		if not data or not elements then return end
		
		gl.bindVertexArray(vao)
		vboD = glx.genBindBufferData(GL_ARRAY_BUFFER, GL_FLOAT, data, useage or GL_STATIC_DRAW)
		glx.enableVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_FLOAT_SIZE * 6, 0)
		glx.enableVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_FLOAT_SIZE * 6, GL_FLOAT_SIZE * 3)

		if elements then
			vboE = glx.genBindBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesType, elements, useage or GL_STATIC_DRAW)
			indices = #elements
		else
			indices = #data / 6
		end
		gl.bindVertexArray(0)

		return public
	end

	function public.render()
		gl.bindVertexArray(vao)
		if vboE ~= 0 then
			gl.drawElements(drawType, indices, indicesType)
		else
			gl.drawArrays(drawType, 0, indices)
		end
		gl.bindVertexArray(0)
	end

	function public.delete()
		gl.deleteVertexArrays(vao)
		gl.deleteBuffers(vboD, vboE)
	end

	if type(meshFile) == "string" then
		public.buffer(import.vertices("Content/meshes/" .. meshFile))
	end

	return public
end