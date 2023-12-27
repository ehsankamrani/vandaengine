--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getmultisamplingvalue/

value = 0

function Init()
	value = GetMultisamplingValue()

	message = string.format("\nMultisampling value is > %d" ,value )
	PrintConsole(message)
end

function Update()

end
