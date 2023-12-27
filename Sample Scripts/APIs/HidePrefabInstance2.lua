--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/hideprefabinstance/

--name of the script is HidePrefabInstance2.lua

timer = 0.0
hidden = false

function Init()
	
end

function Update()
	timer = timer + GetElapsedTime()
	if timer >= 5.0 and not hidden then
		HidePrefabInstance("this")
		hidden = true
	end
end


