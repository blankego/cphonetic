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


#include "marked_pinyin.h"

namespace cphonetic
{
using namespace msound;
CRMaybe<MSyl> MarkedPinyin::munchSyl( cchar*& pStr )const
{
	auto start = pStr;
	INIT init = Void;
	MED med = MED( 0 );
	FIN fin = ZERO;
	TONE t1 = NEUTRAL, t2 = NEUTRAL;
	auto maybe = _miDict.matchStart( pStr );

	do {
		if( maybe ) {
			init = get<0>( maybe.value );
			med = get<1>( maybe.value );
			t1 = get<2>( maybe.value );

			if( init >= J && med == MMAGIC ){ //jy chy shy ry tzy tsy sy
				med = KAI;
				fin = Y;
				break;
			}			
		}		
		
		auto pMark = pStr;		
		auto maybe2 = _mfDict.matchStart( pStr );

		if( maybe2 ) {
			t2 = maybe2.value.second;

			if( t2 != NEUTRAL && t1 != NEUTRAL ) {
				pStr = pMark;
				break;
			}

			fin = maybe2.value.first;

			if( fin == E && ( ( med & I ) == I ) ) {//ie,üe
				fin = EH;
			} else if( fin == Y ) {//ong
				fin == ENG;
				med = MED(med|U);
			}
		}

	} while( 0 );

	if( ( init | med | fin ) == 0 )return nullptr;

	return MSyl( init, med, fin, ( t1 == NEUTRAL ? t2 : t1 ) );
}

string MarkedPinyin::transcribe( const MSyl& syl )const
{
	static cchar* empty = "";
	string start, end;
	INIT i = syl.init();
	TONE t = syl.tone();
	MED m = syl.med();
	RIME r = syl.rime();
	
	
	//initial
	if(i == Void && m != KAI){ //y w yu 
		return _m0Trans[make_pair(r,t)];			
	}else if(syl.group() == GGRP && syl.isPalatized()){ //j q x
		start = _specInit[i];
		if(m == IU)r = U|syl.fin(); //ju qu xu
	}else if(syl.group() == TZGRP && m == I){ //zyi cyi syi
		start = _specInit[i];
	}else 
		start = _miTrans[i];	
	
	//final		
	end = _mfTrans ^ make_pair( make_pair( r, t ), empty );	

	return start + end;
}
const MarkedPinyin mpinyin;
}//end cphonetic
