--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancenamefromactor/

prefab_instance_name = ""

function OnTriggerEnter(otherActorName)
	prefab_instance_name = GetPrefabInstanceNameFromActor(otherActorName)

	message = string.format("\nPrefab instance name is > %s" ,prefab_instance_name)
	PrintConsole(message)
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)

end