#pragma once

class NonCopyable
{
protected:
	// Protected constructor since inheritance is private
	NonCopyable() {}
	// Non-virtual destructor since no data's held
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&);
	NonCopyable& operator=(const NonCopyable&);
};
