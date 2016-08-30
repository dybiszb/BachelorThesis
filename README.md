# Bachelor Thesis

## Building
NOTE: Currently only Windows platform is supported. Sources have been checked on Windows 10 64b.
Please let me know about any issues.
- In repository main folder call following commands:
```
mkdir [project directory]
cd [project directory]
cmake ..
```
- Open [repository main folder]\[project directory]\BachelorThesis.sln, choose 'Release' and Build->Build Soulution.

## Installation
Note: In order to create the installer you have to have Inno Setup Compiler.
- Go to [repository main folder]\[project directory]\Release\win_isntaller
- Open and compile [repository main folder]\[project directory]\Release\win_installer\win_installer.iss
- Setup executable lies in [repository main folder]\[project directory]\Release\win_installer\Output 

## Usage
- Run [repository main folder]\[project directory]\Release\bachelor_water.exe to open the application
- File [repository main folder]\[project directory]\Release\config.ini allows to change any settings related to the simulation. Some of the entries (e.g. resolution, fullscreen or number of quads) are not mutable during runtime.
- 

## History
TODO: Write history

## License
Copyright (c) 2016 Bartłomiej Dybisz


Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
