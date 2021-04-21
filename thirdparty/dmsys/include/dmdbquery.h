
#ifndef __DMDBQUERY_H_INCLUDE__
#define __DMDBQUERY_H_INCLUDE__

#include <string>
#include <vector>
#include "dmescape_string.h"
#include "dmformat.h"

class DMDBQuery
{
public:
    DMDBQuery& into( const std::string& tbName )
    {
        m_table = tbName;
        m_sql += fmt::format( " {} ", tbName );
        return *this;
    }
    DMDBQuery& create( const std::string& tbName, bool check = false )
    {
        if ( check )
        {
            m_sql += fmt::format( " {} IF NOT EXISTS ", tbName );
        }
        else
        {
            m_sql += fmt::format( " {} ", tbName );
        }

        return *this;
    }
    DMDBQuery& begin()
    {
        m_sql += " ( ";
        return *this;
    }

    DMDBQuery& end()
    {
        m_sql += " ) " ;
        return *this;
    }

    DMDBQuery& def( const std::string&   key,
                    const std::string& type,
                    int length = 0,
                    const std::string& dft = "", bool inc  = false )
    {

        if ( definitions.size() > 0 )
        {
            m_sql += " , ";
        }

        std::string lenStr;

        if ( length > 0 )
        {
            lenStr += fmt::format("({})", length);
        }

        m_sql += fmt::format(" {} {}{} {} ", key, type,
                             length > 0 ? lenStr.c_str() : "", inc ? " AUTO_INCREMENT " : "");

        return *this;
    }


    template <typename ... Args>
    DMDBQuery& insert( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "insert into ";
        m_sql += m_table ;

        if ( argLen > 0 )
        {
            m_sql += "( ";
        }

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        m_sql += fmt::format(format.c_str(), args... );

        if ( argLen > 0 )
        {
            m_sql += ( " )  " );
        }

        return *this;
    }

    template <typename ... Args>
    DMDBQuery& update( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "update ";
        m_sql += m_table ;

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        m_sql += fmt::format( format.c_str(), args... );

        return *this;
    }

