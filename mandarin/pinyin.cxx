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


#include "pinyin.h"
#include "mandarin.h"
namespace cphonetic
{
using namespace msound;

CRMaybe<MSyl> Pinyin::munchSyl( cchar*& pStr )const
{
	INIT init = Void;
	MED med = MED( 0 );
	FIN fin = ZERO;
	TONE tone;
	auto pr = _imDict.matchStart( pStr );

	if( pr )PASSIGN( init, med, pr.value );

	if( init >= J && med == IU ) {
		fin = Y;
	} else {
		fin = _fDict.matchStart( pStr );

		if( fin == E && ( ( med & I ) == I ) ) {
			fin = EH;
		} else if( fin == Y ) {
			fin == ENG;

			if( med == I )
				med == IU;
		}
	}

	if( ( init | med | fin ) == 0 )return nullptr;

	tone = _tDict.matchStart( pStr );

	return MSyl( init, med, fin, tone );
}
string Pinyin::transcribe( const MSyl& syl )const
{
	string im, f;
	im = _imTrans[make_pair( syl.init(), syl.med() )];

	if( syl.fin() == ZERO ) {
		if(syl.init()==Void)
			f = syl.med()==I ? "i" : "u";
		else
			f = "";
	} else if(syl.med()==U && syl.fin()==EI)
		f = "i";
	else if(syl.med()==I && syl.fin()==OU)
		f= "u";
	else	
		f = _fTrans[syl.fin()];
	

	return im + f + _tTrans[syl.tone()];
}

const Pinyin pinyin;
}//end namespace
