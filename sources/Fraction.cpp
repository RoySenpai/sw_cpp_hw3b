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

using namespace std;

namespace ariel
{
    Fraction::Fraction(): _numerator(0), _denominator(1) {}

    Fraction::Fraction(float number) {
        int power = 1;
        while (number != (int)number && power < 1000)
        {
            number *= 10;
            power *= 10;
        }

        _numerator = number;
        _denominator = power;

        __reduce();
    }

    Fraction::Fraction(int numerator, int denominator): _numerator(numerator), _denominator(denominator) {
        if (denominator == 0)
            throw std::invalid_argument("Denominator can't be zero");

        if (denominator < 0)
        {
            _numerator *= -1;
            _denominator *= -1;
        }

        __reduce();
    }

    Fraction::Fraction(const Fraction& other): _numerator(other._numerator), _denominator(other._denominator) {}

    Fraction::Fraction(Fraction&& other) noexcept: _numerator(other._numerator), _denominator(other._denominator) {}

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

    ostream& operator<<(ostream& os, const Fraction& fraction) {
        os << fraction._numerator << "/" << fraction._denominator;
        return os;
    }

    istream& operator>>(istream& is, Fraction& fraction) {
        int numerator, denominator;
        char slash;

        is >> numerator >> slash >> denominator;

        if (slash != '/')
            throw invalid_argument("Invalid input");

        fraction = Fraction(numerator, denominator);

        return is;
    }


    // Operators with fractions

    const Fraction Fraction::operator+(const Fraction& other) const {
        int numerator = (_numerator * other._denominator) + (other._numerator * _denominator);
        int denominator = (_denominator * other._denominator);

        __reduce(numerator, denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator-(const Fraction& other) const {
        int numerator = (_numerator * other._denominator) - (other._numerator * _denominator);
        int denominator = (_denominator * other._denominator);

        __reduce(numerator, denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator*(const Fraction& other) const {
        int numerator = (_numerator * other._numerator);
        int denominator = (_denominator * other._denominator);

        __reduce(numerator, denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator/(const Fraction& other) const {
        if (other._numerator == 0)
            throw invalid_argument("Can't divide by zero");

        int numerator = (_numerator * other._denominator);
        int denominator = (_denominator * other._numerator);

        __reduce(numerator, denominator);

        return Fraction(numerator, denominator);
    }

    const Fraction Fraction::operator+() const {
        return Fraction(_numerator, _denominator);
    }

    const Fraction Fraction::operator-() const {
        return Fraction(-_numerator, _denominator);
    }

    Fraction& operator+=(Fraction& fraction, const Fraction& other) {
        fraction._numerator = (fraction._numerator * other._denominator) + (other._numerator * fraction._denominator);
        fraction._denominator *= other._denominator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& operator-=(Fraction& fraction, const Fraction& other) {
        fraction._numerator = (fraction._numerator * other._denominator) - (other._numerator * fraction._denominator);
        fraction._denominator *= other._denominator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& operator*=(Fraction& fraction, const Fraction& other) {
        fraction._numerator *= other._numerator;
        fraction._denominator *= other._denominator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& operator/=(Fraction& fraction, const Fraction& other) {
        if (other._numerator == 0)
            throw invalid_argument("Can't divide by zero");

        fraction._numerator *= other._denominator;
        fraction._denominator *= other._numerator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& Fraction::operator++() {
        _numerator += _denominator;

        __reduce();

        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& Fraction::operator--() {
        _numerator -= _denominator;

        __reduce();

        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    bool Fraction::operator==(const Fraction& other) const {
        return (_numerator == other._numerator && _denominator == other._denominator);
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

    const Fraction Fraction::operator+(const float& number) const {
        return *this + Fraction(number);
    }
    
    const Fraction operator+(const float& num, const Fraction& other) {
        return Fraction(num) + other;
    }

    const Fraction Fraction::operator-(const float& number) const {
        return *this - Fraction(number);
    }

    const Fraction operator-(const float& num, const Fraction& other) {
        return Fraction(num) - other;
    }

    const Fraction Fraction::operator*(const float& number) const {
        return *this * Fraction(number);
    }

    const Fraction operator*(const float& num, const Fraction& other) {
        return Fraction(num) * other;
    }

    const Fraction Fraction::operator/(const float& number) const {
        if (number == 0)
            throw invalid_argument("Can't divide by zero");

        return *this / Fraction(number);
    }

    const Fraction operator/(const float& num, const Fraction& other) {
        if (other._numerator == 0)
            throw invalid_argument("Can't divide by zero");

        return Fraction(num) / other;
    }

    Fraction& operator+=(Fraction& fraction, const float& number) {
        Fraction temp = fraction + Fraction(number);
        
        fraction._numerator = temp._numerator;
        fraction._denominator = temp._denominator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& operator-=(Fraction& fraction, const float& number) {
        Fraction temp = fraction - Fraction(number);
        
        fraction._numerator = temp._numerator;
        fraction._denominator = temp._denominator;

        fraction.__reduce();

        return fraction;
    }

    Fraction& operator*=(Fraction& fraction, const float& number) {
        Fraction temp = fraction * Fraction(number);
        
        fraction._numerator = temp._numerator;
        fraction._denominator = temp._denominator;

        fraction.__reduce();
        
        return fraction;
    }

    Fraction& operator/=(Fraction& fraction, const float& number) {
        if (number == 0)
            throw invalid_argument("Can't divide by zero");
            
        Fraction temp = fraction / Fraction(number);
        
        fraction._numerator = temp._numerator;
        fraction._denominator = temp._denominator;

        fraction.__reduce();
        
        return fraction;
    }

    bool Fraction::operator==(const float& number) const {
        return *this == Fraction(number);
    }

    bool operator==(const float& num, const Fraction& other) {
        return Fraction(num) == other;
    }

    bool Fraction::operator!=(const float& number) const {
        return !(*this == Fraction(number));
    }

    bool operator!=(const float& num, const Fraction& other) {
        return !(Fraction(num) == other);
    }

    bool Fraction::operator<(const float& number) const {
        return *this < Fraction(number);
    }

    bool operator<(const float& num, const Fraction& other) {
        return Fraction(num) < other;
    }

    bool Fraction::operator>(const float& number) const {
        return *this > Fraction(number);
    }

    bool operator>(const float& num, const Fraction& other) {
        return Fraction(num) > other;
    }

    bool Fraction::operator<=(const float& number) const {
        return !(*this > Fraction(number));
    }

    bool operator<=(const float& num, const Fraction& other) {
        return !(Fraction(num) > other);
    }

    bool Fraction::operator>=(const float& number) const {
        return !(*this < Fraction(number));
    }

    bool operator>=(const float& num, const Fraction& other) {
        return !(Fraction(num) < other);
    }
}