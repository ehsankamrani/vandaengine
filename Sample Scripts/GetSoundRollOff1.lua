--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/GetSoundRollOff/

rolloff = 0.0

function Init()
	rolloff = GetSoundRollOff("sound1")

	message = string.format("\nSound rolloff is > %.2f", rolloff)
	PrintConsole(message)
end

function Update()

end
