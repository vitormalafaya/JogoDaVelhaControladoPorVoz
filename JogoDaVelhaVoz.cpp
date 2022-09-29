#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
char quadrado[9] = { '0','1','2','3','4','5','6','7','8' };

auto autenticacao = SpeechConfig::FromSubscription("", ""); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
int marcador(int jogador, int lugar)
{
	if (jogador == 1)
	{
		if(quadrado[lugar]=='X'||quadrado[lugar]=='O'){
			return 1;
		}
		else {
			quadrado[lugar] = 'X';
			return 0;
		}

	}
	else {
		if (quadrado[lugar] == 'X' || quadrado[lugar] == 'O') {
			return 1;
		}
		else {
			quadrado[lugar] = 'O';
			return 0;
		}
	}
}
void display()
{
	for (int i = 0; i < 9; i++)
	{
		cout << quadrado[i] << "\t";
		if (i == 2 || i == 5 || i == 8)
			cout << "\n\n";
	}
}
void texto_em_fala(string Texto)
{
	cout << Texto + "\n";
	requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}
// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
	auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
	cout << resultado->Text + "\n";
	return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}
int validarvenc() // Função para validar o vencedor
{
	if (quadrado[0] == quadrado[1] && quadrado[1] == quadrado[2])
	{
		if (quadrado[0] == 'X')
			return 1;
		else
			return 2; // Preenchimento da tabela
	}
	else
		if (quadrado[3] == quadrado[4] && quadrado[4] == quadrado[5])
		{
			if (quadrado[3] == 'X')
				return 1;
			else
				return 2;
		}
		else
			if (quadrado[6] == quadrado[7] && quadrado[7] == quadrado[8])
			{
				if (quadrado[6] == 'X')
					return 1;
				else
					return 2;
			}
			else
				if (quadrado[0] == quadrado[3] && quadrado[3] == quadrado[6])
				{
					if (quadrado[0] == 'X')
						return 1;
					else
						return 2;
				}
				else
					if (quadrado[1] == quadrado[4] && quadrado[4] == quadrado[7])
					{
						if (quadrado[1] == 'X')
							return 1;
						else
							return 2;
					}
					else
						if (quadrado[2] == quadrado[5] && quadrado[5] == quadrado[8])
						{
							if (quadrado[2] == 'X')
								return 1;
							else
								return 2;
						}
						else
							if (quadrado[0] == quadrado[4] && quadrado[4] == quadrado[8])
							{
								if (quadrado[0] == 'X')
									return 1;
								else
									return 2;
							}
							else
								if (quadrado[2] == quadrado[4] && quadrado[4] == quadrado[6])
								{
									if (quadrado[2] == 'X')
										return 1;
									else
										return 2;
								}
								else
									if (quadrado[0] == quadrado[3] && quadrado[3] == quadrado[6])
									{
										if (quadrado[0] == 'X')
											return 1;
										else
											return 2;
									}
									else
										return 0;
}
int main()
{
	cout << "--------------------------------------------------------------\n";
	cout << "|                         JOGO DA VELHA DO VITAO              |\n";
	string key = "", region = ""; // ENTRADA DA CHAVE DO RECURSO // ENTRADA DA REGIÃO EM QUE O RECURSO FOI HOSPEDADO
	cout << "--------------------------------------------------------------\n\n";
	display();
	autenticacao = SpeechConfig::FromSubscription(key, region);         //  AUTENTICAÇÃO DO RECURSO COM A CHAVE E REGIÃO INFORMADOS PELO USUÁRIO
	autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS
	autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS
	autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA
	requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES
	requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


	// Execução do jogo pegando as informações e passando para função e retornando a vitoria do player1 ou player2
		try
	{
		string lug;
		int jogador1 = 1, jogador2 = 2;
		int lugar, resultado = 0, flag = 0;

		for (int i = 1; i < 5; i++) // Preenche todas as casas requisitadas pelos players com X(Player 1) e O(Player 2)
		{


			cout << "\n";
			// Jeito que achamos da API Entender 0 e 1
			int auxi;
			do {

				int ax = 0;
				do {
					texto_em_fala("\nJogador 1, Qual casa voce quer preencher(numeros de 0 a 8): ");

					lug = fala_em_texto();

					// Jeito que achamos da API Entender 0 e 1 e barrar numeros fora
					if (lug == "Zero.")
					{
						ax = 1;
						lugar = 0;
					}
					else if (lug == "Um.")
					{
						ax = 1;
						lugar = 1;
					}
					else if (lug == "2." || lug == "3." || lug == "4." || lug == "5." || lug == "6." || lug == "7." || lug == "8.") {
						ax = 1;
						lugar = stoi(lug);
					}
					else {
						texto_em_fala("valor inválido");
					}
				} while (ax == 0);
				auxi=marcador(jogador1, lugar);
				if (auxi==1){
					texto_em_fala("ja está preenchida");
			}
			} while (auxi==1);

			display();

			resultado = validarvenc();
			if (resultado == 1)
			{
				texto_em_fala("Parabens jogador 1 voce ganhou!!!");
				flag = 1;
				break;
			}
			else
				if (resultado == 2)
				{
					texto_em_fala("Parabens jogador 2 voce ganhou!!!");
					flag = 1;
					break;
				}
			do {
				int aux = 0;
				do {
					texto_em_fala("\nJogador 2, Qual casa voce quer preencher(numeros de 0 a 8): ");

					lug = fala_em_texto();

					// Jeito que achamos da API Entender 0 e 1 barrar numeros fora
					if (lug == "Zero.")
					{
						aux = 1;
						lugar = 0;
					}
					else if (lug == "Um.")
					{
						aux = 1;
						lugar = 1;
					}
					else if (lug == "2." || lug == "3." || lug == "4." || lug == "5." || lug == "6." || lug == "7." || lug == "8.") {
						aux = 1;
						lugar = stoi(lug);
					}
					else {
						texto_em_fala("valor inválido");
					}
				} while (aux == 0);
				auxi=marcador(jogador2, lugar);
				if (auxi == 1) {
					texto_em_fala("ja está preenchida");
				}
			} while (auxi == 1);
			display();
			resultado = validarvenc();
			if (resultado == 1)
			{
				texto_em_fala ("Parabens jogador 1 voce ganhou!!!");
				flag = 1;
				break;
			}
			else
				if (resultado == 2)
				{
					texto_em_fala("Parabens jogador 2 voce ganhou!!!");
					flag = 1;
					break;
				}
		}
		if (flag == 0)
			texto_em_fala (" \n eita, temos um empate ");
	}

	catch (exception e)
	{
		cout << e.what();
	}
	return 0;
}
