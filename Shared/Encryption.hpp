/*
   Warrior of Dreamworld, 2D Massively Mutiplayer Online Role-playing Game
   Copyright (C) 2012-2013 Ryan Lahfa (OzVessalius)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <cryptopp/rsa.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

class EncryptorRSA
{
    public:
        EncryptorRSA();
        EncryptorRSA(RSA::PublicKey& publicKey, RSA::PrivateKey& privateKey);

        RSA::PublicKey GetPublicKey() const { return publicKey; }
        RSA::PrivateKey GetPrivateKey() const { return privateKey; }

    private:
        RSA::PrivateKey privateKey;
        RSA::PublicKey publicKey;
};

std::string HashSHA512AndEncodeHex(std::string const& Message);
std::string HashSHA512(std::string const& Message);
