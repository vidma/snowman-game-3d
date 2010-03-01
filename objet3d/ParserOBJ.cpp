#include "ParserOBJ.h"
#include "Soup.h"
#include <iostream>

using namespace std;

using namespace prog3d;


static void erreur(string s) {
  cout << "Erreur dans parserOBJ.cpp : " << endl;
  cout << s << endl;
  exit(1);
}

ParserOBJ::ParserOBJ(std::string nom) : Parser(nom,EOL_TOKEN) {
    skipToken();
}

Soup *ParserOBJ::load() {
    Soup *o=new Soup;
    load(o);
    return o;
}

void ParserOBJ::load(Soup *o) {
  Facet *f;
  Vertex *v;
  Vector3d *n;
  while (token()!=FIN) {
    if (sToken()=="#") {
        lireLigne();
    }
    if (sToken()=="vn") {
      n=new Vector3d;
      skipToken();
      o->addNormal(n);
      int k=0;
      while (token()!=P_EOL) {
        if (token()==REEL) n->set(k,lireReel());
        else n->set(k,double(lireEntier()));
          k++; if (k>3) erreur("lecture normale avec plus de 3 composantes !!!");
        }
    }
    if (sToken()=="f") {
        skipToken();
        f=o->createFacet();
        int a[2];
        while (token()!=P_EOL) {
           f->addVertex(o->getVertex(lireEntier()-1));
           if (sToken()=="/") {
             int k=0;
             skipToken();
             if (sToken()=="/") {skipToken(); k++;}
             a[k]=lireEntier();k++;
             if (sToken()=="/") {
               skipToken();
               a[k]=lireEntier();k++;
             }
             if (k==2) f->addNormal(o->getNormal(a[1]-1));
           }
        }
    }
    if (sToken()=="v") {
        skipToken();
        v=o->createVertex();
        Point3d p;
        int k=0;
        while (token()!=P_EOL) {
          if (token()==REEL) p.set(k,lireReel());
          else p.set(k,double(lireEntier()));
          k++; if (k>3) erreur("lecture sommet avec plus de 3 composantes !!!");
        }
        v->setPoint(p);
    }

    skipToken();
  }
}
