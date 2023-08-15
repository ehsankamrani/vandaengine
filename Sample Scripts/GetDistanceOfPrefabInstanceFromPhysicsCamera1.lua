--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdistanceofprefabinstancefromphysicscamera/

distance = 0.0

function Init()
	distance = GetDistanceOfPrefabInstanceFromPhysicsCamera("1_VandaEngine17-SamplePack1_well")

	message = string.format("\nDistance is > %.2f" , distance )
	PrintConsole(message)
end

function Update()

end
