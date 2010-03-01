#ifndef INC_TEXTURE_H
#define INC_TEXTURE_H

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <string>
#include "Color.h"
#include "Point2d.h"

/**
@file
@author F. Aubert
@brief opérations sur les textures
*/


namespace prog3d {
/**
@class Texture
@brief représentation d'une texture (utilise openIL www.openil.sourceforge.net)
*/
class Texture {
    static bool isILInit;
    GLuint width,height,format,bpp;
    ILuint imgId;
	GLuint texId;
	GLuint filtre;
	unsigned int border;
	int niveau;
	void init();
public:
    /// constructeur par défaut (identifiants nuls)
    Texture();
    /// construction à partir d'un fichier image
	Texture(std::string nom);
	/// initialise la taille de la texture (image vide)
	void init(int w,int h);

	void mipMap(char *nom);
	/// affecte l'image de la texture avec le fichier nom
	void read(std::string nom);
	/// donne la taille en pixels sur s
	int getWidth() const;
	/// donne la taille en pixels sur t
	int getHeight() const;
	/// donne un pointeur sur un tableau d'octets représentant l'image (allocation)
	GLubyte *getImageCopy();
	/// recopie dans l'image de la texture les pixels donnés par img
	void copyFrom(GLubyte *img,unsigned int width=0,unsigned int height=0);

	/*
	void changeImage(char *nom);
	void changeFiltre();
	void changeNiveau();
	*/
	/// spécifie s'il y a un bord ou non (1 ou 0) : doit être spécifier *avant* un read ou un init
	void setBorder(unsigned int b);

    /// la texture devient la texture OpenGL courante
    void bind() const;
    /// définit le wrap (passer une constant GL : GL_CLAMP, GL_REPEAT, etc)
    void wrap(GLenum wr);
    /// active le placage en environment mapping (la texture est bind)
	void sphere() const;
	/// active le placage en linéaire en coordonnées locales (la texture est bind)
	void linearObject() const;
	/// active le placage en linéaire en coordonnées eye (la texture est bind)
	void linearEye() const;
	/// change le mode (global)
	void envMode(GLenum m);
	/// active le placage en mode direct par les glTexCoord (la texture est bind)
	void direct() const;
	/// désactive le placage de texture
	void disable() const;
	/// trace à l'écran la texture IL (debug)
	void draw(int x,int y) const;
	/// trace la texture IL à l'écran (sur le viewport x,y,w,h)
	void draw(int x,int y,int w,int h);

	/// donne la couleur du texel localisé par p=(s,t) (normalisé)
	Color getColor(const Point2d &p) const;
	/// copie l'écran dans la texture
	void copyFrame(int x0,int y0,int width,int height);
	/// trace la texture interne OpenGL sur un carré (tout l'écran)
	void drawIndirect();
	/// trace la texture interne OpenGL sur un carré (sur le viewport x,y,w,h)
	void drawIndirect(int x,int y,int w,int h);

};


}

#endif
