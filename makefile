all:
	g++ tests.cpp src/TCPServer.cpp src/TCPCommon.cpp -lpthread -std=c++11 -o server
	g++ testc.cpp src/TCPClient.cpp src/TCPCommon.cpp -std=c++11 -o client
