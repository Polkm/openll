

return function(fileName)
	local public = {}

	local vertexShader = glx.createShader(import.text("Content/shaders/" .. fileName .. ".vert"), GL_VERTEX_SHADER)
	local fragmentShader = glx.createShader(import.text("Content/shaders/" .. fileName .. ".frag"), GL_FRAGMENT_SHADER)
	local program = glx.createProgram("out_color", vertexShader, fragmentShader)

	function public.bind()
		gl.useProgram(program)
		camera.updateShader(public)
	end

	function public.unbind()
		gl.useProgram(0)
	end

	function public.delete()
		gl.deleteProgram(program)
	end

	function public.uniformMaxtrix(uniform, mat)
		gl.uniformMatrix4fv(gl.getUniformLocation(program, uniform), 1, GL_FALSE, mat)
	end

	return public
end