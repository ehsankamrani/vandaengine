--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancetransparency/

--Name of script is GetPrefabInstanceTransparency2.lua

value = 0.0

function Init()
	value = GetPrefabInstanceTransparency("this")

	message = string.format("\nTransparency is : (%.2f)", value)
	PrintConsole(message)
end

function Update()

end
