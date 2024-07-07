#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "funkcje.h"
#include <vector>


void encrypt(const std::string& input, const std::string& output, const std::string& key)
{

	const int LITERKAA{ 'A' }, LITERKAZ{ 'Z' }, TABSIZE{ 26 };

	int codingchar;
	int nkfs = 0;

	std::fstream infile, outfile, keyfile;
	std::string infileline, keyfilestring;

	infile.open(input, std::ios::in);
	outfile.open(output, std::ios::out);
	keyfile.open(key, std::ios::in);

	if (infile && outfile && keyfile); else error();

	while (keyfile >> keyfilestring);
	if (keyfilestring.length() == 0) error();
	for (int i = 0;i < keyfilestring.length();i++) keyfilestring[i] = toupper(keyfilestring[i]);
	while (std::getline(infile, infileline))
	{
		for (int i = 0; i < infileline.length(); i++)
		{
			infileline[i] = toupper(infileline[i]);

			if (LITERKAA <= keyfilestring[nkfs % keyfilestring.length()] && keyfilestring[nkfs % keyfilestring.length()] <= LITERKAZ)
			{
				codingchar = keyfilestring[nkfs % keyfilestring.length()] - LITERKAA;
			}
			else
			{
				codingchar = 0;
			}

			if (LITERKAA <= infileline[i] && infileline[i] <= LITERKAZ)
			{
				infileline[i] = (infileline[i] - LITERKAA + codingchar) % TABSIZE + LITERKAA;
				nkfs++;
			}
		}
		outfile << infileline << std::endl;

	}

	infile.close();
	outfile.close();
	keyfile.close();

	std::cout << "Wiadomosc zaszyfrowana i umieszczona w pliku wyjsciowym" << std::endl;

	return;
}

void decrypt(const std::string& input, const std::string& output, const std::string& key, const int& zerolubniezero)
{
	int nkfs = 0;
	int codingchar;

	const int LITERKAA{ 'A' }, LITERKAZ{ 'Z' };
	const int TABSIZE{ 26 };

	std::fstream infile, outfile, keyfile;
	std::string infileline, keyfilestring;

	infile.open(input, std::ios::in);
	outfile.open(output, std::ios::out);
	keyfile.open(key, std::ios::in);

	if (infile && outfile && (keyfile || zerolubniezero));
	else error();
	
	


	if (zerolubniezero) keyfilestring = key;
	else
	{
		while (keyfile >> keyfilestring);
	}

	if (keyfilestring.length() == 0) error();

	for (int i = 0;i < keyfilestring.length();i++) keyfilestring[i] = toupper(keyfilestring[i]);

	while (std::getline(infile, infileline))
	{
		for (int i = 0; i < infileline.length(); i++)
		{
			infileline[i] = toupper(infileline[i]);

			if (LITERKAA <= keyfilestring[nkfs % keyfilestring.length()] && keyfilestring[nkfs % keyfilestring.length()] <= LITERKAZ)
			{
				codingchar = keyfilestring[nkfs % keyfilestring.length()] - LITERKAA;
			}
			else
			{
				codingchar = 0;
			}

			if (LITERKAA <= infileline[i] && infileline[i] <= LITERKAZ)
			{
				infileline[i] = (infileline[i] - LITERKAZ - codingchar) % TABSIZE + LITERKAZ;
				nkfs++;
			}
		}
		outfile << infileline << std::endl;
	}
	infile.close();
	outfile.close();
	keyfile.close();

	std::cout << "Wiasomosc odszyfrowana i umieszczona w pliku wyjsciowym" << std::endl;

	return;
}

