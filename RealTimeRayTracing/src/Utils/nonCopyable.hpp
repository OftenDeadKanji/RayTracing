#ifndef __NON_COPYABLE_HPP__
#define __NON_COPYABLE_HPP__

class NonCopyable
{
public:
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
