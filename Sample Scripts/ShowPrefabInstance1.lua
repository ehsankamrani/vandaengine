--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/showprefabinstance/

timer = 0.0
shown = false

function Init()
	HidePrefabInstance("1_VandaEngine17-SamplePack1_eggbox")
end

function Update()
	timer = timer + GetElapsedTime()
	if timer >= 5.0 and not shown then
		ShowPrefabInstance("1_VandaEngine17-SamplePack1_eggbox")
		shown = true
	end
end



