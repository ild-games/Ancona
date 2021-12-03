// Altered SFML Vector3.hpp for Ancona's namespace

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef Ancona_Util_Vector3_H_
#define Ancona_Util_Vector3_H_

namespace ild
{
////////////////////////////////////////////////////////////
/// \brief Utility template class for manipulating
///        3-dimensional vectors
///
////////////////////////////////////////////////////////////
template <typename T> class Vector3
{
  public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates a Vector3(0, 0, 0).
    ///
    ////////////////////////////////////////////////////////////
    Vector3();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from its coordinates
    ///
    /// \param X X coordinate
    /// \param Y Y coordinate
    /// \param Z Z coordinate
    ///
    ////////////////////////////////////////////////////////////
    Vector3(T X, T Y, T Z);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another type of vector
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param vector Vector to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U> explicit Vector3(const Vector3<U> &vector);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T x; ///< X coordinate of the vector
    T y; ///< Y coordinate of the vector
    T z; ///< Z coordinate of the vector
};

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of unary operator -
///
/// \param left Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator-(const Vector3<T> &left);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> &operator+=(Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> &operator-=(Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator+(const Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator-(const Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \a right
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator*(const Vector3<T> &left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \a left
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator*(T left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> &operator*=(Vector3<T> &left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \a right
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> operator/(const Vector3<T> &left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T> Vector3<T> &operator/=(Vector3<T> &left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T> bool operator==(const Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T> bool operator!=(const Vector3<T> &left, const Vector3<T> &right);

#include <Ancona/Util/Vector3.inl>

// Define the most common types
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;

} // namespace ild

#endif // Ancona_Util_Vector3_H_
