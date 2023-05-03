/*
 *  Software Systems CPP Course Assignment 3
 *  Copyright (C) 2023  Roy Simanovich
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Fraction.hpp"

namespace ariel
{
    Fraction::Fraction(): _numerator(0), _denominator(1) {}

    Fraction::Fraction(float number): _numerator(static_cast<int>(1000 * number)), _denominator(1000) {
        _reduce();
    }

    Fraction::Fraction(int numerator, int denominator): _numerator(numerator), _denominator(denominator) {
        if (denominator == 0)
            throw std::invalid_argument("Denominator can't be zero");

        if (denominator < 0)
        {
            _numerator *= -1;
            _denominator *= -1;
        }

        _reduce();
    }

    Fraction::Fraction(const Fraction& other): _numerator(other._numerator), _denominator(other._denominator) {}

    Fraction::Fraction(Fraction&& other) noexcept: _numerator(other._numerator), _denominator(other._denominator) {}

    int Fraction::getNumerator() const {
        return _numerator;
    }

    int Fraction::getDenominator() const {
        return _denominator;
    }

    Fraction& Fraction::operator=(const Fraction& other) {
        if (this == &other)
            return *this;
        
        this->_numerator = other._numerator;
        this->_denominator = other._denominator;
        return *this;
    }

    Fraction& Fraction::operator=(Fraction&& other) noexcept {
        if (this == &other)
            return *this;

        this->_numerator = other._numerator;
        this->_denominator = other._denominator;
        return *this;
    }


    // Stream operators (IO friend functions)

    std::ostream& operator<<(std::ostream& outstream, const Fraction& fraction) {
        outstream << fraction._numerator << "/" << fraction._denominator;
        return outstream;
    }

    std::istream& operator>>(std::istream& inptstream, Fraction& fraction) {
        int numitor = 0, denitor = 0;

        inptstream >> numitor >> denitor;

        if (inptstream.fail())
            throw std::runtime_error("Invalid input");

        else if (denitor == 0)
            throw std::runtime_error("Denominator can't be zero");

        else if (denitor < 0)
        {
            numitor *= -1;
            denitor *= -1;
        }

        fraction._numerator = numitor;
        fraction._denominator = denitor;
        fraction._reduce();

        return inptstream;
	}


    // Operators with fractions

    const Fraction Fraction::operator+(const Fraction& other) const {
        int a = _overflow_multiplication_check(_numerator, other._denominator);
        int b = _overflow_multiplication_check(other._numerator, _denominator);
        
        int numerator = _overflow_addition_check(a, b);
        int denominator = _overflow_multiplication_check(_denominator, other._denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator-(const Fraction& other) const {
        int a = _overflow_multiplication_check(_numerator, other._denominator);
        int b = _overflow_multiplication_check(other._numerator, _denominator);
        
        int numerator = _overflow_subtraction_check(a, b);
        int denominator = _overflow_multiplication_check(_denominator, other._denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator*(const Fraction& other) const {
        int numerator = _overflow_multiplication_check(_numerator, other._numerator);
        int denominator = _overflow_multiplication_check(_denominator, other._denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator/(const Fraction& other) const {
        if (other._numerator == 0)
            throw std::runtime_error("Can't divide by zero");

        int numerator = _overflow_multiplication_check(_numerator, other._denominator);
        int denominator = _overflow_multiplication_check(_denominator, other._numerator);

        return Fraction(numerator, denominator);
    }

    Fraction& Fraction::operator++() {
        _numerator += _denominator;

        _reduce();

        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& Fraction::operator--() {
        _numerator -= _denominator;

        _reduce();

        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    bool Fraction::operator==(const Fraction& other) const {
        return (_numerator == other._numerator) && (_denominator == other._denominator);
    }

    bool Fraction::operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool Fraction::operator<(const Fraction& other) const {
        return (_numerator * other._denominator) < (other._numerator * _denominator);
    }

    bool Fraction::operator>(const Fraction& other) const {
        return (_numerator * other._denominator) > (other._numerator * _denominator);
    }

    bool Fraction::operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool Fraction::operator>=(const Fraction& other) const {
        return !(*this < other);
    }


    // Operators with floats

    const Fraction Fraction::operator+(const float& other) const {
        return *this + Fraction(other);
    }
    
    const Fraction operator+(const float& num, const Fraction& other) {
        return Fraction(num) + other;
    }

    const Fraction Fraction::operator-(const float& other) const  {
        return *this - Fraction(other);
    }

    const Fraction operator-(const float& num, const Fraction& other) {
        return Fraction(num) - other;
    }

    const Fraction Fraction::operator*(const float& other) const {
        return *this * Fraction(other);
    }

    const Fraction operator*(const float& num, const Fraction& other) {
        return Fraction(num) * other;
    }

    const Fraction Fraction::operator/(const float& other) const  {
        if (other == 0.0)
            throw std::runtime_error("Can't divide by zero");

        return *this / Fraction(other);
    }

    const Fraction operator/(const float& num, const Fraction& other) {
        if (other._numerator == 0)
            throw std::runtime_error("Can't divide by zero");

        return Fraction(num) / other;
    }

    bool Fraction::operator==(const float& other) const {
        return *this == Fraction(other);
    }

    bool operator==(const float& num, const Fraction& other) {
        return Fraction(num) == other;
    }

    bool Fraction::operator!=(const float& other) const {
        return !(*this == Fraction(other));
    }

    bool operator!=(const float& num, const Fraction& other) {
        return !(Fraction(num) == other);
    }

    bool Fraction::operator<(const float& other) const {
        return *this < Fraction(other);
    }

    bool operator<(const float& num, const Fraction& other) {
        return Fraction(num) < other;
    }

    bool Fraction::operator>(const float& other) const {
        return *this > Fraction(other);
    }

    bool operator>(const float& num, const Fraction& other) {
        return Fraction(num) > other;
    }

    bool Fraction::operator<=(const float& other) const {
        return !(*this > Fraction(other));
    }

    bool operator<=(const float& num, const Fraction& other) {
        return !(Fraction(num) > other);
    }

    bool Fraction::operator>=(const float& other) const {
        return !(*this < Fraction(other));
    }

    bool operator>=(const float& num, const Fraction& other) {
        return !(Fraction(num) < other);
    }
}