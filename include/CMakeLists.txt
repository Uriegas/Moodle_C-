add_library(
	moodle_lib STATIC
	input.h
	exam.h
	parser.h
	question.h
	dataset.h
	${PROJECT_SOURCE_DIR}/src/input.cpp
	${PROJECT_SOURCE_DIR}/src/exam.cpp
	${PROJECT_SOURCE_DIR}/src/parser.cpp
	${PROJECT_SOURCE_DIR}/src/question.cpp
	${PROJECT_SOURCE_DIR}/src/dataset.cpp
	)

#add_library(
#	menu SHARED
#	menu.h
#	${PROJECT_SOURCE_DIR}/src/menu.cpp
#	)