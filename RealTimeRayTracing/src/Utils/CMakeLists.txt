target_sources(RTRT
	PUBLIC
	"nonCopyable.hpp"
	"Timer/timer.hpp"
	"ThreadPool/threadPool.hpp"
	"FileWriter/fileWriter.hpp"
	"cast.hpp"
	"Date/date.hpp"

	PRIVATE
	"ThreadPool/threadPool.cpp"
	"FileWriter/fileWriter.cpp"
	"Date/date.cpp"
)
