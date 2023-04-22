## Project Overview

Inmcache is an in-memory cache storage that uses the TCP protocol for connection. It provides a text interface for interaction.
### Usage

To interact with Inmcache, you can create your [own client](https://gist.github.com/44zb/dea648b8b916efe29d5eff1d91907ff3) using any programming 
language that supports TCP connections. The table below lists the supported commands and their descriptions. Every command should be ended with `\0` symbol.

| Command				| Desription																|
------------------------|---------------------------------------------------------------------------|
|	SET	\<Key> \<Value>	| keyCreate/update stored data by key										|
|	GET \<Key>			| Get stored data by 														|
|	INC \<Key>			| Increment numeric value by 1. Non-numeric data will be interpreted as 0	|
|	DEC \<Key>			| Decrement numeric value by 1. Non-numeric data will be interpreted as 0	|
|	REM \<Key>			| Delete data by key														|
|	EXS \<Key>			| Check if data by key exists												|

### Building 

To build inmcache, you will need C++ compiler that supports C++20 standard and `boost-asio` library

Build was tested on Visual Studio 2022 with vcpkg as a package manager
