--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/ontriggerenter-event/

function OnTriggerEnter(otherActorName)
	if otherActorName == nil then
		PrintConsole("\nMain character entered the trigger and OnTriggerEnter() Event was called")
	else
		prefab_instance_name = GetPrefabInstanceNameFromActor(otherActorName)

		message = string.format("\nOnTriggerEnter() Event was called. Prefab instance name is : %s" ,prefab_instance_name)
		PrintConsole(message)
	end
end
