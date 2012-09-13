#ifndef TRANSLITERATOR_H
#define TRANSLITERATOR_H
#include <string>
#include <map>
#include "tokendict.h"
#include "mandarin.h"

namespace cphonetic
{


class MTransliterator
{

public:
	virtual CRMaybe<MSyl> munchSyl( cchar*& pStr ) const = 0;

	virtual string transliterate( const MSyl& syl ) const = 0;
};


}


#endif // TRANSLITERATOR_H
