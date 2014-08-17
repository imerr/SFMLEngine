#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Box2D/Collision/Shapes/b2ChainShape.o \
	${OBJECTDIR}/src/Box2D/Collision/Shapes/b2CircleShape.o \
	${OBJECTDIR}/src/Box2D/Collision/Shapes/b2EdgeShape.o \
	${OBJECTDIR}/src/Box2D/Collision/Shapes/b2PolygonShape.o \
	${OBJECTDIR}/src/Box2D/Collision/b2BroadPhase.o \
	${OBJECTDIR}/src/Box2D/Collision/b2CollideCircle.o \
	${OBJECTDIR}/src/Box2D/Collision/b2CollideEdge.o \
	${OBJECTDIR}/src/Box2D/Collision/b2CollidePolygon.o \
	${OBJECTDIR}/src/Box2D/Collision/b2Collision.o \
	${OBJECTDIR}/src/Box2D/Collision/b2Distance.o \
	${OBJECTDIR}/src/Box2D/Collision/b2DynamicTree.o \
	${OBJECTDIR}/src/Box2D/Collision/b2TimeOfImpact.o \
	${OBJECTDIR}/src/Box2D/Common/b2BlockAllocator.o \
	${OBJECTDIR}/src/Box2D/Common/b2Draw.o \
	${OBJECTDIR}/src/Box2D/Common/b2Math.o \
	${OBJECTDIR}/src/Box2D/Common/b2Settings.o \
	${OBJECTDIR}/src/Box2D/Common/b2StackAllocator.o \
	${OBJECTDIR}/src/Box2D/Common/b2Timer.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2CircleContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2Contact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ContactSolver.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonContact.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2DistanceJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2FrictionJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2GearJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2Joint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MotorJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MouseJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PrismaticJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PulleyJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RevoluteJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RopeJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WeldJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WheelJoint.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2Body.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2ContactManager.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2Fixture.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2Island.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2World.o \
	${OBJECTDIR}/src/Box2D/Dynamics/b2WorldCallbacks.o \
	${OBJECTDIR}/src/Box2D/Rope/b2Rope.o \
	${OBJECTDIR}/src/Game.o \
	${OBJECTDIR}/src/Light.o \
	${OBJECTDIR}/src/LightSystem.o \
	${OBJECTDIR}/src/Node.o \
	${OBJECTDIR}/src/ResourceManager.o \
	${OBJECTDIR}/src/Scene.o \
	${OBJECTDIR}/src/SpriteNode.o \
	${OBJECTDIR}/src/util/Box2dDebugDraw.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a

${OBJECTDIR}/src/Box2D/Collision/Shapes/b2ChainShape.o: src/Box2D/Collision/Shapes/b2ChainShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision/Shapes
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/Shapes/b2ChainShape.o src/Box2D/Collision/Shapes/b2ChainShape.cpp

${OBJECTDIR}/src/Box2D/Collision/Shapes/b2CircleShape.o: src/Box2D/Collision/Shapes/b2CircleShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision/Shapes
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/Shapes/b2CircleShape.o src/Box2D/Collision/Shapes/b2CircleShape.cpp

${OBJECTDIR}/src/Box2D/Collision/Shapes/b2EdgeShape.o: src/Box2D/Collision/Shapes/b2EdgeShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision/Shapes
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/Shapes/b2EdgeShape.o src/Box2D/Collision/Shapes/b2EdgeShape.cpp

${OBJECTDIR}/src/Box2D/Collision/Shapes/b2PolygonShape.o: src/Box2D/Collision/Shapes/b2PolygonShape.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision/Shapes
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/Shapes/b2PolygonShape.o src/Box2D/Collision/Shapes/b2PolygonShape.cpp

${OBJECTDIR}/src/Box2D/Collision/b2BroadPhase.o: src/Box2D/Collision/b2BroadPhase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2BroadPhase.o src/Box2D/Collision/b2BroadPhase.cpp

${OBJECTDIR}/src/Box2D/Collision/b2CollideCircle.o: src/Box2D/Collision/b2CollideCircle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2CollideCircle.o src/Box2D/Collision/b2CollideCircle.cpp

${OBJECTDIR}/src/Box2D/Collision/b2CollideEdge.o: src/Box2D/Collision/b2CollideEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2CollideEdge.o src/Box2D/Collision/b2CollideEdge.cpp

${OBJECTDIR}/src/Box2D/Collision/b2CollidePolygon.o: src/Box2D/Collision/b2CollidePolygon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2CollidePolygon.o src/Box2D/Collision/b2CollidePolygon.cpp

${OBJECTDIR}/src/Box2D/Collision/b2Collision.o: src/Box2D/Collision/b2Collision.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2Collision.o src/Box2D/Collision/b2Collision.cpp

${OBJECTDIR}/src/Box2D/Collision/b2Distance.o: src/Box2D/Collision/b2Distance.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2Distance.o src/Box2D/Collision/b2Distance.cpp

${OBJECTDIR}/src/Box2D/Collision/b2DynamicTree.o: src/Box2D/Collision/b2DynamicTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2DynamicTree.o src/Box2D/Collision/b2DynamicTree.cpp

${OBJECTDIR}/src/Box2D/Collision/b2TimeOfImpact.o: src/Box2D/Collision/b2TimeOfImpact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Collision
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Collision/b2TimeOfImpact.o src/Box2D/Collision/b2TimeOfImpact.cpp

${OBJECTDIR}/src/Box2D/Common/b2BlockAllocator.o: src/Box2D/Common/b2BlockAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2BlockAllocator.o src/Box2D/Common/b2BlockAllocator.cpp

