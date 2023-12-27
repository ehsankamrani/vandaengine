--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofenginecamera/

--Name of script is ResumeUpdateEventOfEngineCamera2.lua

function Init()
	PauseUpdateEventOfEngineCamera("this")

	ResumeUpdateEventOfEngineCamera("this")
end

function Update()
	PrintConsole("\nUpdate")
end
