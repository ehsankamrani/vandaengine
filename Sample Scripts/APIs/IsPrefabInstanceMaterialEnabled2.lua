--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/isprefabinstancematerialenabled/

enabled = false
message = ""

function Init()
	enabled = IsPrefabInstanceMaterialEnabled("this")

	if enabled then
		message = string.format("\nPrefab instance material is enabled")
	else
		message = string.format("\nPrefab instance material is disabled")
	end

	PrintConsole(message)
end

function Update()

end
