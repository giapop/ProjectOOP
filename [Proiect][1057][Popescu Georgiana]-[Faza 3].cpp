#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<list>
using namespace std;

//Am o podgorie de unde culeg via, am mai multe depozite in diferite orase
//Duc strugurii culesi la depozit, la podgorie ii sortez si duc anumite cant din fiecare soi la depozit

//gestiunea unei podgorii

class IFile
{
	virtual void writeToFile(fstream& file) = 0;//metoda virtuala pura
	virtual void readFromFile(fstream& file) = 0;
};


class Podgorie :public IFile
{
private:
	string numePodgorie;
	char* numeProprietar;
	int nrRanduri;
	const int anInfiintare;
	int nrsoiuri;
	float Suprafata[20];  //pe cat se intinde fiecare soi
public:
	Podgorie() :numeProprietar(NULL), nrRanduri(0), anInfiintare(0), nrsoiuri(0), numePodgorie("NA")
	{

	}

	Podgorie(string numePodgorie, char* numeProprietar, int nrRanduri, const int anInfiintare, int nrsoiuri, float Suprafata[20]) :anInfiintare(anInfiintare)
	{
		this->numePodgorie = numePodgorie;
		if (numeProprietar != NULL)
		{
			this->numeProprietar = new char[strlen(numeProprietar) + 1];
			strcpy(this->numeProprietar, numeProprietar);
		}
		else
			this->numeProprietar = NULL;
		this->nrRanduri = nrRanduri;

		this->nrsoiuri = nrsoiuri;

		if (nrsoiuri > 0)
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = Suprafata[i];
		else
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = 0;



	}

	Podgorie(char* numeProprietar, const int anInfiintare) :anInfiintare(anInfiintare)
	{
		this->numePodgorie = "NA";
		if (numeProprietar != NULL)
		{
			this->numeProprietar = new char[strlen(numeProprietar) + 1];
			strcpy(this->numeProprietar, numeProprietar);
		}
		else
			this->numeProprietar = NULL;
		this->nrRanduri = 0;
		this->nrsoiuri = 0;

	}
	Podgorie(const Podgorie& p) :nrRanduri(p.nrRanduri), anInfiintare(p.anInfiintare)
	{
		this->numePodgorie = p.numePodgorie;
		if (p.numeProprietar != NULL)
		{
			this->numeProprietar = new char[strlen(p.numeProprietar) + 1];
			strcpy(this->numeProprietar, p.numeProprietar);
		}
		else
			this->numeProprietar = NULL;
		this->nrsoiuri = p.nrsoiuri;
		for (int i = 0; i < this->nrsoiuri; i++)
			this->Suprafata[i] = p.Suprafata[i];
	}

	Podgorie& operator=(const Podgorie& p)
	{
		this->numePodgorie = p.numePodgorie;
		if (p.numeProprietar != NULL)
		{
			this->numeProprietar = new char[strlen(p.numeProprietar) + 1];
			strcpy(this->numeProprietar, p.numeProprietar);
		}
		else
			this->numeProprietar = NULL;
		this->nrRanduri = p.nrRanduri;
		this->nrsoiuri = p.nrsoiuri;
		for (int i = 0; i < this->nrsoiuri; i++)
			this->Suprafata[i] = p.Suprafata[i];
		return*this;
	}

	void writeToFile(fstream& file)
	{
		int lg = this->numePodgorie.length() + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->numePodgorie.data(), lg);
		char buffer[100];
		strcpy(buffer, this->numeProprietar);
		file.write(buffer, sizeof(buffer));
		//scriere valoare int
		file.write((char*)&this->nrRanduri, sizeof(int));
		file.write((char*)&this->anInfiintare, sizeof(int));
		file.write((char*)&this->nrsoiuri, sizeof(int));
		file.write((char*)this->Suprafata, sizeof(float) * this->nrsoiuri);

	}

	void readFromFile(fstream& file)
	{
		int lg = 0;
		file.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		file.read(buffer, lg);
		this->numePodgorie = buffer;
		delete[] buffer;

		char buffernume[100];
		file.read(buffernume, sizeof(buffernume));
		if (this->numeProprietar != NULL)
			delete[]this->numeProprietar;
		this->numeProprietar = new char[strlen(buffernume) + 1];
		strcpy(this->numeProprietar, buffernume);

		file.read((char*)&this->nrRanduri, sizeof(int));
		file.read((char*)&this->anInfiintare, sizeof(int));
		file.read((char*)&this->nrsoiuri, sizeof(int));
		file.read((char*)this->Suprafata, sizeof(float) * this->nrsoiuri);


	}



	bool operator==(const Podgorie& p)
	{
		if (this->nrRanduri == p.nrRanduri)
			return true;
		return false;
	}

	Podgorie operator--()
	{
		if (nrsoiuri > 3)
		{
			this->nrsoiuri = nrsoiuri - 1;
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = Suprafata[i];
		}
		else
			throw exception("Nu se scot soiuri");
		return *this;
	}
	Podgorie operator--(int)
	{
		Podgorie rez = *this;
		if (nrsoiuri > 3)
		{
			this->nrsoiuri = nrsoiuri - 1;
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = Suprafata[i];
		}
		else
			throw exception("Nu se scot soiuri");
		return rez;
	}
	Podgorie operator+(int x)
	{
		Podgorie rez = *this;
		rez.nrRanduri = rez.nrRanduri + x;
		return rez;
	}

	bool operator<(const Podgorie& p)
	{
		if (this->anInfiintare < p.anInfiintare)
			return true;
		return false;
	}
	operator const int()
	{
		return this->anInfiintare;
	}

	float& operator[](int index)
	{
		if (index >= 0 && index < this->nrsoiuri)
			return this->Suprafata[index];
		else
			throw exception("\nindex gresit");

	}


	Podgorie operator!()
	{
		Podgorie rez = *this;
		rez.nrRanduri = 0;
		rez.nrsoiuri = 0;
		for (int i = 0; i < rez.nrsoiuri; i++)
			rez.Suprafata[i] = 0;
		return rez;
	}


	~Podgorie()
	{
		if (this->numeProprietar != NULL)
			delete[]this->numeProprietar;
	}



	void plantatie()
	{
		cout << endl;
		if (this->nrRanduri > 20000)
			cout << "\nExista o plantatie considerabila";
		else
			cout << "\nNu este ";
	}
	float suprmax()
	{
		int max1 = this->Suprafata[0];
		for (int i = 0; i < this->nrsoiuri; i++)
			if (max1 < this->Suprafata[i])
				max1 = this->Suprafata[i];
		return max1;

	}


	void setSupr(int nrsoiuri, float Suprafata[20])
	{
		this->nrsoiuri = nrsoiuri;
		if (nrsoiuri > 0)
		{
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = Suprafata[i];
		}
		else
		{
			for (int i = 0; i < this->nrsoiuri; i++)
				this->Suprafata[i] = 0;
		}

	}

	int getnrsoi()
	{
		return this->nrsoiuri;
	}
	float getSupr(int i)
	{
		return this->Suprafata[i];
	}

	void setNume(const char* nume)
	{

		if (strlen(nume) >= 3)
		{
			if (this->numeProprietar != NULL)
				delete[] this->numeProprietar;
			this->numeProprietar = new char[strlen(nume) + 1];
			strcpy(this->numeProprietar, nume);
		}
		else
			throw exception("dimensiune sir prea mica");
	}

	char* getNume()
	{
		return this->numeProprietar;
	}

	void setnrRanduri(int nrRanduri)
	{
		if (nrRanduri > 0)
			this->nrRanduri = nrRanduri;

	}
	int getnrRanduri()
	{
		return this->nrRanduri;
	}
	void setNumePodgorie(string numePodgorie)
	{
		if (numePodgorie.length() >= 3)
			this->numePodgorie = numePodgorie;
		else
			throw exception("dimensiune sir pre mica");
	}

	string getNumePodgorie()
	{
		return this->numePodgorie = numePodgorie;
	}
	const int getAnInfiintare()
	{
		return this->anInfiintare;
	}
	friend ostream& operator<<(ostream& out, const Podgorie& p);
	friend istream& operator>>(istream& in, Podgorie& p);
	friend ofstream& operator<<(ofstream& out, const Podgorie& p);
	friend ifstream& operator>>(ifstream& in, Podgorie& p);
};


istream& operator>>(istream& in, Podgorie& p)
{
	cout << endl;
	if (p.numeProprietar != NULL)
		delete[]p.numeProprietar;
	cout << " Podgoria: ";
	getline(in, p.numePodgorie, '\n');

	cout << " Numele Proprietarului: ";

	if (p.numeProprietar != NULL)
	{
		p.numeProprietar = new char[strlen(p.numeProprietar) + 1];
		strcpy(p.numeProprietar, p.numeProprietar);
		in.get(p.numeProprietar, '\n100');
	}
	else
		p.numeProprietar = NULL;
	cout << "\nNumarul soiurilor: ";
	in >> p.nrsoiuri;
	if (p.nrsoiuri > 0)
	{
		cout << "\nIntroduceti suprafata: ";
		for (int i = 0; i < p.nrsoiuri; i++)
			in >> p.Suprafata[i];
		cout << " ha ";
	}
	else
		for (int i = 0; i < p.nrsoiuri; i++)
			p.Suprafata[i] = 0;

	cout << "\nNr randuri vita de vie: ";
	in >> p.nrRanduri;

	return in;
}



ostream& operator<<(ostream& out, const Podgorie& p)
{
	out << endl;
	out << " Podgoria: " << p.numePodgorie;
	if (p.numeProprietar != NULL)
		out << "\nNumele Proprietarului: " << p.numeProprietar;
	else
		out << "-";

	if (p.nrsoiuri > 0)
	{
		out << " , numarul soiurilor este : " << p.nrsoiuri;
		out << " , suprafata pe care se intinde: ";
		for (int i = 0; i < p.nrsoiuri; i++)
			out << p.Suprafata[i] << " ha ";
	}
	else
		out << ", -";
	out << " , numar randuri de vita de vie: " << p.nrRanduri;
	out << " , an infiintare podgorie: " << p.anInfiintare;

	return out;
}


class Angajat :public IFile
{
private:
	char* numeAngajat;
	int varsta;
	float salariu;
	string functie;
	int nrBonusuri;
	float bonusuri[20];
public:
	Angajat() :numeAngajat(NULL), varsta(0), salariu(0), functie("NA"), nrBonusuri(0)
	{

	}

	Angajat(char* numeAngajat, int varsta, float salariu, string functie, int nrBonusuri, float bonusuri[20])
	{
		if (numeAngajat != NULL)
		{
			this->numeAngajat = new char[strlen(numeAngajat) + 1];
			strcpy(this->numeAngajat, numeAngajat);
		}
		else
			this->numeAngajat = NULL;
		this->varsta = varsta;
		this->salariu = salariu;
		this->functie = functie;
		this->nrBonusuri = nrBonusuri;
		for (int i = 0; i < this->nrBonusuri; i++)
			this->bonusuri[i] = bonusuri[i];

	}

