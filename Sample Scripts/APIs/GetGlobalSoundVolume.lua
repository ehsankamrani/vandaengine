--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getglobalsoundvolume/

volume = 0.0

function Init()
	volume = GetGlobalSoundVolume()

	message = string.format("\nGlobal sound volume is > %.2f" , volume)
	PrintConsole(message)
end

function Update()

end


