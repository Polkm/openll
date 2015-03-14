local specFileName = "Content/enumext.spec"

local finalCPPCode = ""

local curCategory = nil
local dropCategory = false

local function endCategory()
	if curCategory and not dropCategory then
		finalCPPCode = finalCPPCode .. '\n#endif'
	end
end

local function categoryCommand(catName)
	endCategory()

	curCategory = 'GL_' .. catName

	if (not string.find(catName, "VERSION_") and not string.find(catName, "ARB_")) or string.find(catName, "_DEPRECATED") then
		dropCategory = true
		print("droped " .. catName)
	else
		dropCategory = false
		finalCPPCode = finalCPPCode .. '\n#ifdef GL_' .. catName
	end
end
	

local function enumCommand(symbol, value)
	finalCPPCode = finalCPPCode .. '\n\tlua_pushenumuration(L, "GL_' .. symbol .. '", ' .. value .. ');'
end

function GENERATE_CPP_ENUMS()
	local count = 0
	for line in io.lines(specFileName) do
		-- Remove the comment part from any place in the line.
        line = line:gsub('#.*', '')

        if line ~= "" then
        	local matches = {line:match('^(%S+) enum:')}
        	if matches[1] ~= nil then
        		categoryCommand(unpack(matches))
        	else
        		if not dropCategory then
	        		matches = {line:match('(%S+)%s*=%s*(%S+)')}
		        	if matches[1] ~= nil then
		        		enumCommand(unpack(matches))
		        	end
		        end
        	end
        	count = count + 1
        end
	end
	endCategory()

	local file = io.open("Content/enumoutput.txt", "w")
	file:write(finalCPPCode)
	file:close()
end