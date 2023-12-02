--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdistanceofprefabinstancefromphysicscamera/

--name of script is GetDistanceOfPrefabInstanceFromPhysicsCamera2.lua

distance = 0.0

function Init()
	distance = GetDistanceOfPrefabInstanceFromPhysicsCamera("this")

	message = string.format("\nDistance is > %.2f" , distance )
	PrintConsole(message)
end

function Update()

end
