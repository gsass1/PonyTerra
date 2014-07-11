# PonyTerra #

It's the game, using the NSEngine.

## Building ##

Download the latest stable NSEngine build from here: [http://nukesoftware.de/download/nsengine/](http://nukesoftware.de/download/nsengine/).
Use the Debug version or Release version depending on your build.

Drop it in the project folder, rename it to "nsengine".
Be sure that it contains these directories:
	bin/
	include/
	lib/

CD into the project directory.
Run this:

```
#!shell

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Running ##

First, copy the "data" folder to the DLL file. Then launch NSEngine with the "basepath" option.
```
#!shell

NSEngine --basepath "/path/to/ponyterra"
```

You can configure this in Visual Studio: Properties->Configuration Properties->Debugging