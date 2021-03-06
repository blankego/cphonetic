/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef MARKED_PINYIN_H
#define MARKED_PINYIN_H
#include "transliterator.h"
#include "tokendict.h"
#include <map>
#include <vector>
#include "msound.h"

namespace cphonetic 
{	


class MSyl;
using namespace msound;
class Pinyin : public MTransliterator
{
protected:
	static TokenDict<MSyl> _miDict;
	static TokenDict<MSyl > _mfDict;
	static map<INIT,cchar*> _miTrans;
	static map<INIT,cchar*> _specInit;
	static map<MSyl,cchar*> _mfTrans; 	
	static map<MSyl,cchar*> _m0Trans;//yi wu yu
	static vector<cchar*> _ui;
	static vector<cchar*> _iu;
	
	
public:
	virtual MSyl munchSyl(cchar*& pStr)const;
	virtual string transcribe(const MSyl& syl)const;
	

};
}//end cphonetic
#endif // MARKED_PINYIN_H
