return function(public)
	public = public or {}

	local x, y, z = 0, 0, 0
	
	-- Sets x, y, and z if a new value is given.
	function public.setPos(setX, setY, setZ)
		x, y, z = setX or x, setY or y, setZ or z
	end

	-- addPos properly calls the other public members to enforce api.
	function public.addPos(addX, addY, addZ)
		local lX, lY, lZ = public.getPos()
		public.setPos(lX + (addX or 0), lY + (addY or 0), lZ + (addZ or 0))
	end

	-- This is the only function allowed to return local x, y, and z.
	function public.getPos()
		return x, y, z
	end

	-- If you where to overrite getPos you dont have to overrite getPosT.
	function public.getPosT()
		return {public.getPos()}
	end

	return public
end