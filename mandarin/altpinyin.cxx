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


#include "altpinyin.h"
#include "mandarin.h"
#include "tokendict.h"
#include "msound.h"
namespace cphonetic
{
using namespace msound;

TokenDict<TONE> AltPinyin::_tDict ({
	{"ˉ",DARK},{"ˊ",LIGHT},{"ˇ",RISING},{"ˋ",DEPARTING},
	{"·",ENTERING},{"˙",NEUTRAL},{"",NEUTRAL},
	{"1",DARK},{"2",LIGHT},{"3",RISING},{"4",DEPARTING},
	{"0",ENTERING},{"5",NEUTRAL},
	
});
	
	
map<TONE,cchar*> AltPinyin::_tTrans = {
	{DARK,"1"},{LIGHT,"2"},{RISING,"3"},{DEPARTING,"4"},
	{ENTERING,"0"},{NEUTRAL,"5"}
};

MSyl AltPinyin::munchSyl(cchar*& pStr)const
{
	
	MSyl syl = Pinyin::munchSyl(pStr);
	if(syl && syl.tone() == NEUTRAL)
		syl.tone(_tDict.matchStart(pStr));

	return syl;
}


string AltPinyin::transcribe(const MSyl& syl)const
{
	TONE t = syl.tone();
	MSyl sylNoTone (syl);
	sylNoTone.tone(NEUTRAL);
	string s = Pinyin::transcribe(sylNoTone);
	return s + _tTrans[t];
}

const AltPinyin alt_pinyin;
}//end namespace