	Angajat(char* numeAngajat, float salariu) :varsta(0), functie("NA"), nrBonusuri(0)
	{
		if (numeAngajat != NULL)
		{
			this->numeAngajat = new char[strlen(numeAngajat) + 1];
			strcpy(this->numeAngajat, numeAngajat);
		}
		else
			this->numeAngajat = NULL;
		this->salariu = salariu;



	}
	Angajat(const Angajat& a)
	{
		if (a.numeAngajat != NULL)
		{
			this->numeAngajat = new char[strlen(a.numeAngajat) + 1];
			strcpy(this->numeAngajat, a.numeAngajat);
		}
		else
			this->numeAngajat = NULL;
		this->varsta = a.varsta;
		this->salariu = a.salariu;
		this->functie = a.functie;
		this->nrBonusuri = a.nrBonusuri;
		for (int i = 0; i < this->nrBonusuri; i++)
			this->bonusuri[i] = a.bonusuri[i];
	}
	Angajat& operator=(const Angajat& a)
	{
		if (a.numeAngajat != NULL)
		{
			this->numeAngajat = new char[strlen(a.numeAngajat) + 1];
			strcpy(this->numeAngajat, a.numeAngajat);
		}
		else
			this->numeAngajat = NULL;
		this->varsta = a.varsta;
		this->salariu = a.salariu;
		this->functie = a.functie;
		this->nrBonusuri = a.nrBonusuri;
		for (int i = 0; i < this->nrBonusuri; i++)
			this->bonusuri[i] = a.bonusuri[i];
		return *this;
	}
	void writeToFile(fstream& file)
	{
		char buffer[100];
		strcpy(buffer, this->numeAngajat);
		file.write(buffer, sizeof(buffer));
		file.write((char*)&this->varsta, sizeof(int));
		file.write((char*)&this->salariu, sizeof(float));
		int lg = this->functie.length() + 1;
		file.write((char*)&lg, sizeof(int));
		//scriere sir efectiv
		file.write(this->functie.data(), lg);
		file.write((char*)&this->nrBonusuri, sizeof(int));
		file.write((char*)this->bonusuri, sizeof(float) * this->nrBonusuri);



	}

	void readFromFile(fstream& file)
	{
		char buffernume[100];
		file.read(buffernume, sizeof(buffernume));
		if (this->numeAngajat != NULL)
			delete[]this->numeAngajat;
		this->numeAngajat = new char[strlen(buffernume) + 1];
		strcpy(this->numeAngajat, buffernume);

		file.read((char*)&this->varsta, sizeof(this->varsta));
		file.read((char*)&this->salariu, sizeof(this->salariu));
		file.read((char*)&this->nrBonusuri, sizeof(int));
		file.read((char*)this->bonusuri, sizeof(float) * this->nrBonusuri);

	}
	bool operator==(const Angajat& a)
	{
		if (this->functie == a.functie)
			return true;
		return false;
	}

	Angajat operator++()
	{

		if (this->salariu < 4000)
		{
			this->nrBonusuri = nrBonusuri + 1;
			for (int i = 0; i < this->nrBonusuri - 1; i++)
				this->bonusuri[i] = bonusuri[i];
			this->bonusuri[this->nrBonusuri - 1] = 179;
		}
		else
			cout << "\nnu se modif";
		return *this;
	}

	Angajat operator++(int)
	{
		Angajat rez = *this;
		if (this->salariu < 4000)
		{
			this->nrBonusuri = nrBonusuri + 1;
			for (int i = 0; i < this->nrBonusuri - 1; i++)
				this->bonusuri[i] = bonusuri[i];
			this->bonusuri[this->nrBonusuri - 1] = 179;
		}
		else
			cout << "\nnu se modif";
		return rez;
	}

	Angajat operator+(int x)
	{
		Angajat rez = *this;
		if (rez.nrBonusuri == 0)
		{
			rez.salariu = salariu + x;
		}
		else
			cout << "\nnu se modifica";
		return rez;

	}

	bool operator>(const Angajat& a)
	{
		if (this->varsta > a.varsta)
			return true;
		return false;
	}

	explicit operator float()
	{
		return this->salariu;
	}

	float& operator[](int index)
	{
		if (index >= 0 && index < this->nrBonusuri)
			return this->bonusuri[index];
		else
			throw exception("\nindex gresit");

	}
	Angajat operator!()
	{
		Angajat rez = *this;
		rez.nrBonusuri = 0;
		for (int i = 0; i < rez.nrBonusuri; i++)
			rez.bonusuri[i] = 0;
		return rez;
	}

	~Angajat()
	{
		if (this->numeAngajat != NULL)
			delete[] this->numeAngajat;
	}


	virtual void pensie()
	{
		if (this->varsta > 59)
			cout << "\nVa iesi la pensie";
		else
			cout << "\nNu va iesi la pensie";
	}

	float salariutotal()
	{
		float salariut = 0;
		if (this->nrBonusuri != 0)
		{
			{
				for (int i = 0; i < this->nrBonusuri; i++)

					salariut = salariut + bonusuri[i];
			}
			return salariut = salariut + this->salariu;
		}
		else
			return this->salariu;
	}
	void setfunctie(string functie)
	{
		if (functie != this->functie)
			this->functie = functie;
		else
			throw exception("\nnu are rost modificarea");
	}
	string getfunctie()
	{
		return this->functie;
	}

	void setsalariu(float salariu)
	{
		if (salariu != this->salariu)
			this->salariu = salariu;
		else
			throw exception("\nnu modificam salariul");

	}
	float getsalariu()
	{
		return this->salariu;
	}
	void setvarsta(int varsta)
	{
		if (varsta > 18)
			this->varsta = varsta;
		else
			throw exception("\nvarsta nu e permisa");

	}
	int getvarsta()
	{
		return this->varsta;
	}

	void setbonusuri(int nrBonusuri, float bonusuri[20])
	{
		this->nrBonusuri = nrBonusuri;
		if (nrBonusuri > 0)
		{
			for (int i = 0; i < this->nrBonusuri; i++)
				this->bonusuri[i] = bonusuri[i];
		}
		else
		{
			for (int i = 0; i < this->nrBonusuri; i++)
				this->bonusuri[i] = 0;
		}

	}

	int getnrBonusuri()
	{
		return this->nrBonusuri;
	}
	float getbonusuri(int i)
	{
		return this->bonusuri[i];
	}

	void setnumeAngajat(const char* numeAngajat)
	{

		if (strlen(numeAngajat) >= 3)
		{
			if (this->numeAngajat != NULL)
				delete[] this->numeAngajat;
			this->numeAngajat = new char[strlen(numeAngajat) + 1];
			strcpy(this->numeAngajat, numeAngajat);
		}
		else
			throw exception("\ndimensiune sir prea mica");
	}

	char* getnumeAngajat()
	{
		return this->numeAngajat;
	}

	friend ostream& operator<<(ostream& out, const Angajat& a);
	friend istream& operator>>(istream& in, Angajat& a);

	friend ofstream& operator<<(ofstream& out, const Angajat& a);
	friend ifstream& operator>>(ifstream& in, Angajat& a);


};

ostream& operator<<(ostream& out, const Angajat& a)
{
	out << endl;
	if (a.numeAngajat != NULL)
		out << "Numele angajatului: " << a.numeAngajat;
	else
		out << "-";

	out << " , varsta: " << a.varsta << " , salariu: " << a.salariu << " lei , functie: " << a.functie;
	out << " , numarul bonusurilor este : " << a.nrBonusuri;
	if (a.nrBonusuri > 0)
	{

		out << " , bonusuri: ";
		for (int i = 0; i < a.nrBonusuri; i++)
			out << a.bonusuri[i] << " lei ";
	}
	else
		out << " , -";
	return out;
}


istream& operator>>(istream& in, Angajat& a)
{
	cout << endl;
	if (a.numeAngajat != NULL)
		delete[]a.numeAngajat;
	cout << "Numele  angajatului: ";
	if (a.numeAngajat != NULL)
	{
		a.numeAngajat = new char[strlen(a.numeAngajat) + 1];
		strcpy(a.numeAngajat, a.numeAngajat);
		in.get(a.numeAngajat, '\n100');
	}
	else
		a.numeAngajat = NULL;

	cout << "\nVarsta: ";
	in >> a.varsta;
	cout << "\nSalariul: ";
	in >> a.salariu;
	cout << "\nFunctia: ";
	in >> a.functie;
	cout << "\nNumarul bonusurilor: ";
	in >> a.nrBonusuri;
	if (a.nrBonusuri > 0)
	{
		cout << "\nIntroduceti bonusurile: ";
		for (int i = 0; i < a.nrBonusuri; i++)
			in >> a.bonusuri[i];
	}
	else
		for (int i = 0; i < a.nrBonusuri; i++)
			a.bonusuri[i] = 0;
	return in;
}

class OraseDepozite :public IFile//orase cu depozite in care imi depozitez strugurii
{
private:
	char* numeOras;
	int nrDepozite;
	float suprafataDepozit[20];
	static int nrOrase;//in cate orase avem depozite
public:

	OraseDepozite() :numeOras(NULL), nrDepozite(0) //constructor fara parametri
	{

		nrOrase++;

	}
	OraseDepozite(char* numeOras, int nrDepozite, float suprafataDepozit[])
	{
		if (numeOras != NULL)
		{
			this->numeOras = new char[strlen(numeOras) + 1];
			strcpy(this->numeOras, numeOras);
		}
		else
			this->numeOras = NULL;
		this->nrDepozite = nrDepozite;
		for (int i = 0; i < this->nrDepozite; i++)
			this->suprafataDepozit[i] = suprafataDepozit[i];
		nrOrase++;

	}
	OraseDepozite(char* numeOras)
	{
		if (numeOras != NULL)
		{
			this->numeOras = new char[strlen(numeOras) + 1];
			strcpy(this->numeOras, numeOras);
		}
		else
			this->numeOras = NULL;
		this->nrDepozite = 0;


		nrOrase++;

	}
	OraseDepozite(const OraseDepozite& d)
	{
		if (d.numeOras != NULL)
		{
			this->numeOras = new char[strlen(d.numeOras) + 1];
			strcpy(this->numeOras, d.numeOras);
		}
		else
			this->numeOras = NULL;
		this->nrDepozite = d.nrDepozite;
		for (int i = 0; i < this->nrDepozite; i++)
			this->suprafataDepozit[i] = d.suprafataDepozit[i];
		nrOrase++;
	}

	OraseDepozite& operator=(const OraseDepozite& d)
	{
		if (d.numeOras != NULL)
		{
			this->numeOras = new char[strlen(d.numeOras) + 1];
			strcpy(this->numeOras, d.numeOras);
		}
		else
			this->numeOras = NULL;
		this->nrDepozite = d.nrDepozite;
		for (int i = 0; i < this->nrDepozite; i++)
			this->suprafataDepozit[i] = d.suprafataDepozit[i];
		return *this;
		nrOrase++;
	}
	void writeToFile(fstream& file)
	{
		char buffer[100];
		strcpy(buffer, this->numeOras);
		file.write(buffer, sizeof(buffer));
		file.write((char*)&this->nrDepozite, sizeof(int));

		file.write((char*)this->suprafataDepozit, sizeof(float) * this->nrDepozite);
		file.write((char*)&nrOrase, sizeof(int));
	}

	void readFromFile(fstream& file)
	{
		char buffernume[100];
		file.read(buffernume, sizeof(buffernume));
		if (this->numeOras != NULL)
			delete[]this->numeOras;
		this->numeOras = new char[strlen(buffernume) + 1];
		strcpy(this->numeOras, buffernume);
		file.read((char*)&this->nrDepozite, sizeof(int));
		//float suprafata[20];
		file.read((char*)this->suprafataDepozit, sizeof(float) * this->nrDepozite);
		file.read((char*)&nrOrase, sizeof(int));

	}



	bool operator==(const OraseDepozite& d)
	{
		if (this->nrDepozite == d.nrDepozite)
			return true;
		return false;
	}

	OraseDepozite operator++()
	{
		this->nrDepozite = nrDepozite + 1;
		for (int i = 0; i < this->nrDepozite - 1; i++)
			this->suprafataDepozit[i] = suprafataDepozit[i];
		this->suprafataDepozit[this->nrDepozite - 1] = 177;
		return *this;
	}
	OraseDepozite operator++(int)
	{
		OraseDepozite rez = *this;
		this->nrDepozite = nrDepozite + 1;
		for (int i = 0; i < this->nrDepozite - 1; i++)
			this->suprafataDepozit[i] = suprafataDepozit[i];
		this->suprafataDepozit[this->nrDepozite - 1] = 179;
		return rez;
	}