void br(const std::string& encrypted, const std::string& decrypted)
{
	char literka;
	std::fstream strumzaszyfrowany, strumodszyfrowany;
	std::string klucz, liniatekstu, tekst;
	std::stringstream literki, bufor;
	std::vector<std::pair<int, double>> sredniakoincydenja, alfabetzgodnosci;

	double koincydencjapodciagu{ 0 }, srednia, min = std::numeric_limits<double>::max();
	unsigned int Podejrzewanadlklucza{ 0 }, liczbadosredniej{ 0 }, literkaliczbowo, illiter, MAXSPRAWDZANADLKLUCZA{ 20 };

	const int TABSIZE{ 26 }, JEDENINT{ 1 }, LITERKAA{ 'A' }, LITERKAZ{'Z'};
	const double INDEKSZGODNOSCIDLAJANG{ 0.067 };
	const double JEDENDOUBLE{ 1 };

	const std::map<char, double> MAPAZGODNOSCI = {
	{'A', 0.082}, {'B', 0.015}, {'C', 0.028}, {'D', 0.043}, {'E', 0.127}, {'F', 0.022}, {'G', 0.020}, {'H', 0.061}, {'I', 0.070},
	{'J', 0.002}, {'K', 0.008}, {'L', 0.040}, {'M', 0.024}, {'N', 0.067}, {'O', 0.075}, {'P', 0.019}, {'Q', 0.001}, {'R', 0.060}, {'S', 0.063}, {'T', 0.091}, {'U', 0.028}, {'V', 0.010}, {'W', 0.023}, {'X', 0.001}, {'Y', 0.020},{'Z', 0.001} };
	std::map<char, unsigned int> mapadlklucza;



	strumzaszyfrowany.open(encrypted, std::ios::in);

	if (!strumzaszyfrowany) error();

	while (std::getline(strumzaszyfrowany, liniatekstu)) for (int i = 0; i < liniatekstu.length(); i++)
	{
		literka = toupper(liniatekstu[i]);
		if (LITERKAA<=literka && literka<=LITERKAZ)
		{
			bufor << liniatekstu[i];
		}
	}

	bufor >> tekst;
	strumzaszyfrowany.close();
	if (tekst.length() < 20)
	{
		MAXSPRAWDZANADLKLUCZA = tekst.length();
	}

	for (int i = 1; i <= MAXSPRAWDZANADLKLUCZA; i++)
	{
		liczbadosredniej = 0;
		srednia = 0;

		for (int k = 0; k < i; k++)
		{
			koincydencjapodciagu = 0;
			mapadlklucza.clear();

			for (int j = k; j < tekst.length(); j = j + i)
			{
				mapadlklucza[tekst[j]]++;
			}

			illiter = (tekst.length() - k) / i;

			for (const auto& l : mapadlklucza)
			{
				koincydencjapodciagu = koincydencjapodciagu + (JEDENDOUBLE * l.second / illiter) * (JEDENDOUBLE * l.second / illiter);
			}

			srednia = srednia + koincydencjapodciagu;
			liczbadosredniej++;
		}

		srednia = srednia / liczbadosredniej;
		sredniakoincydenja.push_back({ i,srednia });
	}

	for (const auto& i : sredniakoincydenja)
	{
		if (abs(i.second - INDEKSZGODNOSCIDLAJANG) < min)
		{
			min = abs(i.second - INDEKSZGODNOSCIDLAJANG);
			Podejrzewanadlklucza = i.first;
		}
	}

	//	std::cout << "dl klucza jest rowna: " << Podejrzewanadlklucza << std::endl;


	sredniakoincydenja.clear();
	mapadlklucza.clear();

	for (int i = 0; i < Podejrzewanadlklucza; i++)
	{
		alfabetzgodnosci.clear();
		mapadlklucza.clear();
		min = std::numeric_limits<double>::max();

		for (int j = i; j < tekst.length(); j = j + Podejrzewanadlklucza) mapadlklucza[tekst[j]]++;

		illiter = (tekst.length() - i) / Podejrzewanadlklucza;

		for (int k = 0; k < TABSIZE; k++)
		{
			koincydencjapodciagu = 0;

			for (const auto& l : MAPAZGODNOSCI)
			{
				koincydencjapodciagu = koincydencjapodciagu + l.second * JEDENDOUBLE * mapadlklucza[(l.first - LITERKAA + k) % TABSIZE + LITERKAA] / illiter;
			}
			alfabetzgodnosci.push_back({ k,koincydencjapodciagu });
		}
		for (const auto& m : alfabetzgodnosci)
		{
			if ((abs(m.second - INDEKSZGODNOSCIDLAJANG) < min))
			{
				min = abs(m.second - INDEKSZGODNOSCIDLAJANG);
				literkaliczbowo = m.first;
			}
		}
		//			std::cout << char((literkaliczbowo % TABSIZE) + LITERKAA);
		literki << char((literkaliczbowo % TABSIZE) + LITERKAA);
	}

	literki >> klucz;

	std::cout << "Zlamano szyfr." << std::endl;
	std::cout << "Prawdopodobny klucz: " << klucz << std::endl;

	decrypt(encrypted, decrypted, klucz, JEDENINT);

	return;
}

