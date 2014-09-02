/*
   Copyright (c) by Valery Goryachev (Wal)
*/


#ifndef NCHISTORY_H
#define NCHISTORY_H

#include <wal.h>

using namespace wal;

class NCHistory
{
	ccollect<std::vector<unicode_t> > list;
	int current;
public:
	NCHistory(): current( 0 ) {}

	void Clear()
	{
		list.clear();
	}

	void Put( const unicode_t* str )
	{
		current = 0;

		for ( int i = 0; i < list.count(); i++ )
		{
			const unicode_t* s;
			const unicode_t* t;

			for ( s = str, t = list[i].data(); *t && *s; s++, t++ )
				if ( *t != *s ) { break; }

			if ( *t == *s )
			{
				std::vector<unicode_t> p = list[i];
				list.del( i );
				list.insert( 0, p );
				return;
			}
		}

		const size_t HistorySize = 1000;

		if ( list.count() > HistorySize ) { list.del( list.count() - 1 ); }

		list.insert( 0, new_unicode_str( str ) );
	}

	int Count() const { return list.count(); }
	const unicode_t* operator[] ( int n ) { return n >= 0 && n < list.count() ? list[n].data() : 0; }


	unicode_t* Prev() { return ( current < 0 || current >= list.count() ) ? 0 : list[current++].data(); }
	unicode_t* Next() { return ( current <= 0 || current > list.count() ) ? 0 : list[--current].data(); }

	~NCHistory() {}
};


#endif
