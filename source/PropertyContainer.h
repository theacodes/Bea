#ifndef __B__PROP_CONTAINER__
#define __B__PROP_CONTAINER__

#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/any.hpp>
#include <boost/foreach.hpp>
#include "StringHash.h"
#include "PrintAny.h"

namespace bea
{

//! Property Container Class
/*!
    Provides a simple and elegant way to store dynamic properties in a single object.
*/
class PropertyContainer
{

public:

    PropertyContainer()
        : properties()
    {}

    ~PropertyContainer()
    {}

    //! Set property value.
    void set( const std::string& _key, const boost::any& _value )
    {
        properties[_key] = _value;
    }

    //! Get Property
    const boost::any& get( const std::string& _key ) const
    {
        return properties.at( _key );
    }

    //! Templated Get Property
    /*!
        A default value can be provided if the property doesn't exist or
        cannot be converted.
    */
    template <class T>
    const T get( const std::string& _key, const T& _def = T() ) const
    {
        boost::any anyres = get( _key );
        try
        {
            return boost::any_cast<T>( anyres );
        }
        catch( boost::bad_any_cast )
        {
            return _def;
        }
    }

    //! Element Access
    boost::any& operator[]( const std::string& _key )
    {
        return properties[_key];
    }

    //! Dump Values
    const void dump() const
    {
        BOOST_FOREACH( const property_map::value_type& value, properties )
        {
            std::cout<<value.first<<": "<<PrintAny()( value.second )<<std::endl;
        }
    }

    typedef boost::unordered_map< std::string, boost::any, StringHash::hash_function, StringHash::equal_to> property_map;
    property_map& getPropertyMap(){ return properties; }

private:
    
    property_map properties;
};

}

#endif