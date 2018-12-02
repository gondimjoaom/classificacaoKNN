#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class Individuo
{
private:
	string classe, name;
	double a, b, c, d, e, f, g;

public:
	Individuo(string name, double a, double b, double c, double d, double e, double f, double g, string classe)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
    this->e = e;
    this->f = f;
    this->g = g;
    this->name = name;
		this->classe = classe;
	}

	string getClasse()
	{
		return classe;
	}

  string getName()
	{
		return name;
	}

	double getA()
	{
		return a;
	}

	double getB()
	{
		return b;
	}

	double getC()
	{
		return c;
	}

	double getD()
	{
		return d;
	}

  double getE()
	{
		return e;
	}

  double getF()
	{
		return f;
	}

  double getG()
	{
		return g;
	}
};

double obterDistEuclidiana(Individuo ind1, Individuo ind2)
{

	double soma = pow((ind1.getA() - ind2.getA()), 2) +
				  pow((ind1.getB() - ind2.getB()), 2) +
				  pow((ind1.getC() - ind2.getC()), 2) +
				  pow((ind1.getD() - ind2.getD()), 2) +
          pow((ind1.getE() - ind2.getE()), 2) +
          pow((ind1.getF() - ind2.getF()), 2) +
          pow((ind1.getG() - ind2.getG()), 2);

	return sqrt(soma);
}

string classificarAmostra(vector<Individuo>& individuos,
						  Individuo novo_exemplo, int K)
{
	if(K % 2 == 0)
	{
		K--;
		if(K <= 0)
			K = 1;
	}

	int tam_vet = individuos.size();

	set<pair<double, int> > dist_individuos; //usar o set garante que os elementos serão inseridos em ordem de distância

	for(int i = 0; i < tam_vet; i++)
	{
		double dist = obterDistEuclidiana(individuos[i], novo_exemplo);
		dist_individuos.insert(make_pair(dist, i));
	}

	set<pair<double, int> >::iterator it; //setando um iterator para correr no set de dist_individuos

	vector<int> cont_classes(8);

	int contK = 0;

	for(it = dist_individuos.begin(); it != dist_individuos.end(); it++)
	{ //essa iteração começa sempre do conjunto de distância menor para o novo_exemplo
		if(contK == K) break;

		string classe = individuos[it->second].getClasse(); //o índice do individuo é pego no set, o que faz com que o
                                                        //o seja o mais próximo de novo_exemplo a cada iteração de it.

		if(classe == "cp") cont_classes[0]++;
		else if(classe == "im") cont_classes[1]++;
		else if(classe == "pp") cont_classes[2]++;
    else if(classe == "imU") cont_classes[3]++;
    else if(classe == "om") cont_classes[4]++;
    else if(classe == "omL") cont_classes[5]++;
    else if(classe == "imL") cont_classes[6]++;
    else cont_classes[7]++;

		contK++;
	}

	string classe_classificacao;

	if(cont_classes[0] >= cont_classes[1] && cont_classes[0] >= cont_classes[2] && cont_classes[0] >= cont_classes[3]
    && cont_classes[0] >= cont_classes[4] && cont_classes[0] >= cont_classes[5] && cont_classes[0] >= cont_classes[6]
    && cont_classes[0] >= cont_classes[7])
		classe_classificacao = "cp";
	else if(cont_classes[1] >= cont_classes[0] && cont_classes[1] >= cont_classes[2] && cont_classes[1] >= cont_classes[3]
    && cont_classes[1] >= cont_classes[4] && cont_classes[1] >= cont_classes[5] && cont_classes[1] >= cont_classes[6]
    && cont_classes[1] >= cont_classes[7])
		classe_classificacao = "im";
  else if(cont_classes[2] >= cont_classes[0] && cont_classes[2] >= cont_classes[1] && cont_classes[2] >= cont_classes[3]
    && cont_classes[2] >= cont_classes[4] && cont_classes[2] >= cont_classes[5] && cont_classes[2] >= cont_classes[6]
    && cont_classes[2] >= cont_classes[7])
    classe_classificacao = "pp";
  else if(cont_classes[3] >= cont_classes[0] && cont_classes[3] >= cont_classes[1] && cont_classes[3] >= cont_classes[2]
    && cont_classes[3] >= cont_classes[4] && cont_classes[3] >= cont_classes[5] && cont_classes[3] >= cont_classes[6]
    && cont_classes[3] >= cont_classes[7])
    classe_classificacao = "imU";
  else if(cont_classes[4] >= cont_classes[0] && cont_classes[4] >= cont_classes[1] && cont_classes[4] >= cont_classes[2]
    && cont_classes[4] >= cont_classes[3] && cont_classes[4] >= cont_classes[5] && cont_classes[4] >= cont_classes[6]
    && cont_classes[4] >= cont_classes[7])
    classe_classificacao = "om";
  else if(cont_classes[5] >= cont_classes[0] && cont_classes[5] >= cont_classes[1] && cont_classes[5] >= cont_classes[2]
    && cont_classes[5] >= cont_classes[3] && cont_classes[5] >= cont_classes[4] && cont_classes[5] >= cont_classes[6]
    && cont_classes[5] >= cont_classes[7])
    classe_classificacao = "omL";
  else if(cont_classes[6] >= cont_classes[0] && cont_classes[6] >= cont_classes[1] && cont_classes[6] >= cont_classes[2]
    && cont_classes[6] >= cont_classes[3] && cont_classes[6] >= cont_classes[4] && cont_classes[6] >= cont_classes[5]
    && cont_classes[6] >= cont_classes[7])
    classe_classificacao = "imL";
	else
		classe_classificacao = "imS";

	return classe_classificacao;
}