	OraseDepozite operator-(int x)
	{
		OraseDepozite rez = *this;
		if (rez.nrDepozite > x)
		{
			rez.nrDepozite = rez.nrDepozite - x;
			for (int i = 0; i < rez.nrDepozite; i++)
				rez.suprafataDepozit[i] = suprafataDepozit[i];
		}
		else
		{
			rez.nrDepozite = rez.nrDepozite;
			for (int i = 0; i < rez.nrDepozite; i++)
				rez.suprafataDepozit[i] = suprafataDepozit[i];
		}
		return rez;
	}

	bool operator<=(const OraseDepozite& d)
	{
		if (this->nrDepozite <= d.nrDepozite)
			return true;
		return false;
	}

	operator char* ()
	{
		return this->numeOras;
	}

	float& operator[](int index)
	{
		if (index >= 0 && index < this->nrDepozite)
			return this->suprafataDepozit[index];
		else
			throw exception("\nindex gresit");

	}


	OraseDepozite operator!()
	{
		OraseDepozite rez = *this;
		rez.nrDepozite = 0;

		return rez;
	}


	~OraseDepozite()
	{
		if (this->numeOras != NULL)
			delete[] this->numeOras;

	}



	void nrdep()
	{
		if (this->nrDepozite < 3)
			cout << "\nNumele orasului cu nr depozite<3 este: " << this->numeOras;
		else
			cout << "\nau mai multe depozite";

	}
	void minsupr()
	{
		int min = this->suprafataDepozit[0];
		for (int i = 0; i < this->nrDepozite; i++)
			if (min > this->suprafataDepozit[i])
				min = this->suprafataDepozit[i];
		cout << "\nmin: " << min << " mp";

		if (min <= 100)
			cout << "\nNu pot fi depozitati strugurii in acest depozit; ";
		else
			cout << "\nPot fi depozitati strugurii in acest depozit";


	}

	void setSuprafata(int nrDepozite, float suprafataDepozit[20])
	{
		this->nrDepozite = nrDepozite;
		if (nrDepozite > 0)
		{
			for (int i = 0; i < this->nrDepozite; i++)
				this->suprafataDepozit[i] = suprafataDepozit[i];
		}
		else
		{
			for (int i = 0; i < this->nrDepozite; i++)
				this->suprafataDepozit[i] = 0;
		}

	}

	int getnrDepozite()
	{
		return this->nrDepozite;
	}
	float getSuprafataDepozite(int i)
	{
		return this->suprafataDepozit[i];
	}

	void setnumeOras(const char* numeOras)
	{

		if (strlen(numeOras) >= 3)
		{
			if (this->numeOras != NULL)
				delete[] this->numeOras;
			this->numeOras = new char[strlen(numeOras) + 1];
			strcpy(this->numeOras, numeOras);
		}
		else
			throw exception("dimensiune sir prea mica");
	}

	char* getnumeOras()
	{
		return this->numeOras;
	}
	static int getNrOrase()
	{
		return nrOrase;
	}


	friend ostream& operator<<(ostream& out, const OraseDepozite& d);
	friend istream& operator>>(istream& in, OraseDepozite& d);
	friend ofstream& operator<<(ofstream& out, const OraseDepozite& d);
	friend ifstream& operator>>(ifstream& in, OraseDepozite& d);
};
int OraseDepozite::nrOrase = 0;


ostream& operator<<(ostream& out, const OraseDepozite& d)
{
	out << endl;
	if (d.numeOras != NULL)
		out << "Numele orasului: " << d.numeOras;
	else
		out << "-";

	if (d.nrDepozite > 0)
	{
		out << " , numarul depozitelor este : " << d.nrDepozite;
		out << " , suprafata depozite: ";
		for (int i = 0; i < d.nrDepozite; i++)
			out << d.suprafataDepozit[i] << " mp ";
	}
	else
		out << " nr depozite: -";
	return out;
}

istream& operator>>(istream& in, OraseDepozite& d)
{
	cout << endl;
	if (d.numeOras != NULL)
		delete[]d.numeOras;
	cout << "Numele orasului: ";

	if (d.numeOras != NULL)
	{
		d.numeOras = new char[strlen(d.numeOras) + 1];
		strcpy(d.numeOras, d.numeOras);
		in.get(d.numeOras, '\n100');
	}
	else
		d.numeOras = NULL;
	cout << "\nNumarul depozitelor: ";
	in >> d.nrDepozite;
	if (d.nrDepozite > 0)
	{
		cout << "\nIntroduceti suprafata depozitelor: ";
		for (int i = 0; i < d.nrDepozite; i++)
			in >> d.suprafataDepozit[i];
	}
	else
		for (int i = 0; i < d.nrDepozite; i++)
			d.suprafataDepozit[i] = 0;
	return in;
}
class Soiuri
{
private:
	string numeSoiVin;
	int nrSoiuri;
	string* tipSoiuri;//de struguri
	float productie[20]; //pe an
public:
	Soiuri() :nrSoiuri(0), tipSoiuri(NULL), numeSoiVin("Nimic")
	{
		for (int i = 0; i < this->nrSoiuri; i++)
			this->productie[i] = 0;

	}

	Soiuri(string numeSoiVin, int nrSoiuri, string* tipSoiuri, float productie[20]) :numeSoiVin(numeSoiVin)
	{
		if (nrSoiuri != 0 && tipSoiuri != NULL)
		{
			this->nrSoiuri = nrSoiuri;
			this->tipSoiuri = new string[nrSoiuri];
			for (int i = 0; i < this->nrSoiuri; i++)
				this->tipSoiuri[i] = tipSoiuri[i];
		}
		else
		{
			this->nrSoiuri = 0;
			this->tipSoiuri = NULL;
		}
		if (nrSoiuri != 0)
		{
			this->nrSoiuri = nrSoiuri;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = productie[i];
		}
		else
		{
			this->nrSoiuri = 0;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = 0;

		}
	}

	Soiuri(int nrSoiuri, string* tipSoiuri)
	{
		this->numeSoiVin = numeSoiVin;
		if (nrSoiuri != 0 && tipSoiuri != NULL)
		{
			this->nrSoiuri = nrSoiuri;
			this->tipSoiuri = new string[nrSoiuri];
			for (int i = 0; i < this->nrSoiuri; i++)
				this->tipSoiuri[i] = tipSoiuri[i];
		}
		else
		{
			this->nrSoiuri = 0;
			this->tipSoiuri = NULL;
		}


		for (int i = 0; i < this->nrSoiuri; i++)
			this->productie[i] = 0;
	}

	Soiuri(const Soiuri& s)
	{
		this->numeSoiVin = s.numeSoiVin;
		if (s.nrSoiuri != 0 && s.tipSoiuri != NULL)
		{
			this->nrSoiuri = s.nrSoiuri;
			this->tipSoiuri = new string[s.nrSoiuri];
			for (int i = 0; i < this->nrSoiuri; i++)
				this->tipSoiuri[i] = s.tipSoiuri[i];
		}
		else
		{
			this->nrSoiuri = 0;
			this->tipSoiuri = NULL;
		}
		if (s.nrSoiuri != 0)
		{
			this->nrSoiuri = s.nrSoiuri;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = s.productie[i];
		}
		else
		{
			this->nrSoiuri = 0;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = 0;

		}
	}

	Soiuri& operator=(const Soiuri& s)
	{
		this->numeSoiVin = s.numeSoiVin;
		if (s.nrSoiuri != 0 && s.tipSoiuri != NULL)
		{
			this->nrSoiuri = s.nrSoiuri;
			this->tipSoiuri = new string[s.nrSoiuri];
			for (int i = 0; i < this->nrSoiuri; i++)
				this->tipSoiuri[i] = s.tipSoiuri[i];
		}
		else
		{
			this->nrSoiuri = 0;
			this->tipSoiuri = NULL;
		}
		if (s.nrSoiuri != 0)
		{
			this->nrSoiuri = s.nrSoiuri;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = s.productie[i];
		}
		else
		{
			this->nrSoiuri = 0;
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = 0;

		}
		return*this;
	}


	bool operator==(const Soiuri& s)
	{
		if (this->nrSoiuri == s.nrSoiuri)
			return true;
		return false;
	}

	Soiuri operator++()
	{
		Soiuri rez = *this;
		delete[]this->tipSoiuri;
		this->nrSoiuri = rez.nrSoiuri + 1;
		this->tipSoiuri = new string[this->nrSoiuri];
		for (int i = 0; i < this->nrSoiuri - 1; i++)
			this->tipSoiuri[i] = rez.tipSoiuri[i];
		//this->tipSoiuri[this->nrSoiuri-1] =this->tipSoiuri[this->nrSoiuri-2] ;
		this->tipSoiuri[this->nrSoiuri - 1] = "Sarba";
		this->productie[this->nrSoiuri - 1] = 800;
		return *this;
	}

	Soiuri operator++(int)
	{
		Soiuri rez = *this;
		delete[]this->tipSoiuri;
		this->nrSoiuri = rez.nrSoiuri + 1;
		this->tipSoiuri = new string[this->nrSoiuri];
		for (int i = 0; i < this->nrSoiuri - 1; i++)
			this->tipSoiuri[i] = rez.tipSoiuri[i];
		//this->tipSoiuri[this->nrSoiuri-1] =this->tipSoiuri[this->nrSoiuri-2] ;
		this->tipSoiuri[this->nrSoiuri - 1] = "Sarba";
		this->productie[this->nrSoiuri - 1] = 800;
		return rez;

	}

	Soiuri operator-(int x)
	{
		Soiuri rez = *this;
		delete[]rez.tipSoiuri;
		if (rez.nrSoiuri > x) {
			rez.nrSoiuri = rez.nrSoiuri - x;
			rez.tipSoiuri = new string[rez.nrSoiuri];
			for (int i = 0; i < rez.nrSoiuri; i++)
				rez.tipSoiuri[i] = this->tipSoiuri[i];
		}
		else
		{
			rez.nrSoiuri = rez.nrSoiuri;
			rez.tipSoiuri = new string[rez.nrSoiuri];
			for (int i = 0; i < rez.nrSoiuri; i++)
				rez.tipSoiuri[i] = this->tipSoiuri[i];
		}
		return rez;
	}

	bool operator>(const Soiuri& s)
	{
		int suma = 0;
		for (int i = 0; i < this->nrSoiuri; i++)
			suma = suma + this->productie[i];

		int suma1 = 0;
		for (int i = 0; i < s.nrSoiuri; i++)
			suma1 = suma1 + s.productie[i];
		if (suma > suma1)
			return true;
		return false;
	}

	explicit operator int()
	{
		return this->nrSoiuri;
	}

	string& operator[](int index)
	{
		if (index >= 0 && index < this->nrSoiuri)
			return this->tipSoiuri[index];
		else
			throw exception("\nindex gresit");

	}

	Soiuri operator!()
	{
		Soiuri rez = *this;
		rez.nrSoiuri = 0;
		delete[]rez.tipSoiuri;
		rez.tipSoiuri = NULL;
		for (int i = 0; i < rez.nrSoiuri; i++)
			rez.productie[i] = 0;
		return rez;
	}

	~Soiuri()
	{
		if (this->tipSoiuri != NULL)
			delete[]this->tipSoiuri;
	}



