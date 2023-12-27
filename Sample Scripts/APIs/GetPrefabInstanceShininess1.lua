--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstanceshininess/

value = 0.0

function Init()
	value = GetPrefabInstanceShininess("1_VandaEngine17-SamplePack1_wood_pile")

	message = string.format("\nShininess is : (%.2f)", value)
	PrintConsole(message)
end

function Update()

end
