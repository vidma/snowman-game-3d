/******************************************************************
 * Parser -
 * Fabrice Aubert
*/



#ifndef INC_PARSER_H
#define INC_PARSER_H


#include <stdlib.h>
#include <string>
#include <map>
#include <fstream>
#include <vector>


namespace prog3d {


	const int CASE_SENSITIVE=0x0001;
	const int EOL_TOKEN=0x0010;

	typedef enum{NATUREL,REEL,INCONNU,CHAINE,P_EOL,FIN} Token;

	class Lexer {
		std::fstream f;
		bool endline;         // si fin de ligne = token
		bool sensitive;       // si sensible à la casse
		Token le_token;       // token courant
		// valeurs token courant :
		std::string la_chaine;
		float le_float;
		int le_int;
		double le_reel;
		char le_car;

		// euh, je ne sais plus
		bool the_end;

		// nombre lignes lues (debug)
		int nb_ligne;

		bool skipCar();
		bool estSeparateur();

	public:
		Lexer(std::string nom,int mode=0);
		~Lexer();


		void check();
		bool isEnd();
		bool isEol();

		void skipNaturel();
		void skipNombre();
		void skipToken();
		void skipEol();

		bool isDigit();
		Token &token() {return le_token;}

		std::string chaine() {return la_chaine;}
		int entier() {return le_int;}
		double reel() {return le_reel;}

		void lireLigne();
		void passerEspaceLigne();
		void passerAcco();




		inline int nbLigne() {return nb_ligne;}
	};


 class Parser {

		Lexer lex;

	protected:
		std::map<std::string,Token> mots;
	public:
		Parser(std::string nom,int mode=0);
		virtual ~Parser();

		Lexer &lexer() {return lex;}

		virtual void skipToken();
		void analyse(int debut=0,int fin=0);

		int lireEntier();
		double lireReel();
		Token token() {return lex.token(); }
		std::string sToken() {return lex.chaine(); }
		void lireLigne() {lex.lireLigne(); }


};








}; // namespace MM_PARSER

#endif
