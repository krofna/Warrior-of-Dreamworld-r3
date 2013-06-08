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

#include "Encryption.hpp"

EncryptorRSA::EncryptorRSA()
{
    // Pseudo number generator
    AutoSeededRandomPool rng;

    // Generate keys
    privateKey.GenerateRandomWithKeySize(rng, 3072);
    RSA::PublicKey c(privateKey);
    publicKey = c;
}

EncryptorRSA::EncryptorRSA(RSA::PublicKey& pub, RSA::PrivateKey& priv) : publicKey(pub), privateKey(priv)
{

}

std::string HashSHA512AndEncodeHex(std::string const& Message)
{
    SHA512 hash;
    std::string digest;
    StringSource source(Message, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));

    return digest;
}

std::string HashSHA512(std::string const& Message)
{
    SHA512 hash;
    std::string digest;

    StringSource source(Message, true, new HashFilter(hash, new StringSink(digest)));

    return digest;
}