int main(int argc, char *argv[])
{

	vector<Individuo> individuos;

	int K;
	int tam_treinamento;
	int tam_testes;


	int base;

	cout << "Digite 1 para entrar com a base de dados manualmente." << endl;
	cout << "Digite 2 para usar a base de dados Ecoli Dataset." << endl;
	cin >> base;

	if (base == 1){
		cout << "Qual será o tamnho do conjunto de treinamento? ";
		cin >> tam_treinamento;
		cout << "Digite o conjunto de treinamento. Obs.: siga a ordem: nome, atributo1..atributo7, classe:" << endl;
		for(int i = 0; i < tam_treinamento; i++)
		{
			cout << "Dado " << i + 1 << " :" <<endl;
			string classe, name;
			double a, b, c, d, e, f, g;

			cin >> name >> a >> b >> c >> d >> e >> f >> g >> classe;

			individuos.push_back(Individuo(name, a, b, c, d, e, f, g, classe));
		}

		cout << "Entre com o valor dos K vizinhos a serem levados em conta: ";
		cin >> K;

		cout << "Quantos testes serão executados?";
		cin >> tam_testes;

		int acertos = 0;


		for(int i = 0; i < tam_testes; i++)
		{
			cout << "Entre com o caso de teste para classificação. Obs.: siga a ordem: nome, atributo1..atributo7, classe: ";
			string classe, name;
			double a, b, c, d, e, f, g;

	    cin >> name >> a >> b >> c >> d >> e >> f >> g >> classe;

			Individuo ind(name, a, b, c, d, e, f, g, classe);

			string classe_obtida = classificarAmostra(individuos, ind, K);

			cout << "Classe esperada: " << classe << "\n";
			cout << "Classe obtida: " << classe_obtida << "\n\n";

			if(classe == classe_obtida)
				acertos++;
		}

		cout << acertos << " acertos de um total de " << tam_testes << " testes.\n";
	}

	else if (base == 2){
		int acertos = 0;
		cout << "Utilizando o Dataset Ecoli! Localizado em ecoliTreino.txt.]" << endl;
		cout << "Entre com o valor dos K vizinhos a serem levados em conta: ";
		cin >> K;
		ifstream file("ecoliTreino.txt", ios::in);
		string name, classe;
		double a, b, c, d, e, f, g;
		if (!file) cerr << "Dataset não encontrado!" << '\n';
		while (file >> name >> a >> b >> c >> d >> e >> f >> g >> classe){
			individuos.push_back(Individuo(name, a, b, c, d, e, f, g, classe));
		}

		cout << "Casos de teste de classificação em ecoliTeste.txt." << endl;
		ifstream file2("ecoliTeste.txt", ios::in);
		if (!file) cerr << "Dataset não encontrado!" << '\n';
		int size = 0;
		while (file2 >> name >> a >> b >> c >> d >> e >> f >> g >> classe){
			size++;
			individuos.push_back(Individuo(name, a, b, c, d, e, f, g, classe));
			Individuo ind(name, a, b, c, d, e, f, g, classe);
			string classe_obtida = classificarAmostra(individuos, ind, K);

			cout << "Classe esperada: " << classe << "\n";
			cout << "Classe obtida: " << classe_obtida << "\n\n";

			if(classe == classe_obtida)
				acertos++;
		}
		cout << acertos << " acertos de um total de " << size << " testes.\n";
	}

	return 0;
}
