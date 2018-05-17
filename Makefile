CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
LDFLAGS = -lboost_system

VPATH = src
SRC = #sources
OBJ = ${SRC:.cc=.o}
