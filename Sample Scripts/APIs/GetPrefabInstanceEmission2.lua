--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceemission/

--Name of script is GetPrefabInstanceEmission2.lua

r = 0.0
g = 0.0
b = 0.0

function Init()
	r, g, b = GetPrefabInstanceEmission("this")

	message = string.format("\nEmission color is : (%.2f, %.2f, %.2f)", r, g, b)
	PrintConsole(message)
end

function Update()

end
