Windows Build Bats
=====
This is how I (iMer) do my development on windows. 
While MinGW works and is nice and all, it is still easier to debug using visual studio and do things with vc most of the time.
Developing in visual studio however.. No idea how people even..
So yeah, this uses [Ninja](http://martine.github.io/ninja/) to call vc build commands - it works great.
Additionally I just use Netbeans (probably works with your editor/ide of choice) to call the bats

**cmake.bat** generates the cmake directories (debug & release)
**build.bat [type]** runs ninja in build*type* ("build.bat" -> debug build, "build.bat release" -> release build)
**clean.bat [type]** cleans  the respective dir, see build.bat