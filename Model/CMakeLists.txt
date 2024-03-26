cmake_minimum_required(VERSION 3.24)
project(ProgettoPAO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ProgettoPAO
        FileH/Item.h
        FileCPP/Item.cpp
        FileH/Trasporto.h
        FileCPP/Trasporto.cpp
        FileH/Libri.h
        FileCPP/Libri.cpp
        FileH/Cibo.h
        FileCPP/Cibo.cpp
        FileH/Vestiti.h
        FileCPP/Vestiti.cpp
        FileH/Casa.h
        FileCPP/Casa.cpp
        main.cpp
        FileCPP/Utenti.cpp
        FileH/Utenti.h
        FileH/DoubleList.h
        )
