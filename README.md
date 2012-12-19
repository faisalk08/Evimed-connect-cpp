libEvimed-connect-cpp
---------------------

libEvimed-connect-cpp is C++ static library for accessing Evimed API using OAuth authentication.

Requirements
------------

- curl library
- liboauthcpp library

Compiling
---------

- Compile
g++ -Isrc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/OAuthClient.d" -MT"src/OAuthClient.d" -o "src/OAuthClient.o" "../src/OAuthClient.cpp"

- Archive
ar -x liboauthcpp.a ("to extract into objects")
ar -r  "libEvimed-connect-cpp.a"  ./src/HttpClient.o ./src/OAuthClient.o   src/HMAC_SHA1.o src/base64.o src/HttpClient.o src/SHA1.o src/liboauthcpp.o src/urlencode.o

Implementation
--------------
This library includes liboauthcpp only so you will have to include only curl library since it is implemented differently in each OS.



