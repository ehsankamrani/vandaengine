--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/iskeydown/

AkeyDown = false

function Init()

end

function Update()
	AkeyDown = IsKeyDown("DIK_A")

	if AkeyDown then 
		PrintConsole("\nA key is down")
	end

end


