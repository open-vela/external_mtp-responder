CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(mtp-responder C)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src SRCS)

IF(BUILD_GCOV)
	ADD_DEFINITIONS("-DTIZEN_TEST_GCOV")
ENDIF(BUILD_GCOV)

INCLUDE(FindPkgConfig)
pkg_check_modules(pkgs REQUIRED glib-2.0 capi-content-media-content
	capi-media-metadata-extractor vconf dlog tapi capi-system-info storage libsystemd-daemon libsystemd)

FOREACH(flag ${pkgs_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -Wall -Werror")
SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fexceptions -fvisibility=hidden -fprofile-arcs -ftest-coverage")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fPIE")
SET(CMAKE_EXE_LINKER_FLAGS " -Wl,--as-needed -pie -Wl,--hash-style=both,-z,relroi ")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${pkgs_LDFLAGS} pthread rt gcrypt)

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)
INSTALL(FILES conf/mtp-responder.conf DESTINATION /opt/var/lib/misc)

ADD_EXECUTABLE(extract_descs_strs ${CMAKE_SOURCE_DIR}/ffs_tool/ffs_descs_strs_writer.c
	${CMAKE_SOURCE_DIR}/src/mtp_descs_strings.c)
ADD_CUSTOM_COMMAND(OUTPUT descs strs
	COMMAND ./extract_descs_strs
	DEPENDS extract_descs_strs)
ADD_CUSTOM_TARGET(descs_strs ALL DEPENDS descs strs)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/descs DESTINATION /etc/mtp-responder)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/strs DESTINATION /etc/mtp-responder)

IF(BUILD_GTESTS)
	ADD_SUBDIRECTORY(tests)
ENDIF(BUILD_GTESTS)
