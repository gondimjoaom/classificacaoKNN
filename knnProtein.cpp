// Implementa��o do k-NN (k-nearest neighbors algorithm)

#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <map>

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

// fun��o que retorna a dist�ncia euclidiana entre 2 indiv�duos
double obterDistEuclidiana(Individuo ind1, Individuo ind2)
{
	/*
		a dist�ncia euclidiana � a raiz quadrada da soma das
		diferen�as dos valores dos atributos elevado ao quadrado
	*/

	double soma = pow((ind1.getA() - ind2.getA()), 2) +
				  pow((ind1.getB() - ind2.getB()), 2) +
				  pow((ind1.getC() - ind2.getC()), 2) +
				  pow((ind1.getD() - ind2.getD()), 2) +
          pow((ind1.getE() - ind2.getE()), 2) +
          pow((ind1.getF() - ind2.getF()), 2) +
          pow((ind1.getG() - ind2.getG()), 2);

	return sqrt(soma);
}

// essa fun��o classifica uma nova amostra
string classificarAmostra(vector<Individuo>& individuos,
						  Individuo novo_exemplo, int K)
{
	// se o K for par decrementa
	if(K % 2 == 0)
	{
		K--;
		if(K <= 0)
			K = 1;
	}

	// obt�m o tamanho do vetor
	int tam_vet = individuos.size();

	/*
		set de pairs da dist�ncia de cada indiv�duo
		do conjunto de treinamento para o novo exemplo
		cada pair � composto pela dist�ncia e o �ndice
		do indiv�duo no vetor
	*/
	set<pair<double, int> > dist_individuos; //usar o set garante que os elementos serão inseridos em ordem de distância

	/*
		calcula-se a dist�ncia euclidiana do novo exemplo
		para cada amostra do conjunto de treinamento
	*/
	for(int i = 0; i < tam_vet; i++)
	{
		double dist = obterDistEuclidiana(individuos[i], novo_exemplo);
		dist_individuos.insert(make_pair(dist, i));
	}
	/*
	para decidir a qual classe pertence o novo exemplo,
	basta verificar a classe mais frequente dos K
	vizinhos mais pr�ximos
	*/
	set<pair<double, int> >::iterator it; //setando um iterator para correr no set de dist_individuos

	/*
		o contador de Iris-setosa estar� no �ndice 0,
		o contador de Iris-versicolor estar� no �ndice 1
		e o contador de Iris-virginica estar� no �ndice 2
	*/
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
  /*set<int> contadorClasses;
  for (int y = 0; y < 8; y++) {
    contadorClasses.insert(cont_classes[y]);
  }

  if (*contadorClasses.begin() == cont_classes[0]) classe_classificacao = "cp";
  else if (*contadorClasses.begin() == cont_classes[1]) classe_classificacao = "im";
  else if (*contadorClasses.begin() == cont_classes[2]) classe_classificacao = "pp";
  else if (*contadorClasses.begin() == cont_classes[3]) classe_classificacao = "imU";
  else if (*contadorClasses.begin() == cont_classes[4]) classe_classificacao = "om";
  else if (*contadorClasses.begin() == cont_classes[5]) classe_classificacao = "omL";
  else if (*contadorClasses.begin() == cont_classes[6]) classe_classificacao = "imL";
  else classe_classificacao = "imS"; */

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

	/*
		o K � a quantidade de vizinhos que ser�o
		levados em conta para classifica��o de um
		novo dado, � recomend�vel que seja �mpar
		para que n�o possa haver empate
	*/
	int K = 3;

	// tamanho do conjunto de dados de treinamento
	int tam_treinamento = 300;

	/*
		o processo de treinamento consiste em apenas
		armazenar o conjunto de dados de treinamento
	*/
	for(int i = 0; i < tam_treinamento; i++)
	{
		string classe, name;
		double a, b, c, d, e, f, g;

		cin >> name >> a >> b >> c >> d >> e >> f >> g >> classe;

		individuos.push_back(Individuo(name, a, b, c, d, e, f, g, classe));
	}

	int acertos = 0;
	int tam_testes = 336 - tam_treinamento;

	// processo de classifica��o
	for(int i = 0; i < tam_testes; i++)
	{
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

	return 0;
}
