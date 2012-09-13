#include "mandarin.h"
#include "transliterators.h"
#include "bopomofo.h"

namespace cphonetic
{
	bool MSyl::operator<( MSyl rhs)
	{
		return *this == rhs ? false :
			init() < rhs.init() ? true :
				med() < rhs.med() ? true :
					fin() < rhs.fin() ? true :
						tone() < rhs.tone();
				
	}
	CRMaybe<MSyl> MSyl::from(MTransliterator* trans,cchar* sPtr)
	{
		return trans->munchSyl(sPtr);
	}
	//The default string form of MSyl is in  bopomofo notation
	string MSyl::toStr()const
	{
		return bopomofo->transliterate(*this);
	}
	ostream& operator<<(ostream& os, const MSyl& ms)
	{
		return os << bopomofo->transliterate(ms);		
	}
	
}//end namespace cphonetic