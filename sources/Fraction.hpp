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

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>

namespace ariel
{
    class Fraction
    {
        private:
            /*
             * @brief The numerator of the fraction.
             * @note The numerator is the top number of the fraction.
            */
            int _numerator;
            
            /*
             * @brief The denominator of the fraction.
             * @note The denominator is the bottom number of the fraction.
             * @note The denominator can't be 0.
            */
            int _denominator;

            /*
             * @brief Reduces the fraction to its simplest form.
             * @note This function is private because it is only used internally.
            */
            void __reduce() {
                int gcd = __gcd(abs(_numerator), abs(_denominator));
                _numerator /= gcd;
                _denominator /= gcd;
            }

            /*
             * @brief Reduces the fraction to its simplest form.
             * @param numerator The numerator of the fraction.
             * @param denominator The denominator of the fraction.
             * @note This function is private because it is only used internally.
             * @note This function is static because it is only used internally and doesn't require an instance of the class.
            */
            static void __reduce(int& numerator, int& denominator) {
                int gcd = __gcd(abs(numerator), abs(denominator));
                numerator /= gcd;
                denominator /= gcd;
            }

            /*
             * @brief Calculates the greatest common divisor of two numbers.
             * @param a The first number.
             * @param b The second number.
             * @return int The greatest common divisor of the two numbers.
             * @note This function is used to reduce the fraction to its simplest form.
             * @note This function is static because it is only used internally and doesn't require an instance of the class.
            */
            static int __gcd(int a, int b) {
                return (b == 0) ? a:__gcd(b, a % b);
            }

        public:
            /*********************/
            /* Constructors zone */
            /*********************/

            /*
             * @brief Default constructor of the Fraction class.
             * @note The default fraction is 0/1 (zero).
            */
            Fraction();

            /*
             * @brief Convert constructor from float to Fraction.
             * @param number The number to convert to a fraction.
             * @note This constructor is used to convert a float to a fraction.
            */
            Fraction(float number);

            /*
             * @brief Construct a new Fraction object
             * @param numerator The numerator of the fraction.
             * @param denominator The denominator of the fraction.
             * @throw invalid_argument if the denominator is 0.
             * @note The fraction will be reduced to its simplest form.
            */
            Fraction(int numerator, int denominator);

            /*
             * @brief Copy constructor of the Fraction class.
             * @param other The fraction to copy.
            */
            Fraction(const Fraction& other);

            /*
             * @brief Move constructor of the Fraction class.
             * @param other The fraction to move.
             * @note This constructor is used to move the fraction to another fraction.
            */
            Fraction(Fraction&& other) noexcept;

            /*
             * @brief A destructor of the Fraction class.
             * @note This destructor is default because it doesn't do anything.
            */
            ~Fraction() = default;


            /**************************************************/
            /* Operators overload zone - Assignment operators */
            /**************************************************/

            /*
             * @brief Assigns a fraction to another fraction.
             * @param other The fraction to assign.
             * @return Fraction& The assigned fraction.
            */
            Fraction& operator=(const Fraction& other);

            /*
             * @brief Assigns a fraction to another fraction.
             * @param other The fraction to assign.
             * @return Fraction& The assigned fraction.
             * @note This function is used to move the fraction to another fraction.
            */
            Fraction& operator=(Fraction&& other) noexcept;


            /**********************************************/
            /* Operators overload zone - Stream operators */
            /**********************************************/

            /*
             * @brief Prints the fraction to the output stream.
             * @param os The output stream.
             * @param fraction The fraction to print.
             * @return The output stream.
            */
            friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);

            /*
             * @brief Reads the fraction from the input stream.
             * @param is The input stream.
             * @param fraction The fraction to read.
             * @return The input stream.
            */
            friend std::istream& operator>>(std::istream& is, Fraction& fraction);


            /**************************************************/
            /* Operators overload zone - Arithmetic operators */
            /**************************************************/

            /*
             * @brief Adds two fractions.
             * @param other The fraction to add.
             * @return The result of the addition.
            */
            const Fraction operator+(const Fraction& other) const;

            /*
             * @brief Adds a fraction to a float.
             * @param num The float to add.
             * @return  The result of the addition.
            */
            const Fraction operator+(const float& num) const;

            /*
             * @brief Adds a fraction to a float.
             * @param num The float to add.
             * @param other The fraction to add.
             * @return The result of the addition.
            */
            friend const Fraction operator+(const float& num, const Fraction& other);

            /*
             * @brief Subtracts two fractions.
             * @param other The fraction to subtract.
             * @return The result of the subtraction.
            */
            const Fraction operator-(const Fraction& other) const;

            /*
             * @brief Subtracts a fraction from a float.
             * @param num The float to subtract.
             * @return The result of the subtraction.
            */
            const Fraction operator-(const float& num) const;

            /*
             * @brief Subtracts a fraction from a float.
             * @param num The float to subtract.
             * @param other The fraction to subtract.
             * @return The result of the subtraction.
            */
            friend const Fraction operator-(const float& num, const Fraction& other);

            /*
             * @brief Multiplies two fractions.
             * @param other The fraction to multiply.
             * @return The result of the multiplication.
            */
            const Fraction operator*(const Fraction& other) const;

            /*
             * @brief Multiplies a fraction by a float.
             * @param num The float to multiply.
             * @return The result of the multiplication.
            */
            const Fraction operator*(const float& num) const;

            /*
             * @brief Multiplies a fraction by a float.
             * @param num The float to multiply.
             * @param other The fraction to multiply.
             * @return The result of the multiplication.
            */
            friend const Fraction operator*(const float& num, const Fraction& other);

            /*
             * @brief Divides two fractions.
             * @param other The fraction to divide.
             * @return The result of the division.
            */
            const Fraction operator/(const Fraction& other) const;

