--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/generateprefabinstance/

prefab_instance = ""

function OnTriggerEnter(otherActorName)
	prefab_instance = GeneratePrefabInstance("VandaEngine17-SamplePack1_house2", 1.0, 2.0, 3.0, 10.0, 20.0, 30.0, 0.3, 0.5, 0.7)
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	DeletePrefabInstance(prefab_instance)
end





