--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setenginecamerafarclipplane/

--Name of script is SetEngineCameraFarClipPlane2.lua

function Init()
	ActivateEngineCamera("this")
	SetEngineCameraFarClipPlane("this", 20.0)
end

function Update()

end
