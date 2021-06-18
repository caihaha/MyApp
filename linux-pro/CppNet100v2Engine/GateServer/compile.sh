cd `dirname $0`
#
g++ \
server.cpp \
../depends/json/cJSON.c \
../depends/json/CJsonObject.cpp \
-I ../depends/include \
-I ../depends/json \
-std=c++11 -pthread \
-o start
