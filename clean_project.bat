rmdir build\obj
rmdir build\.test

del build\debug\*.pdb /Q
del build\debug\*.ilk /Q

del build\release\*.iobj /Q
del build\release\*.ipdb /Q
del build\release\*.pdb /Q

clean_dev_tools.bat