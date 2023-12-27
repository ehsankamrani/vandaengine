--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getanisotropicfilteringvalue/

value = 0

function Init()
	value = GetAnisotropicFilteringValue()

	message = string.format("\nAnisotropic filtering value is > %d" ,value )
	PrintConsole(message)
end

function Update()

end
