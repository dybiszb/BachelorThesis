# Bachelor Thesis
The thesis task was to create a simple ship simulator, that will model a unit floating on a water surface.
To accomplish that, water has been interpreted as a finite grid of vertices with different heights.
The ship's hull on the other hand, is simulated with usage of three dimensional grid, that
based on its cells immersion level with respect to the heightfield, calculates both: a point and a force of buoyancy.
At each frame PhysX library, supplied with all the information, computes the ship transformations in a current step of
the simulation. The application allows one to tweak all parameters via its extensive graphical user interface and
freely move around the scene. What is more, the ship can be controlled by applying different forces at the front
of its hull.

    ![alt tag](https://raw.githubusercontent.com/dybiszb/BachelorThesis/master/doc/screens/app_1.png)                       |![alt tag](https://raw.githubusercontent.com/dybiszb/BachelorThesis/master/doc/screens/app_2.jpg)
:-------------------------:|:-------------------------:
![alt tag](https://raw.githubusercontent.com/dybiszb/BachelorThesis/master/doc/screens/app_3.png)  |   ![alt tag](https://raw.githubusercontent.com/dybiszb/BachelorThesis/master/doc/screens/app_4.png)

## Building<a name="build"></a>
Note: Currently only Windows platform is supported. Sources have been checked on Windows 10 64bit.
Please let me know about any issues.
- In repository main folder call following commands:

    ```
   mkdir [project directory]
   cd [project directory]
   cmake ..
    ```
- Open 
   ```
   [repository main folder]\[project directory]\BachelorThesis.sln
    ```
- Change *Debug* to *Release* and click Build->Build Soulution.

## Setup.exe<a name="setup"></a>
It is is possible to create setup executable for the application from the repository sources. Please first [build](#build) the app and then make use of the following steps:
- Install [Inno Setup Compiler](http://www.jrsoftware.org/isinfo.php)
- Go to 
   ```
   [repository main folder]\[project directory]\Release\win_installer
   ```
- Open and compile
   ```
   [repository main folder]\[project directory]\Release\win_installer\win_installer.iss
   ```
- Setup executable resides in:
   ```
   [repository main folder]\[project directory]\Release\win_installer\Output
   ```

## Usage
To run the application either use [setup executable](#setup) or [build](#build) it and run:
```
[repository main folder]\[project directory]\Release\bachelor_water.exe 
```
Window with the simulation should pop up along with a console.

Any configuration can be done via modifying:
```
[repository main folder]\[project directory]\Release\config.ini
```
or 
```
[installation directory]\config.ini
```
(depending on the previous steps). Some of the entries (e.g. resolution, fullscreen or number of quads) are not mutable during runtime, hence the file is the only way to set them.



## License
Copyright (c) 2016 Bartłomiej Dybisz


Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
