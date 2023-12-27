--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancescale/

scaleX = 0.0
scaleY = 0.0
scaleZ = 0.0

function Init()
	scaleX, scaleY, scaleZ = GetPrefabInstanceScale("1_VandaEngine17-SamplePack1_well")

	message = string.format("\nPrefab instance scale is > (%.2f, %.2f, %.2f)" , scaleX, scaleY, scaleZ)
	PrintConsole(message)
end

function Update()

end
