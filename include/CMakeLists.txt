add_library(
	moodle_lib STATIC
	input.h
	menu.h
	parser.h
	question.h
	${PROJECT_SOURCE_DIR}/src/input.cpp
	${PROJECT_SOURCE_DIR}/src/menu.cpp
	${PROJECT_SOURCE_DIR}/src/parser.cpp
	${PROJECT_SOURCE_DIR}/src/question.cpp
	)

#add_library(
#	menu SHARED
#	menu.h
#	${PROJECT_SOURCE_DIR}/src/menu.cpp
#	)