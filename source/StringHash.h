#ifndef __HASH_KEY_H__
#define __HASH_KEY_H__

#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

namespace bea
{

class StringHash
{
public:

    StringHash()
        : hash(0)
    {}

    StringHash( const std::string&  _s )
        : hash( hash_function()( _s ) )
    {}

    ~StringHash()
    {}

    /*!
        The hash function for strings.
        This is the central function of this class,
        this essentially takes a string and turns it
        into a number. Also note that it lowercases
        the string, this is to avoid programmers
        mixing cases.
    */
    class hash_function
    {
    public:
        size_t operator()( const std::string& _s ) const
        {
            static boost::hash< std::string> string_hash;
            std::string tempstr( _s );
            boost::to_lower( tempstr );
            return string_hash( tempstr );
        }
    };

    //! Comparison function class for boost.
    class equal_to
    {
    public:
        bool operator()( const std::string& _l, const std::string& _r ) const
        {
            std::string tl( _l );
            std::string tr( _r );
            boost::to_lower( tl );
            boost::to_lower( tr );
            return tl == tr;
        }
    };

    //! Standard assignment from string.
    const StringHash& operator = ( const std::string& _s )
    {
        (*this) = StringHash( _s );
        return *this;
    }

    //! Standard comparison.
    bool operator == ( const StringHash& other ) const
    {
        return hash == other.hash;
    }

    //! Comparison against a string, it hashes the string then compares.
    bool operator == ( const std::string& other ) const
    {
        return hash == hash_function()( other );
    }

    //! Implicit conversion to size_t, so that we can easy print, store, or serialize the hash.
    operator const std::size_t& ()
    {
        return hash;
    }

	const std::size_t getHash() const { return hash; }

private:
    std::size_t hash;
};

inline std::ostream& operator <<(std::ostream& os,const StringHash& obj)
{
      os<<obj.getHash();
      return os;
}

}

#endif;