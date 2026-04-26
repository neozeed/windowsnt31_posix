/*
	Tables which will help translation
*/
rev_list m_rev_lst =
{
	{ SNULL , SNULL }
};

nat_list nat_lst =
{
	{ "P"    , NNULL , RNULL },      /* 0 */
	{ "Zd"   , NNULL , RNULL },      /* 1 */
	{ "c"    , NNULL , RNULL },      /* 2 */
	{ "Fa"   , NNULL , RNULL },      /* 3 */
	{ "Fs"   , NNULL , RNULL },      /* 4 */
	{ "E"    , NNULL , RNULL },      /* 5 */
	{ "Za"   , NNULL , RNULL },      /* 6 */
	{ "Ox"   , NNULL , RNULL },      /* 7 */
	{ "w"    , NNULL , RNULL },      /* 8 */
	{ "DLL"  , NNULL , RNULL },      /* 9 */
	{ "W0"   , NNULL , RNULL },      /* 10 */
	{ "W1"   , NNULL , RNULL },      /* 11 */
	{ "W2"   , NNULL , RNULL },      /* 12 */
	{ "link" , NNULL , RNULL },      /* 13 */
	{ "Fpc"  , NNULL , RNULL },      /* 14 */
	{ "Gc"   , NNULL , RNULL },      /* 15 */
	{ "C"    , NNULL , RNULL },      /* 16 */
	{ "I"    , NNULL , RNULL },      /* 17 */
	{ "X"    , NNULL , RNULL },      /* 18 */
	{ "D"    , NNULL , RNULL },      /* 19 */
	{ "U"    , NNULL , RNULL },      /* 20 */
	{ ( char * ) NULL , NNULL , RNULL }
};

gnu_list gnu_lst =
{
	{ "P"           , NO , RNULL , SNULL ,  nat_lst },
	{ "traditional" , NO , RNULL , SNULL ,  NNULL },
	{ "go"          , NO , RNULL , SNULL ,  nat_lst + 1 },
	{ "f"           , NO , RNULL , SNULL ,  NNULL },
	{ "t"           , NO , RNULL , SNULL ,  NNULL },
	{ "c"           , NO , RNULL , SNULL ,  nat_lst + 2 },
	{ "o"           , OPEN , RNULL , "<file>" ,  nat_lst + 3 },
	{ "S"           , NO , RNULL , SNULL ,  nat_lst + 4 },
	{ "E"           , NO , RNULL , SNULL ,  nat_lst + 5 },
	{ "v"           , NO , RNULL , SNULL ,  NNULL },
	{ "pipe"        , NO , RNULL , SNULL ,  NNULL },
	{ "B"           , OPEN , RNULL , "<path-prefix>" ,  NNULL },
	{ "b"           , NO , RNULL , SNULL ,  NNULL },
	{ "ansi"        , NO , RNULL , SNULL ,  nat_lst + 6 },
	{ "pedantic"    , NO , RNULL , SNULL ,  NNULL },
	{ "O"           , NO , RNULL , SNULL ,  nat_lst + 7 },
	{ "g"           , NO , RNULL , SNULL ,  nat_lst + 1 },
	{ "w"           , NO , RNULL , SNULL ,  nat_lst + 8 },
	{ "static"      , NO , RNULL , SNULL ,  nat_lst + 10 },
	{ "Wimplicit"   , NO , RNULL , SNULL ,  nat_lst + 12 },
	{ "Wrettype"    , NO , RNULL , SNULL ,  nat_lst + 12 },
	{ "Wunused"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wswitch"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wcomment"    , NO , RNULL , SNULL ,  NNULL },
	{ "Wtrigraph"   , NO , RNULL , SNULL ,  NNULL },
	{ "Wall"        , NO , RNULL , SNULL ,  nat_lst + 11 },
	{ "Wshadow"     , NO , RNULL , SNULL ,  NNULL },
	{ "Wid="        , NO , RNULL , SNULL ,  NNULL },
	{ "Wpointer-arith", NO , RNULL , SNULL ,  NNULL },
	{ "Wcast-qual", NO , RNULL , SNULL ,  NNULL },
	{ "Wwrite-strings", NO , RNULL , SNULL ,  NNULL },
	{ "p"             , NO , RNULL , SNULL ,  NNULL },
	{ "pg"            , NO , RNULL , SNULL ,  NNULL },
	{ "l"            , OPEN , RNULL , "<libname>" ,  nat_lst + 13 },
	{ "L"            , OPEN , RNULL , "<libpath>" ,  NNULL },
	{ "nostdlib"     , OPEN , RNULL , SNULL ,  NNULL },
	{ "mmachinspec" , NO , RNULL , SNULL , NULL },
	{ "msoft-float" , NO , RNULL , SNULL , nat_lst + 14 },
	{ "mshort" , NO , RNULL , SNULL , NULL },
	{ "mnobitfield" , NO , RNULL , SNULL , NULL },
	{ "mbitfield" , NO , RNULL , SNULL , NULL },
	{ "mrtd" , NO , RNULL , SNULL , nat_lst + 15 },
	{ "munix" , NO , RNULL , SNULL , NULL },
	{ "mgnu" , NO , RNULL , SNULL , NULL },
	{ "mg" , NO , RNULL , SNULL , NULL },
	{ "mno-epilogue" , NO , RNULL , SNULL , NULL },
	{ "C" , NO , RNULL , SNULL , nat_lst + 16 },
	{ "I" , OPEN , RNULL , SNULL , nat_lst + 17 },
	{ "nostatic" , NO , RNULL , SNULL , nat_lst + 18 },
	{ "MM" , NO , RNULL , SNULL , NNULL },
	{ "M" , NO , RNULL , SNULL , NNULL },
	{ "D" , OPEN , RNULL , SNULL , nat_lst + 19 },
	{ "U" , OPEN , RNULL , SNULL , nat_lst + 20 },
	{ SNULL , OPEN , RNULL , SNULL , NNULL }
};
