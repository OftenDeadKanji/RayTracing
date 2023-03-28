target_sources(RTRT
	PUBLIC
	"nonCopyable.hpp"
	"Timer/timer.hpp"
	"ThreadPool/threadPool.hpp"

	PRIVATE
	"ThreadPool/threadPool.cpp"
)
