
function alx.loadBuffer(filename)
	local buffer = al.genBuffers()
	local wavData, frequency, bitsPerSample, channels = import.audio(filename)
	local format = alx.getFormat(bitsPerSample, channels)
	al.bufferData(buffer, format, wavData, #wavData, frequency)
	return buffer
end

local buffers = {}
function alx.getCacheBuffer(filename)
	if not buffers[filename] then
		buffers[filename] = alx.loadBuffer(filename)
	end
	return buffers[filename]
end

function alx.playFile(filename)
	local source = alx.genSource(alx.getCacheBuffer(filename))
	al.source3f(source, AL_POSITION, 0, 0, 0)
	al.source3f(source, AL_VELOCITY, 0, 0, 0)
	al.sourcePlay(source)
end

-- al.deleteSources(source)
-- al.deleteBuffers(buffer)