            /*
             * @brief Divides a fraction by a float.
             * @param num The float to divide.
             * @return The result of the division.
            */
            const Fraction operator/(const float& num) const;

            /*
             * @brief Divides a fraction by a float.
             * @param num The float to divide.
             * @param other The fraction to divide.
             * @return The result of the division.
            */
            friend const Fraction operator/(const float& num, const Fraction& other);

            /*
             * @brief Returns the fraction.
             * @return The fraction.
            */
            const Fraction operator+() const;

            /*
             * @brief Negates the fraction.
             * @return The negated fraction.
            */
            const Fraction operator-() const;

            
            /**************************************************/
            /* Operators overload zone - Assignment operators */
            /**************************************************/

            /*
             * @brief Adds a fraction to the current fraction.
             * @param fraction The current fraction.
             * @param other The fraction to add.
             * @return The current fraction.
            */
            friend Fraction& operator+=(Fraction& fraction, const Fraction& other);

            /*
             * @brief Adds a float to the current fraction.
             * @param fraction The current fraction.
             * @param num The float to add.
             * @return The current fraction.
            */
            friend Fraction& operator+=(Fraction& fraction, const float& num);

            /*
             * @brief Subtracts a fraction from the current fraction.
             * @param fraction The current fraction.
             * @param other The fraction to subtract.
             * @return The current fraction.
            */
            friend Fraction& operator-=(Fraction& fraction, const Fraction& other);

            /* 
             * @brief Adds a float to the current fraction.
             * @param fraction The current fraction.
             * @param num The float to add.
             * @return The current fraction.
            */
            friend Fraction& operator-=(Fraction& fraction, const float& num);

            /*
             * @brief Multiplies the current fraction by a fraction.
             * @param fraction The current fraction.
             * @param other The fraction to multiply.
             * @return The current fraction.
            */
            friend Fraction& operator*=(Fraction& fraction, const Fraction& other);

            /*
             * @brief Multiplies the current fraction by a float.
             * @param fraction The current fraction.
             * @param num The float to multiply.
             * @return The current fraction.
            */
            friend Fraction& operator*=(Fraction& fraction, const float& num);

            /*
             * @brief Divides the current fraction by a fraction.
             * @param fraction The current fraction.
             * @param other The fraction to divide.
             * @return The current fraction.
            */
            friend Fraction& operator/=(Fraction& fraction, const Fraction& other);

            /*
             * @brief Divides the current fraction by a float.
             * @param fraction The current fraction.
             * @param num The float to divide.
             * @return The current fraction.
            */
            friend Fraction& operator/=(Fraction& fraction, const float& num);

            /*
             * @brief Increments the current fraction by 1 (pre-increment).
             * @return The current fraction.
            */
            Fraction& operator++();

            /*
             * @brief Decrements the current fraction by 1 (pre-decrement).
             * @return The current fraction.
            */
            Fraction& operator--();

            /*
             * @brief Increments the current fraction by 1 (post-increment).
             * @return The current fraction.
            */
            Fraction operator++(int);

            /*
             * @brief Decrements the current fraction by 1 (post-decrement).
             * @return The current fraction.
            */
            Fraction operator--(int);


            /**************************************************/
            /* Operators overload zone - Compersion operators */
            /**************************************************/

            /*
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the fractions are equal, false otherwise.
            */
            bool operator==(const Fraction& other) const;

            /*
             * @brief Compares a fraction and an float.
             * @param other The float to compare.
             * @return True if the fractions are equal, false otherwise.
            */
            bool operator==(const float& other) const;

            /*
             * @brief Compares a fraction and an float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the fractions are equal, false otherwise.
            */
            friend bool operator==(const float& num, const Fraction& other);

            /*
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the fractions are not equal, false otherwise.
            */
            bool operator!=(const Fraction& other) const;

            /*
             * @brief Compares a fraction and an float.
             * @param other The float to compare.
             * @return True if the fractions are not equal, false otherwise.
            */
            bool operator!=(const float& other) const;

            /*
             * @brief Compares a fraction and an float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the fractions are not equal, false otherwise.
            */
            friend bool operator!=(const float& num, const Fraction& other);

            /*
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the current fraction is greater than the other fraction, false otherwise.
            */
            bool operator>(const Fraction& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @return True if the current fraction is greater than the float, false otherwise.
            */
            bool operator>(const float& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the current fraction is greater than the float, false otherwise.
            */
            friend bool operator>(const float& num, const Fraction& other);

            /* 
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the current fraction is less than the other fraction, false otherwise.
            */
            bool operator<(const Fraction& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @return True if the current fraction is less than the float, false otherwise.
            */
            bool operator<(const float& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the current fraction is less than the float, false otherwise.
            */
            friend bool operator<(const float& num, const Fraction& other);

            /*
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the current fraction is greater than or equal to the other fraction, false otherwise.
            */
            bool operator>=(const Fraction& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @return True if the current fraction is greater than or equal to the float, false otherwise.
            */
            bool operator>=(const float& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the current fraction is greater than or equal to the float, false otherwise.
            */
            friend bool operator>=(const float& num, const Fraction& other);

            /*
             * @brief Compares two fractions.
             * @param other The fraction to compare.
             * @return True if the current fraction is less than or equal to the other fraction, false otherwise.
            */
            bool operator<=(const Fraction& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @return True if the current fraction is less than or equal to the float, false otherwise.
            */
            bool operator<=(const float& other) const;

            /*
             * @brief Compares a fraction and a float.
             * @param other The float to compare.
             * @param num The fraction to compare.
             * @return True if the current fraction is less than or equal to the float, false otherwise.
            */
            friend bool operator<=(const float& num, const Fraction& other);
    };

}