	void lasuta(int x)
	{
		int suma2 = 0;
		for (int i = 0; i < this->nrSoiuri; i++)
			suma2 += this->productie[i];
		int procent;
		procent = (this->productie[x] / suma2) * 100;
		cout << "\nReprezinta " << procent << " % din total";
	}
	float maximproductie()
	{
		int max1 = this->productie[0];
		for (int i = 0; i < this->nrSoiuri; i++)
			if (max1 < this->productie[i])
				max1 = this->productie[i];
		return max1;

	}
	void setTipSoi(int nrSoiuri, string* tipSoiuri)
	{
		if (nrSoiuri > 0)
		{
			delete[]this->tipSoiuri;
			if (nrSoiuri != 0 && tipSoiuri != NULL)
			{
				this->nrSoiuri = nrSoiuri;
				this->tipSoiuri = new string[nrSoiuri];
				for (int i = 0; i < this->nrSoiuri; i++)
					this->tipSoiuri[i] = tipSoiuri[i];
			}
			else
			{
				this->nrSoiuri = 0;
				this->tipSoiuri = NULL;
			}
		}
		else
		{
			this->nrSoiuri = 0;
			this->tipSoiuri = NULL;
		}
	}
	string* getTipSoiuri()
	{
		return this->tipSoiuri;
	}


	void setnumeSoi(string numeSoiVin)
	{
		if (numeSoiVin != this->numeSoiVin)
			this->numeSoiVin = numeSoiVin;
		else
			throw exception("nu are rost modificarea");
	}
	string getnumeSoi()
	{
		return this->numeSoiVin;
	}

	void setProductie(int nrSoiuri, float productie[20])
	{
		this->nrSoiuri = nrSoiuri;
		if (nrSoiuri > 0)
		{
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = productie[i];
		}
		else
		{
			for (int i = 0; i < this->nrSoiuri; i++)
				this->productie[i] = 0;
		}

	}

	int getnrSoiuri()
	{
		return this->nrSoiuri;
	}
	float getProductie(int i)
	{
		return this->productie[i];
	}

	friend ostream& operator<<(ostream& out, const Soiuri& s);
	friend istream& operator>>(istream& in, Soiuri& s);
	friend ofstream& operator<<(ofstream& out, const Soiuri& s);
	friend ifstream& operator>>(ifstream& in, Soiuri& s);
};

ostream& operator<<(ostream& out, const Soiuri& s)
{
	out << "\nTip vin: " << s.numeSoiVin;
	out << " , nr de soiuri: " << s.nrSoiuri << " , soiuri: ";
	if (s.tipSoiuri != NULL)
		for (int i = 0; i < s.nrSoiuri; i++)
			out << s.tipSoiuri[i] << " ; ";
	else
		out << "-";
	if (s.nrSoiuri > 0)
	{
		out << " , nr de soiuri: " << s.nrSoiuri << " , productia pe an: ";
		for (int i = 0; i < s.nrSoiuri; i++)
			out << s.productie[i] << " kg ; ";
	}
	else
		out << "-";



	return out;
}


istream& operator>>(istream& in, Soiuri& s)
{
	cout << "\nTip vin : ";
	getline(in, s.numeSoiVin, '\n');
	cout << "\nNumar soiuri: ";
	in >> s.nrSoiuri;
	delete[]s.tipSoiuri;
	in.clear();
	if (s.nrSoiuri > 0)
	{

		s.tipSoiuri = new string[s.nrSoiuri];
		cout << "Tipuri soiuri: ";
		for (int i = 0; i < s.nrSoiuri; i++)
		{
			getline(in, s.tipSoiuri[i], '\n');
			if (s.tipSoiuri[i].empty())
				getline(in, s.tipSoiuri[i], '\n');
		}
	}
	else
	{
		s.nrSoiuri = 0;
		s.tipSoiuri = NULL;
	}

	if (s.nrSoiuri > 0)
	{
		cout << "\nIntroduceti productia pe an: ";
		for (int i = 0; i < s.nrSoiuri; i++)
			in >> s.productie[i];
	}
	else
		for (int i = 0; i < s.nrSoiuri; i++)
			s.productie[i] = 0;

	return in;
}
class Vinuri
{
private:
	string culoareVin;
	const int anproductie;
	int nrtip;
	string* tipVinificatie;
	float pretvin[20];

public:
	Vinuri() :culoareVin("NA"), anproductie(0), nrtip(0), tipVinificatie(NULL)
	{


	}
	Vinuri(string culoareVin, const int anproductie, int nrtip, string* tipVinificatie, float pretvin[20]) :anproductie(anproductie)
	{
		this->culoareVin = culoareVin;
		if (nrtip != 0 && tipVinificatie != NULL)
		{
			this->nrtip = nrtip;
			this->tipVinificatie = new string[nrtip];
			for (int i = 0; i < this->nrtip; i++)
				this->tipVinificatie[i] = tipVinificatie[i];
		}
		else
		{
			this->nrtip = 0;
			this->tipVinificatie = NULL;
		}

		if (nrtip != 0)
		{
			this->nrtip = nrtip;
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = pretvin[i];
		}
		else
		{
			this->nrtip = 0;

		}
	}
	Vinuri(string culoareVin, const int anproductie) :anproductie(anproductie)
	{
		this->culoareVin = culoareVin;
		this->nrtip = 0;
		this->tipVinificatie = NULL;

	}

	Vinuri(const Vinuri& v) :anproductie(v.anproductie)
	{
		this->culoareVin = v.culoareVin;
		if (v.nrtip != 0 && v.tipVinificatie != NULL)
		{
			this->nrtip = v.nrtip;
			this->tipVinificatie = new string[v.nrtip];
			for (int i = 0; i < this->nrtip; i++)
				this->tipVinificatie[i] = v.tipVinificatie[i];
		}
		else
		{
			this->nrtip = 0;
			this->tipVinificatie = NULL;
		}

		if (v.nrtip != 0)
		{
			this->nrtip = v.nrtip;
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = v.pretvin[i];
		}
		else
		{
			this->nrtip = 0;
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = 0;

		}
	}
	Vinuri& operator=(const Vinuri& v)
	{
		this->culoareVin = v.culoareVin;
		if (v.nrtip != 0 && v.tipVinificatie != NULL)
		{
			this->nrtip = v.nrtip;
			this->tipVinificatie = new string[v.nrtip];
			for (int i = 0; i < this->nrtip; i++)
				this->tipVinificatie[i] = v.tipVinificatie[i];
		}
		else
		{
			this->nrtip = 0;
			this->tipVinificatie = NULL;
		}

		if (v.nrtip != 0)
		{
			this->nrtip = v.nrtip;
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = v.pretvin[i];
		}
		else
		{
			this->nrtip = 0;
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = 0;

		}
		return *this;
	}

	bool operator==(const Vinuri& v)
	{
		if (this->anproductie == v.anproductie)
			return true;
		return false;
	}

	Vinuri operator++()
	{
		Vinuri rez = *this;
		delete[]this->tipVinificatie;
		this->nrtip = rez.nrtip + 1;
		this->tipVinificatie = new string[this->nrtip];
		for (int i = 0; i < this->nrtip - 1; i++)
			this->tipVinificatie[i] = rez.tipVinificatie[i];
		this->tipVinificatie[this->nrtip - 1] = "brut";
		this->pretvin[this->nrtip - 1] = 67;
		return *this;
	}
	Vinuri operator++(int)
	{
		Vinuri rez = *this;
		delete[]this->tipVinificatie;
		this->nrtip = rez.nrtip + 1;
		this->tipVinificatie = new string[this->nrtip];
		for (int i = 0; i < this->nrtip - 1; i++)
			this->tipVinificatie[i] = rez.tipVinificatie[i];
		this->tipVinificatie[this->nrtip - 1] = "brut";
		this->pretvin[this->nrtip - 1] = 67;
		return rez;
	}


	Vinuri operator-(int x)
	{
		int suma1 = 0;
		Vinuri rez = *this;
		for (int i = 0; i < rez.nrtip; i++)
			suma1 = suma1 + rez.pretvin[i];
		if (suma1 > 300)
		{
			for (int i = 0; i < rez.nrtip; i++)
				if (rez.pretvin[i] > x)

					rez.pretvin[i] = this->pretvin[i] - x;
				else
					rez.pretvin[i] = this->pretvin[i];

		}
		else
			for (int i = 0; i < rez.nrtip; i++)
				rez.pretvin[i] = this->pretvin[i];
		return rez;
	}

	bool operator>=(const Vinuri& v)
	{
		int suma = 0;
		for (int i = 0; i < this->nrtip; i++)
			suma = suma + this->pretvin[i];

		int suma1 = 0;
		for (int i = 0; i < v.nrtip; i++)
			suma1 = suma1 + v.pretvin[i];
		if (suma >= suma1)
			return true;
		return false;
	}

	explicit operator const int()
	{
		return this->anproductie;
	}

	string& operator[](int index)
	{
		if (index >= 0 && index < this->nrtip)
			return this->tipVinificatie[index];
		else
			throw exception("\nindex gresit");

	}

	Vinuri operator!()
	{
		Vinuri rez = *this;
		rez.nrtip = 0;
		delete[]rez.tipVinificatie;
		rez.tipVinificatie = NULL;
		for (int i = 0; i < rez.nrtip; i++)
			rez.pretvin[i] = 0;
		return rez;
	}


	~Vinuri()
	{
		if (this->tipVinificatie != NULL)
			delete[]this->tipVinificatie;
	}


	void vechimevin(int ancurent)
	{
		int x;
		x = ancurent - this->anproductie;
		cout << "\nvechimea vinului este de: " << x << " ani";
	}

	virtual float medie(int j)
	{
		float medie = 0;
		if (j >= 0 && j < this->nrtip)
		{
			for (int i = 0; i <= j; i++)
				medie += this->pretvin[i];
			return medie / (j + 1);
		}
		else
			throw exception("\nindex gresit");


	}

	void setPret(int nrtip, float pretvin[20])
	{
		this->nrtip = nrtip;
		if (nrtip > 0)
		{
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = pretvin[i];
		}
		else
		{
			for (int i = 0; i < this->nrtip; i++)
				this->pretvin[i] = 0;
		}

	}

	int getnrtip()
	{
		return this->nrtip;
	}
	float getPret(int i)
	{
		return this->pretvin[i];
	}


	void setTipVinificatie(int nrtip, string* tipVinificatie)
	{
		if (nrtip > 0)
		{
			delete[]this->tipVinificatie;
			if (nrtip != 0 && tipVinificatie != NULL)
			{
				this->nrtip = nrtip;
				this->tipVinificatie = new string[nrtip];
				for (int i = 0; i < this->nrtip; i++)
					this->tipVinificatie[i] = tipVinificatie[i];
			}
			else
			{
				this->nrtip = 0;
				this->tipVinificatie = NULL;
			}
		}
		else
		{
			this->nrtip = 0;
			this->tipVinificatie = NULL;
		}
	}
	string* getTipVinificatie()
	{
		return this->tipVinificatie;
	}

	const int getAnproductie()
	{
		return this->anproductie;
	}

	void setCuloare(string culoareVin)
	{
		if (culoareVin != this->culoareVin)
			this->culoareVin = culoareVin;
		else
			throw exception("nu are rost modificarea");
	}
	string getCuloare()
	{
		return this->culoareVin;
	}



	friend ostream& operator<<(ostream& out, const Vinuri& v);
	friend istream& operator>>(istream& in, Vinuri& v);
	friend ofstream& operator<<(ofstream& out, const Vinuri& v);
	friend ifstream& operator>>(ifstream& in, Vinuri& v);
};