${OBJECTDIR}/src/Box2D/Common/b2Draw.o: src/Box2D/Common/b2Draw.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2Draw.o src/Box2D/Common/b2Draw.cpp

${OBJECTDIR}/src/Box2D/Common/b2Math.o: src/Box2D/Common/b2Math.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2Math.o src/Box2D/Common/b2Math.cpp

${OBJECTDIR}/src/Box2D/Common/b2Settings.o: src/Box2D/Common/b2Settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2Settings.o src/Box2D/Common/b2Settings.cpp

${OBJECTDIR}/src/Box2D/Common/b2StackAllocator.o: src/Box2D/Common/b2StackAllocator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2StackAllocator.o src/Box2D/Common/b2StackAllocator.cpp

${OBJECTDIR}/src/Box2D/Common/b2Timer.o: src/Box2D/Common/b2Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Common
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Common/b2Timer.o src/Box2D/Common/b2Timer.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.o: src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.o src/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.o: src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.o src/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2CircleContact.o: src/Box2D/Dynamics/Contacts/b2CircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2CircleContact.o src/Box2D/Dynamics/Contacts/b2CircleContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2Contact.o: src/Box2D/Dynamics/Contacts/b2Contact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2Contact.o src/Box2D/Dynamics/Contacts/b2Contact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ContactSolver.o: src/Box2D/Dynamics/Contacts/b2ContactSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2ContactSolver.o src/Box2D/Dynamics/Contacts/b2ContactSolver.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.o: src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.o src/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.o: src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.o src/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.o: src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.o src/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonContact.o: src/Box2D/Dynamics/Contacts/b2PolygonContact.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Contacts
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Contacts/b2PolygonContact.o src/Box2D/Dynamics/Contacts/b2PolygonContact.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2DistanceJoint.o: src/Box2D/Dynamics/Joints/b2DistanceJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2DistanceJoint.o src/Box2D/Dynamics/Joints/b2DistanceJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2FrictionJoint.o: src/Box2D/Dynamics/Joints/b2FrictionJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2FrictionJoint.o src/Box2D/Dynamics/Joints/b2FrictionJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2GearJoint.o: src/Box2D/Dynamics/Joints/b2GearJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2GearJoint.o src/Box2D/Dynamics/Joints/b2GearJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2Joint.o: src/Box2D/Dynamics/Joints/b2Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2Joint.o src/Box2D/Dynamics/Joints/b2Joint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MotorJoint.o: src/Box2D/Dynamics/Joints/b2MotorJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MotorJoint.o src/Box2D/Dynamics/Joints/b2MotorJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MouseJoint.o: src/Box2D/Dynamics/Joints/b2MouseJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2MouseJoint.o src/Box2D/Dynamics/Joints/b2MouseJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PrismaticJoint.o: src/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PrismaticJoint.o src/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PulleyJoint.o: src/Box2D/Dynamics/Joints/b2PulleyJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2PulleyJoint.o src/Box2D/Dynamics/Joints/b2PulleyJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RevoluteJoint.o: src/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RevoluteJoint.o src/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RopeJoint.o: src/Box2D/Dynamics/Joints/b2RopeJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2RopeJoint.o src/Box2D/Dynamics/Joints/b2RopeJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WeldJoint.o: src/Box2D/Dynamics/Joints/b2WeldJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WeldJoint.o src/Box2D/Dynamics/Joints/b2WeldJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WheelJoint.o: src/Box2D/Dynamics/Joints/b2WheelJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics/Joints
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/Joints/b2WheelJoint.o src/Box2D/Dynamics/Joints/b2WheelJoint.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2Body.o: src/Box2D/Dynamics/b2Body.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2Body.o src/Box2D/Dynamics/b2Body.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2ContactManager.o: src/Box2D/Dynamics/b2ContactManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2ContactManager.o src/Box2D/Dynamics/b2ContactManager.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2Fixture.o: src/Box2D/Dynamics/b2Fixture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2Fixture.o src/Box2D/Dynamics/b2Fixture.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2Island.o: src/Box2D/Dynamics/b2Island.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2Island.o src/Box2D/Dynamics/b2Island.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2World.o: src/Box2D/Dynamics/b2World.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2World.o src/Box2D/Dynamics/b2World.cpp

${OBJECTDIR}/src/Box2D/Dynamics/b2WorldCallbacks.o: src/Box2D/Dynamics/b2WorldCallbacks.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Dynamics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Dynamics/b2WorldCallbacks.o src/Box2D/Dynamics/b2WorldCallbacks.cpp

${OBJECTDIR}/src/Box2D/Rope/b2Rope.o: src/Box2D/Rope/b2Rope.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Box2D/Rope
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Box2D/Rope/b2Rope.o src/Box2D/Rope/b2Rope.cpp

${OBJECTDIR}/src/Game.o: src/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Game.o src/Game.cpp

${OBJECTDIR}/src/Light.o: src/Light.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Light.o src/Light.cpp

${OBJECTDIR}/src/LightSystem.o: src/LightSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LightSystem.o src/LightSystem.cpp

${OBJECTDIR}/src/Node.o: src/Node.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Node.o src/Node.cpp

${OBJECTDIR}/src/ResourceManager.o: src/ResourceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ResourceManager.o src/ResourceManager.cpp

${OBJECTDIR}/src/Scene.o: src/Scene.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Scene.o src/Scene.cpp

${OBJECTDIR}/src/SpriteNode.o: src/SpriteNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SpriteNode.o src/SpriteNode.cpp

${OBJECTDIR}/src/util/Box2dDebugDraw.o: src/util/Box2dDebugDraw.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/util
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I../sfml/include -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/util/Box2dDebugDraw.o src/util/Box2dDebugDraw.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libengine.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
