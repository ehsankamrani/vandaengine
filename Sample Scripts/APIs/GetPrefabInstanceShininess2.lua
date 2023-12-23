--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceshininess/

--Name of script is GetPrefabInstanceShininess2.lua

value = 0.0

function Init()
	value = GetPrefabInstanceShininess("this")

	message = string.format("\nShininess is : (%.2f)", value)
	PrintConsole(message)
end

function Update()

end