ostream& operator<<(ostream& out, const Vinuri& v)
{
	out << "\nCuloare vin: " << v.culoareVin;
	out << "\nAn productie: " << v.anproductie;
	out << " , nr tip: " << v.nrtip << " , vinificatie: ";
	if (v.tipVinificatie != NULL)
		for (int i = 0; i < v.nrtip; i++)
			out << v.tipVinificatie[i] << " ; ";
	else
		out << "-";
	if (v.nrtip > 0)
	{
		out << " , nr tip: " << v.nrtip << " , pret: ";
		for (int i = 0; i < v.nrtip; i++)
			out << v.pretvin[i] << " lei ; ";
	}
	else
		out << "-";
	return out;
}

istream& operator>>(istream& in, Vinuri& v)
{
	cout << "\nCuloare vin : ";
	getline(in, v.culoareVin, '\n');
	cout << "\nNumar tip: ";
	in >> v.nrtip;
	delete[]v.tipVinificatie;
	in.clear();
	if (v.nrtip > 0)
	{

		v.tipVinificatie = new string[v.nrtip];
		cout << "Tipuri vinificatie: ";
		for (int i = 0; i < v.nrtip; i++)
		{
			getline(in, v.tipVinificatie[i], '\n');
			if (v.tipVinificatie[i].empty())
				getline(in, v.tipVinificatie[i], '\n');
		}
	}
	else
	{
		v.nrtip = 0;
		v.tipVinificatie = NULL;
	}

	if (v.nrtip > 0)
	{
		cout << "\nIntroduceti pretul: ";
		for (int i = 0; i < v.nrtip; i++)
			in >> v.pretvin[i];
	}
	else
		for (int i = 0; i < v.nrtip; i++)
			v.pretvin[i] = 0;

	return in;
}

ifstream& operator>>(ifstream& in, Podgorie& p)
{
	cout << endl;
	if (p.numeProprietar != NULL)
		delete[]p.numeProprietar;

	getline(in, p.numePodgorie, '\n');



	if (p.numeProprietar != NULL)
	{
		p.numeProprietar = new char[strlen(p.numeProprietar) + 1];
		strcpy(p.numeProprietar, p.numeProprietar);
		in.get(p.numeProprietar, '\n100');
	}
	else
		p.numeProprietar = NULL;

	in >> p.nrsoiuri;
	if (p.nrsoiuri > 0)
	{

		for (int i = 0; i < p.nrsoiuri; i++)
			in >> p.Suprafata[i];

	}
	else
		for (int i = 0; i < p.nrsoiuri; i++)
			p.Suprafata[i] = 0;


	in >> p.nrRanduri;

	return in;
}
ofstream& operator<<(ofstream& out, const Podgorie& p)
{
	out << endl;
	out << p.numePodgorie;
	if (p.numeProprietar != NULL)
		out << "\n" << p.numeProprietar;

	if (p.nrsoiuri > 0)
	{
		out << endl;
		out << p.nrsoiuri;

		for (int i = 0; i < p.nrsoiuri; i++)
			out << "\n" << p.Suprafata[i];
	}

	out << "\n" << p.nrRanduri;
	out << "\n" << p.anInfiintare;

	return out;
}
ofstream& operator<<(ofstream& out, const Angajat& a)
{

	if (a.numeAngajat != NULL)
		out << "\n " << a.numeAngajat;


	out << " \n" << a.varsta << " \n " << a.salariu << "\n " << a.functie;
	out << " \n " << a.nrBonusuri;
	if (a.nrBonusuri > 0)
	{


		for (int i = 0; i < a.nrBonusuri; i++)
			out << "\n" << a.bonusuri[i];
	}

	return out;
}
ifstream& operator>>(ifstream& in, Angajat& a)
{
	cout << endl;
	if (a.numeAngajat != NULL)
		delete[]a.numeAngajat;

	if (a.numeAngajat != NULL)
	{
		a.numeAngajat = new char[strlen(a.numeAngajat) + 1];
		strcpy(a.numeAngajat, a.numeAngajat);
		in.get(a.numeAngajat, '\n100');
	}
	else
		a.numeAngajat = NULL;

	in >> a.varsta;
	in >> a.salariu;
	in >> a.functie;
	in >> a.nrBonusuri;
	if (a.nrBonusuri > 0)
	{
		cout << "\n";
		for (int i = 0; i < a.nrBonusuri; i++)
			in >> a.bonusuri[i];
	}
	else
		for (int i = 0; i < a.nrBonusuri; i++)
			a.bonusuri[i] = 0;
	return in;
}
ofstream& operator<<(ofstream& out, const OraseDepozite& d)
{

	if (d.numeOras != NULL)
		out << "\n " << d.numeOras;


	if (d.nrDepozite > 0)
	{
		out << "\n " << d.nrDepozite;

		for (int i = 0; i < d.nrDepozite; i++)
			out << "\n " << d.suprafataDepozit[i];
	}

	return out;
}
ifstream& operator>>(ifstream& in, OraseDepozite& d)
{
	cout << endl;
	if (d.numeOras != NULL)
		delete[]d.numeOras;


	if (d.numeOras != NULL)
	{
		d.numeOras = new char[strlen(d.numeOras) + 1];
		strcpy(d.numeOras, d.numeOras);
		in.get(d.numeOras, '\n100');
	}
	else
		d.numeOras = NULL;

	in >> d.nrDepozite;
	if (d.nrDepozite > 0)
	{

		for (int i = 0; i < d.nrDepozite; i++)
			in >> d.suprafataDepozit[i];
	}
	else
		for (int i = 0; i < d.nrDepozite; i++)
			d.suprafataDepozit[i] = 0;
	return in;
}
ofstream& operator<<(ofstream& out, const Soiuri& s)
{
	out << "\n " << s.numeSoiVin;
	out << "\n " << s.nrSoiuri;
	if (s.tipSoiuri != NULL)
		for (int i = 0; i < s.nrSoiuri; i++)
			out << "\n" << s.tipSoiuri[i];

	if (s.nrSoiuri > 0)
	{
		out << " \n " << s.nrSoiuri;
		for (int i = 0; i < s.nrSoiuri; i++)
			out << "\n" << s.productie[i];
	}

	return out;
}
ifstream& operator>>(ifstream& in, Soiuri& s)
{

	getline(in, s.numeSoiVin, '\n');
	in >> s.nrSoiuri;
	delete[]s.tipSoiuri;
	in.clear();
	if (s.nrSoiuri > 0)
	{

		s.tipSoiuri = new string[s.nrSoiuri];
		for (int i = 0; i < s.nrSoiuri; i++)
		{
			getline(in, s.tipSoiuri[i], '\n');
			if (s.tipSoiuri[i].empty())
				getline(in, s.tipSoiuri[i], '\n');
		}
	}
	else
	{
		s.nrSoiuri = 0;
		s.tipSoiuri = NULL;
	}

	if (s.nrSoiuri > 0)
	{

		for (int i = 0; i < s.nrSoiuri; i++)
			in >> s.productie[i];
	}
	else
		for (int i = 0; i < s.nrSoiuri; i++)
			s.productie[i] = 0;

	return in;
}
ofstream& operator<<(ofstream& out, const Vinuri& v)
{
	out << "\n " << v.culoareVin;
	out << "\n " << v.anproductie;
	out << "\n " << v.nrtip;
	if (v.tipVinificatie != NULL)
		for (int i = 0; i < v.nrtip; i++)
			out << "\n" << v.tipVinificatie[i];

	if (v.nrtip > 0)
	{
		out << "\n" << v.nrtip;
		for (int i = 0; i < v.nrtip; i++)
			out << "\n" << v.pretvin[i];
	}

	return out;
}
ifstream& operator>>(ifstream& in, Vinuri& v)
{

	getline(in, v.culoareVin, '\n');
	in >> v.nrtip;
	delete[]v.tipVinificatie;
	in.clear();
	if (v.nrtip > 0)
	{

		v.tipVinificatie = new string[v.nrtip];
		for (int i = 0; i < v.nrtip; i++)
		{
			getline(in, v.tipVinificatie[i], '\n');
			if (v.tipVinificatie[i].empty())
				getline(in, v.tipVinificatie[i], '\n');
		}
	}
	else
	{
		v.nrtip = 0;
		v.tipVinificatie = NULL;
	}

	if (v.nrtip > 0)
	{
		for (int i = 0; i < v.nrtip; i++)
			in >> v.pretvin[i];
	}
	else
		for (int i = 0; i < v.nrtip; i++)
			v.pretvin[i] = 0;

	return in;
}
class Crama
{
	string numeCrama = "NA";
	Vinuri** listaVinuri = NULL;
	int nrVinuri = 0;
public:
	Crama()
	{
	}
	Crama(string numeCrama, Vinuri** listaVinuri,int nrVinuri)
	{
		this->numeCrama = numeCrama;
		if (listaVinuri != NULL && nrVinuri != 0)
		{
			this->nrVinuri = nrVinuri;
			this->listaVinuri = new Vinuri * [this->nrVinuri];
			for (int i = 0; i < this->nrVinuri; i++)
			{
				this->listaVinuri[i] = new Vinuri(*listaVinuri[i]);
			}
		}
	}
	~Crama()
	{
		for (int i = 0; i < this->nrVinuri; i++)
			delete this->listaVinuri[i];
		delete[]this->listaVinuri;
	}
	Crama(const Crama& cr)
	{
		this->numeCrama = cr.numeCrama;
		if (cr.listaVinuri != NULL && cr.nrVinuri != 0)
		{
			this->nrVinuri = cr.nrVinuri;
			this->listaVinuri = new Vinuri * [this->nrVinuri];
			for (int i = 0; i < this->nrVinuri; i++)
			{
				this->listaVinuri[i] = new Vinuri(*cr.listaVinuri[i]);
			}
		}
		
	}
	Crama& operator=(const Crama& cr)
	{
		for (int i = 0; i < this->nrVinuri; i++)
			delete this->listaVinuri[i];
		delete[]this->listaVinuri;
		this->numeCrama = cr.numeCrama;
		if (cr.listaVinuri != NULL && cr.nrVinuri != 0)
		{
			this->nrVinuri = cr.nrVinuri;
			this->listaVinuri = new Vinuri * [this->nrVinuri];
			for (int i = 0; i < this->nrVinuri; i++)
			{
				this->listaVinuri[i] = new Vinuri(*cr.listaVinuri[i]);
			}
		}
	}
	friend bool operator<(const Crama& cr1, const Crama& cr2)
	{
		return cr1.nrVinuri < cr2.nrVinuri;
	}
	friend ostream& operator<<(ostream& out, const Crama& cr);
	friend istream& operator>>(istream& in,  Crama& cr);
	friend ofstream& operator<<(ofstream& out, const Crama& cr);
	friend ifstream& operator>>(ifstream& in, Crama& cr);
};
ostream& operator<<(ostream& out, const Crama& cr)
{
	out << endl;
	out << "\nNumele cramei: " << cr.numeCrama;
	out << "\nNumarul vinurilor: " << cr.nrVinuri;
	if (cr.listaVinuri != NULL)
	{
		out << "\nVinuri: ";
		for (int i = 0; i < cr.nrVinuri; i++)
		{
			out << *cr.listaVinuri[i];
		}
	}
	else
		out << "Nu sunt; ";
	return out;
}
istream& operator>>(istream& in, Crama& cr)
{
	cout << "\nIntroduceti numele: ";
	in >> cr.numeCrama;
	for (int i = 0; i < cr.nrVinuri; i++)
		delete cr.listaVinuri[i];
	delete[]cr.listaVinuri;
	cout << "Introduceti nr: ";
	in >> cr.nrVinuri;
	if (cr.nrVinuri > 0)
	{
		cr.listaVinuri = new Vinuri * [cr.nrVinuri];
		for (int i = 0; i < cr.nrVinuri; i++)
		{
			Vinuri v;
			in >> v;
			cr.listaVinuri[i] = new Vinuri(v);
		}
	}
	else
	{
		cr.nrVinuri = 0;
		cr.listaVinuri = NULL;
	}
	return in;

}
ofstream& operator<<(ofstream& out, const Crama& cr)
{
	out <<  cr.numeCrama;
	out << "\n " << cr.nrVinuri;
	if (cr.listaVinuri != NULL)
	{
		
		for (int i = 0; i < cr.nrVinuri; i++)
		{
			out << *cr.listaVinuri[i];
		}
	}

	return out;
}
ifstream& operator>>(ifstream& in, Crama& cr)
{
	
	in >> cr.numeCrama;
	for (int i = 0; i < cr.nrVinuri; i++)
		delete cr.listaVinuri[i];
	delete[]cr.listaVinuri;

	in >> cr.nrVinuri;
	if (cr.nrVinuri > 0)
	{
		cr.listaVinuri = new Vinuri * [cr.nrVinuri];
		for (int i = 0; i < cr.nrVinuri; i++)
		{
			Vinuri v;
			in >> v;
			cr.listaVinuri[i] = new Vinuri(v);
		}
	}
	else
	{
		cr.nrVinuri = 0;
		cr.listaVinuri = NULL;
	}
	return in;
}
class VApreciate :public Vinuri//clasa vinuri apreciate
{
	float alcool=0;
	int nrlunimaturare = 0;
public:
	VApreciate()
	{/*
		string culoareVin;
		const int anproductie;
		int nrtip;
		string* tipVinificatie;
		float pretvin[20];*/
	}
	VApreciate(string c, int a, int nr, string* tV, float p[20], float al, int m):Vinuri(c,a,nr,tV,p)
	{
		this->alcool = a;
		this->nrlunimaturare = m;

	}
	VApreciate(Vinuri v, float a, int m) :Vinuri(v)
	{
		this->alcool = a;
		this->nrlunimaturare = m;
	}
	VApreciate(const VApreciate& ap) :Vinuri(ap)
	{
		this->alcool = ap.alcool;
		this->nrlunimaturare = ap.nrlunimaturare;
	}
	VApreciate& operator=(const VApreciate& ap)
	{
		Vinuri::operator=(ap);
		this->alcool = ap.alcool;
		this->nrlunimaturare = ap.nrlunimaturare;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const VApreciate& ap)
	{
		out << (Vinuri)ap;
		out << "\nContine " << ap.alcool << " % alcool ";
		out << ", maturat " << ap.nrlunimaturare << " luni ";
		return out;
	}
	~VApreciate()
	{
	}
	float medie(int j)
	{
		if (this->nrlunimaturare < j) 
		{
			return j; //cate luni ar fi trebuit sa stea la maturat
			
		}
		else
		{
			return this->nrlunimaturare;
		}
	}

};
class VPremiate:public VApreciate
{
	int nrconccastigate=0;
public:
	VPremiate()
	{}
	VPremiate(VApreciate va, int nrc) :VApreciate(va)
	{
		this->nrconccastigate = nrc;
	}
	VPremiate(const VPremiate& vp) :VApreciate(vp)
	{
		this->nrconccastigate = vp.nrconccastigate;
	}
	VPremiate& operator=(const VPremiate& vp)
	{
		VApreciate::operator=(vp);
		this->nrconccastigate = vp.nrconccastigate;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const VPremiate& vp)
	{
		out << (VApreciate)vp;
		out << "\nnr concursuri: " << vp.nrconccastigate;
		return out;
	}
	~VPremiate()
	{}
};
class VVandute :public Vinuri//clasa vinuri apreciate
{
	string calitate = "";
public:
	VVandute()
	{/*
		string culoareVin;
		const int anproductie;
		int nrtip;
		string* tipVinificatie;
		float pretvin[20];*/
	}
	VVandute(string c, int a, int nr, string* tV, float p[20], string cal) :Vinuri(c, a, nr, tV, p)
	{
		this->calitate = cal;

	}
	VVandute(Vinuri v, string cal) :Vinuri(v)
	{
		this->calitate = cal;
	}
	VVandute(const VVandute& va) :Vinuri(va)
	{
		this->calitate = va.calitate;
	}
	VVandute& operator=(const VVandute& va)
	{
		Vinuri::operator=(va);
		this->calitate = va.calitate;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const VVandute& va)
	{
		out << (Vinuri)va;
		out << "\nare: " << va.calitate;
		return out;
	}
	~VVandute()
	{
	}


};
class ALunii:public Angajat//angajatul lunii
{
	/*char* numeAngajat;
	int varsta;
	float salariu;
	string functie;
	int nrBonusuri;
	float bonusuri[20];*/
	int nroresupl=0;
	string zilelibere = "NA"; //bonus zile libere
public:
	ALunii(){}
	ALunii(char* nA, int v, float s, string f, int nrb, float b[20], int no, string zl) :Angajat(nA,v,s,f,nrb,b)
	{
		this->nroresupl = no;
		this->zilelibere = zl;
	}
	ALunii(Angajat a, int no, string zl) :Angajat(a)
	{
		this->nroresupl = no;
		this->zilelibere = zl;

	}
	ALunii(const ALunii& al):Angajat(al)
	{
		this->nroresupl = al.nroresupl;
		this->zilelibere = al.zilelibere;
	}
	ALunii& operator=(const ALunii& al)
	{
		Angajat::operator=(al);
		this->nroresupl = al.nroresupl;
		this->zilelibere = al.zilelibere;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const ALunii& al)
	{
		out << (Angajat)al;
		out << "\nNr ore lucrate suplimentar: " << al.nroresupl;
		out << " , perioada libera: " << al.zilelibere;
		return out;
	}
	~ALunii()
	{}
	void pensie()
	{
		if (Angajat::getvarsta() > 59)
		{
			cout << "\nVa iesi la pensie si nu va mai avea parte de zilele libere";
			
		}
		else
			cout << "\nNu va iesi la pensie";
	}
};





