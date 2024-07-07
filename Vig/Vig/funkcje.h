/**@file*/
#pragma once

/**
* @brief Funkcja encrypt().
* @details Funkcja odpowiada za szyfrowanie pliku.
* @param input nazwa pliku wejściowego, z jawną wiadomością.
* @param output nazwa pliku wyjściowego, z zaszyfrowaną wiadomością.
* @param key nazwa pliku wejściowego, z kluczem.
* @return funkcja niczego nie zwraca.
*/


void encrypt(const std::string& input, const std::string& output, const std::string& key);

/**
* @brief Funkcja decrypt().
* @details Funkcja odpowiada za deszyfrowanie pliku.
* @param input nazwa pliku wejściowego, z zaszyfrowaną.
* @param output nazwa pliku wyjściowego, z jawną wiadomością.
* @param key nazwa pliku wejściowego, z kluczem.
* @return funkcja niczego nie zwraca.
*/

void decrypt(const std::string& input, const std::string &output, const std::string &key);

/**
* @brief Funkcja br().
* @details Funkcja odpowiada za deszyfrowanie pliku bez znajomości klucza. Działanie funkcji br oparte jest na metodzie statystycznej Friedmana.
* @param encrypted nazwa pliku wejściowego, z zaszyfrowaną wiadomością.
* @param decrypted nazwa pliku wyjściowego, z jawną wiadomością.
* @return funkcja niczego nie zwraca.
*/

void br(const std::string& encrypted, const std::string &decrypted);

/**
* @brief Funkcja help().
* @details Po wywołaniu tej funkcji wyświetlona zostaje instrukcja działania programu, a następnie program zostaje zakończony.
* @return funkcja niczego nie zwraca.
*/

void help();

/**
* @brief Funkcja error().
* @details Funkcja odpowiada za wyświetlenie błędu programu. 
* Wywołanie tej funkcji równoznaczne jest z zakończeniem programu.
* @return Funkcja niczego nie zwraca.
*/

void error();

/**
* @brief Funkcja wyluskanie().
* @details Funkcja wyłuskuje sobie nazwy plików tekstowych i flagę przekazanych przez użytkownika. Funkcja używa mapy do sprawdzenia spójności plików i gdzy wszystko okej przekazuje nazwy plików funkcjom encrypt, decrypt lub br, w zależności od przekazanej flagi.
* @param argc liczba argumentów przekazanych przez konsolę, przez użytkownika.
* @param argv[] argumenty przekazane przez użytkownika.
*/

void wyluskanie(int argc, char* argv[]);