target_sources(RTRT
	PUBLIC
	"scene.hpp"
	PRIVATE
	"scene.cpp"
)

add_subdirectory("SceneObjects")
add_subdirectory("IntersectionInfo")