int main(int argc, char* argv[])
{
	int nrFisiere = argc; //numarul de argumente primite ca parametru 	
	string* listaFisiere = new string[argc];
	for (int i = 0; i < argc; i++)
		listaFisiere[i] = argv[i];//incarcarea in vectorul de string-uri a parametrilor primiti la apel 	
	for (int i = 0; i < argc; i++)
		cout << listaFisiere[i] << endl;





	//////////////////////////////
	cout << endl << "\n*********Podgorie*********" << endl;
	//clasaPodgorie

	Podgorie p;//constr fara param
	cout << "\np:" << p;

	char numeProprietar[] = "Ionescu";
	float Suprafata[20] = { 5,7,9 };
	Podgorie p1("Cotnari", numeProprietar, 20000, 2004, 3, Suprafata); //constr cu toti param
	cout << "\np1:" << p1;
	cout << endl;
	//cin >> p1;
	//cout << "\np1:" << p1;


	//functii accesor pt numeProprietar
	cout << endl;
	try {
		p1.setNume("Ro"); //setare nume daca are cel putin 3 litere

		cout << "\np1:" << p1;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << p1.getNume();

	//functii accesor pt nr randuri

	p1.setnrRanduri(21000);
	cout << endl << "\np1:" << p1;
	cout << endl << p1.getnrRanduri();

	//functii accesor pt nr angajati si salariu
	float Suprafata1[] = { 8,3,9,2 };
	p1.setSupr(4, Suprafata1); cout << endl;
	cout << "\np1:" << p1 << endl;
	cout << p1.getnrsoi() << endl;
	cout << p1.getSupr(2) << endl;

	//functii accesor pt aninfiintare
	cout << p.getAnInfiintare() << endl;

	//functii accesor pt numele orasului
	try {
		p1.setNumePodgorie("Aiud"); //setare nume daca are cel putin 3 litere

		cout << "\np1:" << p1;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << p1.getNumePodgorie();


	char numeProprietar1[] = "Popescu";
	float Suprafata3[20] = { 2,10,15,9 };
	Podgorie p2("Dragasani", numeProprietar1, 40000, 2002, 4, Suprafata3);

	char numeProprietar2[] = "Costescu";
	float Suprafata2[20] = { 21,12 };
	Podgorie p3("Macin", numeProprietar2, 30600, 1999, 2, Suprafata2);


	cout << "\np " << p << endl;
	cout << "\np1 " << p1 << endl;
	cout << "\np2 " << p2 << endl;
	cout << "\np3 " << p3 << endl;

	//op !
	p = !p1;
	cout << "\np " << p << endl;

	//op []
	try
	{
		float Suprafata = p3[1];
		cout << "\nSuprafata: " << Suprafata << " ha";

	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	p3[1] = 15;
	cout << " \np3: " << p3 << endl;

	//op cast la const int
	const int an = p2;
	cout << "\nan: " << an;

	//op <
	if (p3 < p2)
		cout << "\nPodgoria exista de mai mult timp";
	else
		cout << "\naltfel";

	//op +
	p3 = p2 + 100;
	cout << "\np2 " << p2 << endl;
	cout << "\np3 " << p3 << endl;

	//op--
	try {
		p1 = --p3;

		cout << "\np1:" << p1;
		cout << "\np3:" << p3;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	try {
		p1 = p2--;

		cout << "\np1:" << p1;
		cout << "\np2:" << p2;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl;

	//op ==
	if (p == p3)
		cout << "\nau acelasi nr de randuri";
	else
		cout << "\nnu au acelasi nr de randuri";
	p.plantatie();

	float supr = p2.suprmax();
	cout << "\n" << supr;
	cout << endl << "\n*********Angajat*********" << endl;

	//clasa Angajat
	Angajat a;
	cout << "\na:" << a;

	char numeAngajat[] = "Popescu David";
	float bonusuri[] = { 200,300,100 };
	Angajat a1(numeAngajat, 34, 2500, "sofer", 2, bonusuri);
	cout << "\na1:" << a1;

	//cin >> a1;
	//cout << "\na1:" << a1;

	Angajat a2(a1);
	cout << "\na2:" << a2;

	char numeAngajat1[] = "Gavrila Dana";
	float bonusuri1[] = { 300,350,100 };
	Angajat a3(numeAngajat, 60, 3500, "culegator", 3, bonusuri1);
	cout << "\na3:" << a3;

	//functii accesor pt numeangajat
	try {
		a.setnumeAngajat("Florin Radu"); //setare nume daca are cel putin 3 litere

		cout << "\na: " << a;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << a.getnumeAngajat();

	//functii accesor pt bonusuri
	float bonusuri2[20] = { 190,185 };
	a.setbonusuri(2, bonusuri2);
	cout << "\na:" << a << endl;
	cout << a.getnrBonusuri() << " " << a.getbonusuri(0);

	//pt varsta
	try {
		a.setvarsta(20);

		cout << "\na: " << a;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << a.getvarsta();

	//pt salariu
	try {
		a.setsalariu(4450);

		cout << "\na: " << a;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << a.getsalariu();

	// functie
	try {
		a.setfunctie("sofer");

		cout << "\na: " << a;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << a.getfunctie();

	//op[]
	try
	{
		float bonusuri = a3[1];
		cout << "\nBonusul: " << bonusuri << " lei ";

	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	a3[1] = 400;
	cout << " \na3: " << a3;

	//op !
	Angajat a4;
	a4 = !a3;
	cout << "\na4: " << a4;

	//op cast
	float salariu = (float)a2;
	cout << "\nSalariul: " << salariu;

	//op >
	if (a3 > a2)
		cout << "\nEste mai in varsta";
	else
		cout << "\naltfel";

	//op +
	a = a4 + 100;
	cout << "\na: " << a;
	cout << "\na4: " << a4;
	cout << "\na: " << a;


	a = a4++;
	cout << "\na4: " << a4;
	cout << "\na: " << a;
	a = ++a4;
	cout << "\na4: " << a4;
	cout << "\na: " << a;

	if (a2 == a3)
		cout << "\nau ac functie ";
	else
		cout << "\nnu au ac functie";

	float salariutotal = a3.salariutotal();
	cout << "\nsalariul total: " << salariutotal << " lei ";
	a3.pensie();
	cout << endl << "\n********Orase Dep**********" << endl;
	//clasa orasedepozite

	char numeOrase[] = "Timisoara";
	float suprafataDepozit[20] = { 100,170,185 };
	OraseDepozite d(numeOrase, 3, suprafataDepozit);
	cout << "\nd: " << d;  //afisare constr cu toti param

	OraseDepozite d4(numeOrase);
	cout << "\nd4: " << d4;

	OraseDepozite d1;
	cout << "\nd1: " << d1; //afis  constr fara param

	//cin >> d;
	//cout << d;

	OraseDepozite d2(d); //constr copiere
	cout << "\nd2: " << d2 << endl;

	//functii accesor pt numeorase
	try {
		d2.setnumeOras("Oradea"); //setare nume daca are cel putin 3 litere

		cout << "\nd2: " << d2;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	cout << endl << d.getnumeOras();

	//functii accesor pt suprafatadepozit si nrdepozite
	float suprafataDepozit1[20] = { 190,185 };
	d.setSuprafata(2, suprafataDepozit1);
	cout << "\nd: " << d << endl;
	cout << d.getnrDepozite() << " " << d.getSuprafataDepozite(0);

	char numeOrase1[] = "Cluj Napoca";
	float suprafataDepozit2[20] = { 200,285 };
	OraseDepozite d3(numeOrase1, 2, suprafataDepozit2);
	cout << "\nd3: " << d3;

	//op !
	d1 = !d3;
	cout << "\nd1: " << d1;

	//op[]
	try
	{
		float suprafata = d3[1];
		cout << "\nSuprafata: " << suprafata << " mp ";

	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	d3[1] = 100;
	cout << " \nd3: " << d3;

	//op cast
	char* nume = d3;
	cout << "\nNumele: " << nume;

	//op <=
	if (d3 <= d2)
		cout << "\nare mai putine depozite";
	else
		cout << "\naltfel";

	//op-
	d = d3 - 1;
	cout << "\nd: " << d;
	cout << "\nd1: " << d1;
	cout << "\nd2: " << d2;
	cout << "\nd3: " << d3;

	//op ++
	d1 = ++d2;
	cout << "\nd1: " << d1;

	d = d1++;
	cout << "\nd1: " << d1;
	cout << "\nd: " << d;
	try {
		d1.setnumeOras("Bucuresti");

		cout << "\nd1: " << d1;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	//op ==
	if (d == d3)
		cout << "\nau acelasi nr de depozite";
	else
		cout << "\nnu au acelasi nr de depozite";

	cout << "\nDetin: " << OraseDepozite::getNrOrase();
	d3.nrdep();
	d3.minsupr();

	cout << endl << "\n*********Soiuri*********" << endl;
	//clasaSoiuri
	Soiuri s; //constr  fara parm
	cout << "\ns: " << s;

	string* tipSoiuri = new string[3];
	tipSoiuri[0] = "Feteasca Alba";
	tipSoiuri[1] = "Mustoasa";
	tipSoiuri[2] = "Feteasca Regala";

	float productie[20] = { 120,200,350 };
	Soiuri s1("Vin alb", 3, tipSoiuri, productie); //constr cu pram
	cout << "\ns1: " << s1;

	Soiuri s4(3, tipSoiuri); //constr care nu are toti param
	cout << "\ns4: " << s4;

	Soiuri s2(s1);  //constr de copiere
	cout << "\ns2: " << s2;

	cout << endl;
	//cin >> s2;
	//cout << "\ns2: " << s2 << endl;

	//functii accesor pt productie si nrsoiuri
	float productie1[20] = { 250,480 };
	s1.setProductie(2, productie1);
	cout << "\ns1: " << s1 << endl;
	cout << s.getnrSoiuri() << " " << s1.getProductie(1) << endl;

	//functii accesor pt numesoi

	try
	{
		s1.setnumeSoi("Vin rosu");  //modific doar daca nu e egal cu cel existent deja
		cout << "\ns1: " << s1;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	//functii accesor pt tipsoiuri
	string* tipSoiuri1 = new string[2];
	tipSoiuri1[0] = "Feteasca Neagra";
	tipSoiuri1[1] = "Cadarca";
	s1.setTipSoi(2, tipSoiuri1);
	cout << "\ns1: " << s1;
	cout << "\n" << *s1.getTipSoiuri();

	//op !
	float productie2[20] = { 200,350 };
	Soiuri s3("Vin alb", 2, tipSoiuri, productie2);
	cout << "\ns3: " << s3;
	s = !s3;
	cout << "\ns: " << s;

	//op indexare
	try
	{
		string tip = s3[5];
		cout << "\nTipul soiului: " << tip;

	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	//op cast
	int nr = (int)s3;
	cout << "\nNr soiuri: " << nr;
	//>
	if (s2 > s3)
		cout << "\ns2 are productia mai mare ";
	else
		cout << "\naltfel";

	//op -, elimina ultimele x productii
	s3 = s2 - 2;
	cout << "\ns3: " << s3;
	cout << "\ns2: " << s2;

	//op ++
	s = ++s3;
	cout << "\ns: " << s;
	cout << "\ns3: " << s3;

	s = s3++;
	cout << "\ns: " << s;
	cout << "\ns3: " << s3;

	//op ==
	if (s == s3)
		cout << "\nau acelasi nr de soiuri";
	else
		cout << "\nnu au acelasi nr de soiuri";

	s3.lasuta(1);


	float productie3[20] = { 120,100,50 };
	Soiuri s5("Vin alb", 3, tipSoiuri, productie3); //constr cu pram
	cout << "\ns5: " << s5;
	int maxim = s5.maximproductie();
	cout << "\n Productia maxima e: " << maxim << " kg";
	cout << endl << "\n*********Vinuri*********" << endl;

	//clasa Vinuri
	Vinuri v;  //constr fara param
	cout << "\nv: " << v;

	string* tipVinificatie = new string[3];
	tipVinificatie[0] = "dulce";
	tipVinificatie[1] = "sec";
	tipVinificatie[2] = "demisec";

	float pretVin[20] = { 120,200,350 };
	Vinuri v1("Vin alb", 2006, 3, tipVinificatie, pretVin); //constr cu toti param
	cout << "\nv1: " << v1;

	//cin >> v;
	//cout << "\nv: " << v;

	Vinuri v2("Vin rosu", 2004); //constr care nu are toti param
	cout << "\nv2: " << v2;

	string* tipVinificatie1 = new string[4];
	tipVinificatie1[0] = "dulce";
	tipVinificatie1[1] = "sec";
	tipVinificatie1[2] = "demisec";
	tipVinificatie1[3] = "extrasec";

	float pretVin1[20] = { 90,130,250,200 };
	Vinuri v3("Vin rosu", 2002, 4, tipVinificatie1, pretVin1);
	cout << "\nv3: " << v3;

	//functii accesor pt culoare

	try
	{
		v.setCuloare("Vin rose");  //modific doar daca nu e egal cu cel existent deja
		cout << "\nv: " << v;
	}
	catch (exception ex)
	{
		cout << ex.what();
	}

	cout << "\n" << v1.getCuloare();

	//functii accesor pentru an
	cout << "\nan: " << v1.getAnproductie();

	Vinuri v4(v3);
	cout << "\nv4:" << v4;

	//functii accesor pt tipvinificatie
	v3.setTipVinificatie(2, tipVinificatie);
	string* tipVinificatie2 = new string[3];
	tipVinificatie2[0] = "dulce";
	tipVinificatie2[1] = "extrasec";
	tipVinificatie2[2] = "demidulce";

	v2.setTipVinificatie(3, tipVinificatie2);
	cout << "\nv3: " << v3;

	float pretVin2[20] = { 90,80,70 };
	//accesor pt pret 
	v3.setPret(2, pretVin);
	v2.setPret(2, pretVin2);
	cout << "\nv3: " << v3;
	cout << "\npret: " << v3.getPret(1);

	cout << "\nv: " << v;
	cout << "\nv1: " << v1;
	cout << "\nv2: " << v2;
	cout << "\nv3: " << v3;

	v = !v2;  //op !
	cout << "\nv: " << v;
	//op []
	try
	{
		string tipvinificatie = v3[1];
		cout << "\nTipul vinului: " << tipvinificatie;

	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	//op cast
	int anprod = (const int)v2;
	cout << "\nan prod: " << anprod;

	//>=
	if (v2 >= v3)
		cout << "\n are preturi mai mari ";
	else
		cout << "\naltfel";

	//op-
	v = v3 - 120;  //reducem pretul cu 20 lei daca suma depaseste 300 lei
	cout << "\nv: " << v;
	cout << "\nv3: " << v3;

	//op ++
	v = ++v3;
	cout << "\nv: " << v;
	cout << "\nv3: " << v3;

	v = v3++;
	cout << "\nv: " << v;
	cout << "\nv3: " << v3;

	//op ==
	if (v == v3)
		cout << "\nau ac vechime";
	else
		cout << "\nnu au ac vechime";

	v3.vechimevin(2021);

	try {
		float medie = v2.medie(1);
		cout << "\nmedia: " << medie << " lei";

	}
	catch (exception ex)
	{
		cout << ex.what();
	}


	//fisiere
	//fstream fOut("Podgorie1.dat", ios::out | ios::binary);
	//if (fOut.is_open())
	//{
	//	p3.writeToFile(fOut);
	//	fOut.close();
	//}
	//else
	//	cout << "\neroare";


	//fstream fIn("Podgorie1.dat", ios::in | ios::binary);
	//if (fIn.is_open())
	//{
	//	p2.readFromFile(fIn);
	//	cout << "\np2:::::" << p2;
	//	fIn.close();
	//}
	//else
	//	cout << "\neroare deschidere";

	//fstream fOut1("Angajati1.dat", ios::out | ios::binary);
	//if (fOut1.is_open())
	//{
	//	a3.writeToFile(fOut1);
	//	fOut1.close();
	//}
	//else
	//	cout << "\neroare";

	//cout << "\na::::" << a;
	//fstream fIn1("Angajati1.dat", ios::in | ios::binary);
	//if (fIn1.is_open())
	//{
	//	char numeAngajat4[] = "Roberta Izabela";
	//	float bonusuri4[] = { 300,300,100 };
	//	Angajat a5(numeAngajat4, 44, 3000, "degustator", 3, bonusuri4);
	//	cout << "\na5:::::" << a5;
	//	a1.readFromFile(fIn1);
	//	cout << "\na5:::::" << a5;
	//	fIn1.close();
	//}
	//else
	//	cout << "\neroare deschidere";



	//fstream fOut2("Orase1.dat", ios::out | ios::binary);
	//if (fOut2.is_open())
	//{
	//	d.writeToFile(fOut2);
	//	fOut2.close();
	//}
	//else
	//	cout << "\neroare";


	//fstream fIn2("Orase1.dat", ios::in | ios::binary);
	//if (fIn2.is_open())
	//{
	//	char numeOrase4[] = "Tg-Jiu";
	//	float suprafataDepozit4[20] = { 200 };
	//	OraseDepozite d4(numeOrase4, 1, suprafataDepozit4);

	//	cout << "\nd4:::::" << d4;
	//	d1.readFromFile(fIn2);
	//	cout << "\nd4:::::" << d4;
	//	fIn2.close();
	//}
	//else
	//	cout << "\neroare deschidere";

	//ofstream g("podgorie.txt");
	//g << p2;
	//g.close();

	//Podgorie p5;
	//ifstream f1("podgorie.txt");
	//f1 >> p5;
	//cout << p5;


	//ofstream g1("angajati.txt");
	//g1 << a4;
	//g1.close();

	//Angajat a6;
	//ifstream f2("angajati.txt");
	//f2 >> a6;
	//cout << a6;

	//ofstream g2("orase.txt");
	//g2 << d4;
	//g2.close();
	//OraseDepozite d6;
	//ifstream f3("orase.txt");
	//f3 >> d6;
	//cout << d6;

	//ofstream g3("soiuri.txt");
	//g3 << s4;
	//g3.close();
	//cout << "\ns4::" << s4;
	//ifstream f4("soiuri.txt");
	//f4 >> s4;
	//cout << s4;

	//ofstream g4("vinuri.txt");
	//g4 << v4;
	//g4.close();
	//cout << v4;
	//Vinuri v5;
	//ifstream f5("vinuri.txt");
	//f5 >> v5;
	//cout << v5;

	//Podgorie** podgorie = new Podgorie * [4];
	//podgorie[0] = &p;
	//podgorie[1] = &p1;
	//podgorie[2] = &p2;
	//podgorie[3] = &p3;
	////for (int i = 0; i < 4; i++)
	////	cout<<"\n" << *podgorie[i];

	//Angajat** angajat = new Angajat * [3];
	//angajat[0] = &a;
	//angajat[1] = &a2;
	//angajat[2] = &a3;

	////for (int i = 0; i < 4; i++)
	////	cout << "\n" << *angajat[i];

	//OraseDepozite** orase = new OraseDepozite * [3];
	//orase[0] = &d4;
	//orase[1] = &d2;
	//orase[2] = &d3;
	///*for (int i = 0; i < 3; i++)
	//cout << "\n" << *orase[i];*/

	//Soiuri** soiuri = new Soiuri * [4];
	//soiuri[0] = &s;
	//soiuri[1] = &s1;
	//soiuri[2] = &s3;
	//soiuri[3] = &s2;
	////for (int i = 0; i < 4; i++)
	////	cout << "\n" << *soiuri[i];

	Vinuri** vinuri = new Vinuri * [3];
	vinuri[0] = &v;
	vinuri[1] = &v1;
	vinuri[2] = &v2;

	///*for (int i = 0; i < 3; i++)
	//	cout << "\n" << *vinuri[i];*/
	//int cifra, cifra1, cifra3;
	//cout << endl;
	//do
	//{
	//	cout << "\n1.Afisati componentele.\n2.Introduceti o noua componenta. \n";
	//	cin >> cifra;
	//	switch (cifra)
	//	{
	//	case 1:
	//		cout << "\n1.Afisati  lista podgoriilor. \n2.Afisati  lista angajatilor.\n3.Afisati  lista oraselor.\n4.Afisati  lista soiurilor.\n5.Afisati  lista vinurilor.\n";
	//		cin >> cifra1;
	//		switch (cifra1)
	//		{
	//		case 1:
	//			for (int i = 0; i < 4; i++)
	//				cout << "\n" << *podgorie[i];
	//			break;
	//		case 2:
	//			for (int i = 0; i < 4; i++)
	//				cout << "\n" << *angajat[i];
	//			break;
	//		case 3:
	//			for (int i = 0; i < 3; i++)
	//				cout << "\n" << *orase[i];
	//			break;
	//		case 4:
	//			for (int i = 0; i < 4; i++)
	//				cout << "\n" << *soiuri[i];
	//			break;
	//		case 5:
	//			for (int i = 0; i < 3; i++)
	//				cout << "\n" << *vinuri[i];
	//			break;
	//		}
	//		break;
	//	case 2:
	//		cout << "\n1.Introduceti o noua podgorie.\n2.Introduceti un nou angajat.\n3.Introduceti un nou oras;\n4.Introduceti un noi soi.\n5.Introduceti un nou vin.\n";
	//		cin >> cifra3;
	//		Podgorie p7;
	//		Angajat a7;
	//		OraseDepozite d7;
	//		Soiuri s7;
	//		Vinuri v7;
	//		switch (cifra3)
	//		{
	//		case 1:

	//			cin >> p7;
	//			break;
	//		case 2:

	//			cin >> a7;
	//			break;
	//		case 3:

	//			cin >> d7;
	//			break;
	//		case 4:

	//			cin >> s7;
	//			break;
	//		case 5:

	//			cin >> v7;
	//			break;
	//		}
	//	}

	//} while (cifra != 0);


	//string numee;
	//string numep;
	//string r;
	//string an1;
	//string nr1;
	//string supr3;
	//string supr1;
	//string supr2;

	//ifstream ip("data.csv");
	//while (ip.good())
	//{
	//	getline(ip, numee, ',');
	//	getline(ip, numep, ',');
	//	getline(ip, r, ',');
	//	getline(ip, an1, ',');
	//	getline(ip, nr1, ',');
	//	getline(ip, supr1, ',');
	//	getline(ip, supr2, ',');
	//	getline(ip, supr3, '\n');
	//	cout << "\nNumele podgoriei: " << numee;
	//	cout << "\nNumele proprietarului: " << numep;
	//	cout << "\nnr randuri: " << r << " " << " an: " << an1 << " nr soiuri: " << nr1;
	//	cout << "\nsupr: " << supr1 << " " << supr2 << " " << supr3;
	//}

	//string numea;
	//string varsta;
	//string salariu11;
	//string functie;
	//string nb;
	//string bon;
	//string bon1;

	//ifstream ip1("data1.csv");
	//while (ip1.good())
	//{

	//	getline(ip1, numea, ',');
	//	getline(ip1, varsta, ',');
	//	getline(ip1, salariu11, ',');
	//	getline(ip1, functie, ',');
	//	getline(ip1, nb, ',');
	//	getline(ip1, bon, ',');
	//	getline(ip1, bon1, '\n');

	//	cout << "\nNume angajat: " << numea << " varsta: " << varsta << " salariul: " << salariu11 << " functia: " << functie << " nr bonuri: " << nb;
	//	cout << " Bonuri: " << bon << " " << bon1 << "\n";
	//}

	//string numeor;
	//string nrde;
	//string sdep;
	//string sdep1;
	//ifstream ip2("data2.csv");
	//while (ip2.good())
	//{

	//	getline(ip2, numeor, ',');
	//	getline(ip2, nrde, ',');
	//	getline(ip2, sdep, ',');
	//	getline(ip2, sdep1, '\n');
	//	cout << "\nNume oras: " << numeor << " nr depozite: " << nrde << " supr: " << sdep << " " << sdep1 << "\n";
	//}


	//string numes;
	//string nrs;
	//string tips;
	//string tips1;
	//string prod1;
	//string prod2;
	//ifstream ip3("data3.csv");
	//while (ip3.good())
	//{

	//	getline(ip3, numes, ',');
	//	getline(ip3, nrs, ',');
	//	getline(ip3, tips, ',');
	//	getline(ip3, tips1, ',');
	//	getline(ip3, prod1, ',');
	//	getline(ip3, prod2, '\n');
	//	cout << "\nNume soi vin: " << numes << " nr soiuri: " << nrs << "tip soi: " << tips << " " << tips1 << "productie: " << prod1 << " " << prod2;

	//}

	//string cul;
	//string anprod1;
	//string nrt;
	//string tipv;
	//string tipv1;
	//string pret1;
	//string pret2;
	//ifstream ip4("data4.csv");
	//while (ip4.good())
	//{

	//	getline(ip4, cul, ',');
	//	getline(ip4, anprod1, ',');
	//	getline(ip4, nrt, ',');
	//	getline(ip4, tipv, ',');
	//	getline(ip4, tipv1, ',');
	//	getline(ip4, pret1, ',');
	//	getline(ip4, pret2, '\n');
	//	cout << "\nCuloare vin: " << cul << " an : " << anprod1 << "nr tip:  " << nrt << "tipuri " << tipv << "  " << tipv1 << " preturi: " << pret1 << " " << pret2;

	//}

   //faza3
//Vinuri** vinuri = new Vinuri * [3];
//vinuri[0] = &v;
//vinuri[1] = &v1;
//vinuri[2] = &v2;

            //******has a******//
      Crama cr("Bauer", vinuri, 3);
       cout << cr;
	   Crama cr1("Ba", vinuri, 2);
	   

	   //****is a****//
	   VApreciate va(v3, 15 , 10);
	   cout << "\nva: " << va;
	   
	   ALunii al(a, 10, "24-25 ian.2022");
	   cout << "\nal: " << al;

	   //virtualizare
	   Vinuri** listavin = new Vinuri * [2];
	   listavin[0] = &v3;
	   listavin[1] = &va;
	   
	   for (int i = 0; i < 2; i++)
	   {
		   float x[2];
		   x[i]= listavin[i]->medie(2);
		 cout<<"\n" << x[i];
		
	   }
	   Angajat** listaang = new Angajat * [2];
	   listaang[0] = &a;
	   listaang[1] = &al;
	   listaang[0]->pensie();
	   listaang[1]->pensie();
	   VVandute va1(v3, "calitate superioara");
	   cout << "\n va1: " << va1;
	   
	   VPremiate vpr(va, 4); cout << endl;
	   cout << "\nvpr:" << vpr;
	 /*  Vinuri** listavin1 = new Vinuri * [3];
	   listavin1[0] = &v3;
	   listavin1[1] = &va;
	   listavin1[2] = &va1;
	   for (int i = 0; i < 3; i++)
		   cout << *listavin1[i];*/

	   //STL

	   vector<Podgorie> vP;
	   vP.push_back(p2);
	   vP.push_back(p);
	   cout << endl;
	   vector<Podgorie>::iterator itP;
	   for (itP = vP.begin(); itP != vP.end(); itP++)
	   {
		   cout << *itP << " ";
	   }

	   vector<Angajat> vA;
	   vA.push_back(a);
	   vA.push_back(a2);
	   cout << endl;
	   vector<Angajat>::iterator itA;
	   for (itA = vA.begin(); itA != vA.end(); itA++)
	   {
		   cout << *itA << " ";
	   }
	   vector<OraseDepozite> vO;
	   vO.push_back(d4);
	   vO.push_back(d2);
	   cout << endl;
	   vector<OraseDepozite>::iterator itO;
	   for (itO = vO.begin(); itO != vO.end(); itO++)
	   {
		   cout << *itO << " ";
	   }
	   list<Vinuri> lV;
	   lV.push_back(v1);
	   lV.push_back(v2);
	   lV.push_front(v3);
	   list<Vinuri>::iterator itV;
	   for (itV = lV.begin(); itV != lV.end(); itV++)
		   cout << *itV;
	   list<Soiuri> lS;
	   lS.push_back(s1);
	   lS.push_back(s2);
	   lS.push_front(s3); cout << endl;
	   list<Soiuri>::iterator itS;
	   for (itS = lS.begin(); itS != lS.end(); itS++)
		   cout << *itS;
	   set<Crama> sC;
	   sC.insert(cr);
	   sC.insert(cr1);
	   set<Crama>::iterator itC;
	   for (itC = sC.begin(); itC != sC.end(); itC++)
		   cout << *itC;
	   map<int, Podgorie> mAL;
	   mAL[0] = p2;
	   mAL[5] = p;
	  
	   cout << endl;
	   map<int, Podgorie>::iterator itAL;
	   for (itAL = mAL.begin(); itAL != mAL.end(); itAL++)
		   cout << itAL->first << " " << itAL->second << endl;

	return 0;
}