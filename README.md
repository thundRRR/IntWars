IntWars
==================
About
------
Fork of the 2 year old (outdated project), IntWars. Emulates LoL server environment.  
This is a fork of [Elyotna's fork](https://github.com/Elyotna/IntWars).   
If you want to contribute to the project, please fork the repo and upload any progress to GitHub.  
If you need help compiling the source on Windows, [check here](#notes-for-compiling-on-windows).

Content:
* Load Screen: http://puu.sh/8cbhW.jpg
* Ingame: http://puu.sh/8cbiX.jpg


Instructions:
* Run gamed.exe
* Run StartClient.bat
* If StartClient.bat does not work, run the game with this command: "League of Legends.exe" "8394" "LoLLauncher.exe" "C:/Riot Games/League of Legends/RADS/projects/lol_air_client/releases/0.0.1.79/deploy/LolClient.exe" "127.0.0.1 5119 17BLOhi6KZsTtldTsizvHg== 47917791"

Important rules and information
---------
* Use this style reference for all your code: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
* Keep this project clean and simple
* The project is using parts of the C++ 2011 standard.

Original Creators
-------
* Intline9 - intline9(at)gmail(dot)com
* Ltsstar

Other Important Contributors
-------
* Elyotna (reddit: ?)
* Spudgy (reddit: imSpudgy)
* ProudHeart (reddit: chutch1122)


License
-------
GPLv3 as sharing is caring, and when ever you extend/use/modify/fix any of this project you should share it again!

Contact
-------
For information relating to this fork, contact me on reddit: chutch1122  
I'm working on setting up a website where we can organize this better.

Notes for Compiling on Windows
---------
Note: This is a very basic explanation. I am working on a more detailed explanation, but don't have the time right now.

This project uses elements from C++11, like initialization lists. Visual Studio does not support initialization lists in the 2010 or 2012 versions. Therefore, I recommend installing/using CMake and MinGW's g++ compiler. Websites and download links for these are below.

Step 1). CMake - [Website](http://www.cmake.org/cmake/resources/software.html) | [Direct Download to Version 3.0.0](http://www.cmake.org/files/v3.0/cmake-3.0.0-win32-x86.exe)  

Step 2). The default MinGW compiler from http://www.mingw.org/ does not support threads (which are now being used). 
Windows developers should replace their MinGW installation (eg: C:\MinGW\) with one like this: http://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.8.1/64-bit/threads-posix/sjlj/x64-4.8.1-release-posix-sjlj-rev5.7z/download

Add C:\MinGW\bin to your PATH enviornment variable so you can use g++ anywhere ([Guide](http://www.computerhope.com/issues/ch000549.htm)).

After CMake and MinGW are installed and configured. Generate the makefiles using GenerateMakefiles.bat and compile the source using CompileServer.bat

The executable (intwars.exe) will be located in the /build/gamed/ directory.
