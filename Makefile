
OBJS = RK4_rayple.o RK4_funct.o
OBJS1 = Self_Conv_RP.o RK4_funct.o
OBJS2 = RK4_Rofalpha.o RK4_funct.o
OBJS3 = Richardson_extrap.o RK4_funct.o
cpp=g++ -O3
cppflags= -c 
cppflags2= -c -std=c++11

all:  RK4 Self_Conv_RP RK4_Rofalpha Richardson

RK4 : ${OBJS}
	${cpp} -o RK4 ${OBJS}

RK4_rayple.o : RK4_rayple.C header.h
	${cpp} ${cppflags2} RK4_rayple.C

RK4_funct.o : RK4_funct.C header.h
	${cpp} ${cppflags2} RK4_funct.C

Self_Conv_RP : ${OBJS1}
	${cpp} -o Self_Conv_RP ${OBJS1}

Self_Conv_RP.o : Self_Conv_RP.C header.h
	${cpp} ${cppflags2} Self_Conv_RP.C

RK4_Rofalpha : ${OBJS2}
	${cpp} -o RK4_Rofalpha ${OBJS2}

RK4_Rofalpha.o : RK4_Rofalpha.C header.h
	${cpp} ${cppflags2} RK4_Rofalpha.C 

Richardson : ${OBJS3}
	${cpp} -o Richardson ${OBJS3}

Richardson.o : Richardson_extrap.C header.h
	${cpp} ${cppflags2} Richardson_extrap.C

clean :
	rm RK4 Self_Conv_RP RK4_Rofalpha Richardson ${OBJS} ${OBJS1} ${OBJS2} ${OBJS3} *~
