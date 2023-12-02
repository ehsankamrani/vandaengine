--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceradius/

radius = 0.0

function Init()
	radius = GetPrefabInstanceRadius("1_VandaEngine17-SamplePack1_well")

	message = string.format("\nPrefab instance radius is > %.2f" ,radius)
	PrintConsole(message)
end

function Update()

end
