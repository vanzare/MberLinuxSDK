# Mber C++ SDK #

## Building ##

If you don't have Visual Studio, you can build the C++ SDK using the
[Windows 7 SDK][].

You'll need to use a Windows SDK command prompt for building, since it will have
all the tools pathed correctly. You'll know if you've got the right prompt open
because you'll be able to run `msbuild /version` and get back a version number.

Code is generated with Nodeworker, so run that first.

~~~bash
cd ember\clients
nodeworker
~~~

After that, you can build the Poco libraries.

~~~bash
setenv /Release /x64 /win7
set VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\
set VSINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio 10.0\
cd cpp\poco
buildwin 100 build static_mt both x64 nosamples notests 2>&1
~~~

Once Poco's built, you can bulid the SDK.

~~~bash
msbuild cpp\MberClient.vcxproj /t:Build /p:Configuration=debug_shared;Platform=x64 2>&1
~~~

Once the SDK is built, you can run the tests.

~~~bash
cpp\test\x64\Debug\MberClientTest.exe
~~~

By default, the tests will run against production. You can run them against CI
by setting the `MBER_URL` environment variable.

~~~bash
set MBER_URL=http://dev.office.firepub.net
~~~


[Windows 7 SDK]: http://www.microsoft.com/en-us/download/details.aspx?id=8279 "Microsoft Windows SDK for Windows 7 and .NET Framework 4"
