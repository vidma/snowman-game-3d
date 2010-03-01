#include <string>
#include "Parser.h"
#include "math.h"
#include <iostream>

using namespace prog3d;
using namespace std;

static void erreur(string mesg) {
  cout << "ERREUR PARSER : " << mesg << endl;
  exit(1);
}

static char minuscule(char c) {
	if ((c<='Z') && (c>='A')) return (c-'A')+'a';
	else return c;
}

// ************************************************
// LEXER
// ************************************************

Lexer::Lexer(std::string nom,int mode) {
  the_end=false;
  endline=((mode & EOL_TOKEN)!=0);
  nb_ligne=0;
  sensitive=((mode & CASE_SENSITIVE)!=0);
  f.open(nom.c_str(),fstream::binary | fstream::in);
  if (!f.is_open()) erreur("OUVERTURE FICHIER");
  skipCar();
}

Lexer::~Lexer() {
  printf("nb lignes analysee fichier = %d\n",nb_ligne);
  f.close();
}

bool Lexer::isEnd() {
  return f.eof();
}

bool Lexer::isEol() {
  if (isEnd()) return true;
  if (le_car==char(13)) {
    skipCar();
  }
  if (le_car==char(10))
    return true;
	else return false;
}

void Lexer::skipEol() {
  if (le_car==char(13))
    skipCar();
  if (le_car==char(10))
    skipCar();
}


void Lexer::passerEspaceLigne() {
	if (endline)
		while (le_car==' ') {
			skipCar();
		}
	else
       while ((le_car==' ') || isEol()) {
           if (isEol()) {
              nb_ligne++;
              skipEol();
           }
           else
             skipCar();
	   }

}

void Lexer::lireLigne() {
	while (!isEol()) skipCar();
	skipCar();
}

bool Lexer::skipCar() {
  if (f.eof()) {
    le_token=FIN;
    the_end=true;
    le_car='\0';
    return false;
  }
  f.read(&le_car,1);
  if (!sensitive) le_car=minuscule(le_car);
  return true;
}


bool Lexer::isDigit() {
  return (((le_car<='9') && (le_car>='0')));
}

bool Lexer::estSeparateur() {
  switch (le_car) {
  case '(': case ')': case';': case ' ': case '{': case '}': case char(10) : case char(13) :
  case '/':
  return true;break;
  default:return false;
  }
}


void Lexer::skipNaturel() {
	  le_int=0;
	  int signe=1;
	  if (le_car=='-') signe=-1;
      if ((le_car=='-') || (le_car=='+')) skipCar();
	  if (!isDigit()) erreur("skipNaturel");
	  while (isDigit()) {
		  le_int=le_int*10+((int)(le_car-'0'));
		  skipCar();
	  }
	  le_int=le_int*signe;
  }


void Lexer::skipNombre() {
	le_reel=0.0;
  le_token=NATUREL;
	double signe=1.0;
	if (le_car=='-') signe=-1.0;
	if (isDigit() || (le_car=='-') || (le_car=='+')) skipNaturel();
	if (le_car=='.') {
		double frac,puis;
		frac=0.0; puis=1;
		le_token=REEL;
		skipCar();
		le_reel=(double)le_int;
		while (isDigit()) {
          puis=puis/10.0;
          le_reel=le_reel+signe*(double)((int)(le_car-'0'))*puis;
		  skipCar();
		}
	}
  if (le_car=='e') {
		le_token=REEL;
	  skipCar();
	  skipNaturel();
	  le_reel=le_reel*pow(10,float(le_int));
	}
}





void Lexer::check() {
	switch(le_token) {
	case INCONNU:cout << "sans semantique = " << la_chaine << "(special = " << int(la_chaine[0]) << ")" << endl;break;
	case REEL:cout << "reel = " << le_reel << endl; break;
	case NATUREL:cout << "naturel = "<< le_int << endl;break;
	case FIN:cout << "FIN" << endl ;break;
	case CHAINE:
		cout << "CHAINE = " << la_chaine << endl;
		break;

	default:
		cout << "semantique : " << la_chaine << endl;
	}
}


void Lexer::skipToken() {
  la_chaine="";
  le_token=INCONNU;
  passerEspaceLigne();
  if (isEnd()) {
    le_token=FIN;
    goto fin;
  }
  if (isEol()) {
    nb_ligne++;
    if (endline) le_token=P_EOL;
    else le_token=INCONNU;
    skipEol();
    goto fin;
  }
  if (estSeparateur()) {
    la_chaine+=le_car;
    le_token=INCONNU;
    skipCar();
    goto fin;
  }
  if ((isDigit()) || (le_car=='.') || (le_car=='+') || (le_car=='-')) {
    skipNombre();
    goto fin;
  }
	if (le_car=='"') {
		skipCar();
		while (le_car!='"') {
			if (isEnd()) erreur("Lecture chaine constante non terminée\n");
			la_chaine+=le_car;
			skipCar();
		}
		skipCar();
		le_token=CHAINE;
		goto fin;
	}
  while (!estSeparateur()) {
    la_chaine+=le_car;
    skipCar();
  }
fin:
  return;
}


// *********************************************************************
// PARSER
// *********************************************************************


// mode -> CASE_SENSITIVE | EOL_TOKEN (non par défaut)
Parser::Parser(string nom,int mode) : lex(nom,mode) {
	// NE PAS FAIRE SKIPTOKEN ICI (le faire dans les classes dérivées) !!!
	cout << "******************************\n";
	cout << "Parsing "<< nom << endl;
}

void Parser::analyse(int debut,int fin) {
  while (!lex.isEnd()) {
    lex.skipToken();
    if (((lex.nbLigne()>=debut) || (debut==0)) && (fin==0 || (lex.nbLigne()<=fin)))
      lex.check();
  }
  cout << "nb_ligne : " << lex.nbLigne() << endl;
}

Parser::~Parser() {
	cout << "*******************************\n";
}

int Parser::lireEntier() {
	int res=0;
	if (lexer().token()==NATUREL) {
		res=lexer().entier();
	}
	else erreur("entier attendu");
	skipToken();
	return res;
}

double Parser::lireReel() {
	double res=0.0;
	if (lexer().token()==REEL) {
		res=lexer().reel();
	}
	else if (lexer().token()==NATUREL) {
		res=float(lexer().entier());
	}
	else erreur("reel attendu");
	skipToken();
	return res;
}




void Parser::skipToken() {
	lex.skipToken();
//	cout << "sToken : " << sToken() << endl;
}

// ***********************************************************************************

