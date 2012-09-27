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
MSyl Pinyin::munchSyl ( cchar*& pStr ) const
{
	auto start = pStr;
	INIT init = Void;
	MED med = MED ( 0 );
	FIN fin = ZERO;
	TONE t1 = NEUTRAL, t2 = NEUTRAL;
	MSyl syl = _miDict.matchStart ( pStr );

	do
	{
		if ( syl )
		{
			init = syl.init();
			med = syl.med();
			t1 = syl.tone();
		}

		auto pMark = pStr;

		MSyl syl2 = _mfDict.matchStart ( pStr );
		if ( syl2 )
		{
			t2 = syl2.tone();

			if ( t2 != NEUTRAL && t1 != NEUTRAL )
			{
				pStr = pMark;
				break;
			}

			fin = syl2.fin();
			if ( syl2.med() == U )
			{
				if ( syl2.fin() == ZERO && med == I ) //IU
					fin = OU;
				else if ( syl2.fin() == ENG ) //ONG
				{
					med = MED ( med | U );
					fin = syl2.fin();
				}
				else
					pStr = pMark;
			}
			else
			{
				fin = syl2.fin();
				if( fin == Y && med == U )
				{
					fin = EI;
				}
				else if ( fin == E && ( ( med & I ) == I ) ) //ie,üe
				{
					fin = EH;
				}
			}
		}

	}
	while ( 0 );

	if ( ( init | med | fin ) == 0 ) return MSyl::Default;

	return MSyl ( init, med, fin, ( t1 == NEUTRAL ? t2 : t1 ) );
}

string Pinyin::transcribe ( const MSyl& syl ) const
{
	static cchar* empty = "";
	string start, end;
	INIT i = syl.init();
	TONE t = syl.tone();
	MED m = syl.med();
	RIME r = syl.rime();


	//initial
	if ( i == Void && m != KAI ) //y w yu
	{
		return _m0Trans[MSyl ( r,t )];
	}
	else if ( syl.group() == GGRP && syl.isPalatized() )  //j q x
	{
		start = _specInit[i];
		if ( m == IU && syl.fin() != ENG ) //ü -> u but not iong
		{
			r = ( RIME ) ( U | syl.fin() ); //ju qu xu
		}
	}
	else if ( syl.group() == TZGRP && m == I && syl.fin() == ZERO )  //zyi cyi syi
	{
		start = _specInit[i];
	}
	else
		start = _miTrans[i];

	//final
	end = _mfTrans[MSyl ( r,t )];

	return start + end;
}
const Pinyin pinyin;
}//end cphonetic
