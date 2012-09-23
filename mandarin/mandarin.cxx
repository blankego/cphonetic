#include "mandarin.h"
#include "transcriptor.h"
#include "bopomofo.h"

namespace cphonetic
{
	bool MSyl::operator<( MSyl rhs)const
	{
		return *this == rhs ? false :
			init() < rhs.init() ? true :
				med() < rhs.med() ? true :
					fin() < rhs.fin() ? true :
						tone() < rhs.tone();
				
	}
	CRMaybe<MSyl> MSyl::from(MTranscriptor* trans,cchar* sPtr)
	{
		return trans->munchSyl(sPtr);
	}
	//The default string form of MSyl is in  bopomofo notation
	string MSyl::toStr()const
	{
		return bopomofo.transcribe(*this);
	}
	string MSyl::toStr(const MTranscriptor& trans)const
	{
		return trans.transcribe(*this);
	}
	ostream& operator<<(ostream& os, const MSyl& ms)
	{
		return os << bopomofo.transcribe(ms);		
	}
	
}//end namespace cphonetic