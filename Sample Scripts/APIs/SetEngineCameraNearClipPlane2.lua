--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setenginecameranearclipplane/

--Name of script is SetEngineCameraNearClipPlane2.lua

function Init()
	ActivateEngineCamera("this")
	SetEngineCameraNearClipPlane("this", 0.1)
end

function Update()

end
