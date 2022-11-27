/**
 * @file property.hpp
 * @author Glotov Ilya (glotovia@student.bmstu.ru)
 * @brief Файл реализации паттерна Property
 * @version 1.0
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

/*!
    @brief Класс, реализующий паттерн Property
*/
template <class T, class C>
class Property {
    C* owner;
    T(C::*getter)
    ();
    void (C::*setter)(T);

public:
    Property()
        : owner()
        , getter()
        , setter()
    {
    }
    Property(C* owner, T (C::*getter)(), void (C::*setter)(T))
        : owner(owner)
        , getter(getter)
        , setter(setter)
    {
    }
    void Set(T value) const
    {
        (owner->*setter)(value);
    }
    T Get() const
    {
        return (owner->*getter)();
    }
    operator T() const
    {
        return Get();
    }
    const Property<T, C>& operator=(T value) const
    {
        Set(value);
        return *this;
    }
};

#endif // PROPERTY_HPP
