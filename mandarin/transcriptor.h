#ifndef TRANSLITERATOR_H
#define TRANSLITERATOR_H
#include <string>


template<class T> struct CRMaybe;

namespace cphonetic
{

	class MSyl;

class MTranscriptor
{

public:
	virtual CRMaybe<MSyl> munchSyl( const char*& pStr ) const = 0;

	virtual std::string transcribe( const MSyl& syl ) const = 0;
};


}


#endif // TRANSLITERATOR_H
