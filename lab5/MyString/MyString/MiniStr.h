#pragma 
#include <stdexcept>
#include <memory>

class CMiniStr {
public:
	CMiniStr()
	{}

	CMiniStr(const char * chars, size_t count);

	~CMiniStr();

	char * Get()const;

	void Clear();

	size_t Size();

	CMiniStr & operator=(CMiniStr&);
	char &operator[](size_t index);
private:
	size_t m_count = 0;
	std::unique_ptr<char[]> m_chars;
};