#ifndef __B_PRINT_ANY__
#define __B_PRINT_ANY__

#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>

namespace bea
{

//! Print Any Class
/*!
    Converterts a boost::any into a string for known types.
*/
class PrintAny
{
public:
    PrintAny(){};
    const std::string operator()( const boost::any& _other )
    {
        std::stringstream strm;
        try
        {
            if( _other.type() == typeid( int ) )
                strm<<  boost::any_cast<int>(_other);
            else if( _other.type() == typeid( float ) )
                strm<<  boost::any_cast<float>(_other);
            else if( _other.type() == typeid( std::string ) )
                strm<<  boost::any_cast<std::string>(_other);
            else
                strm<< "Unknown Type '" << _other.type().name() << "'";
        }
        catch( boost::bad_any_cast )
        {
            strm<< "Bad Any";
        }
        return strm.str();
    }
};

}

#endif;