void error()
{
	std::cout << std::endl <<"Cos poszlo nie tak uzyj -help, aby dowiedziec sie wiecej" << std::endl;
	exit(0);
}

void help()
{
	std::cout << std::endl;
	std::cout << "Program napisany do kodowania i dekodowania plikow metoda Vigenere." << std::endl;
	std::cout << "Program nalezy odpalic przez konsole z uzyciem przelacznikow." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "FLAGI: " << std::endl;
	std::cout << "Uzycie tego przelacznika zmienia zastosowanie programu" << std::endl;
	std::cout << "[--en|encrypt]- Odpowiada za szyfrowanie " << std::endl;
	std::cout << "[--de|decrypt]- Odpowiada za deszyfrowanie" << std::endl;
	std::cout << "[--br|break]- Odpowiada za lamanie szyfru" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "POZOSTALE:" << std::endl;
	std::cout << "Odpowiadaja za przekazanie nazwy plikow potrzebnych do dzialania programu" << std::endl;
	std::cout << "[-i|input]- Plik wejsciowy" << std::endl;
	std::cout << "[-o|output]- Plik wyjsciowy" << std::endl;
	std::cout << "[-k|key]- Plik z kluczem szyfrowania" << std::endl;
	std::cout << std::endl;
	std::cout << "PRZYKLADOWE UZYCIE:" << std::endl;
	std::cout << "...\\Vig.exe --en -i input.txt -o output.txt -k key.txt  | Kolejno: flaga szyfrowania, plik wejsciowy jawny, plik wyjsciowy zaszyfrowany, klucz szyfrowania " << std::endl;
	std::cout << "...\\Vig.exe --de -i input.txt -o output.txt -k key.txt	 | Kolejno: flaga deszyfrowania, plik wejsciowy zaszyfrowany, plik wyjsciowy jawny, klucz deszyfrowania" << std::endl;
	std::cout << "...\\Vig.exe --br -i input.txt -o output.txt             | Kolejno: flaga lamania szyfru, plik wejsciowy zaszyfrowany, plik wyjsciowy jawny" << std::endl;
	exit(0);
}

void wyluskanie(int argc, char* argv[])
{
	std::map<std::string, std::string> liczbaarg;
	if (argc == 2)
	{
		std::string argvkopia = argv[1];
		if (argvkopia == "-help") help();
		else error();
	}

	for (int i = 1; i < argc - 1; i++)
	{
		liczbaarg.try_emplace(argv[i], argv[i + 1]);
	}
	liczbaarg.try_emplace(argv[argc - 1], argv[argc - 1]);

	//Sprawdzanie spojnosci 

	if (liczbaarg.size() != --argc) error();

	if (liczbaarg.count("-i") && liczbaarg.count("-o") && (liczbaarg.count("--en") || liczbaarg.count("--de")) && liczbaarg.count("-k") && liczbaarg.size() == 7)
	{
		const int ZERO{ 0 };
		std::string input, output, key;
		input = liczbaarg["-i"];
		output = liczbaarg["-o"];
		key = liczbaarg["-k"];

		if (liczbaarg.count("--en")) encrypt(input, output, key); else decrypt(input, output, key, ZERO);

	}
	else if (liczbaarg.count("-i") && liczbaarg.count("-o") && liczbaarg.count("--br") && liczbaarg.size() == 5)
	{
		std::string input, output;
		input = liczbaarg["-i"];
		output = liczbaarg["-o"];

		br(input, output);

	}
	else error();
	return;
}