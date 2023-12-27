--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceambient/

--Name of script is GetPrefabInstanceAmbient2.lua

r = 0.0
g = 0.0
b = 0.0

function Init()
	r, g, b = GetPrefabInstanceAmbient("this")

	message = string.format("\nAmbient color is : (%.2f, %.2f, %.2f)", r, g, b)
	PrintConsole(message)
end

function Update()

end

