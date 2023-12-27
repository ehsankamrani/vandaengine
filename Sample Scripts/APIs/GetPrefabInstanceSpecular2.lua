--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancespecular/

--Name of script is GetPrefabInstanceSpecular2.lua

r = 0.0
g = 0.0
b = 0.0

function Init()
	r, g, b = GetPrefabInstanceSpecular("this")

	message = string.format("\nSpecular color is : (%.2f, %.2f, %.2f)", r, g, b)
	PrintConsole(message)
end

function Update()

end
