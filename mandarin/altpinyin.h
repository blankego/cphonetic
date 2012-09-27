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


#ifndef PINYIN_H
#define PINYIN_H

#include <map>
#include <string>
#include "pinyin.h"
namespace cphonetic 
{	

class MSyl;
using namespace msound;
using namespace std; 

class AltPinyin: public Pinyin
{
	static TokenDict<TONE> _tDict;
	static map<TONE,cchar*> _tTrans;
	
public:
	virtual MSyl munchSyl(cchar*& pStr)const;
	virtual string transcribe(const MSyl& syl)const;
};

}//end namespace

#endif // PINYIN_H
