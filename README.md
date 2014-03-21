TecReader
=========

TecReader is a RS-232 client application for the MVE TEC 3000, a controller for liquid nitrogen freezers from [Chart Biomedical]. It is useful to extract information from the TEC device as well as to send control commands to the device.

![MVE TEC 3000](http://german-cryo.de/assets/images/TEC3000.jpg)

Usage:
------

Please take a look at `tecreader -h` for now. Viable commands can be looked-up in the [MVE TEC 3000 Manual] page 99 ff.

Compilation:
------------

    make

### Install Dependencies:
The following dependencies are required in order to build TecReader on linux as well as to cross compile a statically linked binary for windows:

    mingw32-gcc-c++ mingw32-boost boost boost-devel libstdc++-static mingw32-boost-static


[Chart Biomedical]: http://www.chartbiomed.com
[MVE TEC 3000 Manual]: http://www.chartbiomed.com/getattachment/20d79734-5072-4ecf-8b50-f535ad2df4e8/.aspx

