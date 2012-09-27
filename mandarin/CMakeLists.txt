SET(mandarin_lib_src 
	mandarin.cxx 
	bopomofo.cxx
	pinyin.cxx
	pinyin_data.cxx
	altpinyin.cxx
	gworo.cxx
	)

add_library(mandarin ${mandarin_lib_src})

