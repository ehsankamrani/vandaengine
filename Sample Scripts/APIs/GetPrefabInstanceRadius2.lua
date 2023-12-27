--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceradius/

--Name of script is GetPrefabInstanceRadius2.lua

radius = 0.0

function Init()
	radius = GetPrefabInstanceRadius("this")

	message = string.format("\nPrefab instance radius is > %.2f" ,radius)
	PrintConsole(message)
end

function Update()

end

