add_library(
	moodle_lib SHARED
	input.h
	menu.h
	pregunta_calculada.h
	pregunta_multiple.h
	pregunta_simple.h
	pregunta_estructura.h
	${PROJECT_SOURCE_DIR}/src/input.cpp
	${PROJECT_SOURCE_DIR}/src/menu.cpp
	${PROJECT_SOURCE_DIR}/src/pregunta_calculada.cpp
	${PROJECT_SOURCE_DIR}/src/pregunta_multiple.cpp
	${PROJECT_SOURCE_DIR}/src/pregunta_simple.cpp
	)

#add_library(
#	menu SHARED
#	menu.h
#	${PROJECT_SOURCE_DIR}/src/menu.cpp
#	)