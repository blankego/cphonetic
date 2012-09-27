#ifndef TRANSLITERATOR_H
#define TRANSLITERATOR_H
#include <string>



namespace cphonetic
{

	class MSyl;

class MTransliterator
{

public:
	virtual MSyl munchSyl( const char*& pStr ) const = 0;

	virtual std::string transcribe( const MSyl& syl ) const = 0;
};


}


#endif // TRANSLITERATOR_H
