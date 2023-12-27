--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancediffuse/

r = 0.0
g = 0.0
b = 0.0

function Init()
	r, g, b = GetPrefabInstanceDiffuse("1_VandaEngine17-SamplePack1_wood_pile")

	message = string.format("\nDiffuse color is : (%.2f, %.2f, %.2f)", r, g, b)
	PrintConsole(message)
end

function Update()

end