    DMDBQuery& set( const std::string& term )
    {
        std::string termStr;
        termStr = fmt::format( " {} ", term );
        sets.push_back( termStr.c_str() );

        if ( sets.size() <= 1 )
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    template<class T>
    DMDBQuery& set( const std::string& key, T val )
    {
        std::string termStr;
        termStr = fmt::format( " {} = {} ", key,  val );
        sets.push_back( termStr.c_str() );

        if (sets.size() <= 1)
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    DMDBQuery& del()
    {
        clear();
        m_sql += "delete from ";
        m_sql += m_table;
        return *this;
    }

    DMDBQuery& set( const std::string& key, const char*   val )
    {
        return this->set( key, std::string( val ) );
    }

    DMDBQuery& set( const std::string& key, const std::string& val )
    {
        std::string termStr;
        auto str = EscapeString( val );
        termStr += fmt::format( " {} = \"{}\" ", key, str );
        sets.push_back( termStr.c_str() );

        if (sets.size() <= 1)
        {
            m_sql += " set ";
            m_sql += termStr;
        }
        else
        {
            m_sql += " ,";
            m_sql += termStr;
        }

        return *this;
    }

    template <class T>
    std::string printarg( T t )
    {
        std::string val = fmt::format("{}", t);
        return val.c_str() ;
    }

    std::string printarg( const char*   t )
    {
        auto str = EscapeString( t );
        return std::string( "\"" ) + str + "\"";
    }

    std::string printarg( const std::string& t )
    {
        auto str = EscapeString( t );
        return std::string( "\"" ) + str + "\"";
    }

    template <typename ... Args>
    DMDBQuery& values( const Args& ... args )
    {
        int argLen = sizeof ...( Args );
        m_sql += " values ";
        m_sql += "("  ;

        std::string format;

        for ( int i  = 0; i   < argLen ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        m_sql += fmt::format( format.c_str(), printarg( args )... );
        m_sql += ( ")" );
        return *this;
    }

    template <typename ... Args>
    DMDBQuery& select( const Args& ... args )
    {
        clear();
        int argLen = sizeof ...( Args );
        m_sql += "select " ;

        std::string format;

        for ( int i  = 0; i   < argLen  ; i++ )
        {
            if ( i < argLen - 1)
            {
                format += " {}, ";
            }
            else
            {
                format += " {} ";
            }
        }

        m_sql += fmt::format( format.c_str(), args... );
        m_sql += fmt::format( " from {} ", m_table );
        return *this;
    }
    DMDBQuery& select( const std::string& selData )
    {
        clear();
        m_sql += fmt::format( "select {} from {} ", selData, m_table );
        return *this;
    }

    DMDBQuery& table( const std::string& tbName )
    {
        m_table = tbName;
        return *this;
    }

    DMDBQuery& where( const std::string& key,  const char* term )
    {
        return this->where( key, "=", term );
    }

    DMDBQuery& where( const std::string& key, const std::string& op,
                      const char* term )
    {
        return where( key, op, std::string( term ) );
    }

    DMDBQuery& where( const std::string& key, const std::string& op,
                      const std::string& term )
    {
        std::string termStr;
        auto str = EscapeString( term );
        termStr += fmt::format( "{} {} \"{}\"", key, op, str );
        wheres.push_back( termStr.c_str() );

        m_sql += fmt::format( wheres.size() > 1 ? " and {} " : " where {} ",
                              termStr.c_str() );
        return *this;
    }

    template <typename T>
    DMDBQuery& where( T term )
    {
        std::string termStr;
        termStr += fmt::format( " {} ",  term );
        wheres.push_back( termStr.c_str() );

        m_sql += fmt::format( wheres.size() > 1 ? " and  {} " : " where {} ", term );
        return *this;
    }

    template <typename T>
    DMDBQuery& where( const std::string& key,  T   term )
    {
        return where<T>( key, "=", term );
    }

    template <typename T>
    DMDBQuery& where( const std::string& key, const std::string& op, T   term )
    {
        std::string termStr;
        termStr += fmt::format( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );

        m_sql += fmt::format( wheres.size() > 1 ? " and {} " : " where {} ",
                              termStr.c_str() );
        return *this;
    }

    template<typename T>
    DMDBQuery& or_where( const std::string& key, const std::string& op, T  term )
    {
        std::string termStr;
        termStr += fmt::format( " {} {} {} ", key, op, term );
        wheres.push_back( termStr.c_str() );
        m_sql += fmt::format( " or {} ", termStr.c_str() );
        return *this;
    }

    DMDBQuery& limit( unsigned int count )
    {
        m_sql += fmt::format( " limit {} ", count );

        return *this;
    }
    DMDBQuery& limit( unsigned int offset, unsigned int count )
    {
        m_sql += fmt::format( " limit {}, {}  ", offset, count );
        return *this;
    }
    DMDBQuery& group_by( const std::string& col )
    {
        m_sql += fmt::format( " group by {} ", col );
        return *this;
    }

    DMDBQuery& order_by( const std::string& col, const std::string& type = "asc" )
    {
        m_sql += fmt::format( " order by {} {} ", col, type );
        return *this;
    }

    DMDBQuery& join( const std::string& tb, const std::string& lId,
                     const std::string& op, const std::string& rId )
    {
        return inner_join( tb, lId, op, rId );
    }

    DMDBQuery& inner_join( const std::string& tb, const std::string& lId,
                           const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " inner join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DMDBQuery& left_join( const std::string& tb, const std::string& lId,
                          const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " left join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    DMDBQuery& right_join( const std::string& tb, const std::string& lId,
                           const std::string& op, const std::string& rId )
    {
        m_sql += fmt::format( " right join {} on {} {} {} ", tb, lId, op, rId );
        return *this;
    }

    const char*   sql() const
    {
        return m_sql.c_str();
    }


    void clear()
    {
        m_sql.clear();
        wheres.clear();
        sets.clear();
    }


private:

    std::vector<std::string > definitions;
    std::vector<std::string > wheres;
    std::vector<std::string > sets ;
    std::string  m_table;
    std::string  m_sql ;
};


static DMDBQuery& DMGetQuery()
{
    static thread_local DMDBQuery g_oQuery;
    return g_oQuery;
}

#endif // __DMDBQUERY_H_INCLUDE__
