--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/ontriggerenterevent/

function OnTriggerEnter(otherActorName)
	if otherActorName == nil then
		PrintConsole("\nOnTriggerEnter() Event was called")
	else
		prefab_instance_name = GetPrefabInstanceNameFromActor(otherActorName)

		message = string.format("\nPrefab instance name is > %s" ,prefab_instance_name)
		PrintConsole(message)
	end
end
