--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/deleteprefabinstance/

--Name of script is DeletePrefabInstance2.lua

timer = 0.0

function Init()

end

function Update()
	timer = timer + GetElapsedTime()
	if timer > 3.0 then DeletePrefabInstance("this") end
end
