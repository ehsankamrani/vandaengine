--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/writefloatvariabletofile/

fVar = 0.0

function Init()
   --Create a folder in Assets/Data/ path
   CreateFolder("Lev1")

   --Create and open file to write data
   OpenFileForWriting("Lev1/level1.bin")
   WriteFloatVariableToFile(2.0)
   CloseFile("Lev1/level1.bin")

   --Open File to load data
   OpenFileForReading("Lev1/level1.bin")
   fVar = ReadFloatVariableFromFile()
   CloseFile("Lev1/level1.bin")
end

