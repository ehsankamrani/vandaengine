--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getdirectionalshadownearclipplane/

value = 0.0

function Init()
	value = GetDirectionalShadowNearClipPlane()

	message = string.format("\nDirectional shadow near clip plane is : %.2f" ,value)
	PrintConsole(message)
end

function Update()

end
