#include "mandarin.h"
#include "transliterator.h"
#include "bopomofo.h"
#include "iosfwd"

namespace cphonetic
{
	MSyl MSyl::Default;
	
	bool MSyl::operator<( MSyl rhs)const
	{
		return *this == rhs ? false :
			init() < rhs.init() ? true :
				med() < rhs.med() ? true :
					fin() < rhs.fin() ? true :
						tone() < rhs.tone();
				
	}
	
	
	//The default string form of MSyl is in  bopomofo notation
	string MSyl::toStr()const
	{
		return bopomofo.transcribe(*this);
	}
	string MSyl::toStr(const MTransliterator& trans)const
	{
		return trans.transcribe(*this);
	}
	ostream& operator<<(ostream& os, const MSyl& ms)
	{
		return os << bopomofo.transcribe(ms);		
	}
	
}//end namespace cphonetic