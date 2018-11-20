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
	string classe;
	double a, b, c, d;

public:
	Individuo(double a, string classe)
	{
		this->a = a;
		this->classe = classe;
	}

	string getClasse()
	{
		return classe;
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
};

// fun��o que retorna a dist�ncia euclidiana entre 2 indiv�duos
double obterDistEuclidiana(Individuo ind1, Individuo ind2)
{
	/*
		a dist�ncia euclidiana � a raiz quadrada da soma das
		diferen�as dos valores dos atributos elevado ao quadrado
	*/
	
	double soma = pow((ind1.getA() - ind2.getA()), 2);
	
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
	set<pair<double, int> > dist_individuos;

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
	set<pair<double, int> >::iterator it;
	
	/*
		o contador de Iris-setosa estar� no �ndice 0,
		o contador de Iris-versicolor estar� no �ndice 1
		e o contador de Iris-virginica estar� no �ndice 2
	*/
	vector<int> cont_classes(5);
	
	int contK = 0;

	for(it = dist_individuos.begin(); it != dist_individuos.end(); it++)
	{
		if(contK == K) break;
		
		string classe = individuos[it->second].getClasse();

		if(classe == "OTIMO")
			cont_classes[0]++;
		else if(classe == "MUITOBOM")
			cont_classes[1]++;
		else if (classe == "BOM")
			cont_classes[2]++;
		else if (classe == "REGULAR")
			cont_classes[3]++;
		else
			cont_classes[4]++;

		contK++;
	}
	
	string classe_classificacao;
	
	if(cont_classes[0] >= cont_classes[1] && cont_classes[0] >= cont_classes[2] && cont_classes[0] >= cont_classes[3] && cont_classes[0] >= cont_classes[4])
		classe_classificacao = "OTIMO";
	else if(cont_classes[1] >= cont_classes[0] && cont_classes[1] >= cont_classes[2] && cont_classes[1] >= cont_classes[3] && cont_classes[1] >= cont_classes[4])
		classe_classificacao = "MUITOBOM";
	else if(cont_classes[2] >= cont_classes[0] && cont_classes[2] >= cont_classes[1] && cont_classes[2] >= cont_classes[3] && cont_classes[2] >= cont_classes[4])
		classe_classificacao = "BOM";
	else if(cont_classes[3] >= cont_classes[0] && cont_classes[3] >= cont_classes[1] && cont_classes[3] >= cont_classes[2] && cont_classes[3] >= cont_classes[4])
		classe_classificacao = "REGULAR";
	else
		classe_classificacao = "IRRELEVANTE";

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
	int tam_treinamento = 265187;

	/*
		o processo de treinamento consiste em apenas
		armazenar o conjunto de dados de treinamento
	*/
	//for(int i = 0; i < tam_treinamento; i++)
	string classe = "";
	do
	{
		string classe;
		double a, b, c, d;

		cin >> a;
		cin >> classe;
		if (classe == "OTIMO" || classe == "MUITOBOM" || classe == "BOM" || classe == "REGULAR" || classe == "IRRELEVANTE")
			individuos.push_back(Individuo(a, classe));
	} while (classe != "pare");

	int acertos = 0;
	int tam_testes = 174536;
	
	// processo de classifica��o
	//for(int i = 0; i < tam_testes; i++)
	double a = -2;
	do
	{
		string classe = "unknown";
		double a, b, c, d;

		cin >> a;
		
		Individuo ind(a, classe);
		
		string classe_obtida = classificarAmostra(individuos, ind, K);
		
		cout << "Classe esperada: " << classe << "\n";
		cout << "Classe obtida: " << classe_obtida << "\n\n";
		
		if(classe == classe_obtida)
			acertos++;
	} while (a != -1);
	
	cout << acertos << " acertos de um total de " << tam_testes << " testes.\n";

	return 0;
}
