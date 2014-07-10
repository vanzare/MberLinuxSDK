MberLinuxSDK
============

Quick and dirty conversion of Windows SDK to Linux.

Sorry for the mess. All the Poco libs are copied here for convenience. You probably want to work based off the the ```arch/linux_64``` branch. That branch is now the default on this repo.
The actual Mber code is in ```generated``` and ```src```. The rest is due for cleanup. 

**Note: Use the Poco 1.5.3 libraries. Those are the latest and they're not backward-compatible. I've deleted the other Poco versions on the ```arch/linux_64``` branch.**

##### Building Poco #####

    cd cpp/poco-1.5.3-all
    make -s clean
    ./configure --omit=Data/ODBC,Data/MySQL --no-tests --no-samples
    make -s -j4
    
##### Building libMber.so #####

    make clean
    make -j
    

##### Building and running the (broken) test target #####
The ```test``` binary starts running and then fails with a SIGABRT. Needs
debugging.

    make clean
    make -j
    make -j test
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:./cpp/poco-1.5.3-all/lib/Linux/x86_64
    ./test
    

    
