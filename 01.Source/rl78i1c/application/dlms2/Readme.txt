If your project tree in CubeSuite+(CS+) have not included dlms folder project,
 please drag dlms folder into project tree in CS+, then set "Subfolder level to search" = 5.
 please ignore under guide for this case.
 Else,
To update code tree automatically by iron python, please follows under steps:
1. Open CubeSuite+ project file. (Source\CS+_CCRL\rl78i1c.mtpj)
2. Open python console on CubeSuite+ by View/Python Console
3. Update to adapt with your project. Please see *** Note.
4. Open Python Console and execute below script:
common.PythonInitialize(<<Absolute path to UpdateProjectFile.py>>)

Example: 
common.PythonInitialize(D:\\Work\\CodeGenerated\\dlms2\\UpdateProjectFile.py)

*** Note:
(1)If generated source code folders are copied to another place, please revise "directory_gen" in UpdateProjectFile.py become new path of destination folder which contain this files.
	Also, above script in (3) will be changed parallel. Remeber UpdateProjectFile.py is always copied with codegen, library, usercode folder.
	ex: C:\Codegen_package copy to C:\smart_meter\dlms. Need to do 2 steps
	1. Change script:
	=> common.PythonInitialize("C:\\Codegen_package\\UpdateProjectFile.py") -> common.PythonInitialize("C:\\smart_meter\\dlms\\UpdateProjectFile.py")
	2. Change "directory_gen" in UpdateProjectFile.py:
	directory_gen = "C:\\Codegen_package" -> directory_gen = "C:\smart_meter\dlms"
(2) Default subfolder level project tree which contains generated code is \\application\\dlms2,
	 so you see in UpdateProjectFile.py, dlms_code_project_tree = ["application","dlms2"]
	If your project tree is different, please revise to adapt to your project, else, please ignore this step.
	For example, subfolder is folder contains generated code(3 folder: codegen, library, usercode)
		1 level subfolder:\\MyDlms2 => dlms_code_project_tree = ["MyDlms2"]
		2 level subfolder:\\my_app\\my_dlms => dlms_code_project_tree = ["my_app","my_dlms"]
		3 level subfolder:\\my_meter\\my_app\\my_dlms => dlms_code_project_tree = ["my_meter","my_app","my_dlms"]
		...