--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancescale/

--Name of script is GetPrefabInstanceScale2.lua

scaleX = 0.0
scaleY = 0.0
scaleZ = 0.0

function Init()
	scaleX, scaleY, scaleZ = GetPrefabInstanceScale("this")

	message = string.format("\nPrefab instance scale is > (%.2f, %.2f, %.2f)" , scaleX, scaleY, scaleZ)
	PrintConsole(message)
end

function Update()

end

