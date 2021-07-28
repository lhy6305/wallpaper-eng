# Introduction
You can use **setwindow.exe** to make a window as wallpaper.(OS: Windows only)  
Use hooks to make the wallpaper window interactable.  
**setwindow.exe** is written in **C#**. You can use **dnSpy** to view and edit the source.  
**1.dll** is pre-compiled with **MinGW** for win64. Its source code is **1.cpp**.  

# Notice
The hooks will be unload automaticlly if you close the **setwindow.exe** window. Then the wallpaper window will be **NOT** interactable.

# Known issues  
Cannot forward mouse wheel events.
