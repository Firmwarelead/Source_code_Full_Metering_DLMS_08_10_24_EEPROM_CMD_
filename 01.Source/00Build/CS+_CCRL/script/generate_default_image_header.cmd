@if (@X)==(@Y) @end /* Harmless hybrid line that begins a JScript comment
@echo off

:: This script output an empty image header with 256 byte 0xFF
:: purpose is for first linker running, then on second linker running, it will link actual data
:: for i1c512k bootloader with bankswap only

if "%~1" neq "" (set outputfile="%~1") else set outputfile=generated_image_header.bin

if not exist %outputfile% (
    echo Image header not existed, creating %outputfile% for initial linking
    call :jscriptFunction %outputfile%
) else (
    echo Image header existed, skip creating
)
exit /b

:jscriptFunction
cscript.exe //E:JScript //nologo "%~f0" %1
exit /b
:: --------- JScript code -----------*/
var g_objFSO = WScript.CreateObject("Scripting.FileSystemObject");
var Lib = eval(g_objFSO.OpenTextFile(g_objFSO.GetParentFolderName(WScript.ScriptFullName) + "\\include.js", 1).ReadAll());
var i;
var output_path = WScript.Arguments.Unnamed(0)
var raw_data = new Array(256);
for (i = 0; i < raw_data.length; i++) {
    raw_data[i] = 0xFF;
}
Lib.binArrayToFile(raw_data, output_path);
WScript.Echo("Initial content written to: " + output_path);
WScript.Quit(0);