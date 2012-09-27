#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mandarin_test
#include <boost/test/unit_test.hpp>
#include "mandarin.h"
#include "helper.h"
#include "tokendict.h"
#include "bopomofo.h"
#include "pinyin.h"
#include "altpinyin.h"
#include <iostream>
#include <fstream>
#include <array>
#include <chrono>
using namespace cphonetic;
using namespace std::chrono;
using namespace std;
BOOST_AUTO_TEST_CASE(maybe)
{
	int i = 42; 
	auto mb = crmaybe(i);
	BOOST_CHECK(mb.hasValue);
	BOOST_CHECK_EQUAL(42,mb.value);
	
	BOOST_CHECK(250==crmaybe(250));
	
	CRMaybe<int> mb1 = nullptr;
	bool b = mb1;
	BOOST_CHECK_EQUAL(false,b);
	
	
	const double d = crmaybe(42.0);
	BOOST_CHECK_EQUAL(42.0,d);
}


using namespace cphonetic::msound;
BOOST_AUTO_TEST_CASE( msyl )
{
	
	MSyl juang4( J, U, ANG, DEPARTING );
	int size = sizeof( juang4 );
	auto init = juang4.init();
	auto med = juang4.med();
	auto fin = juang4.fin();
	auto tone = juang4.tone();
	auto rime = RIME(med | fin);
	
	BOOST_CHECK_EQUAL( 2, size );
	BOOST_CHECK_EQUAL( J, init );
	BOOST_CHECK_EQUAL( U, med );
	BOOST_CHECK_EQUAL( ANG, fin );
	BOOST_CHECK_EQUAL( DEPARTING, tone );
	BOOST_CHECK_EQUAL( juang4.rime(),rime);
	
	MSyl j2 (J,U,ANG,DEPARTING);
	BOOST_CHECK(juang4==j2);
	j2.tone(RISING);
	BOOST_CHECK(j2 < juang4);
	BOOST_CHECK_EQUAL(RISING, j2.tone());
	j2.init(G);
	BOOST_CHECK_EQUAL(G, j2.init());
	j2.med(KAI);
	BOOST_CHECK_EQUAL(KAI , j2.med());
	j2.fin(ENG);
	BOOST_CHECK_EQUAL(ENG,j2.fin());
	j2.med(U);
	BOOST_CHECK_EQUAL((U|ENG),j2.rime());
};


BOOST_AUTO_TEST_CASE( tokendict )
{
	TokenDict<cchar*> td ({
		{"b","b"},{"p","p"},{"m","m"},{"f","f"},{"v","v"},
		{"d","d"},{"t","t"},{"n","n"},{"l","l"},
		{"g","g"},{"k","k"},{"ng","ng"},{"h","h"},
		{"j","g"},{"q","k"},{"gn","gn"},{"x","h"},
		{"zh","j"},{"ch","ch"},{"sh","sh"},{"r","r"},
		{"z","tz"},{"c","ts"},{"s","s"},
		
	});
	TokenDict<cchar*> d2 ({{"","empty"},{"●","symbol"}});
	
	
	cchar* s = "gang";
	cchar* p = s;	
	BOOST_CHECK_EQUAL("empty",d2.matchStart(p));	
 	BOOST_CHECK_EQUAL(s,p);
	
 	BOOST_CHECK_EQUAL("g",td.matchStart(p));
	p = "b";
	BOOST_CHECK_EQUAL("b",td.matchStart(p));
	s= "012";
	p=s;
	BOOST_CHECK(td.matchStart(p) == nullptr);
	BOOST_CHECK_EQUAL(s,p);
	s = "gnzc";
	p=s;
	
	BOOST_CHECK_EQUAL("gn",td.matchStart(p));	
	BOOST_CHECK_EQUAL("tz",td.matchStart(p));
	
	BOOST_CHECK_EQUAL("ts",td.matchStart(p));
	BOOST_CHECK(td.matchStart(p) == nullptr);
	
}


BOOST_AUTO_TEST_CASE(bopomofo_test)
{
	cchar* s = "ㄓㄨㄤˋa", *p = s,*s0 = "ㄓㄨㄤˋ";
	
	auto syl =  bopomofo.munchSyl(p);
	
	BOOST_CHECK_EQUAL("a",p);
	
	BOOST_CHECK_EQUAL(s0,syl.toStr());
	BOOST_CHECK_EQUAL(JGRP,syl.group());
	cchar* s1 = "ㄐㄩㄢˇ";
	p = s1;
	auto syl1 = bopomofo.munchSyl(p);
	BOOST_CHECK_EQUAL(GGRP,syl1.group());
	BOOST_CHECK(syl1.isPalatized());
	
	
	fstream f("all_syllables.txt",ios_base::in);
	vector<string>lines;
	linebuf<50> lb;
	
	while(lb<<f)lines.push_back(&lb);	
	time_point<system_clock> end,start = system_clock::now();
	for(string l : lines)
	{	cchar* pl = &l[0];
		auto thesyl = bopomofo.munchSyl(pl);
		string sl = thesyl.toStr();
// 		if(!thesyl)cout << "wtf"<<","<<sl<<endl;
		BOOST_CHECK_EQUAL( l,sl);
	}
	end = system_clock::now();
	cout << lines.size() <<" Bopomofo entries processed in "
		<<duration_cast<microseconds>(end-start).count()<<" microseconds.\n\n";
	f.close();
	
}

BOOST_AUTO_TEST_CASE(alt_pinyin_test)
{
	cchar* s="zhuang4",*p=s;
	MSyl syl = pinyin.munchSyl(p);
	string bpmf = syl.toStr();
	cchar* pBpmf = &bpmf[0];
	BOOST_CHECK_EQUAL(syl,bopomofo.munchSyl(pBpmf));
	fstream f("all_syllables.txt",ios_base::in);
	vector<cchar*> lines;
	linebuf<50> lb;
	while(lb<<f)lines.push_back(&lb);
	time_point<system_clock> end,start = system_clock::now();
	for(cchar*p : lines)	{	
		
		MSyl thesyl = bopomofo.munchSyl(p);
		string str = thesyl.toStr(pinyin);
		p=&str[0];
		BOOST_CHECK_EQUAL(thesyl,pinyin.munchSyl(p));
		
	}
	end = system_clock::now();
	cout << lines.size() <<" Pinyin entries processed in "
		<<duration_cast<microseconds>(end-start).count()<<" microseconds.\n\n";
	f.close();
}
BOOST_AUTO_TEST_CASE(pinyin_test)
{
	fstream f("all_syllables.txt",ios_base::in);
	vector<cchar*> lines;
	linebuf<50> lb;	
	while(lb<<f)lines.push_back(&lb);
	time_point<system_clock> end,start = system_clock::now();
	for(cchar*p : lines)
	{
		//cchar* p = &lb;
		MSyl syl = bopomofo.munchSyl(p);
		string str = syl.toStr(pinyin);
		p=&str[0];
		MSyl m = pinyin.munchSyl(p);
		BOOST_CHECK_EQUAL(syl,m);
		if(m.toStr()!=syl.toStr())
		{
			cout<< syl.toStr()<<str<<m.toStr()<<endl;
		}
		
	}
	end = system_clock::now();
	cout << lines.size() <<" Marked Pinyin entries processed in "
		<<duration_cast<microseconds>(end-start).count()<<" microseconds."<<endl;
	f.close();
}