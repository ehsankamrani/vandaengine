--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadowfarclipplane/

value = 0.0

function Init()
	value = GetDirectionalShadowFarClipPlane()

	message = string.format("\nDirectional shadow far clip plane is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end
