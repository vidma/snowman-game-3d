#include "Feature.h"
#include "Error.h"

using namespace prog3d;

Feature::Feature() {objet=0;}
Feature::~Feature() {}

Soup *Feature::creator() const {if (objet==0) error("propriétaire nul",__LINE__,__FILE__); return objet;}
void Feature::setCreator(Soup *o) {objet=o;}
