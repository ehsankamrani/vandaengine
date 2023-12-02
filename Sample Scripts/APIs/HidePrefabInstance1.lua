--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/hideprefabinstance/

timer = 0.0
hidden = false

function Init()
	
end

function Update()
	timer = timer + GetElapsedTime()
	if timer >= 5.0 and not hidden then
		HidePrefabInstance("1_VandaEngine17-SamplePack1_eggbox")
		hidden = true
	end
end



