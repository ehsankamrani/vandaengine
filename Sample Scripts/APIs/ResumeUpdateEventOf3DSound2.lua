--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventof3dsound/

--Name of script is ResumeUpdateEventOf3DSound2.lua

function Init()
	PauseUpdateEventOf3DSound("this")

	ResumeUpdateEventOf3DSound("this")
end

function Update()
	PrintConsole("\nUpdate")
end
