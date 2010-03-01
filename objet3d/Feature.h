#ifndef FEATURE_H_INCLUDED
#define FEATURE_H_INCLUDED


namespace prog3d {

class Soup;
class Feature {
	Soup *objet;
    public:
    Feature();
    Soup *creator() const;
    void setCreator(Soup *o);
    ~Feature();
};
}

#endif // FEATURE_H_INCLUDED
